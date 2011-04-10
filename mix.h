#ifndef _DJGPP_INCLUDE_MIX_H
#define  _DJGPP_INCLUDE_MIX_H

#include "pce.h"
#include "sound.h"

void (*update_sound[4])();

UInt32 WriteBufferAdpcm8(UChar *buf,
                       UInt32 begin,
                       UInt32 size,
                       SChar* Index,
                       SInt32* PreviousValue
                       );

void WriteBuffer(char *buf,
				int ch,
				unsigned dwSize);
				
#endif
