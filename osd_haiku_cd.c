#include "osd_haiku_cd.h"


// fd for open cd device
int cd_drive_handle = 0;


int osd_cd_init(char *device)
{
	char *device_buffer;

	MESSAGE_INFO("CDRom2: Opening physical CD Drive... '%s'\n", device);

	if (strcmp(device, "")) {
		device_buffer = device;
	} else {
		// Just a guess
		device_buffer = "/dev/disk/atapi/0/slave/raw";
	}

	cd_drive_handle = open(device_buffer, O_RDONLY | O_NONBLOCK);

	if (cd_drive_handle < 0) {
		MESSAGE_ERROR("CDRom2: Failed to open %s, errno = %lu\n",
			device_buffer, errno);
		return 1;
	}

	MESSAGE_INFO("CDRom2: Physical CD Drive %s opened successfully\n",
		device_buffer);

	return 0;
}


void osd_cd_stop_audio()
{
}


void osd_cd_close()
{
	osd_cd_stop_audio();
	close(cd_drive_handle);
}


void osd_cd_read(UChar *p, UInt32 sector)
{
	int retries = 0;
	char buf[128];

	TRACE("CDRom2: %s\n", __func__);

	while ((lseek(cd_drive_handle, 2048 * sector, SEEK_SET) < 0)
		&& (retries < 3)) {
		sprintf(buf, "osd_cd_read:lseek (sector=%d, retry=%d)", sector, retries);
		perror(buf);
		retries++;
	}

	while ((read(cd_drive_handle, p, 2048) < 0)
		&& (retries++ < 3)) {
		sprintf(buf, "osd_cd_read:read (sector=%d, retry=%d)", sector, retries);
		perror(buf);
	}
}


void osd_cd_subchannel_info(unsigned short offset)
{
	TRACE("CDRom2: %s\n", __func__);
}


void osd_cd_status(int *status)
{
	TRACE("CDRom2: %s\n", __func__);
	*status = 0;
}


void osd_cd_track_info(UChar track, int *min, int *sec, int *fra, int *control)
{
	TRACE("CDRom2: %s\n", __func__);
	*min = 0; *sec = 0; *fra = 0; *control = 0;

	scsi_toc toc;
	status_t result = ioctl(cd_drive_handle, B_SCSI_GET_TOC, &toc);

	if (result != B_OK) {
		MESSAGE_ERROR("CDRom2: %s, Error accessing CD Drive\n", __func__);
		return;
	}

	int16 trackcount = toc.toc_data[3] - toc.toc_data[2] + 1;

	if ((track + 1) < 1 || track > trackcount) {
		MESSAGE_ERROR("CDRom2: %s, Invalid track provided: %d of %d\n",
			__func__,
			track, trackcount);
		return;
	}

	TrackDescriptor *desc = (TrackDescriptor*)&(toc.toc_data[4]);

	int32 tracktime = (desc[track].min * 60) + desc[track].sec;
	tracktime -= (desc[track - 1].min * 60) + desc[track - 1].sec;

	*min = tracktime / 60;
	*sec = tracktime % 60;
}


void osd_cd_nb_tracks(int *first, int *last)
{
	scsi_toc toc;
	status_t result = ioctl(cd_drive_handle, B_SCSI_GET_TOC, &toc);

	if (result != B_OK) {
		MESSAGE_ERROR("CDRom2: %s, Error accessing CD Drive\n", __func__);
		*first = 0;
		*last = 0;
	} else {
		*first = 0;
		*last = toc.toc_data[3];
	}
}


void osd_cd_length(int *min, int *sec, int *fra)
{
	TRACE("CDRom2: %s\n", __func__);
	*min = 0; *sec = 0; *fra = 0;

	scsi_toc toc;
	status_t result = ioctl(cd_drive_handle, B_SCSI_GET_TOC, &toc);

	if (result != B_OK) {
		MESSAGE_ERROR("CDRom2: ioctl error on %s\n", __func__);
		return;
	}

	int16 trackcount = toc.toc_data[3] - toc.toc_data[2] + 1;
	TrackDescriptor *desc = (TrackDescriptor*)&(toc.toc_data[4]);

	*min = desc[trackcount].min;
	*sec = desc[trackcount].sec;
	*fra = desc[trackcount].frame;
}


void osd_cd_pause(void)
{
	TRACE("CDRom2: %s\n", __func__);
}


void osd_cd_resume(void)
{
	TRACE("CDRom2: %s\n", __func__);
}


void osd_cd_play_audio_track(UChar track)
{
	TRACE("CDRom2: %s\n", __func__);
	scsi_play_track playtrack;

	playtrack.start_track = track;
	playtrack.start_index = 1;
	playtrack.end_track = track;
	playtrack.end_index = 1;

	status_t result = ioctl(cd_drive_handle, B_SCSI_PLAY_TRACK, &playtrack);
	if (result != B_OK) {
		MESSAGE_ERROR("CDRom2: ioctl error, couldn't play track %d\n",
			track);
		return;
	}
}


void osd_cd_play_audio_range(UChar min_from, UChar sec_from, UChar fra_from,
	UChar min_to, UChar sec_to, UChar fra_to)
{
	TRACE("CDRom2: %s\n", __func__);
}
