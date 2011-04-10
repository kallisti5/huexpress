# Process this file with autoconf to produce a configure script.
AC_INIT(hugo, 2.12, zeograd@zeograd.com)
AM_INIT_AUTOMAKE(hugo, 2.12)
AC_CONFIG_SRCDIR([pce.c])
# AC_CONFIG_HEADER([config.h])
AM_CONFIG_HEADER(config.h)

AC_CANONICAL_TARGET
# AC_ARG_PROGRAM

AM_MAINTAINER_MODE

# Checks for programs.
AC_PROG_CC
AC_PROG_INSTALL
AC_PROG_LN_S

AC_CHECK_PROG([HAVE_LYX], [lyx], [found])
AC_CHECK_PROG([HAVE_LATEX2HTML], [latex2html], [found])
AC_CHECK_PROG([HAVE_SED], [sed], [found])
AC_CHECK_PROG([HAVE_TIDY], [tidy], [found])

if test -n "$HAVE_LYX"; then
   AM_CONDITIONAL(HAVE_TOOLS_FOR_TXT_DOC,true)
   AVAILABLE_DOC_TARGETS="txt"
   echo "$as_me:$LINENO: TEXTUAL form of the documentation can be made" >&5
   echo $ECHO_N "TEXTUAL form of the documentation can be made" >&6
else
   AM_CONDITIONAL(HAVE_TOOLS_FOR_TXT_DOC,false)
   echo "$as_me:$LINENO: TEXTUAL form of the documentation can NOT be made" >&5
   echo $ECHO_N "TEXTUAL form of the documentation can NOT be made" >&6
fi

if test -n "$HAVE_LYX" -a -n "$HAVE_LATEX2HTML" -a -n "$HAVE_SED" -a -n "$HAVE_TIDY"; then
   AM_CONDITIONAL(HAVE_TOOLS_FOR_HTML_DOC,true)
   AVAILABLE_DOC_TARGETS="$AVAILABLE_DOC_TARGETS html"
else
   AM_CONDITIONAL(HAVE_TOOLS_FOR_HTML_DOC,false)
fi

AC_SUBST(AVAILABLE_DOC_TARGETS)

# Checks for libraries.

AC_CHECK_LIB(SDL, main) #,,[AC_MSG_ERROR([need SDL. See #http://www.libsdl.org])])
AC_CHECK_LIB(SDL_net, main, [HAVE_LIBSDL_NET="yes" LIBS="-lSDL_net $LIBS" AC_DEFINE([HAVE_LIBSDL_NET],[1],[Define to 1 if you have the SDL_net library])], [HAVE_LIBSDL_NET="no"]) #,,[AC_MSG_ERROR([need SDL_net. See #http://www.libsdl.org])])
AC_CHECK_LIB(SDL_mixer,main) #,,[AC_MSG_ERROR([need SDL_mixer. See #http://www.libsdl.org])])
AC_CHECK_LIB(vorbis, main)
AC_CHECK_LIB(vorbisfile, main)

LIBZ_SUPPORT=no

AC_CHECK_LIB(z, main, [ LIBS="$LIBS -lz" AM_CONDITIONAL(ZLIB, true) AC_DEFINE([HAVE_LIBZ], [1], [Define to 1 if you have the 'z' library (-lz)]) LIBZ_SUPPORT=yes])

if test "x$LIBZ_SUPPORT" = "xno"
then

AC_CHECK_LIB(zdll, main, [ LIBS="$LIBS -lzdll"  AM_CONDITIONAL(ZLIB, true) AC_DEFINE([HAVE_LIBZ], [1], [Define to 1 if you have the 'z' library (-lz)]) LIBZ_SUPPORT=yes] , AM_CONDITIONAL(ZLIB, false))

fi

# Checks for endianess

AC_C_BIGENDIAN

AM_PATH_SDL

GUI_SUPPORT=yes

echo "$as_me:$LINENO: checking whether gui was asked" >&5
echo $ECHO_N "checking whether gui was asked...$ECHO_C" >&6

AC_ARG_ENABLE(gui,
  AC_HELP_STRING([--enable-gui], [enable GUI (default is yes)]),
  [ if test "$enableval" = "no"; then GUI_SUPPORT="no"; fi])

if test "x$GUI_SUPPORT" = "xyes"
then

  echo "$as_me:$LINENO: result: yes" >&5
  echo "${ECHO_T}yes" >&6

