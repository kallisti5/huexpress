#include "osd_cd.h"

/*
 *  Mscdex part
 */

// Il s'agit d'une bidouille infame pour que DJGPP n'aligne pas les membres
// unsigned short des structures sur des offsets pairs. (Ce qui bien sur fait
// tout foirer et que j'ai mis deux jours a decouvrir!!)
#define DW(id) (*((unsigned short *)(&id)))
#define DD(id) (*((unsigned int *)(&id)))

#undef BYTE
#undef WORD
#undef DWORD

typedef unsigned char	BYTE;
typedef struct {
	BYTE	b1;
	BYTE	b2;
} WORD;

typedef struct {
	BYTE	b1;
	BYTE	b2;
	BYTE	b3;
	BYTE	b4;
} DWORD;


//-- Structures --------------------------------------------------------------
typedef struct {
	BYTE	len1;
	BYTE 	unit;
	BYTE	command;
	WORD	status;
	BYTE	reserved[8];
	BYTE	descriptor;
	WORD	adr_off;
	WORD	adr_seg;
	WORD 	len2;
	WORD 	secnum;
	WORD	ptr_off;
	WORD	ptr_seg;
} IOCTLI;

typedef struct {
	BYTE	control;
	BYTE	lowest;
	BYTE	highest;
	DWORD	total;
} DISKINFO;

typedef struct {
	BYTE	control;
	BYTE	track;
	DWORD	loc;
	BYTE	info;
} TRACKINFO;

typedef struct {
	BYTE	len;
	BYTE 	unit;
	BYTE	command;
	WORD	status;
	BYTE	reserved[8];
	BYTE 	mode;
	DWORD 	loc;
	DWORD 	secnum;
} PLAYREQ;

typedef struct {
	BYTE	len;
	BYTE 	unit;
	BYTE	command;
	WORD	status;
	BYTE	reserved[8];
	BYTE 	mode_addr;
 	WORD	ptr_off;
	WORD	ptr_seg;
   WORD  nb_to_read;
	DWORD secnum;
   BYTE  mode_lect;
   BYTE  interleave_size;
   BYTE  interleave_skip;
} READREQ;

typedef struct {
	BYTE	len;
	BYTE 	unit;
	BYTE	command;
	WORD	status;
	BYTE	reserved[8];
} STOPREQ;

typedef struct {
	BYTE	control;
	BYTE	mode;
	DWORD	loc;
} HEADINFO;

//-- Imported Variables ------------------------------------------------------
char	global_error[80];

//-- Private Variables -------------------------------------------------------
static __dpmi_regs	_regs;
static int			cdda_track_start;
static int			cdda_track_end;
static int			cdda_loop_counter;

//-- Public Variables --------------------------------------------------------
int			cdda_min_track;
int			cdda_max_track;
int			cdda_first_drive;
int			cdda_nb_of_drives;
int			cdda_current_drive;
int			cdda_current_track;
int			cdda_playing;
int			cdda_disk_length;

void	osd_cd_play_audio_track_mscdex(UChar track);
int	osd_cd_init_mscdex(char* device_name);
void    osd_cd_length_mscdex(int* min,
                   	  int* sec,
                   	  int* fra);
void	osd_cd_stop_audio_mscdex(void);
void	osd_cd_play_audio_range_mscdex(int min_from,
                                int sec_from,
                                int fra_from,
                                int min_to,
                                int sec_to,
                                int fra_to);
void osd_cd_track_info_mscdex(UChar track,
			  int* min,
			  int* sec,
			  int* fra,
			  int* control);
void osd_cd_read_mscdex(unsigned char* p,unsigned long nb_sect);
void osd_cd_nb_tracks_mscdex(int* first,
                             int* last);
void	osd_cd_close_mscdex(void);

/*
 * Aspi part
 */

static int TB;
static int DB;
#define DOSS	_go32_info_block.selector_for_linear_memory
#define INT	r.x.sp = r.x.ss = r.x.flags = 0, _go32_dpmi_simulate_int
#define	__dpmi_regs _go32_dpmi_registers
#define GTB (_go32_info_block.linear_address_of_transfer_buffer & 0xfffff)

union {
  SRB_HAInquiry hai;
  SRB_GDEVBlock gdb;
  SRB_ExecSCSICmd srb;
  SRB_Abort ab;
  SRB_BusDeviceReset res;
} SRB_Everything;

static aspi_fd = -1;
static int aspi_entry_seg;
static int aspi_entry_ofs;
static _go32_dpmi_seginfo dos_buf;

long aspi_buffer_length = 128 * 1024;
char aspi_sense[SENSE_LEN];

static int dat, aspi_stat;
static unsigned char cdb[10];
static unsigned long block_size = 20 * 512;


