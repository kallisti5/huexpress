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
SDL_GLContext sdlGLContext;

//! PC Engine rendered screen
SDL_Surface *screen = NULL;

/* Overlay for hardware scaling */
SDL_Texture *osd_overlay = NULL;
SDL_Color olay_cmap[256];
SDL_Texture *osd_texture = NULL;
SDL_Color osd_color = { 0, 255, 0, 0 };	// Green
SDL_Rect osd_rect = { 10, 5, 0, 0 };

TTF_Font *osd_font;

int blit_x, blit_y;
// where must we blit the screen buffer on screen

uchar *XBuf;
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


TTF_Font *
loadfont(char *file, int ptsize)
{
	TTF_Font *tmpfont;
	tmpfont = TTF_OpenFont(file, ptsize);
	if (tmpfont == NULL) {
		MESSAGE_ERROR("Unable to load font: %s %s \n", file,
			TTF_GetError());
	}
	return tmpfont;
}


static void
Slock(SDL_Surface * screen)
{
	if (SDL_MUSTLOCK(screen)) {
		if (SDL_LockSurface(screen) < 0) {
			return;
		}
	}
}


static void
Sulock(SDL_Surface * screen)
{
	if (SDL_MUSTLOCK(screen)) {
		SDL_UnlockSurface(screen);
	}
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
	uint32 sdlFlags = SDL_GetWindowFlags(sdlWindow);

	Slock(screen);
	dump_rgb_frame(screen->pixels);
	Sulock(screen);

	//Slock(screen);
	// After drawing the game, throw in any onscreen text
	/*
	if (message_delay && osd_texture) {
		SDL_BlitSurface(osd_texture, NULL, physical_screen, &osd_rect);
		message_delay--;
	}
	*/

	//SDL_RenderCopy(sdlRenderer, physical_screen, NULL, &physical_screen_rect);
	//SDL_RenderPresent(sdlRenderer); // was SDL_Flip

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
	if (osd_texture != NULL) {
		SDL_DestroyTexture(osd_texture);
	}

	osd_texture = TTF_RenderText_Blended(osd_font, mess, osd_color);

	if (osd_texture == NULL) {
		MESSAGE_ERROR("SDL: Couldn't render OSD text - %s\n",
			SDL_GetError());
		// report error
	}
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

	if (TTF_Init() < 0) {
		MESSAGE_ERROR("SDL_ttf: Unable to initialize - %s\n",
			TTF_GetError());
		return 0;
	}

	osd_font = loadfont("font.otf", 24);

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

	uint16 windowWidth = option.want_fullscreen
		? option.fullscreen_width : io.screen_w * option.window_size;
	uint16 windowHeight = option.want_fullscreen
		? option.fullscreen_height : io.screen_h * option.window_size;

	if (sdlWindow != NULL) {
		SDL_DestroyWindow(sdlWindow);
		sdlWindow = NULL;
	}

	sdlWindow = SDL_CreateWindow("HuExpress", SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight, SDL_WINDOW_SHOWN
		| SDL_WINDOW_OPENGL);

	if (sdlWindow == NULL) {
		MESSAGE_ERROR("SDL: %s failed at %s:%d - %s\n", __func__, __FILE__,
			__LINE__, SDL_GetError());
		return 0;
	}

	sdlGLContext = SDL_GL_CreateContext(sdlWindow);

	if (sdlGLContext == NULL) {
		MESSAGE_ERROR("SDL: %s failed at %s:%d - %s\n", __func__, __FILE__,
			__LINE__, SDL_GetError());
		return 0;
	}

	SDL_GL_MakeCurrent(sdlWindow, sdlGLContext);

	sdlRenderer = SDL_CreateRenderer(sdlWindow, -1, SDL_RENDERER_ACCELERATED);
	//sdlRenderer = SDL_CreateRenderer(sdlWindow, -1, SDL_RENDERER_SOFTWARE);

	if (sdlRenderer == NULL) {
		MESSAGE_ERROR("SDL: %s failed at %s:%d - %s\n", __func__, __FILE__,
			__LINE__, SDL_GetError());
		return 0;
	}

	SDL_GL_SetSwapInterval(1);

	if (screen != NULL) {
		SDL_FreeSurface(screen);
		screen = NULL;
	}

	screen = SDL_CreateRGBSurface(0, io.screen_w, io.screen_h,
		32, 0x000000FF, 0x0000FF00, 0x00FF0000, 0);

	if (screen == NULL) {
		MESSAGE_ERROR("SDL: CreateRGBSurface failed at %s:%d - %s\n",
			__FILE__, __LINE__, SDL_GetError());
	}

	osd_gfx_glinit();

	return (screen) ? 1 : 0;
}


