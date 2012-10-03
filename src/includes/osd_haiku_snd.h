#ifndef _INCLUDE_OSD_SND_H
#define _INCLUDE_OSD_SND_H

#include "cleantyp.h"
#include "sys_snd.h"
#include "sound.h"

#if defined(ALLEGRO)

  #warning maybe include pce.h or allegro.h here

#endif

#if defined(SDL)

#include <SDL.h>

#endif

#endif
