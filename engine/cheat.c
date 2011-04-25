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
 
#include "cheat.h"

#if !defined(ALLEGRO)

long file_size (char* file_name)
{
	FILE* f = fopen(file_name,"rb");
	long position;
	if (f == NULL)
		return 0;
	fseek(f,0,SEEK_END);
	position = ftell(f);
	fclose(f);
	return position;
}
#endif

inline void fputw (UInt16 value, FILE* F)
{
 fputc((int)(value & 0xFF), F);
 fputc((int)(value >> 8), F);
 }

inline UInt16 fgetw (FILE* F)
{
 return (UInt16)(fgetc(F) + (fgetc(F) << 8));
 }

freezed_value list_to_freeze[MAX_FREEZED_VALUE];
// List of all the value to freeze

unsigned char current_freezed_values;
// Current number of values to freeze

static UChar
bigindextobank (UInt32 index)
{
  if (index<0x8000)
    return 0;
  if (index<0x18000)
    return ((index-0x8000) >> 13) + 1;
  if (index<0x48000)
    return ((index-0x18000) >> 13) + 10;
  // FIXME:  what to return here?
}

UInt16
bigtosmallindex(UInt32 index)
{
  if (index<0x8000)
    return (UInt16)index;
  return (UInt16)(index & 0x1FFF);
}

UChar
readindexedram (UInt32 index)
{
 if (index<0x8000)
   return RAM[index];
 if (index<0x18000)
   return cd_extra_mem[index-0x8000];
 if (index<0x48000)
   return cd_extra_super_mem[index-0x18000];

 return 0;

 }

void
writeindexedram (UInt32 index, UChar value)
{
 if (index<0x8000)
   RAM[index] = value;
 else
 if (index<0x18000)
   cd_extra_mem[index-0x8000] = value;
 else
 if (index<0x48000)
   cd_extra_super_mem[index-0x18000] = value;

 }


/*****************************************************************************

    Function: pokebyte

    Description: set a value in the ram to a specified value
    Parameters: none
    Return: 0

*****************************************************************************/

char
pokebyte ()
{
  char tmp_str[10], new_val;
  unsigned char index = 0;
  unsigned addr;

  while (osd_keypressed())
    /*@-retvalother*/
    osd_readkey ();			// Flushing keys
    /*@=retvalother*/
  while ((index < 10) && ((tmp_str[index++] = (char)(osd_readkey () & 0xFF)) != 13));
  tmp_str[index - 1] = 0;
  addr = (unsigned) atoi (tmp_str);

  while (osd_keypressed ())
    /*@-retvalother*/
    osd_readkey ();			// Flushing keys
    /*@=retvalother*/
  index = 0;
  while ((index < 10) && ((tmp_str[index++] = (char)(osd_readkey () & 0xFF)) != 13));
  tmp_str[index - 1] = 0;
  new_val = atoi (tmp_str);

  writeindexedram(addr, (UChar)new_val);

  {
    char *tmp_buf = (char *) malloc (100);
    snprintf (tmp_buf, 100, MESSAGE[language][byte_set], addr, new_val);
    osd_gfx_set_message (tmp_buf);
    message_delay = 180;
		free(tmp_buf);
  }


  return 0;
}

