#ifndef _INCLUDE_LINUX_OSD_INIT_MACHINE
#define _INCLUDE_LINUX_OSD_INIT_MACHINE

#include <SDL.h>
#include <SDL_keysym.h>

#include "sys_dep.h"
#include "lang.h"
#include "pce.h"
#include "osd_sdl_gfx.h"

extern UChar gamepad;
// gamepad detected ?

extern char dump_snd;
// Do we write sound to file

extern int *fd[4];
// handle for joypad devices

extern int test_parameter;

#if defined(ENABLE_NETPLAY)

#include <sys/times.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
// #include <netinet/in.h>
// #include <netdb.h>

typedef enum {NETPLAY_SINGLE, NETPLAY_SERVER, NETPLAY_CLIENT} t_netplay_mode;

extern int netplay_mode;

extern struct sockaddr_in socket_address_other, socket_address_self;

extern int lenght_socket_address_other;
extern int lenght_socket_address_self;

extern int socket_other;
extern int socket_self;

#endif

#endif
