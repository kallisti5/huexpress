/**************************************************************************/
/*                                                                        */
/*                       List of Rom header                               */
/*                                                                        */
/*              Made by Zeograd (zeograd@caramail.com)                    */
/*                                                                        */
/*    11 June '99 : 521 recognized roms                                   */
/*    24 June '99 : 526 recognized roms                                   */
/*    27 June '99 : 541 recognized roms + separation of rom name/producer */
/*                                                                        */
/**************************************************************************/
#ifndef _INCLUDE_LIST_ROM_H
#define _INCLUDE_LIST_ROM_H

#include "pce.h"

#include "debug.h"

struct pce_rom_info {
	unsigned long CRC;
	char *name, *producer, *date, *note;
	unsigned short flags;
};

#define NB_ROM 542

#include "cleantypes.h"

// extern ROM_TYPE ROM_LIST[NB_ROM];

unsigned long filesize(FILE * F);
uint32 CRC_file(char *name);

#endif