AM_PATH_GTK_2_0(2.0.0, HAVE_GTK="yes", HAVE_GTK="no")

if test "x$HAVE_GTK" = "xno"
then
  AM_CONDITIONAL(GTK,false)
else
  AM_CONDITIONAL(GTK,true)
  AC_DEFINE(GTK, 2, [defined if user have GTK2 installed])
fi

else
  AM_CONDITIONAL(GTK,false)

  echo "$as_me:$LINENO: result: no" >&5
  echo "${ECHO_T}no" >&6

fi

# Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS([fcntl.h limits.h stdlib.h string.h sys/ioctl.h sys/param.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_C_CONST
AC_C_INLINE
AC_HEADER_TIME

# Checks for library functions.
AC_FUNC_ALLOCA
AC_PROG_GCC_TRADITIONAL
# AC_FUNC_MALLOC
AC_FUNC_VPRINTF
AC_CHECK_FUNCS([atexit bzero dup2 gettimeofday memset mkdir select strchr strdup strrchr strstr])

# Check for size of types

AC_CHECK_SIZEOF([char], 1)
AC_CHECK_SIZEOF([short int], 2)
AC_CHECK_SIZEOF([int], 4)
AC_CHECK_SIZEOF([long int], 4)

# Check for netplay support request

echo "$as_me:$LINENO: checking whether netplay support was asked" >&5
echo $ECHO_N "checking whether netplay support was asked...            $ECHO_C" >&6

if test "x$HAVE_LIBSDL_NET" == "xyes"
then

AM_CONDITIONAL(NETPLAY, true)

NETPLAY=yes

AC_ARG_ENABLE(netplay,
  AC_HELP_STRING([--enable-netplay], [enable netplay support (default is yes)]),
  [ if test "$enableval" = "no"; then NETPLAY="no"; fi])

if test "$NETPLAY" = "yes"
then

  AC_DEFINE(ENABLE_NETPLAY, 1, [defined if user wants netplay support])

  AM_CONDITIONAL(NETPLAY, true)

  echo "$as_me:$LINENO: result: yes" >&5
  echo "${ECHO_T}yes" >&6

else # NETPLAY

  AM_CONDITIONAL(NETPLAY, false)

  echo "$as_me:$LINENO: result: no" >&5
  echo "${ECHO_T}no" >&6

fi

else # HAVE_LIBSDL_NET

AM_CONDITIONAL(NETPLAY, false)

  echo "$as_me:$LINENO: result: no (no SDL_net found)" >&5
  echo "${ECHO_T}no (no SDL_net found)" >&6

fi

# Check for kernel version request

echo "$as_me:$LINENO: checking which version of hugo kernel was asked" >&5
echo $ECHO_N "checking whether new kernel version was asked...         $ECHO_C" >&6

NEW_KERNEL=yes

AC_ARG_ENABLE(new-kernel,
  AC_HELP_STRING([--enable-new-kernel], [enable new kernel (default is yes)]),
	[ if test "$enableval" = "no"; then NEW_KERNEL="no"; fi])

if test "$NEW_KERNEL" = "yes"
then

	AC_DEFINE(KERNEL_DS, 1, [defined if user wants new kernel])

  echo "$as_me:$LINENO: result: yes" >&5
  echo "${ECHO_T}yes" >&6

else

  echo "$as_me:$LINENO: result: no" >&5
  echo "${ECHO_T}no" >&6	
  
fi

# Check for shared memory

echo "$as_me:$LINENO: checking shared memory openness" >&5
echo $ECHO_N "checking whether shared memory openness was asked...     $ECHO_C" >&6

SHARED_MEMORY=no

AC_ARG_ENABLE(shared-memory,
  AC_HELP_STRING([--enable-shared-memory], [enable shared memory openness (default is no)]),
	[ if test "$enableval" = "yes"; then SHARED_MEMORY="yes"; fi])

if test "$SHARED_MEMORY" = "yes"
then

	AC_DEFINE(SHARED_MEMORY, 1, [defined if user wants open memory openness])
	
  echo "$as_me:$LINENO: result: yes" >&5
  echo "${ECHO_T}yes" >&6	

else

  echo "$as_me:$LINENO: result: no" >&5
  echo "${ECHO_T}no" >&6	
  
fi

# Check for new gfx engine

echo "$as_me:$LINENO: checking new gfx engine" >&5
echo $ECHO_N "checking whether new gfx engine was asked...             $ECHO_C" >&6

NEW_GFX_ENGINE=yes

