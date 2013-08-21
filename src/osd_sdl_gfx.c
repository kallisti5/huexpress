/*****************************************/
/* SDL Graphics Engine                   */
/* Released under the GPL license        */
/*                                       */
/* Original Author:                      */
/*		Zerograd? - Hu-GO!               */
/* Reworked for HuExpress by:            */
/*		Alexander von Gluck, kallisti5   */
/*****************************************/

#include "osd_sdl_gfx.h"
#include "utils.h"

SDL_Renderer *sdlRenderer = NULL;
SDL_Window *sdlWindow = NULL;

//! PC Engine rendered screen
SDL_Surface *screen = NULL;

/* Overlay for hardware scaling */
SDL_Texture *osd_overlay = NULL;
//SDL_Overlay *olay = NULL;
SDL_Color olay_cmap[256];

//! Host machine rendered screen
SDL_Surface *physical_screen = NULL;
SDL_Texture *osd_texture = NULL;
SDL_GLContext sdlGLContext;

SDL_Color osd_color = { 0, 255, 0, 0 };	// Green
SDL_Rect osd_rect = { 10, 5, 0, 0 };

TTF_Font *osd_font;

SDL_Rect physical_screen_rect;

int blit_x, blit_y;
// where must we blit the screen buffer on screen

int screen_blit_x, screen_blit_y;
// where on the screen we must blit XBuf

uchar *XBuf;
// buffer for video flipping

uchar index_to_RGB[256];
// convertion array from bero's reduced pce palette to x11 palette

int osd_gfx_init();
int osd_gfx_init_normal_mode();
void osd_gfx_put_image_normal();
void osd_gfx_shut_normal_mode();

void osd_gfx_dummy_func();

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


