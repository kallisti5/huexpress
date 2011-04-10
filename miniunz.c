/*
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Library General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <errno.h>
#include <fcntl.h>

# include <limits.h>

#include "utils.h"
#include "unzip.h"

#define CASESENSITIVITY (0)
#define WRITEBUFFERSIZE (8192)
#define MAXFILENAME (256)

static char possible_filename_in_zip[PATH_MAX];

/*!
 * find_possible_filename_in_zip : Look whether the given archive contains a rom
 * @param zipfilename Name of the archive file in zip format in which to search for a rom
 * @return NULL in case of error or no rom found else a pointer to a statically allocated
 * storage containing the filename found inside
 */
char *
find_possible_filename_in_zip (char *zipfilename)
{
  uLong i;
  unz_global_info gi;
  unzFile uf;
  int err;

#if !defined(FINAL_RELEASE)
  fprintf (stderr,
	   "entering function to find a possible rom name in the archive %s\n",
	   zipfilename);
#endif

  if (zipfilename == NULL)
    return NULL;

  uf = unzOpen (zipfilename);

  if (uf == NULL)
    {
      strcat (zipfilename, ".zip");
      uf = unzOpen (zipfilename);
    }

  if (uf == NULL)
    return NULL;

#if !defined(FINAL_RELEASE)
  fprintf (stderr, "Opened the archive");
#endif

  err = unzGetGlobalInfo (uf, &gi);
  if (err != UNZ_OK)
    {
      return NULL;
    }

  for (i = 0; i < gi.number_entry; i++)
    {
      char filename_inzip[256];
      unz_file_info file_info;

#if !defined(FINAL_RELEASE)
      fprintf (stderr, "Testing entry #%ld\n", i);
#endif

      err = unzGetCurrentFileInfo (uf, &file_info, filename_inzip,
				   sizeof (filename_inzip), NULL, 0, NULL, 0);

      if (err != UNZ_OK)
	{
	  return NULL;
	}

#if !defined(FINAL_RELEASE)
      fprintf (stderr, "Filename for this entry is %s\n", filename_inzip);
#endif

      if (strcasestr (filename_inzip, ".PCE"))
	{
	  strncpy (possible_filename_in_zip, filename_inzip, PATH_MAX);
	  return possible_filename_in_zip;
	}

      if ((i + 1) < gi.number_entry)
	{
	  err = unzGoToNextFile (uf);
	  if (err != UNZ_OK)
	    {
	      return NULL;
	    }
	}
    }

  return NULL;
}

/*!
 * do_extract_currentfile_in_memory : Extract the current pointed file in the zip archive into a buffer
 * @param uf the archive file handle
 * @param unzipped_size a pointer to the size of the unzipped data, it is filled by this function for caller
 * @return uncompressed data as pointer, to be freed by caller or NULL in case of problem
 */
static char *
do_extract_currentfile_in_memory (unzFile uf, size_t * unzipped_size)
{
  char filename_inzip[256];
  char *filename_withoutpath;
  char *p;
  int err = UNZ_OK;
  FILE *fout = NULL;
  void *buf;
  uInt size_buf;
  unz_file_info file_info;
  char *return_value = NULL;

  err = unzGetCurrentFileInfo (uf, &file_info, filename_inzip,
			       sizeof (filename_inzip), NULL, 0, NULL, 0);

  if (err != UNZ_OK)
    {
      Log ("error %d with zipfile in unzGetCurrentFileInfo\n", err);
      return NULL;
    }

  size_buf = WRITEBUFFERSIZE;
  buf = (void *) malloc (size_buf);
  if (buf == NULL)
    {
      Log ("Error allocating memory\n");
      return UNZ_INTERNALERROR;
    }

  p = filename_withoutpath = filename_inzip;
  while ((*p) != '\0')
    {
      if (((*p) == '/') || ((*p) == '\\'))
	filename_withoutpath = p + 1;
      p++;
    }

  if ((*filename_withoutpath) != '\0')
    {
      const char *write_filename;
      int skip = 0;

      write_filename = filename_withoutpath;

      err = unzOpenCurrentFile (uf);
      if (err != UNZ_OK)
	{
	  Log ("error %d with zipfile in unzOpenCurrentFile\n", err);
	  return NULL;
	}

      *unzipped_size = 0;

      do
	{
	  err = unzReadCurrentFile (uf, buf, size_buf);
	  if (err < 0)
	    {
	      Log ("error %d with zipfile in unzReadCurrentFile\n", err);
	      break;
	    }
	  if (err > 0)
	    {
	      *unzipped_size += err;
	      return_value = realloc (return_value, *unzipped_size);
	      if (return_value == NULL)
		{
		  err = UNZ_ERRNO;
		  break;
		}
	      memcpy (return_value + *unzipped_size - err, buf, err);
	    }
	}
      while (err > 0);

      if (err != UNZ_OK)
	{
	  Log ("Error %s with zipfile in uncompressing\n", strerror (errno));
	}

      err = unzCloseCurrentFile (uf);
      if (err != UNZ_OK)
	{
	  Log ("error %d with zipfile in unzCloseCurrentFile\n", err);
	}
    }

  free (buf);
  return return_value;
}

/*!
 * do_extract_onefile_in_memory : Extract an archived file into a buffer
 * @param uf Handle to the archive in ip format in which to read data
 * @param filename Name of the file archived in the zip file the data of which we want
 * @param unzipped_size Pointer to the size of the extracted data
 * @return NULL in case of problem or a pointer to the archived file content. It is allocated
 */
static char *
do_extract_onefile_in_memory (unzFile uf, const char *filename,
			      size_t * unzipped_size)
{
  if (unzLocateFile (uf, filename, CASESENSITIVITY) != UNZ_OK)
    {
      Log ("file %s not found in the zipfile\n", filename);
      return NULL;
    }

  return do_extract_currentfile_in_memory (uf, unzipped_size);
}

/*!
 * extract_file_in_memory : Extract an archived file into a buffer
 * @param zipfilename Name of the archive in zip format in which to read data
 * @param archivedfile Name of the file archived in the zip file the data of which we want
 * @param unzipped_size Pointer to the size of the extracted data
 * @return NULL in case of problem or a pointer to the archived file content. It is allocated
 * dynamically and needs to be explicitely freed
 */
extern char *
extract_file_in_memory (char *zipfilename, char *archivedfile,
			size_t * unzipped_size)
{
  unzFile uf;
  int err;
  char *return_value;

  if (zipfilename == NULL)
    return NULL;

  uf = unzOpen (zipfilename);

  if (uf == NULL)
    {
      strcat (zipfilename, ".zip");
      uf = unzOpen (zipfilename);
    }

  if (uf == NULL)
    return NULL;

  return_value =
    do_extract_onefile_in_memory (uf, archivedfile, unzipped_size);

  unzCloseCurrentFile (uf);

  return return_value;
}
