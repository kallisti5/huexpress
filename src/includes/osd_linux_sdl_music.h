#ifndef _SDL_MIXER_MUSIC_H
#define _SDL_MIXER_MUSIC_H

#include "mix.h"
#include "osd_sdl_machine.h"

#include "osd_sdl_snd.h"

#if defined(SDL_mixer)
  #include <SDL_mixer.h>
  
  //#define MAX_SONGS 100	// there cannot be more tracks...
  #define MAX_SONGS 100 // there cannot be more tracks...
  extern Mix_Music *sdlmixmusic[MAX_SONGS];

  void sdlmixer_fill_audio(int channel);
#endif

#endif
