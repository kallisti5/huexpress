#ifndef _SOUND_H_
#define _SOUND_H_

#include "pce.h"

extern UChar sound_driver;

#ifdef DJGPP

#ifdef BYTE

#undef BYTE
#undef WORD
#undef DWORD

#endif

#ifdef DJGPP

#include <audio.h> //SEAL include

extern HAC hVoice;

extern LPAUDIOWAVE lpWave;

#endif

#include <libamp.h>

#endif

#include "cleantyp.h"

#define SOUND_BUF_MS	200
// I think it's too long but for a beginning it'll be enough

//#define SBUF_SIZE_BYTE  44100*SOUND_BUF_MS/1000
// Calculated for mono sound
#define SBUF_SIZE_BYTE 1024*8


#ifdef ALLEGRO

extern AUDIOSTREAM* PCM_stream;

extern SAMPLE *CD_sample;

#endif

extern unsigned char * big_buf;

extern UChar gen_vol;

extern UInt32 sbuf_size;

extern char* sbuf[6];//[SBUF_SIZE_BYTE];
// the buffer where the "DATA-TO-SEND-TO-THE-SOUND-CARD" go
// one for each channel

extern char* adpcmbuf;

extern UChar new_adpcm_play;
// Have we begun a new adpcm sample (i.e. must be reset adpcm index/prev value)

#ifndef SDL

extern char main_buf[SBUF_SIZE_BYTE];
// the mixed buffer, may be removed later for hard mixing...

#else

extern UChar main_buf[SBUF_SIZE_BYTE];
// the mixed buffer, may be removed later for hard mixing...

#endif

extern UInt32	CycleOld;
extern UInt32   CycleNew;
// indicates the last time music has been "released"

extern UInt32	dwNewPos;

extern UInt32 AdpcmFilledBuf;

extern char MP3_playing;
// is MP3 playing ?

int InitSound(void);
void TrashSound(void);
void write_psg(int ch);
void WriteBuffer(char *, int, unsigned);

void write_adpcm(void);
void dump_audio_chunck(UChar* content, int length);

int start_dump_audio(void);
void stop_dump_audio(void);

#endif // HDEF_SOUND_H
