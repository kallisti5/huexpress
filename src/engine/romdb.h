/*
 * Copyright 2013, Alexander von Gluck, All Rights Reserved.
 * Distributed under the terms of the MIT License.
 *
 * Authors:
 *		Alexander von Gluck IV <kallisti5@unixzen.com>
 */
#ifndef _ROMDB_H
#define _ROMDB_H


#include "cleantypes.h"


// Rom Flags
#define SUPER_GRAPHX 0x0001
#define TWO_PART_ROM 0x0002
#define PINBALL_KEY  0x0004
#define CD_SYSTEM    0x0008

#define ORIGINAL     0x0010
#define MODIFIED     0x0020

#define US_ENCODED   0x0040
#define POPULOUS     0x0080

#define USA          0x4000
#define JAP          0x8000

// Known Rom Count (from kKnownRoms)
#define KNOWN_ROM_COUNT 541

struct rom_database {
	uint32      CRC;
	char		Name[255];
	char		Publisher[128];
	char		ID[64];
	char		Date[64];
	uint32      Flags;
};

extern struct rom_database kKnownRoms[KNOWN_ROM_COUNT];


#endif /* _ROMDB_H */