AC_ARG_ENABLE(new-gfx-engine,
  AC_HELP_STRING([--enable-new-gfx-engine], [use new gfx engine to render graphics (default is yes)]),
	[ if test "$enableval" = "no"; then NEW_GFX_ENGINE="no"; fi])

if test "$NEW_GFX_ENGINE" = "yes"
then

	AC_DEFINE(NEW_GFX_ENGINE, 1, [defined if user wants to use the new gfx engine])
	
  echo "$as_me:$LINENO: result: yes" >&5
  echo "${ECHO_T}yes" >&6	

else

  echo "$as_me:$LINENO: result: no" >&5
  echo "${ECHO_T}no" >&6	
  
fi

# Check for debug version

DEBUG_VERSION=no

echo "$as_me:$LINENO: checking for debug version" >&5
echo $ECHO_N "checking whether debug version was asked...              $ECHO_C" >&6

AC_ARG_ENABLE(final-release,
  AC_HELP_STRING([--enable-final-release], [enable strict logging (default is yes)]),
	[ if test "$enableval" = "no"; then DEBUG_VERSION="yes"; fi])
	
if test "$DEBUG_VERSION" = "no"
then
  AC_DEFINE(FINAL_RELEASE, 1, [defined if user wants a 'clean' binary ( = not for hugo developpers)])
	
	echo "$as_me:$LINENO: result: no" >&5
  echo "${ECHO_T}no" >&6	
else
  echo "$as_me:$LINENO: result: yes" >&5
  echo "${ECHO_T}yes" >&6	
fi

# Check for cd debugging

CD_DEBUG=no

echo "$as_me:$LINENO: checking for cd debug version" >&5
echo $ECHO_N "checking whether cd debug version was asked...           $ECHO_C" >&6

AC_ARG_ENABLE(cd-debug,
  AC_HELP_STRING([--enable-cd-debug], [enable CD subsystem debugging (default is no)]),
	[ if test "$enableval" = "yes"; then CD_DEBUG="yes"; fi])

if test "$CD_DEBUG" = "yes"
then
  AC_DEFINE(CD_DEBUG, 1, [for hugo developers working on the cd subsystem])
	echo "$as_me:$LINENO: result: yes" >&5
  echo "${ECHO_T}yes" >&6	
else
  echo "$as_me:$LINENO: result: no" >&5
  echo "${ECHO_T}no" >&6	
fi

# Check for sound debugging

SOUND_DEBUG=no

echo "$as_me:$LINENO: checking for sound debug version" >&5
echo $ECHO_N "checking whether sound debug version was asked...        $ECHO_C" >&6

AC_ARG_ENABLE(sound-debug,
  AC_HELP_STRING([--enable-sound-debug], [enable sound routine debugging (default is no)]),
	[ if test "$enableval" = "yes"; then SOUND_DEBUG="yes"; fi])

if test "$SOUND_DEBUG" = "yes"
then
  AC_DEFINE(SOUND_DEBUG, 1, [for hugo developers working on the cd subsystem])
	echo "$as_me:$LINENO: result: yes" >&5
  echo "${ECHO_T}yes" >&6	
else
  echo "$as_me:$LINENO: result: no" >&5
  echo "${ECHO_T}no" >&6	
fi

# Check for graphics debugging

GFX_DEBUG=no

echo "$as_me:$LINENO: checking for gfx debug version" >&5
echo $ECHO_N "checking whether gfx debug version was asked...          $ECHO_C" >&6

AC_ARG_ENABLE(gfx-debug,
  AC_HELP_STRING([--enable-gfx-debug], [enable graphics routine debugging (default is no)]),
	[ if test "$enableval" = "yes"; then GFX_DEBUG="yes"; fi])

if test "$GFX_DEBUG" = "yes"
then
  AC_DEFINE(GFX_DEBUG, 1, [for hugo developers working on the graphics subsystem])
	echo "$as_me:$LINENO: result: yes" >&5
  echo "${ECHO_T}yes" >&6	
else
  echo "$as_me:$LINENO: result: no" >&5
  echo "${ECHO_T}no" >&6	

fi

# Check for input debugging

INPUT_DEBUG=no

echo "$as_me:$LINENO: checking for input debug version" >&5
echo $ECHO_N "checking whether input debug version was asked...        $ECHO_C" >&6

AC_ARG_ENABLE(input-debug,
  AC_HELP_STRING([--enable-input-debug], [enable input routine debugging (default is no)]),
	[ if test "$enableval" = "yes"; then INPUT_DEBUG="yes"; fi])

