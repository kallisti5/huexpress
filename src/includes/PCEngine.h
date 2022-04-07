/*****************************************************
 * HuExpress, the PC Engine emulator
 *
 * Copyright 2011-2013 Alexander von Gluck IV
 * Released under the terms of the GPLv2 license.
 *
 * Original HuGO! Authors:
 *  Copyright 2001-2005 Zeograd
 *  Copyright 1998 BERO
 *  Copyright 1996 Alex Krasivsky, Marat Fayzullin
 */
#ifndef _PCENGINE_H
#define _PCENGINE_H

#include "debug.h"
#include "pce.h"
#include "iniconfig.h"

void InitPaths(void);

struct PCEngine {
	int fReady;
	struct host_machine  fHost;
	struct hugo_options* fOptions;
};

void PCEngine_init(struct PCEngine *);
void PCEngine_deinit(struct PCEngine *);

int PCEngine_LoadFile(struct PCEngine *, char* file);
void PCEngine_Run(struct PCEngine *);
static inline int PCEngine_isReady(struct PCEngine * thIs) { return thIs->fReady; };

#endif