static void
aspi_entry(void *srb, int srblen)
{
  __dpmi_regs r;
  int i;
  int sp = GTB + 4090;
/*  printf("%x = %x + 4090\n", sp, GTB);*/
  dosmemput(srb, srblen, TB);
/*  printf("go32's TB at 0x%x 0x%x\n", _go32_info_block.linear_address_of_transfer_buffer, GTB); */
/*  printf("entry: SRB at 0x%lx (dos TB at 0x%x)\n", srb, TB); */
  memset(&r, 0, sizeof(r));
  r.x.cs = aspi_entry_seg;
  r.x.ip = aspi_entry_ofs;
  sp -= 2; _farpokew(DOSS, sp, TB >> 4);
  sp -= 2; _farpokew(DOSS, sp, TB & 15);
  r.x.ss =  GTB >> 4;
  r.x.sp = (sp -  r.x.ss*16);
/*  printf("entry: go %04x:%04x, stack %04x:%04x (now 0x%x)\n",
	 r.x.cs, r.x.ip, r.x.ss, r.x.sp, sp); */
#if 0
  printf("stack[0x%x]: ", r.x.ss * 16 + r.x.sp);
  for (i=0; i<37; i++)
    printf(" %02x", _farpeekb(DOSS, r.x.ss * 16 + r.x.sp + i));
  printf("\n");
#endif
  _go32_dpmi_simulate_fcall(&r);
  while (_farpeekb(DOSS, TB+1) == 0);
  dosmemget(TB, srblen, srb);
}

int
aspi_init(void)
{
  __dpmi_regs r;
  SRB_HAInquiry hai;

  setbuf(stdout, 0);
  dos_buf.size = (aspi_buffer_length/16) + (sizeof(SRB_Everything)+15) / 16;
  if (_go32_dpmi_allocate_dos_memory(&dos_buf))
  {
   /*
    * fprintf(stderr, "ASPI Error: Not able to allocate %d Kb buffer\n", aspi_buffer_length / 1024);
    */
    aspi_fd = -1;
    return -1;
  }
  TB = dos_buf.rm_segment * 16;
  DB = TB + (sizeof(SRB_Everything) + 15) & ~15;
  
  aspi_fd = open("SCSIMGR$", O_RDONLY);
  if (aspi_fd < 0)
  {
    perror("SCSIMGR$");
    aspi_fd = -1;
    return -1;
  }

  r.x.ax = 0x4402;
  r.x.bx = aspi_fd;
  r.x.cx = 4;
  r.x.ds = TB >> 4;
  r.x.dx = TB & 15;
  INT(0x21, &r);
  aspi_entry_ofs = _farpeekw(DOSS, TB);
  aspi_entry_seg = _farpeekw(DOSS, TB+2);
  close(aspi_fd);
  aspi_fd = 0;

  memset(&hai, 0, sizeof(hai));
  hai.SRB_Cmd = SC_HA_INQUIRY;
  aspi_entry(&hai, sizeof(hai));

  return hai.HA_Count;
}

int
aspi_close(void)
{
  if (aspi_fd)
    return;
  _go32_dpmi_free_dos_memory(&dos_buf);
  aspi_fd = -1;
  return 0;
}

int
aspi_device_type(int aspi_id)
{
  SRB_GDEVBlock gd;
  if (aspi_fd)
    return;
  memset(&gd, 0, sizeof(gd));
  gd.SRB_Cmd = SC_GET_DEV_TYPE;
  gd.SRB_HaId = ASPI_ID2HOSTAD(aspi_id);
  gd.SRB_Target = ASPI_ID2TARGET(aspi_id);
  gd.SRB_Lun = ASPI_ID2LUN(aspi_id);
  aspi_entry(&gd, sizeof(gd));
  return (gd.SRB_Status == SS_COMP) ? gd.SRB_DeviceType : -1;
}

int
aspi_exec(int id, void *buf, int buflen, int rw, char *cdb, int cdblen)
{
  char *cptr;
  SRB_ExecSCSICmd srb;

  if (aspi_fd)
    return;

  memset(&srb, 0, sizeof(srb));
  srb.SRB_Cmd = SC_EXEC_SCSI_CMD;
  srb.SRB_Status = 0;
  srb.SRB_HaId = ASPI_ID2HOSTAD(id);
  srb.SRB_Flags = SRB_DIR_SCSI;
  srb.SRB_Target = ASPI_ID2TARGET(id);
  srb.SRB_Lun = ASPI_ID2LUN(id);
  srb.SRB_BufLen = buflen;
  srb.SRB_SenseLen = SENSE_LEN;
  srb.SRB_BufPointerOfs = DB & 15;
  srb.SRB_BufPointerSeg = DB >> 4;
  srb.SRB_CDBLen = cdblen;
  memcpy(srb.cptr, cdb, cdblen);
  if (rw & ASPI_RW_WRITE)
    dosmemput(buf, buflen, DB);
  aspi_entry(&srb, sizeof(srb));
  if (rw & ASPI_RW_READ)
    dosmemget(DB, buflen, buf);
  memcpy(aspi_sense, srb.cptr+cdblen, SENSE_LEN);
  return srb.SRB_Status;
}

void aspi_set_blocksize(unsigned long new_block_size)