/*****************************************************************************

    Function: searchbyte

    Description: search the ram for a particuliar value
    Parameters: none
    Return: 1 on error

*****************************************************************************/
char
searchbyte ()
{
  UInt32 MAX_INDEX;
  char tmp_str[10];
  UInt32 index = 0, tmp_word, last_index;
  UChar bank;
  char data_filename[80], old_filename[80];
  char first_research = 1;
  FILE *D, *O;
  SInt16 to_search;

  MAX_INDEX = (UInt16)( CD_emulation ? 0x48000 : 0x8000);

  while (osd_keypressed ())
		/*@-retvalother*/
    osd_readkey ();			// Flushing keys
		/*@=retvalother*/

  while ((index < 10) && ((tmp_str[index++] = (char)(osd_readkey () & 0xFF)) != 13));
  tmp_str[index - 1] = 0;

  to_search = atoi (tmp_str);

  strcpy (old_filename, short_cart_name);
  strcpy (data_filename, short_cart_name);
  strcat (data_filename, "FP1");

  O = fopen ((char *) strcat (old_filename, "FP0"), "rb");
  if (O == NULL)
	  first_research = 1;
/*  
  if (exists ((char *) strcat (old_filename, "FP0")))
    {
      if (!(O = fopen (old_filename, "rb")))
	return 1;
      first_research = 0;
    }
*/
  if (!(D = fopen (data_filename, "wb")))
    return 1;
  tmp_str[9] = 0;


  if ((tmp_str[0] != '-')
     &&(tmp_str[0] != '+'))
  { /* non relative research */

  for (index = 0; index < MAX_INDEX; index++)
    {
      if (readindexedram(index) == (UChar)to_search)
	{

	  if (first_research)
            {
              fputc (readindexedram(index), D);
              fputc (bigindextobank(index), D);
	      fputw (bigtosmallindex(index), D);
            }
	  else
	    {
	      while (!(feof (O)))
		{
                  fgetc (O);
                  bank = (UChar)fgetc(O);
		  tmp_word = fgetw(O);

		  if ((bank > bigindextobank(index))
                      ||
                      ((bank == bigindextobank(index)) && (tmp_word >= bigtosmallindex(index))))
		    {
		      fseek (O, -4, SEEK_CUR);
		      break;
		    }
		}

	      if ((bigtosmallindex(index) == (UInt16)tmp_word) &&
                  (bigindextobank(index) == bank))
		{
                  fputc (to_search, D);
                  fputc (bigindextobank(index), D);
		  fputw (bigtosmallindex(index), D);
		  last_index = index;
		}
	    }			//search for old occurences
	}
    }
  }
  else
  { /* relative research */
  for (index = 0; index < MAX_INDEX; index++)
    {

	  if (first_research)
            {
              fputc (readindexedram(index), D);
              fputc (bigindextobank(index), D);
	      fputw (bigtosmallindex(index), D);
            }
	  else
	{
          UChar old_value;

	    {
	      while (!(feof (O)))
		{
                  fgetc (O);
                  bank = (UChar)fgetc(O);
		  tmp_word = fgetw(O);

		  if ((bank > bigindextobank(index))
                      ||
                      ((bank == bigindextobank(index)) && (tmp_word >= bigtosmallindex(index))))
		    {
		      fseek (O, -4, SEEK_CUR);
		      break;
		    }
		}

	      if ((bigindextobank(index) == bank) &&
                  (bigtosmallindex(index) == (UInt16)tmp_word) &&
                  (readindexedram(index) == old_value + to_search))
		{
                  fputc (readindexedram(index), D);
                  fputc (bigindextobank(index), D);
		  fputw (bigtosmallindex(index), D);
		  last_index = index;
		}
	    }			//search for old occurences
	}
    }

   }

  if (!first_research)
    fclose (O);
  fclose (D);

  rename (data_filename, old_filename);
  if (!file_size (old_filename))
    {
      osd_gfx_set_message (MESSAGE[language][search_failed]);
      message_delay = 180;
      unlink (old_filename);
      return 1;
    }

  if (file_size (old_filename) == 4)
    {
      char *tmp_buf = (char *) malloc (100);
      snprintf (tmp_buf, 100, MESSAGE[language][found_at], last_index);
      osd_gfx_set_message (tmp_buf);
      message_delay = 60 * 5;
			free(tmp_buf);
    }
  else
    {
      osd_gfx_set_message (MESSAGE[language][still_need_search]);
      message_delay = 60 * 3;
    }

  while (osd_keypressed ())
		/*@-retvalother*/
    osd_readkey ();			// Flushing keys
		/*@=retvalother*/

  return 0;
}

