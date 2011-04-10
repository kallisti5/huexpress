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
#include "iniconfig.h"
#include "utils.h"

#if !defined(WIN32) && !defined(SOLARIS)
#include <argp.h>
#endif

static int default_joy_mapping[J_MAX] = {0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, -1, -1, -1, -1, -1, -1, -1, -1};

//! Filename of the cd system rom
char cdsystem_path[PATH_MAX];

char sCfgFileLine[BUFSIZ];
// line buffer for config reading

char temp_result[BUFSIZ];
// temporary return value for get_config_var function

char config_file[PATH_MAX], config_file_tmp[PATH_MAX];
// name of the config file

const int config_ar_size_max = 2000;
// number max of variable read off the configuration file

int config_ar_index = 0;
// next entry where to insert variable / size of the config variable array

typedef struct
{
  char *section;
  char *variable;
  char *value;
} config_var;

config_var *config_ar;
// actual array toward the entries


int
config_var_cmp (const void *lhs, const void *rhs)
{
  int section_cmp =
    stricmp (((config_var *) lhs)->section, ((config_var *) rhs)->section);

  if (section_cmp != 0)
    return section_cmp;

  return stricmp (((config_var *) lhs)->variable,
		  ((config_var *) rhs)->variable);
}

void
set_config_file (const char *filename)
{
  strcpy (config_file_tmp, config_file);
  strcpy (config_file, filename);
}

void
set_config_file_back (void)
{
  strcpy (config_file, config_file_tmp);
}

char
init_config (void)
{
  FILE *FCfgFile = NULL;
  char *pWrd = NULL;
  char *pRet;
  char *pTmp;
  char *section = NULL;

  config_ar_index = 0;
  if ((config_ar =
       (config_var *) malloc (sizeof (config_var) * config_ar_size_max)) ==
      NULL)
    return 0;

  /* open config file for reading */
  if ((FCfgFile = fopen (config_file, "r")) != NULL)
    {
      do
	{
	  memset (sCfgFileLine, '\0', BUFSIZ);
	  /* note.. line must NOT be a comment */
	  pRet = fgets (sCfgFileLine, BUFSIZ, FCfgFile);

	  if (sCfgFileLine[0] == '#')
	    continue;

	  if (sCfgFileLine[0] == '[')
	    {
	      int section_size;
	      pWrd = strrchr (sCfgFileLine, ']');
	      if (pWrd == NULL)	/* Badly formed section line */
		continue;

	      if (section != NULL)
		free (section);

	      section_size = pWrd - sCfgFileLine;
	      section = (char *) malloc (section_size);
	      strncpy (section, sCfgFileLine + 1, section_size - 1);
	      section[section_size - 1] = '\0';
	      continue;
	    }

	  pWrd = strchr (sCfgFileLine, '=');
	  if (pWrd == NULL)
	    continue;

	  pTmp = strchr (pWrd, '\n');
	  if (pTmp != NULL)
	    *pTmp = '\0';

	  if (config_ar_index < config_ar_size_max)
	    {
	      config_ar[config_ar_index].section = (char *) strdup (section);

	      *pWrd = '\0';
	      pTmp = pWrd - 1;
	      while (*pTmp == '\t' || *pTmp == ' ')
		*(pTmp--) = '\0';
	      config_ar[config_ar_index].variable =
		(char *) strdup (sCfgFileLine);

	      while (*pWrd == '\t' || *pWrd == ' ')
		pWrd++;

	      config_ar[config_ar_index].value = (char *) strdup (pWrd + 1);

	      config_ar_index++;
	    }

	}
      while (pRet != NULL);

      fclose (FCfgFile);
    }

  if (section != NULL)
    free (section);

  qsort (config_ar, config_ar_index, sizeof (config_var), config_var_cmp);

  return 1;
}


void
dispose_config (void)
{
  int index;

  for (index = 0; index < config_ar_index; index++)
    {
      free (config_ar[index].section);
      free (config_ar[index].variable);
      free (config_ar[index].value);
    }

  free (config_ar);
}


char *
get_config_var (char *section, char *variable)
{
  config_var key, *result;

  key.section = section;
  key.variable = variable;

  result =
    bsearch (&key, config_ar, config_ar_index, sizeof (config_var),
	     config_var_cmp);

  if (result != NULL)
    {
      strcpy (temp_result, result->value);
      return temp_result;
    }

  return NULL;
}


