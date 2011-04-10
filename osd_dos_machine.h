#ifndef _INCLUDE_OSD_INIT_MACHINE
#define _INCLUDE_OSD_INIT_MACHINE

#include <allegro.h>
#include "sys_dep.h"
#include "lang.h"
#include "pce.h"
#include "osd_gfx.h"

extern UChar gamepad;
// gamepad detected ?

extern int gamepad_driver;
// what kind of jypad must we have to handle

extern char synchro;
// à fond, à fond, à fond? (french joke ;)

extern char dump_snd;
// Do we write sound to file

extern UChar video_dump;
// Do we write generated pictures to files .. ?

extern UInt32 last_generated_image;
// Name of the last image we dumped, in order to make sequential dumping ..

#endif