if test "$INPUT_DEBUG" = "yes"
then
  AC_DEFINE(INPUT_DEBUG, 1, [for hugo developers working on the input subsystem])
	echo "$as_me:$LINENO: result: yes" >&5
  echo "${ECHO_T}yes" >&6	
else
  echo "$as_me:$LINENO: result: no" >&5
  echo "${ECHO_T}no" >&6	
fi

# Check for kernel debugging

KERNEL_DEBUG=no

echo "$as_me:$LINENO: checking for kernel debug version" >&5
echo $ECHO_N "checking whether kernel debug version was asked...       $ECHO_C" >&6

AC_ARG_ENABLE(kernel-debug,
  AC_HELP_STRING([--enable-kernel-debug], [enable hu6280 kernel debugging (default is no)]),
	[ if test "$enableval" = "yes"; then KERNEL_DEBUG="yes"; fi])

if test "$KERNEL_DEBUG" = "yes"
then
  AC_DEFINE(KERNEL_DEBUG, 1, [for hugo developers working on hu6280 emulation])
  echo "$as_me:$LINENO: result: yes" >&5
  echo "${ECHO_T}yes" >&6
else
  echo "$as_me:$LINENO: result: no" >&5
  echo "${ECHO_T}no" >&6	
fi

# Check for netplay debugging

NETPLAY_DEBUG=no

echo "$as_me:$LINENO: checking for netplay debug version" >&5
echo $ECHO_N "checking whether netplay debug version was asked...      $ECHO_C" >&6

AC_ARG_ENABLE(netplay-debug,
  AC_HELP_STRING([--enable-netplay-debug], [enable netplay debugging (default is no)]),
	[ if test "$enableval" = "yes"; then NETPLAY_DEBUG="yes"; fi])

if test "$NETPLAY_DEBUG" = "yes"
then
  AC_DEFINE(NETPLAY_DEBUG, 1, [for hugo developers working on netplay emulation])
  echo "$as_me:$LINENO: result: yes" >&5
  echo "${ECHO_T}yes" >&6
else
  echo "$as_me:$LINENO: result: no" >&5
  echo "${ECHO_T}no" >&6	
fi

# Check for bsd or gpl hardware cd support

BSD_CD_HARDWARE_SUPPORT=yes

echo "$as_me:$LINENO: checking for bsd pc engine cd version" >&5
echo $ECHO_N "checking whether bsd pc engine cd version was asked...   $ECHO_C" >&6

AC_ARG_ENABLE(bsd-pcecd,
	AC_HELP_STRING([--enable-bsd-pcecd], [enable modified bsd version of pce hardware cd support (default is yes)]),
	[ if test "$enableval" = "no"; then BSD_CD_HARDWARE_SUPPORT="no"; fi])

if test "$BSD_CD_HARDWARE_SUPPORT" = "yes"
then
	AC_DEFINE(BSD_CD_HARDWARE_SUPPORT, 1, [modified bsd pce cd hardware support (old one)])
	echo "$as_me:$LINENO: result: yes" >&5
  echo "${ECHO_T}yes" >&6
else
  echo "$as_me:$LINENO: result: no" >&5
  echo "${ECHO_T}no" >&6
fi

# Check if user wants to build with sdl

USE_SDL=yes

echo "$as_me:$LINENO: checking for SDL library version" >&5
echo $ECHO_N "checking whether SDL library version was asked...        $ECHO_C" >&6

AC_ARG_WITH(sdl,
  AC_HELP_STRING([--with-sdl], [uses sdl as library for input/output (default is yes)]),
	[ if test "$withval" = "no"; then USE_SDL="no"; fi])

if test "$USE_SDL" = "yes"
then
  AC_DEFINE(SDL, 1, [defined if user wants SDL as library])
	echo "$as_me:$LINENO: result: yes" >&5
  echo "${ECHO_T}yes" >&6
else
  echo "$as_me:$LINENO: result: no" >&5
  echo "${ECHO_T}no" >&6
fi

# Check for SDL_mixer
echo $ECHO_N "checking whether SDL_mixer library version was asked...  $ECHO_C" >&6
USE_SDL_mixer=no

AC_ARG_WITH(sdl_mixer,
  AC_HELP_STRING([--with-sdl-mixer], [uses sdl_mixer as library for audio input/output (default is no)]),
	[ if test "$withval" = "yes"; then USE_SDL_mixer="yes"; fi])