#if !defined(ALLEGRO)

// Let's redefine the old allegro parsing function

int
get_config_int (char *section, char *keyword, int default_value)
{
  char *p = get_config_var (section, keyword);
  if (p == NULL)
    return default_value;
  return atoi (p);
}

char *
get_config_string (char *section, char *keyword, char *default_value)
{
  char *p = get_config_var (section, keyword);

  return (p == NULL ? default_value : p);
}

#endif

void
read_joy_mapping (void)
{
  char tmp_str[10], tmp_str2[10], section_name[10];
  unsigned char x, y, z;
  unsigned short temp_val;

  Log ("--[ JOYPAD MAPPING ]-------------------------------\n");
  Log ("Loading default values\n");

  memset (tmp_str, 0, 10);

  strcpy (section_name, "CONFIG1");
  for (z = 0; z < 16; z++)
    {
      if (z < 10)
	section_name[6] = '0' + z;
      else
	section_name[6] = (z - 10) + 'a';

      Log (" * Looking for section %s\n", section_name);

      for (x = 0; x < 5; x++)
	{			// for each player

	  config[z].individual_config[x].joydev = 0;
	  strcpy (tmp_str2, "joydev1");
	  tmp_str2[6] = '0' + x;

	  strncpy (tmp_str, get_config_string (section_name, tmp_str2, "0"),
		   10);
	  config[z].individual_config[x].joydev = atoi (tmp_str);

	  for (y = 0; y < J_MAX; y++)
	    {
	      strncpy (tmp_str, joymap_reverse[y], 10);
	      tmp_str[strlen (tmp_str) + 1] = 0;
	      tmp_str[strlen (tmp_str)] = '0' + x;
	      temp_val = get_config_int (section_name, tmp_str, 0xffff);
	      
	      if (0xffff != temp_val)
	      {
	      	config[z].individual_config[x].joy_mapping[y] = temp_val;
	      	Log ("    %s set to %d\n", joymap_reverse[y], temp_val);
	      }
	    }

	}
    }

  Log ("End of joypad mapping\n\n");
}

char
set_arg (char nb_arg, const char *val)
{

  if (!val)
    {
#ifndef FINAL_RELEASE
      fprintf (stderr, "No value for %c arg\n", nb_arg);
#endif
      Log ("No value for arg %c\n", nb_arg);
      return 1;
    }

  switch (nb_arg)
    {
    case 'a':
      option.want_fullscreen_aspect = min (1, max (0, atoi (val)));
      Log ("Fullscreen aspect mode set to %d\n",
	   option.want_fullscreen_aspect);
      return 0;

    case 'c':
      CD_emulation = atoi (val);
      Log ("CD emulation set to %d\n", CD_emulation);
      return 0;

    case 'd':
      debug_on_beginning = atoi (val);
      Log ("Debug on beginning set to %d\n", debug_on_beginning);
      return 0;

    case 'e':
      use_eagle = atoi (val);
      Log ("Eagle mode set to %d\n", use_eagle);
      return 0;

    case 'f':
      option.want_fullscreen = min (1, max (0, atoi (val)));
      Log ("Start in fullscreen mode set to %d\n", option.want_fullscreen);
      return 0;

    case 'i':
      strcpy (ISO_filename, val);
      Log ("ISO filename is %s\n", ISO_filename);
      return 0;
      
    case 'm':
      minimum_bios_hooking = atoi (val);
      Log ("Minimum Bios hooking set to %d\n", minimum_bios_hooking);
      return 0;

    case 'o':
      option.want_hardware_scaling = min (1, max (0, atoi (val)));
      Log ("Hardware scaling %srequested.\n",
	   option.want_hardware_scaling ? "" : "not ");
      return 0;

#if defined(ENABLE_NETPLAY)
    case 'n':
#warning hardcoding of netplay protocol
/*       option.want_netplay = LAN_PROTOCOL; */
      option.want_netplay = INTERNET_PROTOCOL;
      strncpy(option.server_hostname, val, sizeof(option.server_hostname));
      Log ("Netplay mode enabled\nServer hostname set to %s\n",
	   option.server_hostname);
      return 0;
#endif // NETPLAY

    case 's':
      option.want_stereo = min (1, max (0, atoi (val)));
      Log ("Stereo mode set to %d\n", option.want_stereo);
      return 0;
    case 'S':
      use_scanline = min (1, max (0, atoi (val)));
      Log ("Scanline mode set to %d\n", use_scanline);
      return 0;
    case 'u':
      US_encoded_card = atoi (val);
      Log ("US Card encoding set to %d\n", US_encoded_card);
      return 0;
#if defined(ALLEGRO)
    case 'v':
      vmode = atoi (val);
      Log ("Video mode set to %d\n", vmode);
      return 0;
#endif
    case 't':
      nb_max_track = atoi (val);
      Log ("Number of tracks set to %d\n", nb_max_track);
      return 0;
    case 'w':
      option.window_size = max (1, min (4, atoi (val)));
      Log ("Window size set to %d\n", option.window_size);
      return 0;

    default:
#ifndef FINAL_RELEASE
      fprintf (stderr, "Unrecognized option : %c\n", nb_arg);
#endif
      Log ("Unrecognize option : %c\n", nb_arg);
      return 1;
    }
}