/*****************************************************************************

    Function: loadgame

    Description: load a saved game using allegro packing functions
    Parameters: none
    Return: 1 on error, else 0

*****************************************************************************/
int
loadgame ()
{

#ifndef KERNEL_DS

  /* TODO: add support for plain file when allegro isn't present */

#ifdef ALLEGRO
  PACKFILE *fp;
  UInt32 tmp = 0;
  char *tmp_buf = (char *) alloca (100);
  UChar version = 0;

  if (!exists (sav_path))
    return 1;

  if (!(fp = pack_fopen (sav_path, F_READ_PACKED)))
    return 1;

  pack_fread (tmp_buf, 18, fp);
  if (!strncmp (tmp_buf, "Hu-Go! state file", 17))
    {
      version = tmp_buf[17];
    }
  else
    {
      version = 0;
      pack_fclose (fp);
      if (!(fp = pack_fopen (sav_path, F_READ_PACKED)))
	return 1;

    }

  pack_fread (RAM, 0x8000, fp);
  pack_fread (VRAM, VRAMSIZE, fp);
  pack_fread (SPRAM, 64 * 4 * sizeof (short), fp);
  pack_fread (Pal, 512, fp);
  pack_fread (&scanline, sizeof (int), fp);

  if (version == 0x11)
    pack_fread (&io, sizeof (IO), fp);
  else
    pack_fread (&io, 1420, fp);

  pack_fread (&M, sizeof (M6502), fp);

  if (populus)
    pack_fread (PopRAM, PopRAMsize, fp);

  if (CD_emulation)
    {
      pack_fread (cd_extra_mem, 0x10000, fp);
      pack_fread (cd_extra_super_mem, 0x30000, fp);
      pack_fread (cd_sector_buffer, 0x2000, fp);
      pack_fread (&tmp, 2, fp);
      if (tmp != 0xFFFF)
	cd_read_buffer = cd_sector_buffer + tmp;
      else
	cd_read_buffer = 0;
    }

  for (tmp = 0; tmp < 8; tmp++)
    bank_set (tmp, M.MPR[tmp]);
  memset (vchange, 1, VRAMSIZE / 32);
  memset (vchanges, 1, VRAMSIZE / 128);

  CycleOld = (UInt32) M.User;

  pack_fclose (fp);

#endif

#else // KERNEL_DS defined

#ifdef ALLEGRO
  PACKFILE *fp;
  UInt32 tmp = 0;
  char *tmp_buf = (char *) alloca (100);
  UChar version = 0;

  if (!exists (sav_path))
    return 1;

  if (!(fp = pack_fopen (sav_path, F_READ_PACKED)))
    return 1;

  pack_fread (tmp_buf, 18, fp);
  if (!strncmp (tmp_buf, "Hu-Go! state file", 17))
    {
      version = tmp_buf[17];
    }
  else
    {
      version = 0;
      pack_fclose (fp);
      if (!(fp = pack_fopen (sav_path, F_READ_PACKED)))
	return 1;

    }

  pack_fread (RAM, 0x8000, fp);
  pack_fread (VRAM, VRAMSIZE, fp);
  pack_fread (SPRAM, 64 * 4 * sizeof (short), fp);
  pack_fread (Pal, 512, fp);
  pack_fread (&scanline, sizeof (int), fp);

  if ((version == 0x11) || (version == 0x20))
    pack_fread (&io, sizeof (IO), fp);
  else
    pack_fread (&io, 1420, fp);

    {

      pack_fread (mmr, sizeof(mmr[0])*8, fp);
      pack_fread (&cyclecount, sizeof(cyclecount), fp);
      pack_fread (&cyclecountold, sizeof(cyclecountold), fp);

      // registers

      pack_fread (&reg_pc, sizeof(reg_pc), fp);
      pack_fread (&reg_a, sizeof(reg_a), fp);
      pack_fread (&reg_x, sizeof(reg_x), fp);
      pack_fread (&reg_y, sizeof(reg_y), fp);
      pack_fread (&reg_p, sizeof(reg_p), fp);
      pack_fread (&reg_s, sizeof(reg_s), fp);

      pack_fread (&halt_flag, sizeof(halt_flag), fp);
      pack_fread (&cycles, sizeof(cycles), fp);

     }

  if (populus)
    pack_fread (PopRAM, PopRAMsize, fp);

  if (CD_emulation)
    {
      pack_fread (cd_extra_mem, 0x10000, fp);
      pack_fread (cd_extra_super_mem, 0x30000, fp);
      pack_fread (cd_sector_buffer, 0x2000, fp);
      pack_fread (&tmp, 2, fp);
      if (tmp != 0xFFFF)
	cd_read_buffer = cd_sector_buffer + tmp;
      else
	cd_read_buffer = 0;
      pack_fread (&cd_port_1800, sizeof(cd_port_1800), fp);
      pack_fread (&cd_port_1801, sizeof(cd_port_1801), fp);
      pack_fread (&cd_port_1802, sizeof(cd_port_1802), fp);
      pack_fread (&cd_port_1804, sizeof(cd_port_1804), fp);
      pack_fread (&pce_cd_read_datacnt, sizeof(pce_cd_read_datacnt), fp);
      pack_fread (&pce_cd_curcmd, sizeof(pce_cd_curcmd), fp);

    }

  for (tmp = 0; tmp < 8; tmp++)
    bank_set (tmp, mmr[tmp]);
  memset (vchange, 1, VRAMSIZE / 32);
  memset (vchanges, 1, VRAMSIZE / 128);

  // CycleOld = (UInt32) M.User;

  zp_base = RAM;
  sp_base = RAM + 0x100;

  pack_fclose (fp);

#else

  FILE* saved_file;
  
  saved_file = fopen(sav_path, "rb");
  
  if (saved_file == NULL)
	  return 1;
  
  if (fread(hard_pce, 1, sizeof(struct_hard_pce), saved_file) != sizeof(struct_hard_pce))
    {
			fclose(saved_file);
			return 1;
		}
  
  {
		int mmr_index;
	  
    for (mmr_index = 0; mmr_index < 8; mmr_index++)
      {
				bank_set((UChar)mmr_index, mmr[mmr_index]);
				printf("Setting bank %d to 0x%02x\n", mmr_index, mmr[mmr_index]);
      }
  }
	
  fclose(saved_file);
	
#endif



#endif

  return 0;
}

