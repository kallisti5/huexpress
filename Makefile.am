bin_PROGRAMS = hugo

if NETPLAY

bin_PROGRAMS += hugod

hugod_SOURCES = hugod.c netplay.c

endif

hugo_SOURCES = pce.c hard_pce.c sprite.c h6280.c view_zp.c edit_ram.c debug.c format.c \
  subs_eagle.c cd.c hcd.c lsmp3.c sound.c mix.c followop.c dis.c optable.c \
  view_inf.c lang.c list_rom.c iniconfig.c trans_fx.c cheat.c gfx.c bp.c bios.c \
  hugo.c pcecd.c utils.c

if SDL_LINUX
hugo_SOURCES += osd_linux_cd.c osd_linux_snd.c osd_keyboard.c osd_sdl_gfx.c osd_linux_sdl_machine.c
endif

if ZLIB
hugo_SOURCES += unzip.c miniunz.c
endif

if GTK

hugo_SOURCES += support.c interface.c callbacks.c gtk_main.c
hugo_LDADD = @GTK_LIBS@

if NETPLAY
hugod_SOURCES += support.c interface-server.c callbacks-server.c gtk_main-server.c
hugod_LDADD = @GTK_LIBS@

endif NETPLAY

endif GTK

if NETPLAY
hugo_SOURCES += netplay.c
endif

if SDL_MIXER_LINUX
hugo_SOURCES += osd_linux_sdl_music.c
endif

if ZE_HCD_OGG_SUPPORT
hugo_SOURCES += ogglength.c
endif

if ALLEGRO_LINUX
hugo_SOURCES += osd_linux_cd.c osd_linux_snd.c osd_keyboard.c osd_linux_allegro_gfx.c osd_linux_allegro_machine.c
endif

if SDL_WIN32
hugo_SOURCES += osd_win_cd.c osd_win_snd.c osd_keyboard.c osd_sdl_gfx.c osd_win_sdl_machine.c
endif

if ALLEGRO_WIN32
hugo_SOURCES += osd_win_cd.c osd_win_snd.c osd_keyboard.c osd_win_allegro_gfx.c osd_win_allegro_machine.c
endif

if ALLEGRO_DJGPP
hugo_SOURCES += osd_dos_cd.c osd_dos_snd.c osd_keyboard.c osd_dos_gfx.c osd_dos_machine.c
endif

if SDL_FREEBSD
hugo_SOURCES += osd_freebsd_cd.c osd_linux_snd.c osd_keyboard.c osd_sdl_gfx.c osd_linux_sdl_machine.c 
endif

if SDL_SOLARIS
hugo_SOURCES += osd_solaris_cd.c osd_linux_snd.c osd_keyboard.c osd_sdl_gfx.c osd_unix_sdl_machine.c
endif

EXTRA_hugo_SOURCES = osd_dos_cd.c osd_dos_cd.h osd_dos_gfx.c osd_dos_gfx.h \
  osd_dos_machine.c osd_dos_machine.h \
	osd_linux_allegro_gfx.c osd_linux_allegro_gfx.h osd_linux_allegro_machine.c \
	osd_linux_allegro_machine.h osd_linux_cd.c osd_linux_cd.h \
	osd_linux_sdl_machine.c \
	osd_linux_sdl_machine.h osd_linux_snd.c osd_linux_snd.h osd_win_allegro_gfx.c \
	osd_win_allegro_gfx.h osd_win_allegro_machine.c osd_win_allegro_machine.h osd_win_cd.c \
	osd_win_cd.h osd_keyboard.c osd_keyboard.h osd_sdl_gfx.c osd_sdl_gfx.h \
	osd_win_sdl_machine.c osd_win_sdl_machine.h osd_win_snd.c osd_win_snd.h \
	pce.h sys_cd.h sys_dep.h sys_gfx.h sys_inp.h sys_misc.h sys_snd.h cleantyp.h hard_pce.h \
	cheat.h bios.h cd.h crc_ctl.h debug.h dis.h dis_cst.h dis_runtime.h edit_ram.h followop.h \
	lang.h hcd.h h6280.h list_rom.h menu.h mix.h optable.h format.h view_zp.h globals.h \
	defs.h interupt.h gui.h trans_fx.h sprite.h sound.h lsmp3.h libamp.h iso_ent.h bp.h \
	view_inf.h iniconfig.h interf.h gfx.h shared_memory.h \
	osd_freebsd_cd.c osd_freebsd_cd.h hugo.c hugo.h	support.c support.h callbacks.c callbacks.h \
	interface.c interface.h gtk_main.c gtk_main.h akrip32.h myaspi32.h manual.h manual_convert.pl \
	ogglength.c ogglength.h osd_linux_sdl_music.c osd_linux_sdl_music.h \
	unzip.c unzip.h miniunz.c miniunz.h pcecd.c utils.c utils.h pcecd.h osd_solaris_cd.h \
	osd_unix_sdl_machine.h osd_unix_sdl_machine.c osd_solaris_cd.c hugod.c hugod.h \
	netplay.c netplay.h interface-server.h interface-server.c callbacks-server.h \
	callbacks-server.c gtk_main-server.h gtk_main-server.c