{
  unsigned char buffer[12];
  block_size = new_block_size;
  memset(cdb, 0, 6);
  cdb[0] = 0x15;
  cdb[4] = 0x0c;
  memset(buffer, 0, sizeof(buffer));
  buffer[2] = 0x10;
  buffer[3] = 8;
  buffer[9] = (block_size) >> 16;
  buffer[10] = (block_size) >> 8;
  buffer[11] = (block_size);
  aspi_stat = aspi_exec(dat, buffer, 12, ASPI_RW_WRITE, cdb, 6);
}


int	osd_cd_init_aspi(char* device_name);
void	osd_cd_close_aspi();
void 	osd_cd_nb_tracks_aspi(int* first,
                           int* last);
void    osd_cd_track_info_aspi(UChar track,
                            int* min,
                            int* sec,
                            int* fra,
                            int* control);
void    osd_cd_read_aspi(unsigned char *buffer, unsigned long sector);
void	osd_cd_play_audio_range_aspi(int min_from,
                                int sec_from,
                                int fra_from,
                                int min_to,
                                int sec_to,
                                int fra_to);
void	osd_cd_play_audio_track_aspi(UChar track);
void	osd_cd_stop_audio_aspi(void);
 /*
  * Generic part
  */

osd_cd_driver_type osd_cd_driver = mscdex_driver;

//----------------------------------------------------------------------------
int	osd_cd_init(char* device_name)
{
 switch (osd_cd_driver)
   {
    case mscdex_driver:
         return osd_cd_init_mscdex(device_name);
    case aspi_driver:
         return osd_cd_init_aspi(device_name);
    default:
         return 0;
   }
}
//----------------------------------------------------------------------------
int	osd_cd_init_aspi(char* device_name)
{
  int nb_device = atoi(device_name);
  int nh = aspi_init();

  if (nh == -1)
    return 1;

  if (!nb_device) /* if asked to use the 0th device, set it to 1 */
    nb_device = 1;

  for (dat=0; dat<64*nh; dat++)
  {
    aspi_stat = aspi_device_type(dat);
    if (aspi_stat == -1)
      continue;
    if (aspi_stat == DTYPE_CROM) /* Check for cdrom drive */
    {
      Log("dos/osd_cd.c : detected cdrom device number %d at scsi(%d:%d:%d)\n",
             nb_device,
	     ASPI_ID2HOSTAD(dat),
	     ASPI_ID2TARGET(dat),
	     ASPI_ID2LUN(dat));

      nb_device --;

      if (!nb_device)
        {
          aspi_set_blocksize(2048);
          return 0;
        }
    }
  }

 return 1;
 }
//----------------------------------------------------------------------------
int	osd_cd_init_mscdex(char* device_name)
{
	IOCTLI 		cmd;
	DISKINFO	di;

        if (strcmp(device_name,""))
          cdda_current_drive = toupper(device_name[0])-'A';
        else
          cdda_current_drive = 0;

	strcpy(global_error, "");

        Log("dos/osd_cd.c : drive number %d (%c) is used for mscdex init\n",
            cdda_current_drive,
            'A' + cdda_current_drive);

	cdda_min_track = cdda_max_track = 0;
	cdda_current_track = 0;
	cdda_playing = 0;
	cdda_loop_counter = 0;

	memset(&_regs, 0, sizeof(_regs));
	_regs.d.eax = 0x1500;
	_regs.d.ebx = 0;

	if (__dpmi_int(0x2f, &_regs) == 0) {

          	Log("dos/osd_cd.c : valid dpmi int called\n");

		cdda_first_drive = _regs.d.ecx;
		cdda_nb_of_drives = _regs.d.ebx;
		
		if ((cdda_current_drive<cdda_first_drive)||
		(cdda_current_drive>(cdda_first_drive+cdda_nb_of_drives))) {
			if (cdda_current_drive!=-1)
				strcpy(global_error,
					"CDAUDIO: WARNING - Invalid drive override!");
			cdda_current_drive = cdda_first_drive;
		}
		
		cmd.len1 = sizeof(IOCTLI);
		cmd.unit = 0;
		cmd.command = 3;
		cmd.descriptor = 0;
		DW(cmd.adr_seg) = (__tb>>4);
		DW(cmd.adr_off) = sizeof(IOCTLI);
		DW(cmd.len2) = 7;
		DW(cmd.secnum) = 0;
		DW(cmd.ptr_seg) = 0;
		DW(cmd.ptr_off) = 0;
		di.control = 10;
	
		dosmemput(&cmd, sizeof(IOCTLI), __tb);
		dosmemput(&di, sizeof(DISKINFO), (__tb + sizeof(IOCTLI)));
		
		memset(&_regs, 0, sizeof(_regs));
		_regs.x.es = _regs.x.ds = _regs.x.cs = (__tb>>4);
		_regs.x.bx = 0;
		_regs.x.cx = cdda_current_drive;
		_regs.x.ax = 0x1510;
		__dpmi_int(0x2f, &_regs);
	
		dosmemget(__tb, sizeof(IOCTLI), &cmd);
		dosmemget((__tb + sizeof(IOCTLI)), sizeof(DISKINFO), &di);

		if (DW(cmd.status)&0x8000) {
			strcpy(global_error, "CDAUDIO - FATAL: No CD in drive!");
                        Log("dos/osd_cd.c : No cd in drive\n");
			return 1;
		}

		cdda_min_track = di.lowest;
		cdda_max_track = di.highest;
		cdda_disk_length = DD(di.total);

		if (global_error[0]==0)
			strcpy(global_error, "CDAUDIO: Initialization OK!");

		return 0;
	}
	strcpy(global_error,
		"CDAUDIO: FATAL - No CD-ROM driver was found!");
	return	1;
}
//----------------------------------------------------------------------------
void	osd_cd_play_audio_track(UChar track)
{
 switch (osd_cd_driver)
   {
    case mscdex_driver:
         osd_cd_play_audio_track_mscdex(track);
         break;
    case aspi_driver:
         osd_cd_play_audio_track_aspi(track);
         break;

    default:
   }
}
//----------------------------------------------------------------------------
void	osd_cd_play_audio_track_aspi(UChar track)
{
 /*
  unsigned char *sense;
  memset(cdb, 0, 10);

  cdb[0] = SCSI_PLAYA_TKIN;
  cdb[4] = track;
  cdb[5] = 0;
  cdb[7] = track + 1;
  cdb[8] = 0;

  aspi_stat = aspi_exec(dat, NULL, block_size, 0, cdb, 10);
 */
 /* This way of doing isn't right, please tell me if you know */

 int m1, s1, f1, m2, s2, f2, dum;
 osd_cd_track_info_aspi(track,
                   &m1,
                   &s1,
                   &f1,
                   &dum);
 osd_cd_track_info_aspi(track + 1,
                   &m2,
                   &s2,
                   &f2,
                   &dum);

 osd_cd_play_audio_range_aspi(m1,
                        s1,
                        f1,
                        m2,
                        s2,
                        f2);

  /* We may want to deal with error there */
  /*
  check_sense();
  if (aspi_sense[2] & SENSE_FILEMRK)
    return;
  */
  return;
}

