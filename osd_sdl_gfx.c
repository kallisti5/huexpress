#include "osd_sdl_gfx.h"

//! PC Engine rendered screen
SDL_Surface *screen = NULL;

/* Overlay for hardware scaling */
SDL_Overlay *olay = NULL;
SDL_Color olay_cmap[256];

//! Host machine rendered screen
SDL_Surface *physical_screen = NULL;

SDL_Rect physical_screen_rect;

int blit_x,blit_y;
// where must we blit the screen buffer on screen

int screen_blit_x, screen_blit_y;
// where on the screen we must blit XBuf

UChar* XBuf;
// buffer for video flipping

UChar index_to_RGB[256];
// convertion array from bero's reduced pce palette to x11 palette

int osd_gfx_init();
int osd_gfx_init_normal_mode();
void osd_gfx_put_image_normal();
void osd_gfx_shut_normal_mode();

void osd_gfx_dummy_func();

osd_gfx_driver osd_gfx_driver_list[3] =
{
  { osd_gfx_init, osd_gfx_init_normal_mode, osd_gfx_put_image_normal, osd_gfx_shut_normal_mode },
  { osd_gfx_init, osd_gfx_init_normal_mode, osd_gfx_put_image_normal, osd_gfx_shut_normal_mode },  
  { osd_gfx_init, osd_gfx_init_normal_mode, osd_gfx_put_image_normal, osd_gfx_shut_normal_mode }
};

