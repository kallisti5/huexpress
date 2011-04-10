#ifndef _DJGPP_INCLUDE_HCD_H
#define _DJGPP_INCLUDE_HCD_H

#include "cleantyp.h"
#include "pce.h"
#include "lsmp3.h"

#if defined(DOS) || defined(linux)
  #include "libamp.h"
#endif

extern UInt32 HCD_first_track;
/* first track of emulated cd */

extern UInt32 HCD_last_track;
/* last track of emulated cd */

extern UInt32 HCD_frame_at_beginning_of_track;
/* nb of frame when this track started,
 * used to make subtitle
 */

extern char   HCD_cover_filename[256];

extern FILE * HCD_iso_FILE;


#ifdef ALLEGRO

extern PACKFILE * HCD_packed_iso_FILE;

#endif

#ifdef SDL_mixer
  #include "osd_linux_sdl_music.h"
#endif

#ifdef OGG_SUPPORT
  #include "ogglength.h"
#endif

int fill_HCD_info(char* name);

void HCD_play_sectors(int begin_sect, int sect_len, char repeat);

void HCD_pause_playing();

void HCD_play_track(UChar track, char repeat);

void HCD_shutdown();

void HCD_handle_subtitle();

void HCD_iso_read_sector(unsigned char *p, UInt32 dum, UInt32 result);

void HCD_cd_read_sector(unsigned char *p, UInt32 dum, UInt32 result);

#endif
