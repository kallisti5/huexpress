/****************************************************************************
 defs.h
 ****************************************************************************/

#ifndef DEFS_H_
#define DEFS_H_

#include "cleantyp.h"

//
// misc typedefs:
// --------------

//
//
//
typedef struct {
#ifdef BYTEORD_LSBFIRST
  UChar bl;
  UChar bh;
#else
  UChar bh;
  UChar bl;
#endif
} BytesOfWord;

typedef union {
  UInt16       w;
  BytesOfWord  b;
} Word;

typedef struct {
#ifdef BYTEORD_LSBFIRST
  Word  wl;
  Word  wh;
#else
  Word  wh;
  Word  wl;
#endif
} WordsOfLong;

typedef union {
  UInt32       i;
  WordsOfLong  w;
} LongWord;

//
// 'mode_struct' and 'operation' hold information about opcodes
//   (used in disassembly and execution)
//

typedef struct mode {
  Int16 size;
  void (*func_format)(Char *, long, UChar *, Char *);
} mode_struct;


typedef struct op {
   int (*func_exe)(void);
   Int16  addr_mode;
   Char * opname;
//   short int filler[3];   // force align to power-of-2 (?)
} operation;


#endif