AM_CFLAGS = @GTK_CFLAGS@ @CFLAGS@ -D@HUGO_TARGET_MACHINE@ @HUGO_TARGET_LIBRARY@

hugo_LDFLAGS = @HUGO_TARGET_LIBRARY_LD@
hugod_LDFLAGS = -lSDL_net

install-data-local:
	@$(NORMAL_INSTALL)
	if test -d $(srcdir)/pixmaps; then \
	  $(mkinstalldirs) $(DESTDIR)$(pkgdatadir)/pixmaps; \
	  for pixmap in $(srcdir)/pixmaps/*; do \
	    if test -f $$pixmap; then \
	      $(INSTALL_DATA) $$pixmap $(DESTDIR)$(pkgdatadir)/pixmaps; \
	    fi \
	  done \
	fi && \
	if test -d $(srcdir)/doc; then \
	  $(mkinstalldirs) $(DESTDIR)$(pkgdatadir)/doc; \
	  for doc in $(srcdir)/doc/*.{html,txt,css}; do \
	    if test -f $$doc; then \
	      $(INSTALL_DATA) $$doc $(DESTDIR)$(pkgdatadir)/doc; \
	    fi \
	  done \
	fi

uninstall-local:
	@$(NORMAL_UNINSTALL)
	rm -rf $(DESTDIR)$(pkgdatadir)/{pixmaps,doc};

dist-hook: doc
	if test -d pixmaps; then \
	  mkdir $(distdir)/pixmaps; \
	  for pixmap in pixmaps/*; do \
	    if test -f $$pixmap; then \
	      cp -p $$pixmap $(distdir)/pixmaps; \
	    fi \
	  done \
	fi && \
	if test -d extra_dev; then \
	  mkdir $(distdir)/extra_dev; \
	  for extra_dev in extra_dev/*; do \
	    if test -f $$extra_dev; then \
	      cp -p $$extra_dev $(distdir)/extra_dev; \
	    fi \
	  done \
	fi

manual.h : doc/quickstart.txt manual_convert.pl
	  ./manual_convert.pl > manual.h

gtk_main.o : gtk_main.c manual.h gtk_main.h

# Installation targets

WINE=wine
LYX=lyx
LATEX2HTML=latex2html
TIDY=tidy
UNIX2DOS=unix2dos
SED=sed

INNOSETUP_LOCATION=~/.wine/fake_windows/Program\ Files/Inno\ Setup\ 4/ISCC.exe
LATEX2HTML_FLAGS= -split 0 -local_icons -no_navigation -info 0
LYX_DOC=$(wildcard doc/*.lyx)
HTML_DOC=$(patsubst %.lyx,%.html,$(LYX_DOC))
TXT_DOC=$(patsubst %.lyx,%.txt,$(LYX_DOC))

EXTRA_DIST = setup.iss doc/hugo_manual.css doc/index.html doc/README.old.txt $(HTML_DOC) $(TXT_DOC) $(LYX_DOC)

.PHONY: doc html txt

Output/setup.exe: setup.iss hugo.exe hugod.exe doc
	$(UNIX2DOS) $<
	$(WINE) $(INNOSETUP_LOCATION) $<

doc: $(AVAILABLE_DOC_TARGETS)

if HAVE_TOOLS_FOR_HTML_DOC
html: $(HTML_DOC)
%.html: %.tex
	test -d /tmp/latex2html.tmp || mkdir /tmp/latex2html.tmp
	$(LATEX2HTML) $(LATEX2HTML_FLAGS) -dir /tmp/latex2html.tmp `test -f '$<' || echo '$(srcdir)/'`$<
	test -d $(@D) || mkdir $(@D)
	$(SED) s/$(patsubst %.tex,%.css,$(<F))/hugo_manual.css/ $(patsubst %.tex,%.html,/tmp/latex2html.tmp/$(<F)) > $@
	-$(TIDY) -im $@
endif

if HAVE_TOOLS_FOR_TXT_DOC
txt: $(TXT_DOC)
%.txt: %.lyx
	test -d $(@D) || mkdir $(@D)
	LANG=C $(LYX) -e text `test -f '$<' || echo '$(srcdir)/'`$<
endif

%.tex: %.lyx
	test -d $(@D) || mkdir $(@D)
	$(LYX) -e latex `test -f '$<' || echo '$(srcdir)/'`$<
