#ifndef _INCLUDE_LINUX_OSD_GFX_H
#define _INCLUDE_LINUX_OSD_GFX_H
#include "cleantyp.h"
#include "pce.h"
#include "sys_dep.h"

#ifdef ALLEGRO

#include <allegro.h>
extern BITMAP* OSD_MESSAGE_SPR;
#ifdef EAGLE
extern BITMAP *EAGLE_buf;    // the buffer where we will put eagleized video
#endif // EAGLE

#elif defined(SDL)

#include <SDL.h>
extern UChar *OSD_MESSAGE_SPR;

#endif // ALLEGRO

extern int blit_x,blit_y;// where must we blit the screen buffer on screen
extern int screen_blit_x, screen_blit_y;// where on the screen we must blit XBuf

int ToggleFullScreen(void);

#endif