if test "$USE_SDL_mixer" = "yes"
then
  if test "$USE_SDL" = "yes"
  then
    AC_DEFINE(SDL_mixer, 1, [defined if user wants SDL_mixer as library])
    echo "$as_me:$LINENO: result: yes" >&5
    echo "${ECHO_T}yes" >&6
  else
    echo "$as_me:$LINENO: result: no (needs SDL)" >&5
    echo "${ECHO_T}no" >&6
  fi
else
  echo "$as_me:$LINENO: result: no" >&5
  echo "${ECHO_T}no" >&6
fi

#Checking for ogg/vorbis support in .hcd
#echo "$as_me:$LINENO: checking whether ogg/vorbis support in .hcd was asked" >&5
echo $ECHO_N "checking whether ogg/vorbis support in .hcd was asked... $ECHO_C" >&6
OGG_SUPPORT=no

AC_ARG_WITH(ogg-support,
  AC_HELP_STRING([--with-ogg-support], [enable ogg/vorbis support in hcd (default is no)]),
  [ if test "$withval" = "yes"; then OGG_SUPPORT="yes"; fi])

if test "$OGG_SUPPORT" = "yes"
then
  if test "$USE_SDL_mixer" = "yes"
  then
    AC_DEFINE(OGG_SUPPORT, 1, [defined if user wants ogg support in hcd])
    echo "$as_me:$LINENO: result: yes" >&5
    echo "${ECHO_T}yes" >&6
  else
    echo "$as_me:$LINENO: result: no (needs SDL_mixer)" >&5
    echo "${ECHO_T}no" >&6
  fi
else
  echo "$as_me:$LINENO: result: no" >&5
  echo "${ECHO_T}no" >&6
fi

# Mode for testing rom made to run with an offset of 0x68 for bank

TEST_RELOCATED_ROM=no

echo "$as_me:$LINENO: checking for test relocated rom version" >&5
echo $ECHO_N "checking whether test relocated rom version was asked... $ECHO_C" >&6

AC_ARG_ENABLE(test-relocated-rom,
  AC_HELP_STRING([--enable-test-relocated-rom], [prepares execution of patched rom for running in SCD ram (default is no)]),
	[ if test "$enableval" = "yes"; then TEST_RELOCATED_ROM="yes"; fi])

if test "$TEST_RELOCATED_ROM" = "yes"
then
  AC_DEFINE(TEST_ROM_RELOCATED, 1, [defined if rom are expected to be patched to run from bank 0x68])
	echo "$as_me:$LINENO: result: yes" >&5
  echo "${ECHO_T}yes. UNUSABLE FOR NORMAL GAMES." >&6
else
  echo "$as_me:$LINENO: result: no" >&5
  echo "${ECHO_T}no" >&6

fi

# Inlined accessors ? they're slightly faster but doens't work for AC games

INLINED_ACCESSORS=no

echo "$as_me:$LINENO: checking for inlined accessors version" >&5
echo $ECHO_N "checking whether inlined accessors version was asked...  $ECHO_C" >&6

AC_ARG_ENABLE(inlined-accessors,
  AC_HELP_STRING([--enable-inlined-accessors], [uses inlined accessors for memory (faster but not AC games compatible) (default is no)]),
	[ if test "$enableval" = "yes"; then INLINED_ACCESSORS="yes"; fi])

if test "$INLINED_ACCESSORS" = "yes"
then
  AC_DEFINE(INLINED_ACCESSORS, 1, [defined if inlined accessors should be used])
	echo "$as_me:$LINENO: result: yes" >&5
  echo "${ECHO_T}yes (AC games won't work properly)." >&6
else
  echo "$as_me:$LINENO: result: no" >&5
  echo "${ECHO_T}no" >&6	
fi

# Selecting machine / lib specific files

if test "$target_alias" = ""; then
  
	echo "$as_me:$LINENO: no target explicitely given, guessing" >&5
  echo $ECHO_N "no target explicitely given, guessing... $ECHO_C" >&6
  
  target_alias=`uname -m`-`uname -s`
	
  echo "$as_me:$LINENO: result: $target_alias" >&5
  echo "${ECHO_T}$target_alias" >&6	
		
fi

