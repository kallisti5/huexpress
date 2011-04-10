#ifndef INCLUDE_OSD_GFX_H
#define INCLUDE_OSD_GFX_H

#include "cleantyp.h"
#include "pce.h"
#include "sys_dep.h"
#include <allegro.h>

extern BITMAP* OSD_MESSAGE_SPR;

extern int blit_x,blit_y;
// where must we blit the screen buffer on screen

extern int screen_blit_x, screen_blit_y;
// where on the screen we must blit XBuf

extern BITMAP *EAGLE_buf;
// the buffer where we will put eagleized video


#endif