#if 0
void
DrawPixel(SDL_Surface * screen, int x, int y, Uint8 R, Uint8 G, Uint8 B)
{
	Uint32 color = SDL_MapRGB(screen->format, R, G, B);
	switch (screen->format->BytesPerPixel) {
	case 1:					// Assuming 8-bpp
		{
			Uint8 *bufp;
			bufp = (Uint8 *) screen->pixels + y * screen->pitch + x;
			*bufp = color;
		}
		break;
	case 2:					// Probably 15-bpp or 16-bpp
		{
			Uint16 *bufp;
			bufp = (Uint16 *) screen->pixels + y * screen->pitch / 2 + x;
			*bufp = color;
		}
		break;
	case 3:					// Slow 24-bpp mode, usually not used
		{
			Uint8 *bufp;
			bufp = (Uint8 *) screen->pixels + y * screen->pitch + x * 3;
			if (SDL_BYTEORDER == SDL_LIL_ENDIAN) {
				bufp[0] = color;
				bufp[1] = color >> 8;
				bufp[2] = color >> 16;
			} else {
				bufp[2] = color;
				bufp[1] = color >> 8;
				bufp[0] = color >> 16;
			}
		}
		break;
	case 4:					// Probably 32-bpp
		{
			Uint32 *bufp;
			bufp = (Uint32 *) screen->pixels + y * screen->pitch / 4 + x;
			*bufp = color;
		}
		break;
	}

}
#endif


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
	uint16 y;
	uint32 sdlFlags = SDL_GetWindowFlags(sdlWindow);

	//if (!host.video.hardware_scaling) {
		Slock(screen);

		for (y = 0; y < io.screen_h; y++)
			memmove(screen->pixels + y * io.screen_w,
				osd_gfx_buffer + y * XBUF_WIDTH, io.screen_w);

		Sulock(screen);

		if (sdlFlags & SDL_WINDOW_FULLSCREEN
			|| option.window_size > 1)
			SDL_BlitScaled(screen, NULL, physical_screen,
				&physical_screen_rect);
		else
			memmove(physical_screen->pixels, screen->pixels,
				io.screen_w * io.screen_h);

		// After drawing the game, throw in any onscreen text
		if (message_delay && osd_texture) {
			SDL_BlitSurface(osd_texture, NULL, physical_screen, &osd_rect);
			message_delay--;
		}

		/*
		SDL_RenderCopy(sdlRenderer, physical_screen, NULL, &physical_screen_rect);
		SDL_RenderPresent(sdlRenderer); // was SDL_Flip
		*/

		osd_gfx_blit();

	#if 0
	} else {
		// TODO: Fix hardware scaling
		uint16 x;
		uchar *p, *op;

		SDL_LockTexture(osd_overlay, NULL, NULL, NULL);

		for (y = 0; y < io.screen_h; y++) {
			p = osd_gfx_buffer + y * XBUF_WIDTH;
			op = olay->pixels[0] + olay->pitches[0] * y;

			for (x = 0; x < io.screen_w; x++) {
				if (!(x % 2)) {
					if (olay->format == SDL_UYVY_OVERLAY) {
						*(op++) = olay_cmap[*p].g;	// 1
						*(op++) = olay_cmap[*p].r;	// 0
						*(op++) = olay_cmap[*p].b;	// 2
					} else if (olay->format == SDL_YUY2_OVERLAY) {
						*(op++) = olay_cmap[*p].r;
						*(op++) = olay_cmap[*p].g;
						op[1] = olay_cmap[*p].b;
					} else {
						Log("Unsupported hardware packing : %x\n",
							olay->format);
					}
				} else {
					*(op++) = olay_cmap[*p].r;	// 2
					if (olay->format == SDL_YUY2_OVERLAY)
						op++;
				}

				p++;
			}
		}
		SDL_UnlockTexture(osd_overlay);
		// TODO: Review
		SDL_RenderCopy(sdlRenderer, osd_overlay, NULL, &physical_screen_rect);
		SDL_RenderPresent(sdlRenderer);
	}
	#endif
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
	if (!host.video.hardware_scaling) {

		if (osd_texture != NULL) {
			SDL_DestroyTexture(osd_texture);
		}

		osd_texture = TTF_RenderText_Blended(osd_font, mess, osd_color);

		if (osd_texture == NULL) {
			MESSAGE_ERROR("SDL: Couldn't render OSD text - %s\n",
				SDL_GetError());
			// report error
		}
	} else {
		// TODO : osd_gfx_set_message for SDL overlay
		printf("%s\n", mess);
	}
}


/*
 * osd_gfx_init:
 * One time initialization of the main output screen
 */
