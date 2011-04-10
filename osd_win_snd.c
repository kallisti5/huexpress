#include "osd_win_snd.h"

#if defined(ALLEGRO)

 void osd_snd_set_volume(UChar v)
{
	set_volume(v);
}

#endif // ALLEGRO

#if defined(SDL)

extern void sdl_fill_audio(void *data, Uint8 *stream, int len);

void osd_snd_set_volume(UChar v)
{
	#warning implement set volume for sdl
}

int osd_snd_init_sound(void)
{
    SDL_AudioSpec wanted, got;

    if (SDL_InitSubSystem(SDL_INIT_AUDIO))
    {
        printf("SDL_InitSubSystem(AUDIO) failed at %s:%d - %s\n", __FILE__, __LINE__, SDL_GetError());
        return 0;
    }

    wanted.freq = option.want_snd_freq;
    wanted.format = AUDIO_U8;
    wanted.channels = option.want_stereo + 1;   /* 1 = mono, 2 = stereo */
    wanted.samples = sbuf_size;  /* Good low-latency value for callback */
    wanted.callback = sdl_fill_audio;
    wanted.userdata = main_buf;     /* Open the audio device, forcing the desired format */

    if ( SDL_OpenAudio(&wanted, &got) < 0 ) {
        Log("Couldn't open audio: %s\n", SDL_GetError());
        return(0);
    }

    host.sound.stereo = (got.channels == 2);
    host.sound.sample_size = got.samples;
    host.sound.freq = got.freq;
    host.sound.signed_sound = (got.format >= 0x8000);

    SDL_PauseAudio(SDL_DISABLE);

    return(1);
}


void osd_snd_trash_sound(void)
{
    UChar chan;

	SDL_CloseAudio();
    SDL_QuitSubSystem(SDL_INIT_AUDIO);

    for (chan = 0; chan < 6; chan++)
        memset(sbuf[chan], 0, SBUF_SIZE_BYTE);

    memset(adpcmbuf, 0, SBUF_SIZE_BYTE);
}

#endif // SDL