#if !defined(WIN32) && !defined(SOLARIS)

//! program header for GNU argp function
const char *argp_program_version = "Hu-Go! 2.12";

//! bug report address for GNU argp function
const char *argp_program_bug_address = "<zeograd@zeograd.com>";

//! Program documentation
static char doc[] =
  "hugo -- a program to play pc engine games (roms, cds and various kind of dumps)";

//! A description of the arguments we accept
static char args_doc[] = "<rom filename> <BRAM filename>";

//! The options we understand
static struct argp_option options[] = {
  {"aspect-ratio", 'a', "0/1", OPTION_ARG_OPTIONAL,
   "Keep aspect ratio of pc engine in fullscreen mode (default is 0)"},
  {"cd-emulation", 'c', "<CD emulation level>", 0,
   "CD emulation mode (default is 0, rom only)"},
  {"debug-startup", 'd', "0/1", OPTION_ARG_OPTIONAL,
   "Launch debugger on startup (default is 0)"},
  {"eagle", 'e', "0/1", OPTION_ARG_OPTIONAL,
   "Use eagle mode for rendering, if available (default is 0)"},
  {"fullscreen", 'f', "0/1", OPTION_ARG_OPTIONAL,
   "Start game in fullscreen (default is 0)"},
  {"cd-device", 'i', "<CD device>", 0,
   "CD device to use (if CD emulation mode = 1, default is /dev/cdrom)"},
  {"no-bios-hooking", 'm', "0/1", OPTION_ARG_OPTIONAL,
   "No hard bios hooking (slower but more compatible, default is 0)"},
  {"overlay", 'o', "0/1", OPTION_ARG_OPTIONAL,
   "Use hardware scaling mode for rendering, if available (default is 0)"},
#if defined(ENABLE_NETPLAY)
  {"netplay", 'n', "<server ip or hostname>", 0,
   "Enable Netplay and set server name"},
#endif
  {"stereo", 's', "0/1", OPTION_ARG_OPTIONAL,
   "Render sound in stereo (default is 0)"},
  {"scanline", 'S', "0/1", OPTION_ARG_OPTIONAL,
   "Use scanline mode for rendering, if available (default is 0)"},
  {"us-decryption", 'u', "0/1", OPTION_ARG_OPTIONAL,
   "Decrypt roms using the US -> JAP decryption algorythm (default is 0)"},
  {"tracks-number", 't', "<track number>", 0,
   "Number of tracks when emulating a single iso (default is 22)"},
  {"window-size", 'w', "<zoom factor>", 0,
   "Zoom factor when in windowed mode (Between 1 and 4, default is 1)"},
  {0}
};

