#ifndef _GFX_H_
#define _GFX_H_

#include "sys_dep.h"

#define	WIDTH	(360+64)
#define	HEIGHT	256

#if defined(NEW_GFX_ENGINE)

// The extra 32's and 64's are linked to the way the sprite are blitted on screen, which can overlap to near memory
// If only one pixel is drawn in the screen, the whole sprite is written, which can eventually overlap unexpected area
// A sharper way of doing would probably reduce the amount of needed data from 220kb to 128kb (eventually smaller if restricting
// games with hi res to be launched)
// XBUF_WIDTH = 536 + 32 + 32
// XBUG_HEIGHT = 240 + 64 + 64

#define XBUF_WIDTH 	(536 + 32 + 32)
#define	XBUF_HEIGHT	(240 + 64 + 64)

#else

#define XBUF_WIDTH 	(320+64+40)
#define	XBUF_HEIGHT	240

#endif

#include "sprite.h"

#define textoutshadow(bmp,f,s,x,y,color1,color2,offsetx,offsety) { textout(bmp,f,s,x+offsetx,y+offsety,color2); textout(bmp,f,s,x,y,color1); }
// Just a little define to avoid too many keystrokes ;)

/*
 * generic_rect - Used to keep calc_fullscreen_aspect gfx lib independant.  Currently
 *   used to remap values to an SDL_Rect structure.
 */
struct generic_rect
{
  unsigned short start_x, start_y;
  unsigned short end_x, end_y;
};

typedef struct {
	typeof(io.VDC[BXR].W) scroll_x;
	typeof(io.VDC[BYR].W) scroll_y;
	int	scroll_y_diff;
	typeof(io.VDC[CR].W) cr;
} gfx_context;

#ifdef SDL

#include <SDL.h>

extern SDL_Surface *physical_screen;
extern SDL_Rect physical_screen_rect;
extern SDL_Color olay_cmap[256];

#endif

extern int video_dump_flag;
extern int gfx_need_video_mode_change;

void calc_fullscreen_aspect(unsigned short physical_screen_width, unsigned short physical_screen_height,
                            struct generic_rect *rect, unsigned short pce_screen_width, unsigned short pce_screen_height);
void change_pce_screen_height();

void save_gfx_context(int slot_number);

int start_dump_video();

void stop_dump_video();

void dump_video_frame();

UChar Loop6502();

#if defined(GFX_DEBUG)
void gfx_debug_printf(char *format, ...);
#endif														

#endif