//----------------------------------------------------------------------------
void	osd_cd_play_audio_track_mscdex(UChar track)
{
	IOCTLI		cmd;
	TRACKINFO	trk;
	PLAYREQ		prq;
	char		h, m, s;
	char		h2, m2, s2;

	if ((track<cdda_min_track)||(track>cdda_max_track))
		return;

	cmd.len1 = sizeof(IOCTLI);
	cmd.unit = 0;
	cmd.command = 3;
	cmd.descriptor=0;
	DW(cmd.adr_seg) = (__tb>>4);
	DW(cmd.adr_off) = sizeof(IOCTLI);
	DW(cmd.len2) = 7;
	DW(cmd.secnum) = 0;
	DW(cmd.ptr_seg) = 0;
	DW(cmd.ptr_off) = 0;
	trk.control = 11;
	trk.track = track;

	dosmemput(&cmd, sizeof(IOCTLI), __tb);
	dosmemput(&trk, sizeof(TRACKINFO), (__tb + sizeof(IOCTLI)));
	
	memset(&_regs, 0, sizeof(_regs));
	_regs.x.es = _regs.x.ds = _regs.x.cs = (__tb>>4);
	_regs.x.bx = 0;
	_regs.x.cx = cdda_current_drive;
	_regs.x.ax = 0x1510;
	__dpmi_int(0x2f, &_regs);

	dosmemget(__tb, sizeof(IOCTLI), &cmd);
	dosmemget((__tb + sizeof(IOCTLI)), sizeof(TRACKINFO), &trk);

	if (DW(cmd.status)&0x8000)
		return;
		
	cdda_track_start = DD(trk.loc);

        // TEST
        // printf("Track %d begins at 0x%X\n",track,cdda_track_start);
        // TEST

	if (track==cdda_max_track)
		cdda_track_end = cdda_disk_length ;
	else {
		cmd.len1 = sizeof(IOCTLI);
		cmd.unit = 0;
		cmd.command = 3;
		cmd.descriptor=0;
		DW(cmd.adr_seg) = (__tb>>4);
		DW(cmd.adr_off) = sizeof(IOCTLI);
		DW(cmd.len2) = 7;
		DW(cmd.secnum) = 0;
		DW(cmd.ptr_seg) = 0;
		DW(cmd.ptr_off) = 0;
		trk.control = 11;
		trk.track = track+1;
	
		dosmemput(&cmd, sizeof(IOCTLI), __tb);
		dosmemput(&trk, sizeof(TRACKINFO), (__tb + sizeof(IOCTLI)));
		
		memset(&_regs, 0, sizeof(_regs));
		_regs.x.es = _regs.x.ds = _regs.x.cs = (__tb>>4);
		_regs.x.bx = 0;
		_regs.x.cx = cdda_current_drive;
		_regs.x.ax = 0x1510;
		__dpmi_int(0x2f, &_regs);
	
		dosmemget(__tb, sizeof(IOCTLI), &cmd);
		dosmemget((__tb + sizeof(IOCTLI)), sizeof(TRACKINFO), &trk);
	
		if (DW(cmd.status)&0x8000)
			return;
	
		cdda_track_end = DD(trk.loc);
	}
	
	h = cdda_track_end>>24;
	m = cdda_track_end>>16;
	s = cdda_track_end>>8;
	
	s -= 1;
	if (s<0) {
		m--;
		s += 60;
		if (m<0) {
			h--;
			m+=60;
		}
	}
	
	cdda_track_end = (h<<24) + (m<<16) + (s<<8);

	h2 = cdda_track_start>>24;
	m2 = cdda_track_start>>16;
	s2 = cdda_track_start>>8;

	h -= h2;
	m -= m2;
	s -= s2;
	
	if (s<0) {
		s += 60;
		m--;
	}
	
	if (m<0) {
		m += 60;
		h--;
	}

	prq.len = 22;
	prq.unit = 0;
	prq.command = 132;
	prq.mode = 1;
	DD(prq.loc) = cdda_track_start;
	DD(prq.secnum) = (h*270000) + (m*4500) + (s*75);
	cdda_loop_counter = (h*216000) + (m*3600) + (s*60);

// printf("begin = %d\nlength = %d\n",cdda_track_start, (h*270000) + (m*4500) + (s*75));
	
	dosmemput(&prq, sizeof(PLAYREQ), __tb);
	memset(&_regs, 0, sizeof(_regs));
	_regs.x.es = _regs.x.ds = _regs.x.cs = (__tb>>4);
	_regs.x.bx = 0;
	_regs.x.cx = cdda_current_drive;
	_regs.x.ax = 0x1510;
	__dpmi_int(0x2f, &_regs);
	dosmemget(__tb, sizeof(PLAYREQ), &prq);

	if (DW(cmd.status)&0x8000)
		return;
	
	cdda_current_track = track;
	cdda_playing = 1;
	return;
}
//----------------------------------------------------------------------------
void osd_cd_length(int* min,
                   int* sec,
                   int* fra)
{
 switch (osd_cd_driver)
   {
    case mscdex_driver:
	 osd_cd_length_mscdex(min, sec, fra);
         break;
    default:
   }
 }
