#include "osd_haiku_cd.h"

int osd_cd_init(char *device)
{
	return 1;
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

void osd_cd_subchannel_info(unsigned short offset)
{
}

void osd_cd_status(int *status)
{
	*status = 0;
}

void osd_cd_track_info(UChar track, int *min, int *sec, int *fra, int *control)
{
	*min = 0; *sec = 0; *fra = 0; *control = 0;
}

void osd_cd_nb_tracks(int *first, int *last)
{
	*first = 0; *last = 0;
}

void osd_cd_length(int *min, int *sec, int *fra)
{
	*min = 0; *sec = 0; *fra = 0;
}

void osd_cd_pause(void)
{
}

void osd_cd_resume(void)
{
}

void osd_cd_play_audio_track(UChar track)
{
}

void osd_cd_play_audio_range(UChar min_from, UChar sec_from, UChar fra_from,
                             UChar min_to, UChar sec_to, UChar fra_to)
{
}