static error_t
parse_opt (int key, char *arg, struct argp_state *state)
{
  switch (key)
    {
    case 'a':
      option.want_fullscreen_aspect =
	(arg == NULL ? 1 : (min (1, max (0, atoi (arg)))));
      Log ("Fullscreen aspect mode set to %d\n",
	   option.want_fullscreen_aspect);
      break;
    case 'c':
      CD_emulation = atoi (arg);
      Log ("CD emulation set to %d\n", CD_emulation);
      break;
    case 'd':
      debug_on_beginning = (arg == NULL ? 1 : atoi (arg));
      Log ("Debug on beginning set to %d\n", debug_on_beginning);
      break;
    case 'e':
      use_eagle = (arg == NULL ? 1 : atoi (arg));
      Log ("Eagle mode set to %d\n", use_eagle);
      break;
    case 'f':
      option.want_fullscreen =
	(arg == NULL ? 1 : min (1, max (0, atoi (arg))));
      Log ("Start in fullscreen mode set to %d\n", option.want_fullscreen);
      break;
    case 'i':
      strcpy (ISO_filename, arg);
      Log ("ISO filename is %s\n", ISO_filename);
      break;
    case 'm':
      minimum_bios_hooking = (arg == NULL ? 1 : atoi (arg));
      Log ("Minimum Bios hooking set to %d\n", minimum_bios_hooking);
      break;
    case 'o':
      option.want_hardware_scaling =
	(arg == NULL ? 1 : min (1, max (0, atoi (arg))));
      Log ("Hardware scaling %srequested.\n",
	   option.want_hardware_scaling ? "" : "not ");
      break;
#if defined(ENABLE_NETPLAY)
    case 'n':
/*       option.want_netplay = LAN_PROTOCOL; */
      option.want_netplay = INTERNET_PROTOCOL;
      strncpy(option.server_hostname, arg, sizeof(option.server_hostname));
      Log ("Netplay mode enabled\nServer hostname set to %s\n",
	   option.server_hostname);
      break;
#endif // NETPLAY
    case 's':
      option.want_stereo = (arg == NULL ? 1 : min (1, max (0, atoi (arg))));
      Log ("Stereo mode set to %d\n", option.want_stereo);
      break;
    case 'S':
      use_scanline = (arg == NULL ? 1 : min (1, max (0, atoi (arg))));
      Log ("Scanline mode set to %d\n", use_scanline);
      break;
    case 'u':
      US_encoded_card = (arg == NULL ? 1 : atoi (arg));
      Log ("US Card encoding set to %d\n", US_encoded_card);
      break;
#if defined(ALLEGRO)
    case 'v':
      vmode = atoi (arg);
      Log ("Video mode set to %d\n", vmode);
      break;
#endif
    case 't':
      nb_max_track = atoi (arg);
      Log ("Number of tracks set to %d\n", nb_max_track);
      break;
    case 'w':
      option.window_size = max (1, min (4, atoi (arg)));
      Log ("Window size set to %d\n", option.window_size);
      break;
    case ARGP_KEY_ARG:
      if (state->arg_num >= 2)
	{
	  /* Too many arguments. */
	  argp_usage (state);
	  break;
	}

      switch (state->arg_num)
	{
	case 0:
	  strcpy (cart_name, arg);
	  Log ("Setting card name to %s\n", cart_name);
	  {
	    int x;
	    for (x = 0; x < strlen (cart_name); x++)
	      if (cart_name[x] == '\\')
		cart_name[x] = '/';
	  }
	  break;
	case 1:
	  bmdefault = arg;
	  Log ("Setting backup mem file name to %s\n", bmdefault);
	  break;
	default:
	  Log
	    ("Internal error when parsing command line, state->arg_num = %d\n",
	     state->arg_num);
	}
      break;
    default:
      return ARGP_ERR_UNKNOWN;
    }
  return 0;
}

//! Our argp parser
static struct argp argp = { options, parse_opt, args_doc, doc };

#endif

void
parse_commandline (int argc, char **argv)
{
#if defined(WIN32) || defined(SOLARIS)
  char next_arg, i, arg_error = 0;
#endif

  Log ("--[ PARSING COMMAND LINE ]--------------------------\n");

#if !defined(WIN32) && !defined(SOLARIS)
  argp_parse (&argp, argc, argv, 0, 0, &option);
#else
  next_arg = 0;
  for (i = 1; i < argc; i++)
    if (!next_arg)
      {
	if (argv[i][0] == '-')
	  {
	    if (strlen (argv[i]) == 2)
	      {
		switch (argv[i][1])
		  {
		  default:
		    next_arg = argv[i][1];
		    break;
		  }
	      }
	    else
	      arg_error |= set_arg (argv[i][1], (char *) &argv[i][2]);
	  }
	else
	  {
	    if (!cart_name[0])
	      {
		strcpy (cart_name, argv[i]);
		Log ("Setting card name to %s\n", cart_name);
		{
		  int x;
		  for (x = 0; x < strlen (cart_name); x++)
		    if (cart_name[x] == '\\')
		      cart_name[x] = '/';
		}
	      }
	    else if (!bmdefault)
	      {
		Log ("Setting backup mem file name to %s\n", argv[i]);
		bmdefault = argv[i];
	      }
	    else
	      {
		Log ("Unrecognized option : %s\n", argv[i]);
		arg_error = 1;
	      };
	  }
      }
    else
      {
	arg_error |= set_arg (next_arg, argv[i]);
	next_arg = 0;
      }

  if (next_arg)
    {
      Log ("No value for last arg : %c\n", next_arg);
      next_arg = 0;
      arg_error = 1;
    };

#endif

  Log ("End of parsing command line\n");

  video_driver = 0;

  if (use_eagle)
    video_driver = 1;
  else if (use_scanline)
    video_driver = 2;
}