void osd_gfx_dummy_func(void)
{
 return;
 }

 void DrawPixel(SDL_Surface *screen, int x, int y,
                                    Uint8 R, Uint8 G, Uint8 B)
{
  Uint32 color = SDL_MapRGB(screen->format, R, G, B);
  switch (screen->format->BytesPerPixel)
  {
    case 1: // Assuming 8-bpp
      {
        Uint8 *bufp;
        bufp = (Uint8 *)screen->pixels + y*screen->pitch + x;
        *bufp = color;
      }
      break;
    case 2: // Probably 15-bpp or 16-bpp
      {
        Uint16 *bufp;
        bufp = (Uint16 *)screen->pixels + y*screen->pitch/2 + x;
        *bufp = color;
      }
      break;
    case 3: // Slow 24-bpp mode, usually not used
      {
        Uint8 *bufp;
        bufp = (Uint8 *)screen->pixels + y*screen->pitch + x * 3;
        if(SDL_BYTEORDER == SDL_LIL_ENDIAN)
        {
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
    case 4: // Probably 32-bpp
      {
        Uint32 *bufp;
        bufp = (Uint32 *)screen->pixels + y*screen->pitch/4 + x;
        *bufp = color;
      }
      break;
  }
}
 
void Slock(SDL_Surface *screen)
{
  if ( SDL_MUSTLOCK(screen) )
  {
    if ( SDL_LockSurface(screen) < 0 )
    {
      return;
    }
  }
}

void Sulock(SDL_Surface *screen)
{
  if ( SDL_MUSTLOCK(screen) )
  {
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
void osd_gfx_put_image_normal(void)
{
  UInt16 y;

  if (!host.video.hardware_scaling)
  {
    Slock(screen);

    for (y = 0; y < io.screen_h; y++)
		#if defined(NEW_GFX_ENGINE)
			memmove(screen->pixels + y * io.screen_w, osd_gfx_buffer + y * XBUF_WIDTH, io.screen_w);	
		#else
      memmove(screen->pixels + y * io.screen_w, XBuf + y * WIDTH + (WIDTH - io.screen_w) / 2, io.screen_w);	
		#endif

    Sulock(screen);

    if (physical_screen->flags & SDL_FULLSCREEN)
      SDL_SoftStretch(screen, NULL, physical_screen, &physical_screen_rect);
    else if (option.window_size > 1)
      SDL_SoftStretch(screen, NULL, physical_screen, &physical_screen_rect);
    else
      memmove(physical_screen->pixels, screen->pixels, io.screen_w * io.screen_h);

    SDL_Flip(physical_screen);
  }
  else
  {
    UInt16 x;
    UChar *p, *op;

    SDL_LockYUVOverlay(olay);

    for (y = 0; y < io.screen_h; y++)
    {
		#if defined(NEW_GFX_ENGINE)
			p = osd_gfx_buffer + y * XBUF_WIDTH;
		#else
      p = XBuf + y * XBUF_WIDTH + (WIDTH - io.screen_w) / 2;
		#endif
		
      op = olay->pixels[0] + olay->pitches[0] * y;

      for (x = 0; x < io.screen_w; x++)
      {
        if (!(x % 2))
        {
          if (olay->format == SDL_UYVY_OVERLAY)
          {
            *(op++) = olay_cmap[*p].g; // 1
            *(op++) = olay_cmap[*p].r; // 0
            *(op++) = olay_cmap[*p].b; // 2
          }
          else if (olay->format == SDL_YUY2_OVERLAY)
          {
            *(op++) = olay_cmap[*p].r;
            *(op++) = olay_cmap[*p].g;
            op[1] = olay_cmap[*p].b;
          } else
					{
						Log("Unsupported hardware packing : %x\n", olay->format);
					}
        }
        else
        {
          *(op++) = olay_cmap[*p].r;	// 2
          if (olay->format == SDL_YUY2_OVERLAY)
            op++;
        }

        p++;
      }
    }
    SDL_UnlockYUVOverlay(olay);

    SDL_DisplayYUVOverlay(olay, &physical_screen_rect);
  }
}

/*****************************************************************************

    Function: osd_gfx_set_message

    Description: compute the message that will be displayed to create a sprite
       to blit on screen
    Parameters: char* mess, the message to display
    Return: nothing but set OSD_MESSAGE_SPR

*****************************************************************************/
void osd_gfx_set_message(char* mess)
{
/*
 if (OSD_MESSAGE_SPR)
   destroy_bitmap(OSD_MESSAGE_SPR);

 OSD_MESSAGE_SPR=create_bitmap(text_length(font,mess)+1,text_height(font)+1);
 clear(OSD_MESSAGE_SPR);
 textout(OSD_MESSAGE_SPR,font,mess,1,1,3);
 textout(OSD_MESSAGE_SPR,font,mess,0,0,255);
*/

#warning implement set_message
  printf("%s\n",mess);
}


/*
 * osd_gfx_init:
 * One time initialization of the main output screen
 */
int osd_gfx_init(void)
{
  struct generic_rect rect;
		
	// We can't rely anymore on io variable being accessible at this stage of a game launching
	const int fake_io_screen_w = 352;
  const int fake_io_screen_h = 256;

	if (!SDL_WasInit(SDL_INIT_VIDEO))
   	{
   		if (SDL_InitSubSystem(SDL_INIT_VIDEO))
   		{
   			printf("SDL_InitSubSystem(VIDEO) failed at %s:%d - %s\n", __FILE__, __LINE__, SDL_GetError());
   			return 0;
		}
   	}

  if ((physical_screen = SDL_SetVideoMode(option.want_fullscreen ? option.fullscreen_width : fake_io_screen_w * option.window_size,
                                          option.want_fullscreen ? option.fullscreen_height : fake_io_screen_h * option.window_size,
                                          (option.want_hardware_scaling ? 0 : 8), (option.want_fullscreen ? SDL_FULLSCREEN : 0) |
                                          (option.want_hardware_scaling ? SDL_HWSURFACE : SDL_SWSURFACE) |
                                          (option.want_hardware_scaling ? 0 : SDL_HWPALETTE))) == NULL)
  {
    printf("SDL_SetVideoMode failed at %s:%d - %s\n", __FILE__, __LINE__, SDL_GetError());
    return 0;
  }

  SDL_WM_SetCaption("Hu-Go! (www.zeograd.com)",NULL);	

  if (option.want_fullscreen)
    SDL_ShowCursor(SDL_DISABLE);

  if (option.want_hardware_scaling)
  {
    host.video.hardware_scaling = TRUE;

		if (option.wanted_hardware_format != 0) // Try this first if asked to
			{
				olay = SDL_CreateYUVOverlay(fake_io_screen_w, fake_io_screen_h, option.wanted_hardware_format, physical_screen);
				if (olay->hw_overlay == 1)
					Log("Hardware scaling enabled using a %x overlay.\n", option.wanted_hardware_format);
			}
			
		if ((option.wanted_hardware_format == 0) || (olay->hw_overlay != 1))
			{
				if (((olay = SDL_CreateYUVOverlay(fake_io_screen_w, fake_io_screen_h, SDL_UYVY_OVERLAY, physical_screen)) == NULL) ||
						(olay->hw_overlay != 1))
				{
					if (((olay = SDL_CreateYUVOverlay(fake_io_screen_w, fake_io_screen_h, SDL_YUY2_OVERLAY, physical_screen)) == NULL) ||
							(olay->hw_overlay != 1))
					{
						host.video.hardware_scaling = FALSE;
							
						Log("Hardware scaling isn't available--falling back to software.\n");
							
						if ((physical_screen = SDL_SetVideoMode(option.want_fullscreen ? option.fullscreen_width : fake_io_screen_w * option.window_size,
																										option.want_fullscreen ? option.fullscreen_width : fake_io_screen_h * option.window_size,
																										8, (option.want_fullscreen ? SDL_FULLSCREEN : 0) |
																										SDL_SWSURFACE | SDL_HWPALETTE)) == NULL)
						{
							printf("SDL_SetVideoMode failed at %s:%d - %s\n", __FILE__, __LINE__, SDL_GetError());
							return 0;
						}
					}
					else
						Log("Hardware scaling enabled using a YUY2 overlay.\n");
				}
				else
					Log("Hardware scaling enabled using a UYVY overlay.\n");
			}
  }
  else
    host.video.hardware_scaling = FALSE;

  calc_fullscreen_aspect(physical_screen->w, physical_screen->h, &rect, fake_io_screen_w, fake_io_screen_h);

  physical_screen_rect.x = rect.start_x;
  physical_screen_rect.y = rect.start_y;
  physical_screen_rect.w = rect.end_x;
  physical_screen_rect.h = rect.end_y;

  SetPalette();

  if (!host.video.hardware_scaling)
  {
    if ((screen = SDL_CreateRGBSurface(SDL_SWSURFACE, fake_io_screen_w, fake_io_screen_h, 8, 0, 0, 0, 0)) == NULL)
    {
      printf("SDL_CreateRGBSurface failed at %s:%d - %s\n", __FILE__, __LINE__, SDL_GetError());
      return 0;
    }
  }

  return 1;
}


/*****************************************************************************

    Function:  osd_gfx_init_normal_mode

    Description: initialize the classic 256*224 video mode for normal video_driver
    Parameters: none
    Return: 0 on error
            1 on success

*****************************************************************************/
int osd_gfx_init_normal_mode()
{
  struct generic_rect rect;

	if (!host.video.hardware_scaling)
		{
			if ((screen->w == io.screen_w) && (screen->h == io.screen_h))
				return;
		}
	else
		{
			if ((olay->w == io.screen_w) && (olay->h == io.screen_h))
				return;
		}
	
  if (!host.video.hardware_scaling)
    SDL_FreeSurface(screen);
  else
    SDL_FreeYUVOverlay(olay);

#ifdef GFX_DEBUG
  printf("Mode change: %dx%d\n", io.screen_w, io.screen_h);
#endif

  if (io.screen_w == 0)
  {
    printf("This shouldn't happen? (io.screen_w == 0 in osd_gfx_init_normal_mode)\n");
    io.screen_w = 256;
  }

  if (io.screen_h == 0)
  {
    printf("This shouldn't happen? (io.screen_h == 0 in osd_gfx_init_normal_mode)\n");
    io.screen_h = 224;
  }

  if (physical_screen->flags & SDL_FULLSCREEN)
  {
    SDL_FillRect(physical_screen, NULL, 0);
  }
  else if (((physical_screen->w / option.window_size) != io.screen_w) ||
           ((physical_screen->h / option.window_size) != io.screen_h))
  {
    physical_screen = SDL_SetVideoMode(io.screen_w * option.window_size, io.screen_h * option.window_size,
                                       (host.video.hardware_scaling ? 0 : 8),
                                       (host.video.hardware_scaling ? SDL_HWSURFACE : SDL_SWSURFACE) |
                                       (host.video.hardware_scaling ? 0 : SDL_HWPALETTE));

    SetPalette();
  }

  calc_fullscreen_aspect(physical_screen->w, physical_screen->h, &rect, io.screen_w, io.screen_h);

  physical_screen_rect.x = rect.start_x;
  physical_screen_rect.y = rect.start_y;
  physical_screen_rect.w = rect.end_x;
  physical_screen_rect.h = rect.end_y;

  if (!host.video.hardware_scaling)
    screen = SDL_CreateRGBSurface(SDL_SWSURFACE, io.screen_w, io.screen_h, 8, 0, 0, 0, 0);
  else
		if (option.wanted_hardware_format == 0)
  	  olay = SDL_CreateYUVOverlay(io.screen_w, io.screen_h, SDL_UYVY_OVERLAY, physical_screen);
		else
			olay = SDL_CreateYUVOverlay(io.screen_w, io.screen_h, option.wanted_hardware_format, physical_screen);

  return (screen && physical_screen) ? 1 : 0;
}


//! Delete the window
void osd_gfx_shut_normal_mode(void)
{
  if (!host.video.hardware_scaling)
  {
    SDL_FreeSurface(screen);
    screen = NULL;
  }
  else
  {
    SDL_FreeYUVOverlay(olay);
    olay = NULL;
  }

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
UInt16 osd_gfx_savepict()
  {
    short unsigned tmp=0;
    char filename[PATH_MAX];
    char filename_base[PATH_MAX];
    char* frame_buffer;
    FILE* output_file;
    time_t current_time;
    
    time(&current_time);

    if (!strftime(filename_base, PATH_MAX, "%%s/screenshot_%F_%R-%%d.ppm", localtime(&current_time)))
      return 0xFFFF;

    do {
      snprintf(filename, PATH_MAX, filename_base, video_path, tmp);
    } while (file_exists(filename) && ++tmp < 0xFFFF);
    
    frame_buffer = malloc(3 * (io.screen_w & 0xFFFE) * (io.screen_h & 0xFFFE));
    
    if (frame_buffer == NULL)
      return 0xFFFF;

    dump_rgb_frame(frame_buffer);

    output_file = fopen(filename, "wb");
    if (output_file != NULL)
      {
	char buf[100];
	
	snprintf(buf, sizeof(buf),
		 "P6\n%d %d\n%d\n",
		 io.screen_w & 0xFFFE, io.screen_h & 0xFFFE, 255);
	fwrite(buf, strlen(buf), 1, output_file);
	fwrite(frame_buffer, 3 * (io.screen_w & 0xFFFE) * (io.screen_h & 0xFFFE), 1, output_file);
	fclose(output_file);
      }

    return tmp;
  }


/*****************************************************************************

    Function:  osd_gfx_set_hugo_mode

    Description: change the video mode
    Parameters: mode : mode of video screen
                width, height : minimum size of screen required
    Return: 0 on success
                 1 on error

*****************************************************************************/
SInt32 osd_gfx_set_hugo_mode(SInt32 mode,SInt32 width,SInt32 height)
{

  screen = SDL_SetVideoMode(320,200, 8, SDL_SWSURFACE);
  SetPalette();	
  return !screen;
	 
 }

/*****************************************************************************

    Function: osd_gfx_set_color

    Description: Change the component of the choosen color
    Parameters: UChar index : index of the color to change
    			UChar r	: new red component of the color
                UChar g : new green component of the color
                UChar b : new blue component of the color
    Return:

*****************************************************************************/
void osd_gfx_set_color(UChar index,
                       UChar r,
                       UChar g,
                       UChar b)
{
  SDL_Color R;

  r <<= 2;
  g <<= 2;
  b <<= 2;

  if (!host.video.hardware_scaling)
  {
    R.r = r; 
    R.g = g; 
    R.b = b;

    SDL_SetColors(physical_screen, &R, index, 1);
  }
  else
  {
    olay_cmap[index].r = (0.299 * r) + (0.587 * g) + (0.114 * b);
    olay_cmap[index].g = (b - olay_cmap[index].r) * 0.565 + 128;
    olay_cmap[index].b = (r - olay_cmap[index].r) * 0.713 + 128;
  }
}


int ToggleFullScreen(void)
{
  struct generic_rect rect;

  SDL_PauseAudio(SDL_ENABLE);

  if (physical_screen->flags & SDL_FULLSCREEN)
  {
    if ((physical_screen = SDL_SetVideoMode(io.screen_w * option.window_size, io.screen_h * option.window_size,
                                            (host.video.hardware_scaling ? 0 : 8),
                                            (host.video.hardware_scaling ? SDL_HWSURFACE : SDL_SWSURFACE) |
                                            (host.video.hardware_scaling ? 0 : SDL_HWPALETTE))) == NULL)
    {
      Log("Can't get physical_screen for full screen\n");
      printf("Can't get physical screen\n");
    }
  } else {
    if ((physical_screen = SDL_SetVideoMode(option.fullscreen_width, option.fullscreen_height,
                                            (host.video.hardware_scaling ? 0 : 8),
                                            (host.video.hardware_scaling ? SDL_HWSURFACE : SDL_SWSURFACE) |
                                            (host.video.hardware_scaling ? 0 : SDL_HWPALETTE) | SDL_FULLSCREEN)) == NULL)
    {
      Log("Can't get physical_screen for full screen\n");
      printf("Can't get physical screen\n");
    }
  }

  SetPalette();

  calc_fullscreen_aspect(physical_screen->w, physical_screen->h, &rect, io.screen_w, io.screen_h);

  physical_screen_rect.x = rect.start_x;
  physical_screen_rect.y = rect.start_y;
  physical_screen_rect.w = rect.end_x;
  physical_screen_rect.h = rect.end_y;

  SDL_PauseAudio(SDL_DISABLE);

  return (physical_screen->flags & SDL_FULLSCREEN) ? 0 : 1;
}