//----------------------------------------------------------------------------
void osd_cd_length_mscdex(int* min,
                   	  int* sec,
                   	  int* fra)
{
 Redbook2Time(cdda_disk_length,
              min,
              sec,
              fra);
 }
//----------------------------------------------------------------------------
void	osd_cd_stop_audio(void)
{
 switch (osd_cd_driver)
   {
    case mscdex_driver:
         osd_cd_stop_audio_mscdex();
         break;
    case aspi_driver:
         osd_cd_stop_audio_aspi();
         break;

    default:
   }
 }
//----------------------------------------------------------------------------
/* TODO : check the command code to pause/resume playing */
void	osd_cd_stop_audio_aspi(void)
{
  unsigned char *sense;
  memset(cdb, 0, 10);

  // cdb[0] = SCSI_PAUSE;

  aspi_stat = aspi_exec(dat, NULL, block_size, 0, cdb, 10);

  /* We may want to deal with error there */
  /*
  check_sense();
  if (aspi_sense[2] & SENSE_FILEMRK)
    return;
  */
  return;
}
//----------------------------------------------------------------------------
void	osd_cd_stop_audio_mscdex(void)
{
	STOPREQ	cmd;
	
	cmd.len = 13;
	cmd.unit = 0;
	cmd.command = 133;
	dosmemput(&cmd, sizeof(STOPREQ), __tb);
	memset(&_regs, 0, sizeof(_regs));
	_regs.x.es = _regs.x.ds = _regs.x.cs = (__tb>>4);
	_regs.x.bx = 0;
	_regs.x.cx = cdda_current_drive;
	_regs.x.ax = 0x1510;
	__dpmi_int(0x2f, &_regs);
	
	cdda_current_track = 0;
	cdda_playing = 0;
	cdda_loop_counter = 0;
}

//----------------------------------------------------------------------------
void 	osd_cd_close(void)
{
 switch (osd_cd_driver)
   {
    case mscdex_driver:
         osd_cd_close_mscdex();
         break;
    case aspi_driver:
         osd_cd_close_aspi();
         break;
    default:
   }
 }
//----------------------------------------------------------------------------
void	osd_cd_close_aspi(void)
{
	aspi_close();
 }