/*****************************************************************************

    Function: savegame

    Description: save a game using allegro packing functions
    Parameters: none
    Return: 1 on error, else 0

*****************************************************************************/


int
savegame ()
{

#ifndef KERNEL_DS

#ifdef ALLEGRO

  PACKFILE *fp;
  UInt32 tmp;

  if (!(fp = pack_fopen (sav_path, F_WRITE_PACKED)))
    return 1;

  pack_fwrite ("Hu-Go! state file\21", 18, fp);

  pack_fwrite (RAM, 0x8000, fp);
  pack_fwrite (VRAM, VRAMSIZE, fp);
  pack_fwrite (SPRAM, 64 * 4 * sizeof (short), fp);
  pack_fwrite (Pal, 512, fp);
  pack_fwrite (&scanline, sizeof (int), fp);
  pack_fwrite (&io, sizeof (IO), fp);
  pack_fwrite (&M, sizeof (M6502), fp);
  if (populus)
    pack_fwrite (PopRAM, PopRAMsize, fp);
  if (CD_emulation)
    {
      pack_fwrite (cd_extra_mem, 0x10000, fp);
      pack_fwrite (cd_extra_super_mem, 0x30000, fp);
      pack_fwrite (cd_sector_buffer, 0x2000, fp);
      if (cd_read_buffer)
	{
	  tmp = cd_read_buffer - cd_sector_buffer;
	  pack_fwrite (&tmp, 2, fp);
	}
      else
	{
	  tmp = 0xFFFF;
	  pack_fwrite (&tmp, 2, fp);
	}
    }

  return pack_fclose (fp);
#else

  return 0;

#endif

#else  // KERNEL_DS defined

#ifdef ALLEGRO

  PACKFILE *fp;
  UInt32 tmp;

  if (!(fp = pack_fopen (sav_path, F_WRITE_PACKED)))
    return 1;

  pack_fwrite ("Hu-Go! state file\40", 18, fp);

  pack_fwrite (RAM, 0x8000, fp);
  pack_fwrite (VRAM, VRAMSIZE, fp);
  pack_fwrite (SPRAM, 64 * 4 * sizeof (short), fp);
  pack_fwrite (Pal, 512, fp);
  pack_fwrite (&scanline, sizeof (int), fp);
  pack_fwrite (&io, sizeof (IO), fp);

  // pack_fwrite (&M, sizeof (M6502), fp);
  pack_fwrite (mmr, sizeof(mmr[0])*8, fp);
  pack_fwrite (&cyclecount, sizeof(cyclecount), fp);
  pack_fwrite (&cyclecountold, sizeof(cyclecountold), fp);

  // registers

  pack_fwrite (&reg_pc, sizeof(reg_pc), fp);
  pack_fwrite (&reg_a, sizeof(reg_a), fp);
  pack_fwrite (&reg_x, sizeof(reg_x), fp);
  pack_fwrite (&reg_y, sizeof(reg_y), fp);
  pack_fwrite (&reg_p, sizeof(reg_p), fp);
  pack_fwrite (&reg_s, sizeof(reg_s), fp);

  pack_fwrite (&halt_flag, sizeof(halt_flag), fp);
  pack_fwrite (&cycles, sizeof(cycles), fp);

  if (populus)
    pack_fwrite (PopRAM, PopRAMsize, fp);

  if (CD_emulation)
    {
      pack_fwrite (cd_extra_mem, 0x10000, fp);
      pack_fwrite (cd_extra_super_mem, 0x30000, fp);
      pack_fwrite (cd_sector_buffer, 0x2000, fp);
      if (cd_read_buffer)
	{
	  tmp = cd_read_buffer - cd_sector_buffer;
	  pack_fwrite (&tmp, 2, fp);
	}
      else
	{
	  tmp = 0xFFFF;
	  pack_fwrite (&tmp, 2, fp);
	}

      pack_fwrite (&cd_port_1800, sizeof(cd_port_1800), fp);
      pack_fwrite (&cd_port_1801, sizeof(cd_port_1801), fp);
      pack_fwrite (&cd_port_1802, sizeof(cd_port_1802), fp);
      pack_fwrite (&cd_port_1804, sizeof(cd_port_1804), fp);
      pack_fwrite (&pce_cd_read_datacnt, sizeof(pce_cd_read_datacnt), fp);
      pack_fwrite (&pce_cd_curcmd, sizeof(pce_cd_curcmd), fp);

    }

  return pack_fclose (fp);
#else // ALLEGRO not defined

	FILE* saved_file;

	saved_file = fopen(sav_path, "wb");
	
	if (saved_file == NULL)
		return 1;
	
	if (fwrite(hard_pce, 1, sizeof(struct_hard_pce), saved_file) != sizeof(struct_hard_pce))
	  {
		fclose(saved_file);
		return 1;
	  }
	
	fclose(saved_file);	

#endif

#endif

  return 0;

}