//! Delete the window
void
osd_gfx_shut_normal_mode(void)
{
	if (osd_texture != NULL)
		SDL_DestroyTexture(osd_texture);

	SDL_FreeSurface(screen);
	screen = NULL;

	//SDL_DestroyTexture(osd_overlay);
	//osd_overlay = NULL;

	TTF_CloseFont(osd_font);

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
	SDL_Color R;

	r <<= 2;
	g <<= 2;
	b <<= 2;

	R.r = r;
	R.g = g;
	R.b = b;

	SDL_SetPaletteColors(screen->format->palette,
		&R, 0, 1);
}


void
osd_gfx_glinit()
{
	glEnable( GL_TEXTURE_2D );

	uint16 windowWidth = option.want_fullscreen
		? option.fullscreen_width : screen->w * option.window_size;
	uint16 windowHeight = option.want_fullscreen
		? option.fullscreen_height : screen->h * option.window_size;

	GLuint texture = 0;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, linear_filter ? GL_LINEAR : GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glViewport(0, 0, windowWidth, windowHeight);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_ALPHA_TEST);
	glDisable(GL_BLEND);
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_3D_EXT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	/*if (conf->video_mask_overscan) {
	glOrtho(0.0, (GLdouble)screen->w,
		(GLdouble)screen->h - (OVERSCAN_BOTTOM * scalefactor),
		(GLdouble)(OVERSCAN_TOP * scalefactor), -1.0, 1.0);
	}
	else {*/
	glOrtho(0.0, (GLdouble)windowWidth,	(GLdouble)windowHeight, 0.0, -1.0, 1.0);
	//}
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}


void
osd_gfx_blit()
{
	Slock(screen);
	// Edit the texture object's image data	using the information SDL_Surface gives us
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
		screen->w, screen->h, 0, GL_RGB, GL_UNSIGNED_BYTE,
		screen->pixels);
	Sulock(screen);

	int X = 0;
	int Y = 0;
	int windowWidth = screen->w * option.window_size;
	int windowHeight = screen->h * option.window_size;

	glBegin(GL_QUADS) ;
		glTexCoord2f(0, 0);
		glVertex3f(X, Y, 0);
		glTexCoord2f(1, 0);
		glVertex3f(X + windowWidth, Y, 0);
		glTexCoord2f(1, 1);
		glVertex3f(X + windowWidth, Y + windowHeight, 0);
		glTexCoord2f(0, 1);
		glVertex3f(X, Y + windowHeight, 0);
	glEnd();

	SDL_GL_SwapWindow(sdlWindow);
}


int
ToggleFullScreen(void)
{
	struct generic_rect rect;
	uint32 sdlFlags = SDL_GetWindowFlags(sdlWindow);

	SDL_PauseAudio(SDL_ENABLE);

	// TODO: Fix FullScreen
	// option.fullscreen_width
	// option.fullscreen_height

	SetPalette();

	calc_fullscreen_aspect(screen->w, screen->h, &rect,
		io.screen_w, io.screen_h);

	SDL_PauseAudio(SDL_DISABLE);

	return (sdlFlags & SDL_WINDOW_FULLSCREEN) ? 0 : 1;
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