//----------------------------------------------------------------------------
void	osd_cd_close_mscdex(void)
{
	osd_cd_stop_audio();
}
//----------------------------------------------------------------------------
/* TODO : implement this stuff to repeat audio tracks */
void	osd_cd_loop_check(void)
{
	if (cdda_playing==1) {
		cdda_loop_counter--;
		if (cdda_loop_counter==0) {
			osd_cd_play_audio_track(cdda_current_track);
		}
	}
}
/*----------------------------------------------------------------------------

void cdda_cooked_read_sector_msf(unsigned char* p,unsigned long nb_sect)
{
   READREQ     cmd;


   if (!p)
     return ;

	cmd.len = 27;
	cmd.unit = 0;
	cmd.command = 0x80;

  	cmd.mode_addr = 0 ; // mode HSG
 	DW(cmd.ptr_off) = 27;
	DW(cmd.ptr_seg) = (__tb >> 4);
   DW(cmd.nb_to_read) = 1;
	DD(cmd.secnum) = nb_sect;
   cmd.mode_lect = 0 ; // cooked mode
   cmd.interleave_size = 0; // ?
   cmd.interleave_skip = 0; // ?

	dosmemput(&cmd, sizeof(READREQ), __tb);
	memset(&_regs, 0, sizeof(_regs));
	_regs.x.es = _regs.x.ds = _regs.x.cs = (__tb>>4);
	_regs.x.bx = 0;
	_regs.x.cx = cdda_current_drive;
	_regs.x.ax = 0x1510;
	__dpmi_int(0x2f, &_regs);

   if (DW(cmd.command) & 0x8000)
     {
      memset(p,0,2048);
      return ;
      }

   dosmemget(__tb+sizeof(READREQ),2048,p);

   return ;

 }
*/
//----------------------------------------------------------------------------
void osd_cd_read(unsigned char* p,unsigned long nb_sect)
{
 switch (osd_cd_driver)
   {
    case mscdex_driver:
         osd_cd_read_mscdex(p, nb_sect);
         break;
    case aspi_driver:
         osd_cd_read_aspi(p, nb_sect);
         break;
    default:
   }
 }
//----------------------------------------------------------------------------
void osd_cd_read_aspi(unsigned char *buffer, unsigned long sector)
{
  unsigned char *sense;
  memset(cdb, 0, 10);

  cdb[0] = 0x28;
  cdb[2] = sector >> 24;
  cdb[3] = (sector >> 16) & 0xff;
  cdb[4] = (sector >> 8) & 0xff;
  cdb[5] = sector & 0xff;
  cdb[8] = 0x01;

  aspi_stat = aspi_exec(dat, buffer, block_size, ASPI_RW_READ, cdb, 10);

  /* We may want to deal with error there */
  /*
  check_sense();
  if (aspi_sense[2] & SENSE_FILEMRK)
    return;
  */
  return;
}
//----------------------------------------------------------------------------
void osd_cd_read_mscdex(unsigned char* p,unsigned long nb_sect)
{
   READREQ     cmd;


   if (!p)
     return ;

	cmd.len = 27;
	cmd.unit = 0;
	cmd.command = 0x80;

  	cmd.mode_addr = 0 ; // 1 == mode RedBook
                                    // 0 == mode MSF
 	DW(cmd.ptr_off) = 27;
	DW(cmd.ptr_seg) = (__tb >> 4);
        DW(cmd.nb_to_read) = 1;
	DD(cmd.secnum) = nb_sect;

   cmd.mode_lect = 0 ; // 0 == cooked mode
                       // 1 == raw mode
   cmd.interleave_size = 0; // ?
   cmd.interleave_skip = 0; // ?

	dosmemput(&cmd, sizeof(READREQ), __tb);
	memset(&_regs, 0, sizeof(_regs));
	_regs.x.es = _regs.x.ds = _regs.x.cs = (__tb>>4);
	_regs.x.bx = 0;
	_regs.x.cx = cdda_current_drive;
	_regs.x.ax = 0x1510;
	__dpmi_int(0x2f, &_regs);

/*
   if (DW(cmd.command) & 0x8000)
     {
      memset(p,0,2048);
      return ;
      }
*/

   dosmemget(__tb+sizeof(READREQ),2048,p);

   return ;

 }


//----------------------------------------------------------------------------
void osd_cd_nb_tracks(int* first,
                      int* last)
{
 switch (osd_cd_driver)
   {
    case mscdex_driver:
         osd_cd_nb_tracks_mscdex(first, last);
         break;
    case aspi_driver:
         osd_cd_nb_tracks_aspi(first, last);
         break;
    default:
   }
 }
//----------------------------------------------------------------------------
void osd_cd_nb_tracks_aspi(int* first,
                           int* last)
{
  UChar *sense;
  UChar *buffer=alloca(2048);

  memset(cdb, 0, 12);
  cdb[0] = SCSI_READ_TOC;
  cdb[8] = 0x12;

  aspi_stat = aspi_exec(dat, buffer, block_size, ASPI_RW_READ, cdb, 12);
  /* TEST */
  *first = buffer[2];
  *last = buffer[3];
/*  *first = 1;
  *last = 2;
  */
  /* TODO : we may like to handle errors here */
  /*
  aspi_check_sense();
  if (aspi_sense[2] & SENSE_FILEMRK)
    return 1;
  */
}
//----------------------------------------------------------------------------
void osd_cd_nb_tracks_mscdex(int* first,
                             int* last)
{
 *first = cdda_min_track;
 *last = cdda_max_track;
 return ;
 }
