#include "utils.h"
#include "osd_linux_snd.h"

#if defined(ALLEGRO)

 void osd_snd_set_volume(UChar v)
{
	set_volume(v);
}

#endif // ALLEGRO

#if defined (SDL)
  #include <SDL.h>

#if !defined(SDL_mixer)
  extern void sdl_fill_audio(void *data, Uint8 *stream, int len);
#else //SDL_mixer
  #include "osd_linux_sdl_music.h"
#endif

void osd_snd_set_volume(UChar v)
{
#if !defined (SDL_mixer)
	//#warning implement set volume for sdl

#else //SDL_mixer
	Uint8 vol;
	vol=v/2+((v==0)?0:1);// v=0 <=> vol=0; v=255 <=> vol=128
	Mix_Volume(-1,vol);
	Log("set volume %c\n",vol);
#endif
}


int osd_snd_init_sound(void)
{
#if !defined(SDL_mixer)
  SDL_AudioSpec wanted, got;

  if (SDL_InitSubSystem(SDL_INIT_AUDIO))
  {
    printf("SDL_InitSubSystem(SOUND) failed at %s:%d - %s\n", __FILE__, __LINE__, SDL_GetError());
    return 0;
  }

  wanted.freq = option.want_snd_freq;
  wanted.format = AUDIO_U8;

  wanted.samples = sbuf_size;  /* Good low-latency value for callback */
  wanted.channels = option.want_stereo + 1;

  wanted.callback = sdl_fill_audio;
  wanted.userdata = main_buf;     /* Open the audio device, forcing the desired format */

  if (SDL_OpenAudio(&wanted, &got) < 0)
  {
    Log("Couldn't open audio: %s\n", SDL_GetError());
    return 0;
  }

  host.sound.stereo = (got.channels == 2);
  host.sound.sample_size = got.samples;
  host.sound.freq = got.freq;
  host.sound.signed_sound = (got.format >= 0x8000);

  SDL_PauseAudio(SDL_DISABLE);

#else //SDL_mixer
  Uint16 i;
  Uint16 format;
  int numopened,frequency,channels;
	
if (HCD_last_track>1)
	{
	for (i=1;i<=HCD_last_track;i++)
	{
		if ((CD_track[i].type==0) && (CD_track[i].source_type==HCD_SOURCE_REGULAR_FILE))
		{
			sdlmixmusic[i] = Mix_LoadMUS(CD_track[i].filename);
			if(!sdlmixmusic[i])
			{
				Log("Warning: Error when loading '%s'\n",CD_track[i].filename);
			}
		}
	USE_S16 = 1;
	}		
}else{
	USE_S16 = 0;				
}

numopened=Mix_QuerySpec(&frequency,&format,&channels);
  if (!numopened)
  {
    Log("Mixer initializing...\n");
    if (SDL_InitSubSystem(SDL_INIT_AUDIO))
    {
      printf("SDL_InitSubSystem(SOUND) failed at %s:%d - %s\n", __FILE__, __LINE__, SDL_GetError());
      return 0;
    }
	//MIX_DEFAULT_FORMAT : AUDIO_S16SYS (system byte order).
    host.sound.stereo = option.want_stereo + 1;
    host.sound.sample_size = sbuf_size;
    host.sound.freq = option.want_snd_freq;
	if (Mix_OpenAudio((host.sound.freq),
		(USE_S16?AUDIO_S16:AUDIO_U8),
		(USE_S16?2:host.sound.stereo),
		sbuf_size) < 0)
    {
      Log("Couldn't open audio: %s\n", Mix_GetError());
      return 0;
    }
	numopened=Mix_QuerySpec(&frequency,&format,&channels);
    if (channels == 2) {
		Log("Mixer obtained stereo.\n");
		};
    if (frequency == 44100) {
		Log("Mixer obtained frequency 44100.\n");
		};
    if (format == AUDIO_U8) {
		Log("Mixer obtained format U8.\n");
		};
    host.sound.stereo = channels;
	host.sound.freq = frequency;
    host.sound.sample_size = sbuf_size;


  //sets the callback
  Callback_Stop=FALSE;
  Mix_AllocateChannels(1);
  Mix_ChannelFinished(sdlmixer_fill_audio);

  //FIXME: start playing silently!!
  //needed for sound fx to start
  len=sbuf_size*host.sound.stereo;
  stream = (Uint8*)malloc(len);
  //memset(stream,0,len); //FIXME start playing silently!! 

  if (!(chunk=Mix_QuickLoad_RAW(stream, len))) {
	Log("Mix_QuickLoad_RAW: %s\n",Mix_GetError());
  }

	if (Mix_PlayChannel(0,chunk,0)==-1) {
	  Log("Mix_PlayChannel: %s\n",Mix_GetError());
	}

  }else{
    Log("Mixer already initialized :\n");
    Log("allocated mixer channels : %d\n",Mix_AllocateChannels(-1));
  }

  Mix_Resume(-1);
#endif
  return 1;
}


void osd_snd_trash_sound(void)
{
  UChar chan;
#if !defined(SDL_mixer)
	SDL_CloseAudio();
	
#else //SDL_mixer
	//needed to stop properly...
	Callback_Stop=TRUE;
	//SDL_Delay(1000);
	Mix_CloseAudio();
#endif

	SDL_QuitSubSystem(SDL_INIT_AUDIO);

  for (chan = 0; chan < 6; chan++)
    memset(sbuf[chan], 0, SBUF_SIZE_BYTE);

  memset(adpcmbuf, 0, SBUF_SIZE_BYTE);
}

#endif //SDL
