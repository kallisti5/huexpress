#include "osd_linux_sdl_machine.h"

int netplay_mode;

char initial_path[PATH_MAX] = "";
// prefered path for for searching

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
// … fond, … fond, … fond? (french joke ;)

int vwidth, vheight;
// size of visible part of the screen (I got troubles with allegro screen->* values!)

int *fd[4];
// handle for joypad devices

SDL_TimerID timerId;
// handle for the timer callback

UInt32 interrupt_60hz(UInt32, void*);
// declaration of the actual callback to call 60 times a second

int osd_init_machine(void)
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

  if (!(XBuf = (UChar*)malloc(XBUF_WIDTH * XBUF_HEIGHT)))
    {
      printf (MESSAGE[language][failed_init]);
      return (0);
    }

  printf (MESSAGE[language][clear_buffer]);
  bzero (XBuf, XBUF_WIDTH * XBUF_HEIGHT);

  Log ("Initiating sound\n");
  printf (MESSAGE[language][init_sound]);
  InitSound();

/*
 * Moved to play_game so changes made in the gui will take effect on the next game start

  if (osd_snd_init_sound ())
  {
	  Log("Sound ok\n");
	  printf(MESSAGE[language][audio_inited], 0, "SDL sound card", host.sound.freq);
	  SDL_PauseAudio(0);
  }
  else
  {
	  Log("Sound not initialized\n");
	  printf(MESSAGE[language][audio_init_failed]);
  }

  */

#ifndef SDL
  /* Opening joypad number 0 */
  (int)fd[0] = open ("/dev/js0", O_NONBLOCK);
#endif

  osd_gfx_buffer = XBuf + 32 + 64 * XBUF_WIDTH; // We skip the left border of 32 pixels and the 64 first top lines

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
  
  if (sound_driver == 1)
    osd_snd_set_volume (0);

  if (timerId != NULL)
	  SDL_RemoveTimer(timerId);

#ifndef SDL  
  /* closing joypad device */
  close ((int)fd[0]);
#endif

	if (dump_snd)
		fclose(out_snd);

  TrashSound();

  SDL_Quit();

  wipe_directory(tmp_basepath);

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
	char* home_path;
		
	home_path = getenv("HOME");

	// short_exe_name is not really the short part of the exe, but a real multi user aware
	// path (when HOME environment variable is available)
	if (home_path)
		{			
			sprintf(short_exe_name,"%s/.hugo/",home_path);
			
			// Create directory if not existing
			mkdir(short_exe_name,0777);			
		}
	else
		{
			strcpy(short_exe_name,"./");
		}
	
  sprintf(log_filename,"%s%s",short_exe_name,"hugo.log");	
		
	// Set a temporary path per user (should it be by process ?)
	sprintf(tmp_basepath, "%shugo.tmp", short_exe_name);
	mkdir(tmp_basepath, 0777);
	
	// Set the saved game directory
	sprintf (sav_basepath, "%ssav/", short_exe_name);
	mkdir(sav_basepath, 0777);
		
	// Set the video output directory
  sprintf (video_path, "%svideo/", short_exe_name);
	mkdir(video_path, 0777);

}