int
osd_gfx_init(void)
{
	// We can't rely anymore on io variable being accessible at this stage of a game launching
	const int fake_io_screen_w = 352;
	const int fake_io_screen_h = 256;

	if (!SDL_WasInit(SDL_INIT_VIDEO)) {
		if (SDL_InitSubSystem(SDL_INIT_VIDEO)) {
			MESSAGE_ERROR("SDL: %s failed at %s:%d - %s\n",
				__func__, __FILE__, __LINE__, SDL_GetError());
			return 0;
		}
	}

	uint16 width = option.want_fullscreen
		? option.fullscreen_width : fake_io_screen_w * option.window_size;
	uint16 height = option.want_fullscreen
		? option.fullscreen_height : fake_io_screen_h * option.window_size;
	uint16 bpp = option.want_hardware_scaling ? 0 : 32;

	// TODO: Fix fullscreen
	sdlWindow = SDL_CreateWindow("HuExpress", SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN
		| SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

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

	#if SDL_BYTEORDER == SDL_BIG_ENDIAN
	physical_screen = SDL_CreateRGBSurface(0, width, height, bpp,
		0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF);
	#else
	physical_screen = SDL_CreateRGBSurface(0, width, height, bpp,
		0x000000FF, 0x0000FF00, 0x00FF0000, 0xFF000000);
	#endif

	if (physical_screen == NULL) {
		MESSAGE_ERROR("SDL: %s failed at %s:%d - %s\n", __func__, __FILE__,
			__LINE__, SDL_GetError());
		return 0;
	}

	osd_gfx_glinit();
		
	#if 0
	// TODO: MOVE TO osd_texture
	osd_texture = SDL_CreateTexture(physical_screen,
		SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING,
		width, height);
	
	if (option.want_fullscreen)
		SDL_ShowCursor(SDL_DISABLE);

	if (option.want_hardware_scaling) {
		host.video.hardware_scaling = TRUE;

		// TODO: Fix hardware rendering
		#if 0
		if (option.wanted_hardware_format != 0) {
			// Try this first if asked to
			// TODO: SDL_CreateYUVOverlay also had physical_screen?
			osd_overlay = SDL_CreateTexture(sdlRenderer,
				option.wanted_hardware_format, SDL_TEXTUREACCESS_STREAMING,
				fake_io_screen_w, fake_io_screen_h);

			if (olay->hw_overlay == 1)
				MESSAGE_INFO("SDL: Hardware scaling enabled "
					"using overlay %x.\n", option.wanted_hardware_format);
		}
		
		if ((option.wanted_hardware_format == 0)
			|| (olay->hw_overlay != 1)) {
			if (((olay = SDL_CreateYUVOverlay(fake_io_screen_w, fake_io_screen_h,
									   SDL_UYVY_OVERLAY,
									   physical_screen)) == NULL)
				|| (olay->hw_overlay != 1)) {
				if (((olay = SDL_CreateYUVOverlay(fake_io_screen_w,
												  fake_io_screen_h,
												  SDL_YUY2_OVERLAY,
												  physical_screen))
					 == NULL) || (olay->hw_overlay != 1)) {
					host.video.hardware_scaling = FALSE;
					MESSAGE_ERROR("SDL: Hardware scaling isn't available,"
								  " falling back to software scaling.");
					if ((physical_screen
						 = SDL_SetVideoMode(option.want_fullscreen
											? option.
											fullscreen_width :
											fake_io_screen_w *
											option.window_size,
											option.
											want_fullscreen ? option.
											fullscreen_width :
											fake_io_screen_h *
											option.window_size, 8,
											(option.
											 want_fullscreen ?
											 SDL_WINDOW_FULLSCREEN : 0)
											| SDL_SWSURFACE |
											SDL_HWPALETTE)) == NULL) {
						MESSAGE_ERROR("SDL: Set video mode failed - %s\n",
									  SDL_GetError());
						return 0;
					}
				} else
					MESSAGE_INFO
						("SDL: Hardware scaling enabled using YUY2.\n");
			} else
				MESSAGE_INFO
					("SDL: Hardware scaling enabled using UYVY.\n");
		} else
			host.video.hardware_scaling = FALSE;
	#endif
	}


	// TODO: Hack to disable hardware scaling
	host.video.hardware_scaling = FALSE;
	#endif

	struct generic_rect rect;
	calc_fullscreen_aspect(width, height, &rect,
		fake_io_screen_w, fake_io_screen_h);

	physical_screen_rect.x = rect.start_x;
	physical_screen_rect.y = rect.start_y;
	physical_screen_rect.w = rect.end_x;
	physical_screen_rect.h = rect.end_y;

	SetPalette();

	if (TTF_Init() < 0) {
		MESSAGE_ERROR("SDL_ttf: Unable to initialize - %s\n",
					  TTF_GetError());
		return 0;
	}

	osd_font = loadfont("font.otf", 24);

	if (!host.video.hardware_scaling) {
		if ((screen = SDL_CreateRGBSurface(SDL_SWSURFACE, fake_io_screen_w,
			fake_io_screen_h, 32, 0, 0, 0, 0)) == NULL) {
			MESSAGE_ERROR("SDL: CreateRGBSurface failed at %s:%d - %s\n",
						  __FILE__, __LINE__, SDL_GetError());
			return 0;
		}
	}

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
	uint32 sdlFlags = SDL_GetWindowFlags(sdlWindow);

	struct generic_rect rect;

	// TODO: Fix hardware scaling
	//if (!host.video.hardware_scaling) {
		if ((screen->w == io.screen_w) && (screen->h == io.screen_h))
			return 1;
	//} else {
	//	if ((olay->w == io.screen_w) && (olay->h == io.screen_h))
	//		return 1;
	//}

	if (!host.video.hardware_scaling)
		SDL_FreeSurface(screen);
	else
		SDL_DestroyTexture(osd_overlay);

#if ENABLE_TRACING_GFX
	printf("GFX: Mode change: %dx%d\n", io.screen_w, io.screen_h);
#endif

	if (io.screen_w == 0) {
		printf
			("This shouldn't happen? (io.screen_w == 0 in osd_gfx_init_normal_mode)\n");
		io.screen_w = 256;
	}

	if (io.screen_h == 0) {
		printf
			("This shouldn't happen? (io.screen_h == 0 in osd_gfx_init_normal_mode)\n");
		io.screen_h = 224;
	}

	if (sdlFlags & SDL_WINDOW_FULLSCREEN) {
		SDL_FillRect(physical_screen, NULL, 0);
	} else if (((physical_screen->w / option.window_size) != io.screen_w)
			   || ((physical_screen->h / option.window_size) !=
				   io.screen_h)) {
		// TODO: SDL_CreateWindow?
		#if 0
		physical_screen = SDL_SetVideoMode(io.screen_w * option.window_size,
			io.screen_h * option.window_size,
			(host.video.hardware_scaling ? 0 : 8),
			(host.video.hardware_scaling ? SDL_HWSURFACE : SDL_SWSURFACE)
				| (host.video.hardware_scaling ? 0 : SDL_HWPALETTE));
		#endif

		SetPalette();
	}

	calc_fullscreen_aspect(physical_screen->w, physical_screen->h, &rect,
						   io.screen_w, io.screen_h);

	physical_screen_rect.x = rect.start_x;
	physical_screen_rect.y = rect.start_y;
	physical_screen_rect.w = rect.end_x;
	physical_screen_rect.h = rect.end_y;

	if (!host.video.hardware_scaling)
		screen = SDL_CreateRGBSurface(SDL_SWSURFACE, io.screen_w, io.screen_h,
			8, 0, 0, 0, 0);
	// TODO: Fix hardware scaling
	#if 0
	else if (option.wanted_hardware_format == 0) {
		osd_overlay = SDL_CreateTexture(sdlRenderer,
			option.wanted_hardware_format, SDL_TEXTUREACCESS_STREAMING,
			io.screen_w, io.screen_h);
		//olay = SDL_CreateYUVOverlay(io.screen_w, io.screen_h, 
		//	SDL_UYVY_OVERLAY, physical_screen);
	} else {
		osd_overlay = SDL_CreateTexture(sdlRenderer,
			option.wanted_hardware_format, SDL_TEXTUREACCESS_STREAMING,
			io.screen_w, io.screen_h);
		//olay = SDL_CreateYUVOverlay(io.screen_w, io.screen_h,
		//	option.wanted_hardware_format,
		//	physical_screen);
	}
	#endif

	return (screen && physical_screen) ? 1 : 0;
}


//! Delete the window
void
osd_gfx_shut_normal_mode(void)
{
	if (osd_texture != NULL)
		SDL_DestroyTexture(osd_texture);

	if (!host.video.hardware_scaling) {
		SDL_FreeSurface(screen);
		screen = NULL;
	} else {
		SDL_DestroyTexture(osd_overlay);
		osd_overlay = NULL;
	}

	TTF_CloseFont(osd_font);

	if (sdlWindow != NULL)
		SDL_DestroyWindow(sdlWindow);

	/* SDL will free physical_screen internally */
	SDL_QuitSubSystem(SDL_INIT_VIDEO);

	physical_screen = NULL;
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

		snprintf(buf, sizeof(buf),
				 "P6\n%d %d\n%d\n",
				 io.screen_w & 0xFFFE, io.screen_h & 0xFFFE, 255);
		fwrite(buf, strlen(buf), 1, output_file);
		fwrite(frame_buffer,
			   3 * (io.screen_w & 0xFFFE) * (io.screen_h & 0xFFFE), 1,
			   output_file);
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

	if (!host.video.hardware_scaling) {
		R.r = r;
		R.g = g;
		R.b = b;

		SDL_SetPaletteColors(physical_screen->format->palette,
			&R, 0, 1);
	} else {
		olay_cmap[index].r = (0.299 * r) + (0.587 * g) + (0.114 * b);
		olay_cmap[index].g = (b - olay_cmap[index].r) * 0.565 + 128;
		olay_cmap[index].b = (r - olay_cmap[index].r) * 0.713 + 128;
	}
}

void
osd_gfx_glinit()
{
	glEnable( GL_TEXTURE_2D );
	
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, linear_filter ? GL_LINEAR : GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	
	//glViewport( 0, 0, screen->w, screen->h);
	glViewport(0, 0, physical_screen->w, physical_screen->h);
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
	//glOrtho(0.0, (GLdouble)screen->w, (GLdouble)screen->h, 0.0, -1.0, 1.0);
	glOrtho(0.0, (GLdouble)physical_screen->w,
		(GLdouble)physical_screen->h, 0.0, -1.0, 1.0);
	//}
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();	
}


void
osd_gfx_blit()
{
	GLint nOfColors = physical_screen->format->BytesPerPixel;
	GLenum texture_format = GL_RGBA;

	int width = physical_screen->w;
	int height = physical_screen->h;

	// Edit the texture object's image data	using the information SDL_Surface gives us
	glTexImage2D(GL_TEXTURE_2D, 0, nOfColors, width, height,
		0, texture_format, GL_UNSIGNED_BYTE, physical_screen->pixels);

	glBegin(GL_QUADS) ;
		glTexCoord2f(1.0f, 1.0f);
		glVertex2i(width, height);

		glTexCoord2f(1.0f, 0.0f);
		glVertex2i(width, 0);

		glTexCoord2f(0.0f, 0.0f);
		glVertex2i(0, 0);

		glTexCoord2f(0.0f, 1.0f);
		glVertex2i(0, height);
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
	#if 0
	if (sdlFlags & SDL_WINDOW_FULLSCREEN) {
		if ((physical_screen =
			 SDL_SetVideoMode(io.screen_w * option.window_size,
							  io.screen_h * option.window_size,
							  (host.video.hardware_scaling ? 0 : 8),
							  (host.video.
							   hardware_scaling ? SDL_HWSURFACE :
							   SDL_SWSURFACE) | (host.video.
												 hardware_scaling ? 0 :
												 SDL_HWPALETTE))) ==
			NULL) {
			Log("Can't get physical_screen for full screen\n");
			printf("Can't get physical screen\n");
		}
	} else {
		if ((physical_screen =
			 SDL_SetVideoMode(option.fullscreen_width,
							  option.fullscreen_height,
							  (host.video.hardware_scaling ? 0 : 8),
							  (host.video.
							   hardware_scaling ? SDL_HWSURFACE :
							   SDL_SWSURFACE) | (host.video.
												 hardware_scaling ? 0 :
												 SDL_HWPALETTE) |
							  SDL_WINDOW_FULLSCREEN)) == NULL) {
			Log("Can't get physical_screen for full screen\n");
			printf("Can't get physical screen\n");
		}
	}
	#endif

	SetPalette();

	calc_fullscreen_aspect(physical_screen->w, physical_screen->h, &rect,
						   io.screen_w, io.screen_h);

	physical_screen_rect.x = rect.start_x;
	physical_screen_rect.y = rect.start_y;
	physical_screen_rect.w = rect.end_x;
	physical_screen_rect.h = rect.end_y;

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
