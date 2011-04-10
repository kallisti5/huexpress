#ifndef _DJGPP_INCLUDE_SDL_MIXER_MUSIC_H
#define  _DJGPP_INCLUDE_SDL_MIXER_MUSIC_H

#include "mix.h"

#if defined(SDL_mixer)
  #include <SDL_mixer.h>
  
  Sint16 tmp;
  int len;
  Uint8 *stream; 
  Mix_Chunk *chunk;
  SDL_AudioCVT cvt;
  boolean Callback_Stop;
  boolean USE_S16;

  #define MAX_SONGS 100	// there cannot be more tracks...
  Mix_Music *sdlmixmusic[MAX_SONGS];

  void sdlmixer_fill_audio(int channel);
#endif

#if defined(LINUX) || defined(FREEBSD)
  #include "osd_linux_sdl_machine.h"
#elif defined(WIN32)
  #include "osd_win_sdl_machine.h"
#endif

#endif
