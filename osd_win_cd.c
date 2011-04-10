#include "osd_win_cd.h"#include "cleantyp.h"

#if defined(ALLEGRO)

#include <windows.h>
#include "myaspi32.h"

static int HaId;static int Target;static int Lun;static int aspi_init = 0;DWORD (*pfnGetASPI32SupportInfo) (void);DWORD (*pfnSendASPI32Command) (LPSRB);

#pragma pack(1)
typedef struct{  BYTE rsvd;  BYTE ADR;  BYTE trackNumber;  BYTE rsvd2;  BYTE addr[4];}PACKED TOCTRACK;typedef struct{  WORD tocLen;  BYTE firstTrack;  BYTE lastTrack;  TOCTRACK tracks[100];}PACKED TOC, *PTOC, FAR * LPTOC;

#pragma pack()
static TOC toc;DWORDReadToc (){  SRB_ExecSCSICmd s;  HANDLE hEvent;  DWORD dwStatus;
	/* if (aspi_init == 0)   loadASPI();*/  Log("Reading TOC\n");  hEvent = CreateEvent (NULL, TRUE, FALSE, NULL);	  memset (&s, 0, sizeof (s));	  memset (&toc, 0, sizeof (toc));	  s.SRB_Cmd = SC_EXEC_SCSI_CMD;	  s.SRB_HaID = HaId;	  s.SRB_Target = Target;	  s.SRB_Lun = Lun;	  s.SRB_Flags = SRB_DIR_IN | SRB_EVENT_NOTIFY;	  s.SRB_BufLen = 0x324;	  s.SRB_BufPointer = (BYTE FAR *) & toc;	  s.SRB_SenseLen = 0x0E;	  s.SRB_CDBLen = 0x0A;	  s.SRB_PostProc = (LPVOID) hEvent;	  s.CDBByte[0] = 0x43;	// command to read TOC	  s.CDBByte[7] = 0x03;	// ofs. 7-8 used for toc len	  s.CDBByte[8] = 0x24;	// TOC buffer length == 0x324	  dwStatus = pfnSendASPI32Command ((LPSRB) & s);          if (dwStatus == SS_PENDING)	    {	      WaitForSingleObject (hEvent, INFINITE);	    }
		
		{
			int i;
			Log("First track: %d\nLast track: %d\n", toc.firstTrack, toc.lastTrack);
			
			for (i = toc.firstTrack; i <= toc.lastTrack; i++) {
			  Log("Track %d: %d\n", i, toc.tracks[i-1].addr);			
			}
		}
		          CloseHandle(hEvent);          return s.SRB_Status; }DWORDReadDevice (int H,            int T,            int L){  SRB_GDEVBlock s;  HANDLE hEvent;  DWORD dwStatus;
	
  /*  if (aspi_init == 0)   loadASPI();
  */  hEvent = CreateEvent (NULL, TRUE, FALSE, NULL);	  memset (&s, 0, sizeof (s));          s.SRB_Cmd = SC_GET_DEV_TYPE;          s.SRB_HaID = H;          s.SRB_Target = T;          s.SRB_Lun = L;	  dwStatus = pfnSendASPI32Command ((LPSRB) & s);          if (dwStatus == SS_PENDING)	    {	      WaitForSingleObject (hEvent, INFINITE);              return -1;	    }          CloseHandle(hEvent);          if (dwStatus == SS_COMP)            return s.SRB_DeviceType;          return -1; }intloadASPI (void){  HINSTANCE hDll;  hDll = LoadLibrary ("WNASPI32.DLL");  if (!hDll)    return 0;  pfnGetASPI32SupportInfo =    (DWORD (*)(void)) GetProcAddress (hDll, "GetASPI32SupportInfo");  pfnSendASPI32Command =    (DWORD (*)(LPSRB)) GetProcAddress (hDll, "SendASPI32Command");  if (!pfnGetASPI32SupportInfo || !pfnSendASPI32Command)    {      Log("Win Aspi NOT initiated\n");      return 0;    }  aspi_init = 1;  Log("Win Aspi initiated\n");  return -1;}voidMSB2DWORD (DWORD * d, BYTE * b){  DWORD retVal;  retVal = (DWORD) b[0];  retVal = (retVal << 8) + (DWORD) b[1];  retVal = (retVal << 8) + (DWORD) b[2];  retVal = (retVal << 8) + (DWORD) b[3];  *d = retVal;}int osd_cd_init(char* device)
{
 int HaId_in, Target_in, Lun_in;
 int nb = atoi(device);
 Log("Init win aspi cdrom device\n");
 if (nb == 0)
   nb = 1;
/*
 if (loadASPI())
   return 1;
*/
 Log("Trying to check cd driver number %d\n", nb);
 loadASPI(); for (HaId_in = 0; HaId_in < 8; HaId_in++)    for (Target_in = 0; Target_in < 8; Target_in++)       for (Lun_in = 0; Lun_in < 8; Lun_in++)          {/*          Log("Trying %d:%d:%d\n",                      HaId_in,                      Target_in,                      Lun_in);*/          if (ReadDevice(HaId_in,                         Target_in,                         Lun_in) != 5)            continue;/*          Log("Found 1 CD...\n");*/          if (--nb)            continue;	  Log ("CD found at %d:%d:%d\n", HaId_in, Target_in, Lun_in);          HaId = HaId_in;          Target = Target_in;          Lun = Lun_in;
		  
		  ReadToc();
		            return 0;          }    return 1;  }void osd_cd_close(){}void osd_cd_read(UChar* p, UInt32 sector){  HANDLE hEvent;  SRB_ExecSCSICmd s;  DWORD dwStatus;  // BYTE* intern_buffer = (BYTE*)malloc(2352);
	
	printf("Reading sector %d in %s - %s\n", sector, __FILE__, __LINE__);
	
	return;
	
	/* if (aspi_init == 0)   loadASPI();		  hEvent = CreateEvent( NULL, TRUE, FALSE, NULL );		  memset (&s, 0, sizeof (s));		  s.SRB_Cmd = SC_EXEC_SCSI_CMD;		  s.SRB_HaID = HaId;		  s.SRB_Target = Target;		  s.SRB_Lun = Lun;		  s.SRB_Flags = SRB_DIR_IN | SRB_EVENT_NOTIFY;		  s.SRB_BufLen = 2352;		  s.SRB_BufPointer = intern_buffer;		  s.SRB_SenseLen = SENSE_LEN;		  s.SRB_CDBLen = 12;		  s.SRB_PostProc = (LPVOID) hEvent;		  s.CDBByte[0] = 0xBE;	// read CD Raw                  s.CDBByte[3] = (sector >> 16) & 0xFF;                  s.CDBByte[4] = (sector >> 8) & 0xFF;                  s.CDBByte[5] = sector & 0xFF;                  s.CDBByte[8] = 1;		  s.CDBByte[9] = 0xF0;		  ResetEvent (hEvent);		  dwStatus = pfnSendASPI32Command ((LPSRB) & s);		  if (dwStatus == SS_PENDING)		    {		      WaitForSingleObject (hEvent, INFINITE);		    }		  if (s.SRB_Status != SS_COMP) {
			  free(intern_buffer);                    return s.SRB_Status;
		  }		  CloseHandle( hEvent );                  memcpy(p, intern_buffer + 16, 2048);
		  
		  free(intern_buffer);
		                    return s.SRB_Status;*/}void osd_cd_stop_audio(){}void osd_cd_track_info( UChar track,			int* min,			int* sec,			int* fra,			int* control){ DWORD frame;
	
 Log("Looking for track info of #%d - %s %d\n", track, __FILE__, __LINE__);
	
 track--;  *control = ((TOCTRACK)(toc.tracks[track])).ADR;
	 MSB2DWORD( &frame, ((TOCTRACK)(toc.tracks[track])).addr ); Frame2Time(frame + 150, min, sec, fra); Log("Track begins at frame %d\n", frame + 150);}void osd_cd_nb_tracks(int* first,		      int* last){ if (aspi_init == 0)   loadASPI(); // ReadToc(); Log("Will output tracks limit\n"); *first = toc.firstTrack; *last = toc.lastTrack;}void osd_cd_length(int* min,                   int* sec,                   int* fra){ *min = 25; *sec = 06; *fra = 00;}void osd_cd_play_audio_track(UChar track){}void osd_cd_play_audio_range(			     UChar min_from,			     UChar sec_from,			     UChar fra_from,			     UChar min_to,			     UChar sec_to,			     UChar fra_to){}

void osd_cd_subchannel_info(unsigned short offset)
{
  Wr6502(offset, 4);
  }


void osd_cd_status(int *status)
{
      *status = 0;
}

void osd_cd_pause(void)
{
}


void osd_cd_resume(void)
{
}
#else

#include <windows.h>
#include <stdio.h>
#include "akrip32.h"#include <SDL.h>
int akrip_init = 0;SDL_CD *cdrom;
void MSB2DWORD( DWORD *d, BYTE *b );
LPTRACKBUF NewTrackBuf( DWORD numFrames );

static LPTRACKBUF track_buffer;
static HCDROM handle_CD;
static TOC toc;

int akrip_read(HCDROM hCD, unsigned int sector)
{
  DWORD dwStatus;

  track_buffer->numFrames = 1;
  track_buffer->startOffset = 0;
  track_buffer->len = 0;
  track_buffer->startFrame = sector;
  dwStatus = ReadCDAudioLBA( hCD, track_buffer );

  if ( dwStatus == SS_COMP )
    {
      return 0;
    }
  else
    {
      Log( "Error (%d:%d)\n", GetAspiLibError(), GetAspiLibAspiError() );
      return GetAspiLibAspiError();
    }

}

int init_akrip()
{
  static CDLIST cdlist;
  GETCDHAND cdh;
  HCDROM hCD;

  int cd_index, track_index, prefered_cd_index, read_toc_result;	  prefered_cd_index = -1;
	  if (akrip_init)    {	    Log("Avoiding akrip_init to be called another time\n");						if (handle_CD != -1)				CloseCDHandle(handle_CD);    }  else	  {			akrip_init = 1;					#if defined(CD_DEBUG)			Log("Entering init_akrip()\n");		#endif  			
			ZeroMemory( &cdlist, sizeof(cdlist) );
		
			cdlist.max = MAXCDLIST;
		
			// Check the available cd drives
			GetCDList( &cdlist );		}  handle_CD = (HCDROM) -1;					
  if ( cdlist.num < 1)
    {#if defined(CD_DEBUG)		
      Log("No cd drive available\n");#endif		
      return 1;
    }  else    {#if defined(CD_DEBUG)			  Log("%d drive(s) found\n", cdlist.num);	  for (cd_index = 0; cd_index < cdlist.num; cd_index++)	    {		  Log("Drive #%d (%d:%d:%d)\n", cd_index, cdlist.cd[cd_index].ha, cdlist.cd[cd_index].tgt, cdlist.cd[cd_index].lun);		}#endif			}

  track_buffer = NewTrackBuf( 1 );

  for ( cd_index = 0; (cd_index < cdlist.num) && (prefered_cd_index == -1); cd_index++ )
    {		
      ZeroMemory( &cdh, sizeof(cdh) );
      cdh.size     = sizeof(GETCDHAND);
      cdh.ver      = 1;
      cdh.ha       = cdlist.cd[cd_index].ha;
      cdh.tgt      = cdlist.cd[cd_index].tgt;
      cdh.lun      = cdlist.cd[cd_index].lun;
      cdh.readType  = CDR_ANY;      // set for autodetect
#if defined(CD_DEBUG)					  Log("Trying to test cd (%d:%d:%d)\n", cdh.ha, cdh.tgt, cdh.lun);#endif		
      hCD = GetCDHandle( &cdh);

      ModifyCDParms( hCD, CDP_MSF, FALSE );
      if ( read_toc_result = ReadTOC( hCD, &toc ) != SS_COMP )
        {#if defined(CD_DEBUG)					
          Log( "Error reading TOC (%d)\n", read_toc_result );#endif			          CloseCDHandle( hCD );
    	  continue;        }
#if defined(CD_DEBUG)			  Log("%d tracks on this CD (%d - %d)\n", 1 + toc.lastTrack - toc.firstTrack, toc.firstTrack, toc.lastTrack);#endif				
      for (track_index = 0; track_index <= toc.lastTrack - toc.firstTrack; track_index++)
        {		  					#warning disabled code track checking					/*
          if (toc.tracks[track_index].ADR & 0X04)					*/
            {
	          DWORD addr;
 	          MSB2DWORD( &addr, toc.tracks[track_index].addr );
#if defined(CD_DEBUG)					  Log("Found a code track (#%d, LBA %d)\n", track_index, addr);#endif				
              akrip_read(hCD, addr);
	          // Add detection of signature for easiness of use

	          prefered_cd_index = cd_index;	          break;
            }					
        }		
#if defined(CD_DEBUG)	  Log("Closing handle for this drive\n");#endif		
      CloseCDHandle ( hCD );

    }  

    if (prefered_cd_index != -1)
      {
		DWORD play_track_result;		  
        ZeroMemory( &cdh, sizeof(cdh) );
        cdh.size     = sizeof(GETCDHAND);
        cdh.ver      = 1;
        cdh.ha       = cdlist.cd[prefered_cd_index].ha;
        cdh.tgt      = cdlist.cd[prefered_cd_index].tgt;
        cdh.lun      = cdlist.cd[prefered_cd_index].lun;
        cdh.readType  = CDR_ANY;      // set for autodetect		  
#if defined(CD_DEBUG)				Log("Prefered CD drive #%d (%d:%d:%d)\n", prefered_cd_index, cdh.ha, cdh.tgt, cdh.lun);#endif		  
        handle_CD = GetCDHandle( &cdh );

        ModifyCDParms( handle_CD, CDP_MSF, FALSE );
        if ( read_toc_result = ReadTOC( handle_CD, &toc ) != SS_COMP )
          {#if defined(CD_DEBUG)					  
            Log( "Error reading TOC (%d)\n", read_toc_result);#endif
            CloseCDHandle( handle_CD );
    	    return 1;
          }				
	      return (handle_CD >= 0 ? 0 : 1);
      }

    return 2;
}

void shut_akrip()
{
  CloseCDHandle ( handle_CD );  
}

int osd_cd_init( char* dummy )
{
  return init_akrip();
}

void osd_cd_close(){  osd_cd_stop_audio();
	shut_akrip();}void osd_cd_read(UChar* p, UInt32 sector){
  if (akrip_read( handle_CD, sector ) == 0)
		{			memcpy(p, track_buffer->buf + 16 , 2048);						return;
		}
	Log("Error reading cd sector %d at %s - %d\n", sector, __FILE__, __LINE__);
  return;
	}


void MSB2DWORD( DWORD *d, BYTE *b )
{
  DWORD retVal;

  retVal = (DWORD)b[0];
  retVal = (retVal<<8) + (DWORD)b[1];
  retVal = (retVal<<8) + (DWORD)b[2];
  retVal = (retVal<<8) + (DWORD)b[3];

  *d = retVal;
}

void osd_cd_nb_tracks(int* first,		      int* last){ *first = toc.firstTrack; *last = toc.lastTrack;}

void osd_cd_track_info( UChar track,			int* min,			int* sec,			int* fra,			int* control){ DWORD frame;	
#if defined(CD_DEBUG)			
 Log("Looking for track info of #%d - %s %d\n", track, __FILE__, __LINE__);
#endif	
 track -= toc.firstTrack;  *control = ((TOCTRACK)(toc.tracks[track])).ADR;
 MSB2DWORD( &frame, ((TOCTRACK)(toc.tracks[track])).addr ); Frame2Time(frame + 150, min, sec, fra);	#if defined(CD_DEBUG) Log("Track begins at frame %d\n", frame + 150);#endif	}

LPTRACKBUF NewTrackBuf( DWORD numFrames )
{
  LPTRACKBUF t;
  int numAlloc;

  numAlloc = (((int)numFrames)*2352) + TRACKBUFEXTRA;

  t = (LPTRACKBUF)GlobalAlloc( GPTR, numAlloc );

  if ( !t )
    return NULL;

  t->startFrame = 0;
  t->numFrames = 0;
  t->maxLen = numFrames * 2352;
  t->len = 0;
  t->status = 0;
  t->startOffset = 0;

  return t;
}

void osd_cd_length(int* min,
                   int* sec,
                   int* fra)
{  int index;	DWORD cd_length;	#if defined(CD_DEBUG)	Log("Length of CD asked\n");#endif	/*	for ( index = toc.firstTrack; index <= toc.lastTrack; index ++ )		{			cd_length += toc.tracks[index].trackLen;#if defined(CD_DEBUG)			Log("Adding length of track #%d which is %d frames long\n", index, toc.tracks[index].trackLen);#endif		}	*/	#warning It s an unprecise heuristic			MSB2DWORD( &cd_length, toc.tracks[toc.lastTrack].addr);	#if defined(CD_DEBUG)	Log("Total cd length : %d frames\n", cd_length);#endif			Frame2Time(cd_length,min,sec,fra);	}

void osd_cd_play_audio_track(UChar track)
{	UChar real_track;	UChar min_from, sec_from, fra_from;	UChar min_to, sec_to, fra_to;		DWORD cd_begin, cd_end;	#if defined(CD_DEBUG)	Log("Playing track #%d\n", track);#endif		if (track >= toc.lastTrack)		{			Log("Trying to play the last track, abording\n");			return;		}		real_track = track - toc.firstTrack;		MSB2DWORD( &cd_begin, toc.tracks[real_track].addr);		MSB2DWORD( &cd_end, toc.tracks[real_track+1].addr);		fra_from = cd_begin % 75;	cd_begin /= 75;			sec_from = cd_begin % 60;	cd_begin /= 60;			min_from = cd_begin;			fra_to = cd_end % 75;	cd_end /= 75;			sec_to = cd_end % 60;	cd_end /= 60;			min_to = cd_end;			osd_cd_play_audio_range( min_from, sec_from, fra_from, min_to, sec_to, fra_to);}

void osd_cd_play_audio_range(
			     UChar min_from,
			     UChar sec_from,
			     UChar fra_from,
			     UChar min_to,
			     UChar sec_to,
			     UChar fra_to)
{	DWORD begin, end, length;	#if defined(CD_DEBUG)	Log("Playing from %02d:%02d:%02d to %02d:%02d:%02d\n", min_from, sec_from, fra_from,				min_to, sec_to, fra_to);#endif		begin = ((min_from * 60) + sec_from) * 75 + fra_from;		end = ((min_to * 60) + sec_to) * 75 + fra_to;		length = end - begin;		begin -= 150;	#if defined(CD_DEBUG)	Log("Playing from frame %d while %d frames\n", begin, length);#endif		PlayAudioRange( handle_CD, begin, length);	}

void osd_cd_subchannel_info(unsigned short offset)
{
      Wr6502(offset, 4);
}


void osd_cd_status(int *status)
{
      *status = 0;
}

void osd_cd_pause(void)
{	pauseResumeCD( handle_CD, 1);	}

void osd_cd_resume(void)
{	pauseResumeCD( handle_CD, 0);}

void osd_cd_stop_audio(){	startStopUnit( handle_CD, 0, 0);}
#endif
