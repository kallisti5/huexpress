MAIN_SRCS = \
	src/huexpress.c \
	src/PCEngine.c \
	src/iniconfig.c \
	src/utils.c \
	src/view_inf.c \
	src/view_zp.c \
	src/zipmgr.c \

SDL_SRCS = \
	src/osd_sdl_machine.c \
	src/osd_sdl_snd.c \
	src/osd_sdl_music.c \
	src/osd_sdl_gfx.c \

ENGINE_SRCS = \
	src/engine/bios.c \
	src/engine/bp.c \
	src/engine/cd.c \
	src/engine/cheat.c \
	src/engine/debug.c \
	src/engine/dis.c \
	src/engine/edit_ram.c \
	src/engine/followop.c \
	src/engine/format.c \
	src/engine/gfx.c \
	src/engine/h6280.c \
	src/engine/hard_pce.c \
	src/engine/hcd.c \
	src/engine/lsmp3.c \
	src/engine/mix.c \
	src/engine/ogglength.c \
	src/engine/optable.c \
	src/engine/pce.c \
	src/engine/pcecd.c \
	src/engine/romdb.c \
	src/engine/sound.c \
	src/engine/sprite.c \
	src/engine/subs_eagle.c \
	src/engine/trans_fx.c \


# 'posix', 'linux', 'freebsd'
PLATFORM_SRCS = \
	src/osd_linux_cd.c \
	src/osd_keyboard.c \

PLATFORM_SRCS_DARWIN = \
	src/osd_dummy_cd.c \
	src/osd_keyboard.c \

PLATFORM_SRCS_HAIKU = \
	src/osd_haiku_cd.c \
	src/osd_keyboard.c \

SRCS = $(MAIN_SRCS) $(SDL_SRCS) $(ENGINE_SRCS) $(PLATFORM_SRCS)
OBJS = $(SRCS:%.c=%.o)

PKG_CONFIG ?= pkg-config

SDL2_FLAGS := $(shell $(PKG_CONFIG) --cflags --libs sdl2)
SDL2M_FLAGS := $(shell $(PKG_CONFIG) --cflags --libs SDL2_mixer)
VF_FLAGS := $(shell $(PKG_CONFIG) --cflags --libs vorbisfile)
LZ_FLAGS := $(shell $(PKG_CONFIG) --cflags --libs --static libzip)

REQ_FLAGS := $(SDL2_FLAGS) $(SDL2M_FLAGS) $(VF_FLAGS) $(LZ_FLAGS)

-include config.mak

CPPFLAGS += -Isrc/includes -Isrc/engine $(REQ_FLAGS) \
	-DVERSION_MAJOR=3 -DVERSION_MINOR=0 -DVERSION_UPDATE=4

all: huexpress hucrc

huexpress : $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(REQ_FLAGS) -lGL $(LDFLAGS)

hucrc: src/hucrc.c src/utils.c src/engine/romdb.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -o $@ $^

clean:
	rm -f $(OBJS) huexpress hucrc

.PHONY: all clean