//----------------------------------------------------------------------------
void osd_cd_track_info(UChar track,
			  int* min,
			  int* sec,
			  int* fra,
			  int* control)
{
 switch (osd_cd_driver)
   {
    case mscdex_driver:
         osd_cd_track_info_mscdex(track,
                           	  min,
                           	  sec,
                           	  fra,
                           	  control);
         break;
    case aspi_driver:
         osd_cd_track_info_aspi(track,
                           	  min,
                           	  sec,
                           	  fra,
                           	  control);
         break;
    default:
   }
 }
//----------------------------------------------------------------------------
void osd_cd_track_info_aspi(UChar track,
                            int* min,
                            int* sec,
                            int* fra,
                            int* control)
{
  UChar *sense;
  UChar *buffer=alloca(2048);

  memset(cdb, 0, 12);
  cdb[0] = SCSI_READ_TOC;
  cdb[1] = 2; /* MSF mode */
  cdb[6] = track;
  cdb[8] = 0x12;

  aspi_stat = aspi_exec(dat, buffer, block_size, ASPI_RW_READ, cdb, 12);

  Log("dos/osd_cd.c : Control for track in scsi driver for track %d is %02X\n",
      track,
      buffer[5]);

  *min = buffer[9];
  *sec = buffer[10];
  *fra = buffer[11];
  *control = buffer[5] & 0x4;

  /* TODO : we may like to handle errors here */
  /*
  aspi_check_sense();
  if (aspi_sense[2] & SENSE_FILEMRK)
    return 1;
  */
}
//----------------------------------------------------------------------------
void osd_cd_track_info_mscdex(UChar track,
			  int* min,
			  int* sec,
			  int* fra,
			  int* control)
{
	IOCTLI		cmd;
	TRACKINFO	trk;

        *min = *sec = *fra = *control = 0;

	if ((track<cdda_min_track)||(track>cdda_max_track))
		return ;

	cmd.len1 = sizeof(IOCTLI);
	cmd.unit = 0;
	cmd.command = 3;
	cmd.descriptor=0;
	DW(cmd.adr_seg) = (__tb>>4);
	DW(cmd.adr_off) = sizeof(IOCTLI);
	DW(cmd.len2) = 7;
	DW(cmd.secnum) = 0;
	DW(cmd.ptr_seg) = 0;
	DW(cmd.ptr_off) = 0;
	trk.control = 11;
	trk.track = track;

	dosmemput(&cmd, sizeof(IOCTLI), __tb);
	dosmemput(&trk, sizeof(TRACKINFO), (__tb + sizeof(IOCTLI)));
	
	memset(&_regs, 0, sizeof(_regs));
	_regs.x.es = _regs.x.ds = _regs.x.cs = (__tb>>4);
	_regs.x.bx = 0;
	_regs.x.cx = cdda_current_drive;
	_regs.x.ax = 0x1510;
	__dpmi_int(0x2f, &_regs);

	dosmemget(__tb, sizeof(IOCTLI), &cmd);
	dosmemget((__tb + sizeof(IOCTLI)), sizeof(TRACKINFO), &trk);

	if (DW(cmd.status)&0x8000)
          {
            /* memset(result,0,sizeof(TRACKINFO)); */
            return ;
          }

        Redbook2Time(trk.loc, min, sec, fra);
        *control = (trk.info >> 4) & 4;
        Log("dos/osd_cd.c : mscdex driver report type %s for track %d\n",
            (*control)?"CODE":"AUDIO", track);
	/* memcpy(result,&trk,sizeof(TRACKINFO)); */

}

//----------------------------------------------------------------------------
void	osd_cd_play_audio_range(int min_from,
                                int sec_from,
                                int fra_from,
                                int min_to,
                                int sec_to,
                                int fra_to)
{
 switch (osd_cd_driver)
   {
    case mscdex_driver:
         osd_cd_play_audio_range_mscdex(min_from,
                                        sec_from,
                                        fra_from,
                                        min_to,
                                        sec_to,
                                        fra_to);
         break;
    case aspi_driver:
         osd_cd_play_audio_range_aspi(min_from,
                                      sec_from,
                                      fra_from,
                                      min_to,
                                      sec_to,
                                      fra_to);
         break;

    default:
   }
}
//----------------------------------------------------------------------------
void	osd_cd_play_audio_range_aspi(int min_from,
                                int sec_from,
                                int fra_from,
                                int min_to,
                                int sec_to,
                                int fra_to)
{
  unsigned char *sense;
  memset(cdb, 0, 10);

        fra_to -= fra_from;
        sec_to -= sec_from;
        min_to -= min_from;

        if (fra_to<0)
          {
           fra_to += 75;
           sec_to++;
           }

        if (sec_to<0)
          {
           sec_to += 60;
           min_to++;
           }


  cdb[0] = SCSI_PLAYAUDMSF;
  cdb[3] = min_from;
  cdb[4] = sec_from;
  cdb[5] = fra_from;
  cdb[6] = min_to;
  cdb[7] = sec_to;
  cdb[8] = fra_to;

  aspi_stat = aspi_exec(dat, NULL, block_size, 0, cdb, 10);

  /* We may want to deal with error there */
  /*
  check_sense();
  if (aspi_sense[2] & SENSE_FILEMRK)
    return;
  */
  return;
}

