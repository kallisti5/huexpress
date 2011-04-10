#ifndef _INCLUDE_LANG_H
#define _INCLUDE_LANG_H

#define  NB_LANG 10
#define  NB_MESSAGES 53

extern char* MESSAGE[NB_LANG][NB_MESSAGES];
// Messages to display during emulation

#define  all_frame    0
#define  frame_skip   1
#define  full_speed   2
#define  syncro_60hz  3
#define  screen_shot  4
#define  game_save    5
#define  game_load    6
#define  dump_on      7
#define  dump_off     8
#define  unknown_rom  9
#define  help_debug   10
#define  help_debug_size   10
#define  shut_down    20
#define  init_allegro 21
#define	failed_init  22
#define	clear_buffer 23
#define  init_sound   24
#define  cant_set_gmode 25
#define  no_mem         26
#define  autodetect_mode 27
#define  no_device_found 28
#define  device_found    29
#define  audio_init_failed 30
#define  audio_inited     31
#define  byte_set         32
#define  search_failed    33
#define  found_at         34
#define	still_need_search 35
#define  alloc_spr    36
#define  played       37
#define  unknown_contact_me    38
#define  C_ya          39
#define	time_elapsed  40
#define  frame_per_sec 41
#define	reading_dir   42
#define  joy_detected  43
#define  joy_no_detected 44
#define  eagle_asked     45
#define  eagle_mode_not_init 46
#define  translated_by   47
#define  iso_file_not_found 48
#define  volume_set_to 49
#define  freq_set_to   50
#define  video_dump_on 51

#endif
