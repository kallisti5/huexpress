/* modified bsd pce cd hardware support (old one) */
#define BSD_CD_HARDWARE_SUPPORT 1

/* Trace settings for debug purposes */
#define ENABLE_TRACING 1
#define ENABLE_TRACING_AUDIO 0
#define ENABLE_TRACING_BIOS 1
#define ENABLE_TRACING_CD 1
#define ENABLE_TRACING_GFX 0

/* Define to one of `_getb67', `GETB67', `getb67' for Cray-2 and Cray-YMP
   systems. This function is required for `alloca.c' support on those systems.
   */
#undef CRAY_STACKSEG_END

/* Define to 1 if using `alloca.c'. */
/* #undef C_ALLOCA */

/* defined if user wants netplay support */
/* #undef ENABLE_NETPLAY */

/* defined if user wants a 'clean' binary ( = not for hugo developpers) */
#define FINAL_RELEASE 1

/* defined if user have GTK2 installed */
/* #undef GTK */

/* Define to 1 if you have the <limits.h> header file. */
#undef HAVE_LIMITS_H

/* defined if inlined accessors should be used */
#undef INLINED_ACCESSORS

/* for hugo developers working on the input subsystem */
#undef INPUT_DEBUG

/* for hugo developers working on hu6280 emulation */
#undef KERNEL_DEBUG

/* defined if user wants new kernel */
#define KERNEL_DS 1

/* for hugo developers working on netplay emulation */
#undef NETPLAY_DEBUG

/* defined if user wants ogg support in hcd */
#define OGG_SUPPORT 1

/* Name of package */
#undef PACKAGE

/* Define to the address where bug reports for this package should be sent. */
#undef PACKAGE_BUGREPORT

/* directory in which data are located */
#undef PACKAGE_DATA_DIR

/* Define to the full name of this package. */
#undef PACKAGE_NAME

/* Define to the full name and version of this package. */
#undef PACKAGE_STRING

/* Define to the one symbol short name of this package. */
#undef PACKAGE_TARNAME

/* Define to the version of this package. */
#undef PACKAGE_VERSION

/* defined if user wants SDL as library */
#define SDL 1

/* defined if user wants SDL_mixer as library */
#define SDL_mixer 1

/* defined if user wants open memory openness */
#undef SHARED_MEMORY

/* The size of a `char', as computed by sizeof. */
#define SIZEOF_CHAR 1

/* The size of a `int', as computed by sizeof. */
#define SIZEOF_INT 4

/* The size of a `long int', as computed by sizeof. */
#define SIZEOF_LONG_INT 4

/* The size of a `short int', as computed by sizeof. */
#define SIZEOF_SHORT_INT 2

/* If using the C implementation of alloca, define if you know the
   direction of stack growth for your system; otherwise it will be
   automatically deduced at run-time.
	STACK_DIRECTION > 0 => grows toward higher addresses
	STACK_DIRECTION < 0 => grows toward lower addresses
	STACK_DIRECTION = 0 => direction of growth unknown */
#undef STACK_DIRECTION

/* Define to 1 if you have the ANSI C header files. */
#define STDC_HEADERS 1

/* defined if rom are expected to be patched to run from bank 0x68 */
#undef TEST_ROM_RELOCATED

/* Define to 1 if you can safely include both <sys/time.h> and <time.h>. */
#define TIME_WITH_SYS_TIME 1

/* Version number of package */
#define VERSION "2.12"

/* Define to 1 if your processor stores words with the most significant byte
   first (like Motorola and SPARC, unlike Intel and VAX). */
#undef WORDS_BIGENDIAN

/* Define to empty if `const' does not conform to ANSI C. */
#undef const

/* Define to `__inline__' or `__inline' if that's what the C compiler
   calls it, or to nothing if 'inline' is not supported under any name.  */
#ifndef __cplusplus
#undef inline
#endif