AM_CONDITIONAL(SDL_LINUX, false)
AM_CONDITIONAL(SDL_MIXER_LINUX, false)
AM_CONDITIONAL(ZE_HCD_OGG_SUPPORT, false)
AM_CONDITIONAL(SDL_NET_LINUX, false)
AM_CONDITIONAL(ALLEGRO_LINUX, false)

AM_CONDITIONAL(SDL_WIN32, false)
AM_CONDITIONAL(ALLEGRO_WIN32, false)

AM_CONDITIONAL(ALLEGRO_DJGPP, false)

AM_CONDITIONAL(SDL_FREEBSD, false)

AM_CONDITIONAL(SDL_SOLARIS, false)

case $target_alias in
   i386-mingw32msvc)
 	   echo "Microsoft Windows 32bits with mingw build enabled"
		 HUGO_TARGET_MACHINE="WIN32"

		 if test "$USE_SDL" = "yes"; then

			 CFLAGS="$CFLAGS `sdl-config --cflags`"
       LIBS="$LIBS `sdl-config --libs` -lakrip32"

		   AM_CONDITIONAL(SDL_WIN32, true)
		 else

			 HUGO_TARGET_LIBRARY="-DALLEGRO `allegro-config --cflags`"
			 HUGO_TARGET_LIBRARY_LD="`allegro-config --libs`"

		   AM_CONDITIONAL(ALLEGRO_WIN32, true)
		 fi
	 ;;
	 i386-djgpp)
	   echo "DJGPP build enabled"

		 HUGO_TARGET_MACHINE="DJGPP"
		 HUGO_TARGET_LIBRARY="-DALLEGRO"
		 HUGO_TARGET_LIBRARY_LD="-lalleg"

		 AM_CONDITIONAL(ALLEGRO_DJGPP, true)
	 ;;
	 *i?86-?inux*)
	   echo "Linux build enabled"

		 HUGO_TARGET_MACHINE="LINUX"

		 if test "$USE_SDL" = "yes"; then

 			 CFLAGS="$CFLAGS `sdl-config --cflags`"
			 LIBS="$LIBS `sdl-config --libs`"
			 AM_CONDITIONAL(SDL_LINUX, true)

			 if test "$USE_SDL_mixer" = "yes"; then
				LIBS="$LIBS -lSDL_mixer "
			 	AM_CONDITIONAL(SDL_MIXER_LINUX, true)
			 fi

			 if test "$OGG_SUPPORT" = "yes"; then
				LIBS="$LIBS -lvorbis -lvorbisfile"
			 	AM_CONDITIONAL(ZE_HCD_OGG_SUPPORT, true) # ZE_: needs to be processed after SDL_MIXER_LINUX...
			 fi

		 else

			 HUGO_TARGET_LIBRARY="-DALLEGRO `allegro-config --cflags`"
			 HUGO_TARGET_LIBRARY_LD="`allegro-config --libs`"
		    AM_CONDITIONAL(ALLEGRO_LINUX, true)

		 fi
	 ;;
	 i386-FreeBSD)
	  echo "FreeBSD build enabled"

		 	 HUGO_TARGET_MACHINE="FREEBSD"

 			 CFLAGS="$CFLAGS `sdl-config --cflags`"
       LIBS="$LIBS `sdl-config --libs`"

			AM_CONDITIONAL(SDL_FREEBSD, true)
	 ;;
	sun4u-SunOS)
	  echo "Solaris build enabled"

	HUGO_TARGET_MACHINE="SOLARIS"

	CFLAGS="$CFLAGS `sdl-config --cflags`"
	LIBS="$LIBS `sdl-config --libs`"

	AM_CONDITIONAL(SDL_SOLARIS, true) 
	;;
	*)
	   echo "No target specified, Please ask maintainer about target: $target_alias"
	 ;;
esac

dnl Set PACKAGE_DATA_DIR in config.h.
if test "x${datadir}" = 'x${prefix}/share'; then
  if test "x${prefix}" = "xNONE"; then
    AC_DEFINE_UNQUOTED(PACKAGE_DATA_DIR,"${ac_default_prefix}/share/hugo",[directory in which data are located])
  else
    AC_DEFINE_UNQUOTED(PACKAGE_DATA_DIR,"${prefix}/share/hugo")
  fi
else
  AC_DEFINE_UNQUOTED(PACKAGE_DATA_DIR,"${datadir}/hugo")
fi

AC_SUBST(HUGO_TARGET_MACHINE)
AC_SUBST(HUGO_TARGET_LIBRARY)
AC_SUBST(HUGO_TARGET_LIBRARY_LD)

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
