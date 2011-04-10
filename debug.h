#ifndef _INCLUDE_DEBUG_H
#define _INCLUDE_DEBUG_H

#include "pce.h"
#include "dis.h"
#include "optable.h"
// #include "osd_gfx.h"

#define  MAX_BP        16
// Max number of breakpoints

#define  MAX_USER_BP   14
// Max number of breakpoints user definabled

#define  RESTORE_BP    14
// Place in the list of a pseudo-break point for internal usage

#define  GIVE_HAND_BP  15
// Place in the list of the breakpoint used in stepping...

// Some defines for the flag value
#define NOT_USED   0
#define ENABLED    1
#define DISABLED   2


typedef struct
{
  UInt16 position;
  UChar flag;
  UChar original_op;
}
Breakpoint;

extern UInt16 Bp_pos_to_restore;
// Used in RESTORE_BP to know where we must restore a BP

extern Breakpoint Bp_list[MAX_BP];
// The list of all breakpoints

extern UChar save_background;
// Do we have to preserve the background

unsigned char Op6502 (unsigned int A);

void disass_menu ();
// Kind of front end for the true disassemble function

int toggle_user_breakpoint (UInt16);
// Toggle the breakpoint at the specified address

void display_debug_help ();
// Display a help screen

UInt32 cvtnum (char *string);
// Convert a hexa string into a number

void set_bp_following (UInt16 where, UChar nb);
// Set a bp at the location that follows a given address

UChar change_value (int X, int Y, UChar length, UInt32 * result);
// Wait for user to enter a value and display in on screen

#endif
