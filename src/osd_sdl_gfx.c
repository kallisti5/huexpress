/*****************************************/
/* SDL Graphics Engine                   */
/* Released under the GPL license        */
/*                                       */
/* Original Author:                      */
/*		Zerograd? - Hu-GO!               */
/* Redesignd for HuExpress by:           */
/*		Alexander von Gluck, kallisti5   */
/*****************************************/

#include "osd_sdl_gfx.h"
#include "utils.h"


//! Host machine rendered screen
SDL_Renderer *sdlRenderer = NULL;
SDL_Window *sdlWindow = NULL;
//! PC Engine rendered screen
static SDL_Texture *sdlTexture;
static int fullscreen;

int blit_x, blit_y;
// where must we blit the screen buffer on screen

extern uchar *XBuf;
// buffer for video flipping

osd_gfx_driver osd_gfx_driver_list[3] = {
	{osd_gfx_init, osd_gfx_init_normal_mode,
	 osd_gfx_put_image_normal, osd_gfx_shut_normal_mode},
	{osd_gfx_init, osd_gfx_init_normal_mode,
	 osd_gfx_put_image_normal, osd_gfx_shut_normal_mode},
	{osd_gfx_init, osd_gfx_init_normal_mode,
	 osd_gfx_put_image_normal, osd_gfx_shut_normal_mode}
};


void
osd_gfx_dummy_func(void)
{
	return;
}

/*****************************************************************************

		Function: osd_gfx_put_image_normal

		Description: draw the raw computed picture to screen, without any effect
		trying to center it (I bet there is still some work on this, maybe not
														in this function)
		Parameters: none
		Return: nothing

*****************************************************************************/
void
osd_gfx_put_image_normal(void)
{
	osd_gfx_blit();
}


/*****************************************************************************

		Function: osd_gfx_set_message

		Description: compute the message that will be displayed to create a sprite
			to blit on screen
		Parameters: char* mess, the message to display
		Return: nothing but set OSD_MESSAGE_SPR

*****************************************************************************/
void
osd_gfx_set_message(char *mess)
{
	
}


/*
 * osd_gfx_init:
 * One time initialization of the main output screen
 */
int
osd_gfx_init(void)
{
	if (!SDL_WasInit(SDL_INIT_VIDEO)) {
		if (SDL_InitSubSystem(SDL_INIT_VIDEO)) {
			MESSAGE_ERROR("SDL: %s failed at %s:%d - %s\n",
				__func__, __FILE__, __LINE__, SDL_GetError());
			return 0;
		}
	}

	MESSAGE_INFO("Window Size: %d\n", option.window_size);
	MESSAGE_INFO("Fullscreen: %d\n", option.want_fullscreen);
	osd_gfx_init_normal_mode();

	if (option.want_fullscreen)
		SDL_ShowCursor(SDL_DISABLE);

	SetPalette();

	return 1;
}


/*****************************************************************************

		Function:	osd_gfx_init_normal_mode

		Description: initialize the classic 256*224 video mode for normal video_driver
		Parameters: none
		Return: 0 on error
						1 on success

*****************************************************************************/
int
osd_gfx_init_normal_mode()
{
	struct generic_rect rect;

#if ENABLE_TRACING_SDL
	printf("GFX: Mode change: %dx%d\n", io.screen_w, io.screen_h);
#endif

	if (sdlWindow == NULL) {
		// First start? Lets just set a fake screen w/h
		io.screen_w = 352;
		io.screen_h = 256;
	}

	if (io.screen_w < 160 || io.screen_w > 512) {
		MESSAGE_ERROR("Correcting out of range screen w %d\n", io.screen_w);
		io.screen_w = 256;
	}
	if (io.screen_h < 160 || io.screen_h > 256) {
		MESSAGE_ERROR("Correcting out of range screen h %d\n", io.screen_h);
		io.screen_h = 224;
	}


	struct generic_rect viewport;
	viewport.start_x = 0;
	viewport.start_y = 0;

	if (option.want_fullscreen) {
		SDL_DisplayMode current;
    	if (SDL_GetCurrentDisplayMode(0, &current)) {
			MESSAGE_ERROR("Unable to determine current DisplayMode");
		}

		calc_fullscreen_aspect(current.w, current.h, &viewport,
			io.screen_w, io.screen_h);

		MESSAGE_INFO("%dx%d , %dx%d\n", viewport.start_x, viewport.start_y,
			viewport.end_x, viewport.end_y);
	} else {
		
		viewport.end_x = io.screen_w * option.window_size;
		viewport.end_y = io.screen_h * option.window_size;
	}

	uint16 viewportWidth = viewport.end_x - viewport.start_x;
	uint16 viewportHeight = viewport.end_y - viewport.start_y;

	if (sdlWindow != NULL) {
		SDL_DestroyWindow(sdlWindow);
		sdlWindow = NULL;
	}

	uint32 windowFlags = SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL;

	if (option.want_fullscreen) {
		windowFlags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
		fullscreen = 1;
	}

	sdlWindow = SDL_CreateWindow("HuExpress", SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED, viewport.end_x, viewport.end_y, windowFlags);

	if (sdlWindow == NULL) {
		MESSAGE_ERROR("SDL: %s failed at %s:%d - %s\n", __func__, __FILE__,
			__LINE__, SDL_GetError());
		return 0;
	}


	sdlRenderer = SDL_CreateRenderer(sdlWindow, -1, SDL_RENDERER_ACCELERATED);
	//sdlRenderer = SDL_CreateRenderer(sdlWindow, -1, SDL_RENDERER_SOFTWARE);

	if (sdlRenderer == NULL) {
		MESSAGE_ERROR("SDL: %s failed at %s:%d - %s\n", __func__, __FILE__,
			__LINE__, SDL_GetError());
		return 0;
	}

	sdlTexture = SDL_CreateTexture(sdlRenderer, SDL_PIXELFORMAT_BGRA32,
                        SDL_TEXTUREACCESS_STREAMING, io.screen_w, io.screen_h);

	if (sdlTexture == NULL) {
		MESSAGE_ERROR("SDL: SDL_CreateTexture failed at %s:%d - %s\n",
			__FILE__, __LINE__, SDL_GetError());
	}

	return sdlTexture ? 1 : 0;
}