void
parse_INIfile_raw ()
{
#ifdef MSDOS
  char x;
#endif

  Log ("Looking in %s\n", config_file);

  read_joy_mapping ();

  strcpy (initial_path, get_config_string ("main", "rom_dir", "."));
  if ((initial_path[0]) && (initial_path[strlen (initial_path) - 1] != '/')
      && (initial_path[strlen (initial_path) - 1] != '\\'))
    strcat (initial_path, "/");
  // rom_dir setting

  Log ("Setting initial path to %s\n", initial_path);

#if defined(ALLEGRO)

  strcpy (skin_filename, get_config_string ("main", "skin", "skin_h~1.bmp"));
  // skin filename to look for

  Log ("Skin filename set to %s\n", skin_filename);

#endif

  current_config = get_config_int ("main", "config", 0);
  // choose input config

  Log ("Setting joypad config number to %d\n", current_config);

  language = min (get_config_int ("main", "language", 0), NB_LANG - 1);
  // language setting

  Log ("Setting language to %d\n", language);

#if defined(ALLEGRO)
  vmode = get_config_int ("main", "vmode", 0);
  // video mode setting

  Log ("Setting video mode to %d\n", vmode);

  static_refresh = get_config_int ("main", "static_refresh", 0);
  // file selector refreshment

  Log ("Setting static refresh to %d\n", static_refresh);

#endif

  smode = get_config_int ("main", "smode", -1);
  // sound mode setting

  Log ("Setting sound mode to %d\n", smode);

  use_eagle = get_config_int ("main", "eagle", 0);
  // do we use EAGLE ?

  Log ("Setting eagle mode to %d\n", use_eagle);

  use_scanline = get_config_int ("main", "scanline", 0);
  // do we use EAGLE ?

  Log ("Setting scanline mode to %d\n", use_scanline);

  option.want_snd_freq = get_config_int ("main", "snd_freq", 22050);
  // frequency of the sound generator

  Log ("Setting default frequency to %d\n", option.want_snd_freq);

#if defined(WIN32)
  sbuf_size = get_config_int ("main", "buffer_size", 1024);
#elif defined(LINUX)
  sbuf_size = get_config_int ("main", "buffer_size", 512);
#else
  sbuf_size = get_config_int ("main", "buffer_size", 256);
#endif
  // size of the sound buffer

  Log ("Setting sound buffer size to %d bytes\n", sbuf_size);

  gamepad_driver = get_config_int ("main", "joy_type", -1);

  Log ("Setting joy type to %d\n", gamepad_driver);

  sound_driver = get_config_int ("main", "sound_driver", 1);

  Log ("Setting sound driver to %d\n", sound_driver);

#if defined(ALLEGRO)

  zip_support_in_fs = get_config_int ("main", "zip_support", 1);

  Log ("Setting zip support in File Selector to %d\n", zip_support_in_fs);

#endif

  synchro = get_config_int ("main", "limit_fps", 0);

  Log ("Setting fps limitation to %d\n", synchro);

  option.want_fullscreen = get_config_int ("main", "start_fullscreen", 0);

  Log ("Setting start in fullscreen mode to %d\n", option.want_fullscreen);

  option.want_fullscreen_aspect =
    get_config_int ("main", "use_fullscreen_aspect", 0);

  Log ("Setting fullscreen aspect to %d\n", option.want_fullscreen_aspect);

  option.want_hardware_scaling = get_config_int ("main", "use_overlay", 0);
  Log ("Setting hardware scaling to %d\n", option.want_hardware_scaling);

  option.want_stereo = get_config_int ("main", "stereo_sound", 0);

  Log ("Setting stereo sound to %d\n", option.want_stereo);

  option.window_size = get_config_int ("main", "window_size", 1);

  Log ("Setting window size to %d\n", option.window_size);

  option.fullscreen_width = get_config_int ("main", "fullscreen_width", 640);

  Log ("Setting preferred fullscreen width to %d\n", option.fullscreen_width);

  option.fullscreen_height =
    get_config_int ("main", "fullscreen_height", 480);

  Log ("Setting preferred fullscreen height to %d\n",
       option.fullscreen_height);

  option.wanted_hardware_format =
    get_config_int ("main", "hardware_format", 0);

  Log ("Setting wanted hardware format to %x\n",
       option.wanted_hardware_format);

#ifdef MSDOS

  x = get_config_int ("main", "cd_driver", 0);

  if (x)
    {
      osd_cd_driver = aspi_driver;
      Log ("Setting cd driver to ASPI\n");
    }
  else
    {
      osd_cd_driver = mscdex_driver;
      Log ("Setting cd driver to MSCDEX\n");
    }

#endif

  minimum_bios_hooking = get_config_int ("main", "minimum_bios_hooking", 0);

  Log ("Minimum Bios hooking set to %d\n", minimum_bios_hooking);

  strcpy (cdsystem_path, get_config_string ("main", "cdsystem_path", ""));

  Log ("CD system path set to %d\n", cdsystem_path);

  strcpy (ISO_filename, get_config_string ("main", "cd_path", ""));

  Log ("CD path set to %s\n", ISO_filename);

  option.want_arcade_card_emulation =
    get_config_int ("main", "arcade_card", 1);

  Log ("Arcade card emulation set to %d\n",
       option.want_arcade_card_emulation);

  option.want_supergraphx_emulation =
    get_config_int ("main", "supergraphx", 1);

  Log ("SuperGraphX emulation set to %d\n",
       option.want_supergraphx_emulation);

  option.want_television_size_emulation =
    get_config_int ("main", "tv_size", 0);

  Log ("Limiting graphics size to emulate tv output set to %d\n",
       option.want_television_size_emulation);

  Log ("End of parsing INI file\n\n");
}

