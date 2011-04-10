#ifndef _INCLUDE_KEYBOARD_H
#define _INCLUDE_KEYBOARD_H

#include "pce.h"

#if defined(WIN32)

#if defined(SDL)
#include "osd_win_sdl_machine.h"
#else // !SDL

#if defined(ALLEGRO)
#include "osd_win_allegro_machine.h"
#endif // ALLEGRO

#endif // !SDL

#else // !WIN32

#if defined(SDL)
#include "osd_linux_sdl_machine.h"
#else // !SDL

#if defined(ALLEGRO)
#include "osd_linux_allegro_machine.h"
#endif // ALLEGRO

#if !defined(FREEBSD)
#include <linux/joystick.h>
#endif // !FREEBSD

#endif // !SDL
#endif // !WIN32

typedef struct
{
  SInt16 axis[4];
  SInt16 button[16];
} js_status;

extern char auto_fire_A[5];
/* Is auto fire on */

extern char auto_fire_B[5];
/* Is auto fire on */

#endif
