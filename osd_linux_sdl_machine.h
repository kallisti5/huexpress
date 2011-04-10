#ifndef _INCLUDE_LINUX_OSD_INIT_MACHINE
#define _INCLUDE_LINUX_OSD_INIT_MACHINE

#include <SDL.h>
#include <SDL_keysym.h>

#include "sys_dep.h"
#include "lang.h"
#include "pce.h"
#include "osd_sdl_gfx.h"

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

#endif
