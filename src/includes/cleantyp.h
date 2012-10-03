#ifndef _INCLUDE_CLEANTYP_H
#define _INCLUDE_CLEANTYP_H

#include "config.h"

#ifdef TRUE
#undef TRUE
#endif

#ifdef FALSE
#undef FALSE
#endif

typedef enum
{
  FALSE,
  TRUE
} boolean;

/* 8 Bits defines */

#if SIZEOF_CHAR == 1

/* Unsigned */
typedef unsigned char UChar;

#ifdef __AUDIO_H
  typedef unsigned char BYTE;
#endif

/* Signed */
typedef signed char SChar;
typedef signed char Char;

#else

#error sizeof (char) is not 1. Pretty weird. Contact author

#endif // SIZEOF_CHAR == 1

/****************************************************************************/

/* 16 Bits defines */

#if SIZEOF_SHORT_INT == 2

/* Unsigned */
typedef unsigned short int UInt16;

#ifdef __AUDIO_H
typedef unsigned short int WORD;
#endif

/* Signed */
typedef signed short int SInt16;
typedef signed short int Int16;

#elif SIZEOF_INT == 2

/* Unsigned */
typedef unsigned int UInt16;

#ifdef __AUDIO_H
typedef unsigned short int WORD;
#endif

/* Signed */
typedef signed int SInt16;
typedef signed int Int16;

#else // neither int nor short are coded on 16 bits

#error neither short ints or ints are 16 bits long. Contact author.

#endif

/************************************************************************/

/* 32 Bits defines */

#if SIZEOF_INT == 4

/* Unsigned */
typedef unsigned int UInt32;

#ifdef __AUDIO_H
typedef unsigned int DWORD;
#endif

/* Signed */
typedef signed int SInt32;
typedef signed int Int32;

#elif SIZEOF_LONG_INT == 4

/* Unsigned */
typedef unsigned long int UInt32;

#ifdef __AUDIO_H
typedef unsigned long int DWORD;
#endif

/* Signed */
typedef signed long int SInt32;
typedef signed long int Int32;

#else

#error neither ints nor long ints are 32 bits long. Contact author.

#endif

#endif
