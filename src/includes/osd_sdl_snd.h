#ifndef _INCLUDE_OSD_SND_H
#define _INCLUDE_OSD_SND_H

#include "cleantypes.h"
#include "sys_snd.h"
#include "sound.h"


#include <SDL.h>
#include <SDL_mixer.h>

extern Uint8 *stream;
extern Mix_Chunk *chunk;
extern SDL_AudioCVT cvt;
extern bool Callback_Stop;
extern bool USE_S16;

#endif