//! Delete the window
void
osd_gfx_shut_normal_mode(void)
{
	if (sdlTexture) SDL_DestroyTexture(sdlTexture);
	sdlTexture = NULL;

	if (sdlWindow != NULL)
		SDL_DestroyWindow(sdlWindow);

	/* SDL will free physical_screen internally */
	SDL_QuitSubSystem(SDL_INIT_VIDEO);
}


/*****************************************************************************

		Function: osd_gfx_savepict

		Description: save a picture in the current directory
		Parameters: none
		Return: the numeric part of the created filename, 0xFFFF meaning that no more
			names were available

*****************************************************************************/
uint16
osd_gfx_savepict()
{
	short unsigned tmp = 0;
	char filename[PATH_MAX];
	char filename_base[PATH_MAX];
	char *frame_buffer;
	FILE *output_file;
	time_t current_time;

	time(&current_time);

	if (!strftime
		(filename_base, PATH_MAX, "%%s/screenshot_%F_%R-%%d.ppm",
			localtime(&current_time)))
		return 0xFFFF;

	do {
		snprintf(filename, PATH_MAX, filename_base, video_path, tmp);
	} while (file_exists(filename) && ++tmp < 0xFFFF);

	frame_buffer =
		malloc(3 * (io.screen_w & 0xFFFE) * (io.screen_h & 0xFFFE));

	if (frame_buffer == NULL)
		return 0xFFFF;

	dump_rgb_frame(frame_buffer);

	output_file = fopen(filename, "wb");
	if (output_file != NULL) {
		char buf[100];

		snprintf(buf, sizeof(buf), "P6\n%d %d\n%d\n", io.screen_w & 0xFFFE,
			io.screen_h & 0xFFFE, 255);
		fwrite(buf, strlen(buf), 1, output_file);
		fwrite(frame_buffer, 3 * (io.screen_w & 0xFFFE)
			* (io.screen_h & 0xFFFE), 1, output_file);
		fclose(output_file);
	}

	return tmp;
}


/*****************************************************************************

		Function: osd_gfx_set_color

		Description: Change the component of the choosen color
		Parameters: uchar index : index of the color to change
					uchar r	: new red component of the color
								uchar g : new green component of the color
								uchar b : new blue component of the color
		Return:

*****************************************************************************/
void
osd_gfx_set_color(uchar index, uchar r, uchar g, uchar b)
{
	rgb_map[index].r = r;
	rgb_map[index].g = g;
	rgb_map[index].b = b;
}

void
osd_gfx_blit()
{
	void *pixels;
	int pitch;
	SDL_LockTexture(sdlTexture, NULL, &pixels, &pitch);
	dump_rgb_frame32(pixels);
	SDL_UnlockTexture(sdlTexture);
	SDL_RenderCopy(sdlRenderer, sdlTexture, 0, 0);
	SDL_RenderPresent(sdlRenderer);
}


int
ToggleFullScreen(void)
{
	SDL_PauseAudio(SDL_ENABLE);
	SDL_SetWindowFullscreen(sdlWindow, fullscreen ? 0 : SDL_WINDOW_FULLSCREEN);
	fullscreen = !fullscreen;
	SDL_PauseAudio(SDL_DISABLE);
	SDL_ShowCursor(!fullscreen);
	return fullscreen;
}


/* drawVolume */
/* Given a string, and a value between 0 and 255, */
/* draw a 'volume' style bar */
void
drawVolume(char *name, int volume)
{
	int i;
	char volumeTemplate[] = "[---------------]";
	char result[255];

	// Load result with the bar title
	strcat(result, name);

	// 17 rounds easily into 255 and gives us 15 bars
	for (i = 1; i < 16; i++) {
		if ((i * 17) <= volume)
			volumeTemplate[i] = '|';
	}

	strcat(result, volumeTemplate);

	osd_gfx_set_message(result);
}
