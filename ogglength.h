#ifndef _DJGPP_INCLUDE_OGGLENGTH_H
#define  _DJGPP_INCLUDE_OGGLENGTH_H
#include "config.h"

#ifdef OGG_SUPPORT
  #include <string.h>
  #include <sys/ioctl.h>
  #include <stdio.h>
  #include <vorbis/vorbisfile.h>

  int OGG_length(const char *);
#endif

#endif