void
parse_INIfile ()
{
  Log ("--[ PARSING INI FILE ]------------------------------\n");

#ifndef LINUX
  sprintf (config_file, "%shugo.ini", short_exe_name);
#else
  {

    char tmp_home[256];
    FILE *f;

    sprintf (tmp_home, "%shugo.ini", short_exe_name);

    f = fopen (tmp_home, "rb");

    if (f != NULL)
      {
	strcpy (config_file, tmp_home);
	fclose (f);
      }
    else
      strcpy (config_file, "/etc/hugo.ini");
  }
#endif


  init_config ();

  parse_INIfile_raw ();

  dispose_config ();

}

void
set_config_var_str (char *section, char *name, char *value)
{
  config_var key, *result;

#if !defined(FINAL_RELEASE)
  printf ("Setting [%s] %s to %s\n", section, name, value);
#endif

  key.section = section;
  key.variable = name;

  result =
    bsearch (&key, config_ar, config_ar_index, sizeof (config_var),
	     config_var_cmp);

  if (result != NULL)
    {
      free (result->value);
      result->value = strdup (value);
      return;
    }

  if (config_ar_index < config_ar_size_max)
    {

      config_ar[config_ar_index].section = strdup (section);
      config_ar[config_ar_index].variable = strdup (name);
      config_ar[config_ar_index].value = strdup (value);

      config_ar_index++;

    }
  else
    {

      Log ("Couldn't set [%s]%s to %sn bit enough internal space\n", section,
	   name, value);

    }
}

void
set_config_var_int (char *section, char *name, int value)
{
  char temp_string[10];

  snprintf (temp_string, 10, "%d", value);

  set_config_var_str (section, name, temp_string);
}

void
dump_config (char *filename)
{
  FILE *output_file;
  int local_index;
  char *last_section_name;

  last_section_name = "";

  output_file = fopen (filename, "wt");
  if (output_file == NULL)
    {
      Log ("Couldn't save configuration to %s\n", filename);
      return;
    }

  Log ("Saving %d entries in the configuration file\n", config_ar_index);

  for (local_index = 0; local_index < config_ar_index; local_index++)
    {
      if (strcmp (last_section_name, config_ar[local_index].section))
	{
	  last_section_name = config_ar[local_index].section;
	  fprintf (output_file, "[%s]\n", last_section_name);
	}
      fprintf (output_file, "%s=%s\n", config_ar[local_index].variable,
	       config_ar[local_index].value);
    }

  fclose (output_file);

}

