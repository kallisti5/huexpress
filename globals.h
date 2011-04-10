/****************************************************************************
 globals.h
 ****************************************************************************/

#ifndef GLOBALS_H_
#define GLOBALS_H_

#include "hard_pce.h"
#include "defs.h"

//
// Bitmask values for PCE status flags:
//
#define FL_N 0x80
#define FL_V 0x40
#define FL_T 0x20
#define FL_B 0x10
#define FL_D 0x08
#define FL_I 0x04
#define FL_Z 0x02
#define FL_C 0x01

//
// Globals for PCE memory-addressing:
//
extern UChar * base[256];
extern UChar * zp_base;
extern UChar * sp_base;
extern UChar * mmr_base[8];

//
// Globals for PCE CPU registers:
//
extern UInt16  reg_pc;
extern UChar   reg_a;
extern UChar   reg_x;
extern UChar   reg_y;
extern UChar   reg_p;
extern UChar   reg_s;
extern UChar * mmr;

//
// Globals which hold emulation-realted info:
//
extern UInt32    cycles;
extern UChar   halt_flag;

//
// Tables for disassembly/execution of PCE opcodes:
//
extern mode_struct addr_info[];
extern operation optable[];

#endif
