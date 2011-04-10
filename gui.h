#ifndef _DJ_INCLUDE_GUI_H
#define _DJ_INCLUDE_GUI_H

#ifdef DOS

#include <dir.h>
#include <keys.h>

#endif

#ifdef ALLEGRO
#include <allegro.h>
#endif
#include "list_rom.h"
#include "trans_fx.h"
#include <string.h>
#include <math.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>
#include "pce.h"
#include "cleantyp.h"

typedef struct {
       char str[16];
		 unsigned corr;
		 } TO_DISPLAY;

/* Warning, this has changed */
typedef struct {
       char basefilename[13];
       char romfilename[13];

		 char romname[16];
		 } INDEX_ITEM;
/* Warning, this has changed */

typedef struct {
       char basefilename[13];
       char archived[13];
       } ARCH_FILE;

extern char selected_rom[128];

extern char name_to_extract[64];

extern UChar static_refresh;
// used to know whether we check the game directory each time

extern UChar zip_support_in_fs;
// used to know whether we check inside zip archive in a directory

extern int vwidth;

extern int vheight;

void Dir(unsigned *dirt,
         unsigned *fich,
         unsigned *arch,

         char *nom_dir,

         ARCH_FILE * fichier,

         char* must_draw,

         TO_DISPLAY * to_display);



char* select_rom();



#endif