//! makes the configuration changes permanent
void
save_config (void)
{

  char config_name[PATH_MAX];
  unsigned char input_config_number, input_config_button, input_config_player;

  // Reads all variables in the ini file
  init_config ();

  set_config_var_str ("main", "rom_dir", initial_path);
  set_config_var_int ("main", "config", current_config);
  set_config_var_int ("main", "language", language);
  set_config_var_int ("main", "smode", smode);
  set_config_var_int ("main", "eagle", use_eagle);
  set_config_var_int ("main", "scanline", use_scanline);
  set_config_var_int ("main", "snd_freq", option.want_snd_freq);
  set_config_var_int ("main", "buffer_size", sbuf_size);
  set_config_var_int ("main", "joy_type", gamepad_driver);
  set_config_var_int ("main", "sound_driver", sound_driver);
  set_config_var_int ("main", "start_fullscreen", option.want_fullscreen);
  set_config_var_int ("main", "use_fullscreen_aspect",
		      option.want_fullscreen_aspect);
  set_config_var_int ("main", "use_overlay", option.want_hardware_scaling);
  set_config_var_int ("main", "minimum_bios_hooking", minimum_bios_hooking);
  set_config_var_str ("main", "cdsystem_path", cdsystem_path);
  set_config_var_str ("main", "cd_path", ISO_filename);
  set_config_var_int ("main", "stereo_sound", option.want_stereo);
  set_config_var_int ("main", "fullscreen_width", option.fullscreen_width);
  set_config_var_int ("main", "fullscreen_height", option.fullscreen_height);
  set_config_var_int ("main", "window_size", option.window_size);
  set_config_var_int ("main", "arcade_card",
		      option.want_arcade_card_emulation);
  set_config_var_int ("main", "supergraphx",
		      option.want_supergraphx_emulation);
  set_config_var_int ("main", "tv_size",
		      option.want_television_size_emulation);
  set_config_var_int ("main", "hardware_format",
		      option.wanted_hardware_format);

	// For each input configuration ...
  for (input_config_number = 0; input_config_number < 16;
       input_config_number++)
    {
      char section_name[] = "CONFIG0";

      if (input_config_number < 10)
	section_name[6] = '0' + input_config_number;
      else
	section_name[6] = 'a' + input_config_number - 10;

			// For each player configuration ...
      for (input_config_player = 0; input_config_player < 5;
	   input_config_player++)
	{
	  char input_name[8];
	  char input_type_name[10];

		// If there's a joypad, dump it
		if (config[input_config_number].individual_config[input_config_player].joydev)
		{
		  snprintf (input_name, 8, "joydev%1d", input_config_player);
		  snprintf (input_type_name, 10, "%d",
			    config[input_config_number].individual_config[input_config_player].joydev);
		  set_config_var_str (section_name, input_name, input_type_name);
		}
		
		// For each button configuration ...
	  for (input_config_button = 0; input_config_button < J_MAX;
	       input_config_button++)
	    {
	      char temp_joy_str[15];

	      // Skip empty entries in joypad mapping
	      if (config[input_config_number].individual_config[input_config_player].
		  joy_mapping[input_config_button] == default_joy_mapping[input_config_button])
			continue;
			
			if ((0 == config[input_config_number].individual_config[input_config_player].joydev)
				&& (input_config_button >= J_PAD_START))
			{
				// If it is a joystick button/axis and it is disabled, we skip it
				continue;
			}

	      snprintf (temp_joy_str, 15, "%s%1d",
			joymap_reverse[input_config_button], input_config_player);
			
	      set_config_var_int (section_name, temp_joy_str,
				  config[input_config_number].individual_config[input_config_player].
				  joy_mapping[input_config_button]);
	    }
	}
    }

  // Sorts the configuration array
  qsort (config_ar, config_ar_index, sizeof (config_var), config_var_cmp);

  // Dump the configuration into a file
  sprintf (config_name, "%shugo.ini", short_exe_name);
  dump_config (config_name);

  dispose_config ();

}
