#include "osd_freebsd_cd.h"

int osd_cd_init(char *device)
{
}


void osd_cd_stop_audio()
{
}


void osd_cd_close()
{
}


void osd_cd_read(UChar *p, UInt32 sector)
{
}

extern unsigned char binbcd[];

void osd_cd_subchannel_info(unsigned short offset)
{
}


void osd_cd_status(int *status)
{
}


void osd_cd_track_info(UChar track, int *min, int *sec, int *fra, int *control)
{
}


void osd_cd_nb_tracks(int *first, int *last)
{
}


void osd_cd_length(int *min, int *sec, int *fra)
{
}


void osd_cd_pause(void)
{
}


void osd_cd_resume(void)
{
}


/* TODO : check for last track asked */
void osd_cd_play_audio_track(UChar track)
{
}


void osd_cd_play_audio_range(UChar min_from, UChar sec_from, UChar fra_from,
                             UChar min_to, UChar sec_to, UChar fra_to)
{
}
