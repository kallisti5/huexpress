#ifndef _INCLUDE_OSD_GFX_H
#define _INCLUDE_OSD_GFX_H
#include "cleantyp.h"
#include "pce.h"
#include "sys_dep.h"

#include <SDL.h>
#include <SDL_ttf.h>

extern UChar *OSD_MESSAGE_SPR;

extern int blit_x,blit_y;// where must we blit the screen buffer on screen
extern int screen_blit_x, screen_blit_y;// where on the screen we must blit XBuf

int ToggleFullScreen(void);
void drawVolume(char* name, int volume);

#endif
