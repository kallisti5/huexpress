#include "utils.h"
#include "osd_sdl_machine.h"

int netplay_mode;
char initial_path[PATH_MAX] = "";
// prefered path for for searching

uchar* osd_gfx_buffer = NULL;

uchar gamepad = 0;
// gamepad detected ?

uchar* XBuf;
// The screen buffer where we draw before blitting it on screen

int gamepad_driver = 0;
// what kind of jypad must we have to handle

char dump_snd = 0;
// Do we write sound to file

char synchro;
// … fond, … fond, … fond? (french joke ;)

int vwidth, vheight;
// size of visible part of the screen (I got troubles with allegro screen->* values!)

#ifndef SDL
int *fd[4];
// handle for joypad devices
#endif

SDL_TimerID timerId;
// handle for the timer callback

uint32 interrupt_60hz(uint32, void*);
// declaration of the actual callback to call 60 times a second

int
osd_init_machine(void)
{
	MESSAGE_INFO("Emulator initialization\n");

	if (SDL_Init(SDL_INIT_TIMER)) {
		MESSAGE_ERROR("Could not initialise SDL : %s\n", SDL_GetError());
		return 0;
	}

	atexit(SDL_Quit);

	if (!(XBuf = (uchar*)malloc(XBUF_WIDTH * XBUF_HEIGHT)))
	{
		MESSAGE_ERROR("Initialization failed...\n");
		TRACE("%s, couldn't malloc XBuf\n", __func__);
		return (0);
	}

	MESSAGE_INFO("Clearing buffers...\n");
	bzero(XBuf, XBUF_WIDTH * XBUF_HEIGHT);

	MESSAGE_INFO("Initiating sound...\n");
	InitSound();

	osd_gfx_buffer = XBuf + 32 + 64 * XBUF_WIDTH;
		// We skip the left border of 32 pixels and the 64 first top lines

	timerId = SDL_AddTimer(1000 / 60, interrupt_60hz, NULL);
	if (timerId)
		MESSAGE_INFO("SDL timer initialization successful\n");
	else {
		MESSAGE_ERROR("SDL timer initialization failed...\n");
		TRACE("Couldn't SDL_AddTimer in %s\n", __func__);
	}

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

  if (timerId != NULL)
	  SDL_RemoveTimer(timerId);

#ifndef SDL  
	/* closing joypad device */
	close((int)fd[0]);
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
char
osd_keypressed(void)
{
	#warning TODO: implement keypressed with sdl
	return 0;
}


/*****************************************************************************

    Function: osd_readkey

    Description: Return the first available key stroke, waiting if needed
    Parameters: none
    Return: the key value (currently, lower byte is ascii and higher is scancode)

*****************************************************************************/
uint16
osd_readkey(void)
{
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_KEYDOWN:
				return event.key.keysym.unicode;
			case SDL_QUIT:
				return 0;
		}
	}
	return 0;
}


/*****************************************************************************

    Function: osd_fix_filename_slashes

    Description: Changes slashes in a filename to correspond to an os need
    Parameters: char* s
    Return: nothing but the char* is updated

*****************************************************************************/
void
osd_fix_filename_slashes(char* s)
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
			sprintf(short_exe_name,"%s/.huexpress",home_path);
			
			// Create directory if not existing
			mkdir(short_exe_name,0777);			
		}
	else
		{
			strcpy(short_exe_name,"./");
		}
	
	sprintf(log_filename,"%s/%s",short_exe_name,"huexpress.log");	
		
	// Set a temporary path per user (should it be by process ?)
	sprintf(tmp_basepath, "%s/tmp", short_exe_name);
	mkdir(tmp_basepath, 0777);
	
	// Set the saved game directory
	sprintf (sav_basepath, "%s/sav/", short_exe_name);
	mkdir(sav_basepath, 0777);
		
	// Set the video output directory
	sprintf (video_path, "%s/video/", short_exe_name);
	mkdir(video_path, 0777);

}
