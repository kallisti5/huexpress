#ifndef _DJGPP_INCLUDE_CD_H
#define _DJGPP_INCLUDE_CD_H

#define COOKED  0
#define RAW     1

#define MSF     0
#define REDBOOK 1

// variables are quite self explanatory
extern int			cdda_first_drive;
extern int			cdda_nb_of_drives;
extern int			cdda_current_drive;
extern int			cdda_current_track;
extern int			cdda_playing;
extern int			cdda_min_track;
extern int			cdda_max_track;
extern int			cdda_disk_length;

extern char	global_error[80];

int cdda_init();
// initialize the cd rom driver

int cdda_play(int track);
// play an audio track

void cdda_stop();
// stop the current playing

void cdda_shutdown();
// for now, just stop the playing

void cdda_loop_check();
// seems to must be called each seconde if you want audio tracks to be
// played again when finished

void cdda_track_info(unsigned char *result, int track);
// return info on the given track, result is 7-bytes long

void cdda_read_sector(unsigned char* p,unsigned long nb_sect,
                      unsigned char mode_read, unsigned char mode_addr);

void cdda_cooked_prefech_read_sector_redbook(unsigned long nb_sect);

void cdda_cooked_prefech_read_sector_msf(unsigned long nb_sect);

void cdda_dos_cooked_read_sector_lba(unsigned char* p, unsigned long nb_sect);

int	cdda_play_sectors(int begin_sect, int length);

//-- Fonctions de conversion -------------------------------------------------

unsigned Time2Frame(int min, int sec, int frame);

unsigned Time2HSG(int min, int sec, int frame);

unsigned Time2Redbook(int min, int sec, int frame);

void Frame2Time(unsigned frame,
                int *Min,
                int *Sec,
                int *Fra);

void Redbook2Time(unsigned redbook,
                  int* Min,
                  int* Sec,
                  int* Fra);

void HSG2Time(unsigned hsg,
              int *Min,
              int *Sec,
              int *Fra);

unsigned Redbook2HSG(unsigned redbook);
unsigned HSG2Redbook(unsigned HSG);

#endif