/*****************************************************************************

    Function:  freeze_value

    Description: set or unset a value to freeze
    Parameters:none
    Return: 0 if unset an old freezed value or can't set a value anymore
 	         1 if new was created,
				may modify 'list_freezed_value'

*****************************************************************************/
int
freeze_value (void)
{
  char tmp_str[10];
  unsigned char index = 0;
  unsigned where;

  while (osd_keypressed ())
		/*@-retvalother*/
    osd_readkey ();			// Flushing keys
		/*@=retvalother*/

  while ((index < 10) && ((tmp_str[index++] = (char)(osd_readkey () & 0xFF)) != 13));
  tmp_str[index - 1] = 0;

  where = (unsigned)atoi (tmp_str);

  for (index = 0; index < current_freezed_values; index++)
    if (list_to_freeze[index].position == (unsigned short)where)
      {
	// We entered an already freezed offset

	memcpy (&list_to_freeze[index], &list_to_freeze[index + 1],
		(current_freezed_values - index +
		 1) * sizeof (freezed_value));
	// We erase the current struct letting no hole...

	current_freezed_values--;
	// And we got one less value

	return 0;
      }

  if (current_freezed_values < MAX_FREEZED_VALUE)
    {
      list_to_freeze[current_freezed_values].position = (unsigned short)where;

      while ((index < 10) && ((tmp_str[index++] = (char)(osd_readkey () & 0xFF)) != 13));
      tmp_str[index - 1] = 0;

      list_to_freeze[current_freezed_values++].value = (unsigned) atoi (tmp_str);

      return 1;
    }
  else
    return 0;
}