//----------------------------------------------------------------------------
void	osd_cd_play_audio_range_mscdex(int min_from,
                                int sec_from,
                                int fra_from,
                                int min_to,
                                int sec_to,
                                int fra_to)
{
	PLAYREQ		prq;

	prq.len = 22;
	prq.unit = 0;
	prq.command = 132;
	prq.mode = 0; // 0 = mode HSG
                      // 1 = mode RedBook
	DD(prq.loc) = Time2HSG(min_from, sec_from, fra_from);

        fra_to -= fra_from;
        sec_to -= sec_from;
        min_to -= min_from;

        if (fra_to<0)
          {
           fra_to += 75;
           sec_to++;
           }

        if (sec_to<0)
          {
           sec_to += 60;
           min_to++;
           }

	DD(prq.secnum) = Time2HSG(min_to, sec_to, fra_to);

	// cdda_loop_counter = (h*216000) + (m*3600) + (s*60);
	
	dosmemput(&prq, sizeof(PLAYREQ), __tb);
	memset(&_regs, 0, sizeof(_regs));
	_regs.x.es = _regs.x.ds = _regs.x.cs = (__tb>>4);
	_regs.x.bx = 0;
	_regs.x.cx = cdda_current_drive;
	_regs.x.ax = 0x1510;
	__dpmi_int(0x2f, &_regs);

	dosmemget(__tb, sizeof(PLAYREQ), &prq);

        /*
	 * if (DW(cmd.status)&0x8000)
	 *	  return;
	 */

	cdda_playing = 1;
	return;
}

//----------------------------------------------------------------------------
/*
 * void cdda_cooked_prefech_read_sector_msf(unsigned long nb_sect)
 * {
 *  READREQ     cmd;
 *
 *  cmd.len = 27;
 *  cmd.unit = 0;
 *  cmd.command = 0x82;
 *
 *  cmd.mode_addr = 0 ; // mode HSG
 *  DW(cmd.ptr_off) = 0;
 *  DW(cmd.ptr_seg) = 0;
 *  DW(cmd.nb_to_read) = 1;
 *  DD(cmd.secnum) = nb_sect;
 *  cmd.mode_lect = 0 ; // cooked mode
 *  cmd.interleave_size = 0; // ?
 *  cmd.interleave_skip = 0; // ?
 *
 *	dosmemput(&cmd, sizeof(READREQ), __tb);
 *	memset(&_regs, 0, sizeof(_regs));
 *	_regs.x.es = _regs.x.ds = _regs.x.cs = (__tb>>4);
 *	_regs.x.bx = 0;
 *	_regs.x.cx = cdda_current_drive;
 *	_regs.x.ax = 0x1510;
 * 	__dpmi_int(0x2f, &_regs);
 *
 *  return ;
 *
 * }
 */
//----------------------------------------------------------------------------
/*
 * void cdda_cooked_prefech_read_sector_redbook(unsigned long nb_sect)
 * {
 *  READREQ     cmd;
 *
 *
 *  cmd.len = 27;
 *  cmd.unit = 0;
 *  cmd.command = 0x82;
 *
 *  cmd.mode_addr = 1 ; // mode RedBook
 *  DW(cmd.ptr_off) = 0;
 *  DW(cmd.ptr_seg) = 0;
 *  DW(cmd.nb_to_read) = 1;
 *  DD(cmd.secnum) = nb_sect;
 *  cmd.mode_lect = 0 ; // cooked mode
 *  cmd.interleave_size = 0; // ?
 *  cmd.interleave_skip = 0; // ?
 *
 *	dosmemput(&cmd, sizeof(READREQ), __tb);
 *	memset(&_regs, 0, sizeof(_regs));
 *	_regs.x.es = _regs.x.ds = _regs.x.cs = (__tb>>4);
 *	_regs.x.bx = 0;
 *	_regs.x.cx = cdda_current_drive;
 *	_regs.x.ax = 0x1510;
 *	__dpmi_int(0x2f, &_regs);
 *
 *  return ;
 *
 * }
 */
//----------------------------------------------------------------------------
/* void cdda_dos_cooked_read_sector_lba(unsigned char* p, unsigned long nb_sect)
 * {
 *
 *	memset(&_regs, 0, sizeof(_regs));
 *	_regs.x.es = _regs.x.ds = _regs.x.cs = (__tb>>4);
 *	_regs.x.bx = 0;
 *	_regs.x.cx = cdda_current_drive;
 *	_regs.x.ax = 0x1508;
 *       _regs.x.si = nb_sect >> 16;
 *       _regs.x.di = nb_sect & 0xFFFF;
 *       _regs.x.dx = 1;
 *	__dpmi_int(0x2f, &_regs);
 *
 *       printf("0x%x\n",_regs.x.flags);
 *
 *       if ((_regs.h.al == 15) ||
 *           (_regs.h.al == 21))
 *       {
 *         printf("DRIVE NOT READABLE\n");
 *       }
 *
 *       dosmemget(__tb, 2048, p);
 *
 * }
 */
