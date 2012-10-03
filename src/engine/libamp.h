/* libamp header */

#ifdef ALLEGRO_H

/* test for Allegro version */
#if ALLEGRO_VERSION<3
/* we need at least 3.0 to support audio streams */
#error LibAmp requires Allegro 3.0
#endif
/* we have Allegro 3.x */
/* but pure 3.0 supports only mono streams, so we have to use
   two streams, panned hard left and hard right respectively */
#define AMP_ALLEGRO30
#ifdef ALLEGRO_DATE
/* ALLEGRO_DATE is defined, so we have 3.0+WIP */
/* the WIP changed the API slightly, so we need to undefine
   AMP_ALLEGRO30 to use the new API */
#undef AMP_ALLEGRO30
/* the new API also enables the use of AMP_MIXSTEREO */
/* only define if your programs can use it (programs that use
   amp_play_left and amp_play_right to show scopes will need
   to be modified for the new stereo mode) */
#define AMP_MIXSTEREO
#endif

#endif

extern int amp_bitrate,amp_samprat;
extern int amp_mpg_ver,amp_layer,amp_stereo,amp_pollsize;
extern int amp_playing,amp_loaded,amp_reverse_phase;
extern int amp_dec_frame,amp_dec_time;
extern int amp_frame,amp_time;

extern unsigned short*amp_buf_left,*amp_buf_right;
extern int amp_buf_len;

extern unsigned short*amp_play_left,*amp_play_right;
extern int amp_play_len;

int install_amp(void);
int load_amp(char*filename,int loop);
int poll_amp(void);
int run_amp(void);
int replay_amp(void);
int seek_amp_abs(int frame);
int seek_amp_rel(int framecnt);
int unload_amp(void);

