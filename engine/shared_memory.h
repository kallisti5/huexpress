#ifndef INCLUDE_SHARED_MEMORY
#define INCLUDE_SHARED_MEMORY

#include "cleantyp.h"

#define VRAMSIZE           0x10000

#define PSG_DIRECT_ACCESS_BUFSIZE 1024

#define SHM_HANDLE       0x25679
#define SHM_ROM_HANDLE   0x25680

typedef union
{
#if defined(WORDS_BIGENDIAN)
  struct { UChar h,l; } B;
#else
  struct { UChar l,h; } B;
#endif
  UInt16 W;
} pair;

/* The structure containing all variables relatives to Input and Output */
typedef struct tagIO {
  /* VCE */
  pair VCE[0x200]; /* palette info */
  pair vce_reg;    /* currently selected color */
  UChar vce_ratch; /* temporary value to keep track of the first byte
                    * when setting a 16 bits value with two byte access
                    */
  /* VDC */
  pair VDC[32];    /* value of each VDC register */
  UInt16 vdc_inc;  /* VRAM pointer increment once accessed */
  UInt16 vdc_raster_count; /* unused as far as I know */
  UChar vdc_reg;   /* currently selected VDC register */
  UChar vdc_status; /* current VCD status (end of line, end of screen, ...) */
  UChar vdc_ratch; /* temporary value to keep track of the first byte
                    * when setting a 16 bits value with two byte access
                    */
  UChar vdc_satb;  /* boolean which keeps track of the need to copy
                    * the SATB from VRAM to internal SATB
                    */
  UChar vdc_pendvsync; /* unsure, set if a end of screen IRQ is waiting */
  Int32 bg_h;      /* number of tiles vertically in virtual screen */
  Int32 bg_w;      /* number of tiles horizontaly in virtual screen */
  Int32 screen_w;  /* size of real screen in pixels */
  Int32 screen_h;  /* size of real screen in pixels */
  Int32 scroll_y;
  Int32 minline;
  Int32 maxline;

  UInt16 vdc_min_display; // First scanline of active display
  UInt16 vdc_max_display; // Last scanline of active display

  /* joypad */
  UChar JOY[16];   /* value of pressed button/direct for each pad
                    * (why 16 ? 5 should be enough for everyone :)
                    */
  UChar joy_select; /* used to know what nibble we must return */
  UChar joy_counter; /* current addressed joypad */

  /* PSG */
  UChar PSG[6][8], wave[6][32];
  // PSG STRUCTURE
  // 0 : dda_out
  // 2 : freq (lo byte)  | In reality it's a divisor
  // 3 : freq (hi byte)  | 3.7 Mhz / freq => true snd freq
  // 4 : dda_ctrl
  //     000XXXXX
  //     ^^  ^
  //     ||  ch. volume
  //     ||
  //     |direct access (everything at byte 0)
  //     |
  //    enable
  // 5 : pan (left vol = hi nibble, right vol = low nibble)
  // 6 : wave ringbuffer index
  // 7 : noise data for channels 5 and 6

  UChar psg_ch,psg_volume,psg_lfo_freq,psg_lfo_ctrl;

  UChar psg_da_data[6][PSG_DIRECT_ACCESS_BUFSIZE];
  UInt16 psg_da_index[6], psg_da_count[6];
  boolean psg_channel_disabled[6];

  /* TIMER */
  UChar timer_reload,timer_start,timer_counter;

  /* IRQ */
  UChar irq_mask,irq_status;

  /* CDROM extention */
  SInt32 backup,adpcm_firstread;
  UChar cd_port_1800;
  UChar cd_port_1801;
  UChar cd_port_1802;
  UChar cd_port_1804;

  /* Adpcm related variables */
  pair adpcm_ptr;
  UInt16 adpcm_rptr,adpcm_wptr;
  UInt16 adpcm_dmaptr;
  UChar adpcm_rate;
  UInt32 adpcm_pptr; /* to know where to begin playing adpcm (in nibbles) */
  UInt32 adpcm_psize; /* to know how many 4-bit samples to play */

  /* Arcade Card variables */
  UInt32 ac_base[4];     /* base address for AC ram accessing */
  UInt16 ac_offset[4];   /* offset address for AC ram accessing */
  UInt16 ac_incr[4];     /* incrment value after read or write accordingly to the control bit */

  UChar  ac_control[4];  /* bit 7: unused
                          * bit 6: only $1AX6 hits will add offset to base
                          * bit 5 + bit 6: either hit to $1AX6 or $1AXA will add offset to base
                          * bit 4: auto increment offset if 0, and auto
                          *        increment base if 1
                          * bit 3: unknown
                          * bit 2: unknown
                          * bit 1: use offset address in the effective address
                          *   computation
                          * bit 0: apply autoincrement if set
                          */
  UInt32 ac_shift;
  UChar  ac_shiftbits;   /* number of bits to shift by */

/*        UChar  ac_unknown3; */
  UChar  ac_unknown4;

  /* Remanence latch */
  UChar io_buffer;

} IO;

typedef struct {
  UChar RAM[0x8000];
  UChar PCM[0x10000];
  UChar WRAM[0x2000];
  UChar VRAM[VRAMSIZE];

  UChar VRAM2[VRAMSIZE];
  UChar VRAMS[VRAMSIZE];
  UChar vchange[VRAMSIZE / 32];
  UChar vchanges[VRAMSIZE / 128];

  UChar cd_extra_mem[0x10000];
  UChar cd_extra_super_mem[0x30000];
  UChar ac_extra_mem[0x200000];
  UChar cd_sector_buffer[0x2000];

  UInt32 s_scanline;

  UInt16 SPRAM[64 * 4];
  UChar  Pal[512];

  UInt16 s_reg_pc;
  UChar  s_reg_a;
  UChar  s_reg_x;
  UChar  s_reg_y;
  UChar  s_reg_p;
  UChar  s_reg_s;

  UInt32 s_cyclecount;
  UInt32 s_cyclecountold;

  UInt32 s_cycles;

  SInt32 s_external_control_cpu;

  UChar  mmr[8];

  IO     s_io;

  UInt32 rom_shared_memory_size;

} struct_hard_pce;

#endif
