#include <SDL.h>
#include <SDL_keysym.h>

#include "debug.h"

#include "sys_dep.h"
#include "lang.h"
#include "pce.h"
#include "osd_sdl_gfx.h"


#ifndef _INCLUDE_HAIKU_OSD_INIT_MACHINE
#define _INCLUDE_HAIKU_OSD_INIT_MACHINE

extern UChar gamepad;
// gamepad detected ?

extern char dump_snd;
// Do we write sound to file

extern int *fd[4];
// handle for joypad devices

extern int test_parameter;

#if defined(ENABLE_NETPLAY)

#include "netplay.h"

#endif

#endif // end _INCLUDE_HAIKU_OSD_INIT_MACHINE
