#include "osd_win_sdl_machine.h"

char initial_path[PATH_MAX] = "";

UChar* osd_gfx_buffer = NULL;

UChar gamepad = 0;
// gamepad detected ?

UChar* XBuf;
// The screen buffer where we draw before blitting it on screen

int gamepad_driver = 0;
// what kind of jypad must we have to handle

char dump_snd = 0;
// Do we write sound to file

char synchro;
// � fond, � fond, � fond? (french joke ;)

int vwidth, vheight;
// size of visible part of the screen (I got troubles with allegro screen->* values!)

int *fd[4];
// handle for joypad devices

SDL_TimerID timerId;
// handle for the timer callback

UInt32 interrupt_60hz(UInt32, void*);
// declaration of the actual callback to call 60 times a second

int osd_init_machine()
{

  int result;

  Log ("\n--[ INITIALISE MACHINE ]--------------------------\n");
		
  if (SDL_Init(SDL_INIT_TIMER)) {
	  Log("Could not initialise SDL : %s\n",SDL_GetError());
	  return 0;
  }	

  atexit(SDL_Quit);

  printf (MESSAGE[language][init_allegro]);

  printf (MESSAGE[language][translated_by]);

  if (!(XBuf = (UChar*)malloc(XBUF_WIDTH* XBUF_HEIGHT)))
    {
      printf (MESSAGE[language][failed_init]);
      return (0);
    }

  printf (MESSAGE[language][clear_buffer]);
  memset (XBuf, 0, XBUF_WIDTH * XBUF_HEIGHT);

  Log ("Initiating sound\n");
  printf (MESSAGE[language][init_sound]);
  InitSound ();

#warning enable eagle with sdl
/*
  if (use_eagle)
    {
      printf (MESSAGE[language][eagle_asked]);
      if (!set_gfx_mode (GFX_AUTODETECT, 640, 480, 0, 0))
	{
	  vwidth = 640;
	  vheight = 480;
	  blit_x = (320 - 256) / 2;
	  blit_y = (240 - 216) / 2;
	  screen_blit_x = (WIDTH - io.screen_h) / 2;
	  screen_blit_y = (HEIGHT - io.screen_w) / 2;
	  SetPalette ();

	  EAGLE_buf = create_bitmap (640, 480);
	}
      else
	printf (MESSAGE[language][eagle_mode_not_init]);
    }
  else
  */

  osd_gfx_buffer = XBuf;
	
  timerId = SDL_AddTimer(1000 / 60, interrupt_60hz, NULL);
  if (timerId)
	  Log("Timer initialised\n");
  else
	  Log("Timer non initialised\n");	
	
  Log ("End of initialisation of the machine\n");
  return 1;

}

/*****************************************************************************

    Function: osd_shut_machine

    Description: Deinitialize all stuff that have been inited in osd_int_machine
    Parameters: none
    Return: nothing

*****************************************************************************/
void
osd_shut_machine (void)
{
 
	free(XBuf);

#warning enable eagle with sdl
/*	
  if (EAGLE_buf)
    destroy_bitmap (EAGLE_buf);
*/
  
  if (sound_driver == 1)
    osd_snd_set_volume (0);

   if (timerId != NULL)
	  SDL_RemoveTimer(timerId);
  
  /* closing joypad device */
  close ((int)fd[0]);
    
/*  (*fade_out_proc[rand () % nb_fadeout]) (0, 0, vwidth, vheight); */

  TrashSound ();

  SDL_Quit();

  wipe_directory(tmp_basepath);
  
  return;
}

/*****************************************************************************

    Function: osd_keypressed

    Description: Tells if a key is available for future call of osd_readkey
    Parameters: none
    Return: 0 is no key is available
            else any non zero value

*****************************************************************************/
SChar osd_keypressed(void)
{

#warning implement keypressed with sdl	
	
 }

/*****************************************************************************

    Function: osd_readkey

    Description: Return the first available key stroke, waiting if needed
    Parameters: none
    Return: the key value (currently, lower byte is ascii and higher is scancode)

*****************************************************************************/
UInt16 osd_readkey(void)
{
	SDL_Event event;
	while ( SDL_PollEvent( &event ))
	{
		switch (event.type)
		{
			case SDL_KEYDOWN:
				return event.key.keysym.unicode;
			case SDL_QUIT:
				return 0;
		}
	}
 }

 /*****************************************************************************

    Function: osd_fix_filename_slashes

    Description: Changes slashes in a filename to correspond to an os need
    Parameters: char* s
    Return: nothing but the char* is updated

*****************************************************************************/
void osd_fix_filename_slashes(char* s)
{
	while (*s)
	{
		if (*s == '\\')
			*s = '/';
		s++;
	}
}

/*****************************************************************************

    Function: osd_init_paths

    Description: set global variables for paths and filenames
    Parameters: int argc, char* argv[]   same as the command line parameters
    Return: nothing

*****************************************************************************/
void
osd_init_paths(int argc, char* argv[])
{
	#warning Check whether this is still correct since the exploding of initialisation code (= no reported bugs in version 2.11 => accepted)
	
	char exe_path[PATH_MAX];
	
	memset(exe_path, 0, PATH_MAX);
	strncpy(exe_path, argv[0], PATH_MAX - 1);
	
	osd_fix_filename_slashes(exe_path);
	
	if (strrchr(exe_path, '/') != NULL)
		*strrchr(exe_path, '/') = '\0';
	
	strcat(exe_path, "/");
	
	strncpy(short_exe_name, exe_path, PATH_MAX);
	
    sprintf(log_filename,"%shugo.log",short_exe_name);	
		
	// Set a temporary path per user (should it be by process ?)
	sprintf(tmp_basepath, "%shugo.tmp", short_exe_name);
	mkdir(tmp_basepath);
	
	// Set the saved game directory
	sprintf (sav_basepath, "%ssav/", short_exe_name);
	mkdir(sav_basepath);
		
	// Set the video output directory
    sprintf (video_path, "%svideo/", short_exe_name);
	mkdir(video_path);

}

