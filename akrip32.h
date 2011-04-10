/*
 * akrip32.h - Copyright (C) 1999 Jay A. Key
 *
 * API for akrip32.dll
 *
 **********************************************************************
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 *
 **********************************************************************
 *
 */

#ifndef _AKRIP32_H_
#define _AKRIP32_H_

#include <windows.h>
#include "myaspi32.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef __GNUC__
#define PACKED
#endif

#define TRACK_AUDIO   0x00
#define TRACK_DATA    0x01

#define  MAXIDLEN   64
#define  MAXCDLIST  8

/*
 * TRACKBUF
 *
 * This structure should not be allocated directly.  If a buffer containing
 * 27 * 2353 bytes is desired, a buffer should be allocated containing
 * the desired amount + 24 bytes.  The allocated memory can then be
 * typecast to a LPTRACKBUF.  It is the program's responsibility to guard
 * against reading/writing past the end of allocated memory.
 *
 * The following must always apply:
 *   (len + startOffset) <= (numFrames * 2352) <= maxLen
 */
typedef struct
{
  DWORD   startFrame;       /* 00: starting frame number          */
  DWORD   numFrames;        /* 04: number of frames read          */
  DWORD   maxLen;           /* 08: length of buffer itself        */
  DWORD   len;              /* 0C: length of data actually in buf */
  DWORD   status;           /* 10: status of last read operation  */
  int     startOffset;      /* 14: offset of valid data in buf    */
  BYTE    buf[1024*1024];     /* 18: the data itself                */
} *PTRACKBUF, FAR *LPTRACKBUF;

typedef struct
{
  DWORD   startFrame;       /* 00: starting frame number          */
  DWORD   numFrames;        /* 04: number of frames read          */
  DWORD   maxLen;           /* 08: length of buffer itself        */
  DWORD   len;              /* 0C: length of data actually in buf */
  DWORD   status;           /* 10: status of last read operation  */
  int     startOffset;      /* 14: offset of valid data in buf    */
} TRACKBUFDUMMY;
#define TRACKBUFEXTRA   sizeof(TRACKBUFDUMMY)


typedef struct
{
  char vendor[9];
  char prodId[17];
  char rev[5];
  char vendSpec[21];
} CDINFO, *PCDINFO, FAR *LPCDINFO;

typedef struct
{
  BYTE      ha;
  BYTE      tgt;
  BYTE      lun;
  BYTE      pad;
  char      id[MAXIDLEN + 1];
  CDINFO    info;
} CDREC, *PCDREC, FAR *LPCDREC;

typedef struct
{
  BYTE      max;
  BYTE      num;
  CDREC     cd[MAXCDLIST];
} CDLIST, *PCDLIST, FAR *LPCDLIST;


#ifndef __GNUC__
#pragma pack(1)
#endif

/*
 * TOCTRACK and TOC must be byte-aligned.  If you're not using Mingw32,
 * CygWin, or some other compiler that understands the PACKED keyword,
 * you need to ensure that these structures are byte aligned.  Usually,
 * this is done using a
 *  #pragma pack(1)
 * See your compiler's documentation for details
 */
typedef struct
{
  BYTE      rsvd;
  BYTE      ADR;
  BYTE      trackNumber;
  BYTE      rsvd2;
  BYTE      addr[4];
} PACKED TOCTRACK;

typedef struct
{
  WORD      tocLen;
  BYTE      firstTrack;
  BYTE      lastTrack;
  TOCTRACK tracks[100];
} PACKED TOC, *PTOC, FAR *LPTOC;

typedef struct
{
  int   trackNo;
  DWORD startLBA;
  DWORD trackLen;
  BYTE  type;
  BYTE  pad[3];
  char  name[256];
} PACKED TRACK, *PTRACK, FAR *LPTRACK;

#ifndef __GNUC__
#pragma pack()
#endif

typedef struct
{
  BYTE sm;
  BYTE ss;
  BYTE sf;
  BYTE em;
  BYTE es;
  BYTE ef;
} READMSF, *PREADMSF, FAR *LPREADMSF;


/*
 * Error codes set by functions in ASPILIB.C
 */
#define ALERR_NOERROR           0
#define ALERR_NOWNASPI         -1
#define ALERR_NOGETASPI32SUPP  -2
#define ALERR_NOSENDASPICMD    -3
#define ALERR_ASPI             -4
#define ALERR_NOCDSELECTED     -5
#define ALERR_BUFTOOSMALL      -6
#define ALERR_INVHANDLE        -7
#define ALERR_NOMOREHAND       -8
#define ALERR_BUFPTR           -9
#define ALERR_NOTACD           -10
#define ALERR_LOCK             -11
#define ALERR_DUPHAND          -12
#define ALERR_INVPTR           -13
#define ALERR_INVPARM          -14
#define ALERR_JITTER           -15
#define ALERR_NOADAPTERS       -16
#define ALERR_NOCDFOUND        -17

/*
 * API codes
 */
#define APIC_NONE        0
#define APIC_ASPI        1
#define APIC_SCSIPT      2

/*
 * constants used for queryCDParms()
 */

#define CDP_READCDR      0x0001     // can read CD-R
#define CDP_READCDE      0x0002     // can read CD-E
#define CDP_METHOD2      0x0003     // can read CD-R wriiten via method 2
#define CDP_WRITECDR     0x0004     // can write CD-R
#define CDP_WRITECDE     0x0005     // can write CD-E
#define CDP_AUDIOPLAY    0x0006     // can play audio
#define CDP_COMPOSITE    0x0007     // composite audio/video stream
#define CDP_DIGITAL1     0x0008     // digital output (IEC958) on port 1
#define CDP_DIGITAL2     0x0009     // digital output (IEC958) on port 2
#define CDP_M2FORM1      0x000A     // reads Mode 2 Form 1 (XA) format
#define CDP_M2FORM2      0x000B     // reads Mode 2 Form 2 format
#define CDP_MULTISES     0x000C     // reads multi-session or Photo-CD
#define CDP_CDDA         0x000D     // supports cd-da
#define CDP_STREAMACC    0x000E     // supports "stream is accurate"
#define CDP_RW           0x000F     // can return R-W info
#define CDP_RWCORR       0x0010     // returns R-W de-interleaved and err.
                                    // corrected
#define CDP_C2SUPP       0x0011     // C2 error pointers
#define CDP_ISRC         0x0012     // can return the ISRC info
#define CDP_UPC          0x0013     // can return the Media Catalog Number
#define CDP_CANLOCK      0x0014     // prevent/allow cmd. can lock the media
#define CDP_LOCKED       0x0015     // current lock state (TRUE = LOCKED)
#define CDP_PREVJUMP     0x0016     // prevent/allow jumper state
#define CDP_CANEJECT     0x0017     // drive can eject disk
#define CDP_MECHTYPE     0x0018     // type of disk loading supported
#define CDP_SEPVOL       0x0019     // independent audio level for channels
#define CDP_SEPMUTE      0x001A     // independent mute for channels
#define CDP_SDP          0x001B     // supports disk present (SDP)
#define CDP_SSS          0x001C     // Software Slot Selection
#define CDP_MAXSPEED     0x001D     // maximum supported speed of drive
#define CDP_NUMVOL       0x001E     // number of volume levels
#define CDP_BUFSIZE      0x001F     // size of output buffer
#define CDP_CURRSPEED    0x0020     // current speed of drive
#define CDP_SPM          0x0021     // "S" units per "M" (MSF format)
#define CDP_FPS          0x0022     // "F" units per "S" (MSF format)
#define CDP_INACTMULT    0x0023     // inactivity multiplier ( x 125 ms)
#define CDP_MSF          0x0024     // use MSF format for READ TOC cmd
#define CDP_OVERLAP      0x0025     // number of overlap frames for jitter
#define CDP_JITTER       0x0026     // number of frames to check for jitter
#define CDP_READMODE     0x0027     // mode to attempt jitter corr.

/*
 * defines for GETCDHAND  readType
 *
 */
#define CDR_ANY          0x00       // unknown
#define CDR_ATAPI1       0x01       // ATAPI per spec
#define CDR_ATAPI2       0x02       // alternate ATAPI
#define CDR_READ6        0x03       // using SCSI READ(6)
#define CDR_READ10       0x04       // using SCSI READ(10)
#define CDR_READ_D8      0x05       // using command 0xD8 (Plextor?)
#define CDR_READ_D4      0x06       // using command 0xD4 (NEC?)
#define CDR_READ_D4_1    0x07       // 0xD4 with a mode select
#define CDR_READ10_2     0x08       // different mode select w/ READ(10)

/*
 * defines for the read mode (CDP_READMODE)
 */
#define CDRM_NOJITTER      0x00     // never jitter correct
#define CDRM_JITTER        0x01     // always jitter correct
#define CDRM_JITTERONERR   0x02     // jitter correct only after a read error

#ifndef __GNUC__
#pragma pack(1)
#endif

typedef HANDLE HCDROM;
typedef struct _GETCDHAND {
  BYTE size;             /* set to sizeof(GETCDHAND)            */
  BYTE ver;              /* set to AKRIPVER                     */
  BYTE ha;               /* host adapter                        */
  BYTE tgt;              /* target id                           */
  BYTE lun;              /* LUN                                 */
  BYTE readType;         /* read function to use                */
  BOOL jitterCorr;       /* use built-in jitter correction?     */
  BYTE numJitter;        /* number of frames to try to match    */
  BYTE numOverlap;       /* number of frames to overlap         */
} PACKED GETCDHAND, *PGETCDHAND, FAR *LPGETCDHAND;

#ifndef __GNUC__
#pragma pack()
#endif

// Used by InsertCDCacheItem
#define CDDB_NONE    0
#define CDDB_QUERY   1
#define CDDB_ENTRY   2


#define CDDB_OPT_SERVER      0
#define CDDB_OPT_PROXY       1
#define CDDB_OPT_USEPROXY    2
#define CDDB_OPT_AGENT       3
#define CDDB_OPT_USER        4
#define CDDB_OPT_PROXYPORT   5
#define CDDB_OPT_CGI         6
#define CDDB_OPT_HTTPPORT    7
#define CDDB_OPT_USECDPLAYERINI 8
#define CDDB_OPT_USEHTTP1_0  9
#define CDDB_OPT_SUBMITCGI   10
#define CDDB_OPT_USERAUTH    11
#define CDDB_OPT_PROTOLEVEL  12

int GetNumAdapters( void );
int GetCDList( LPCDLIST cd );
int GetAspiLibError( void );
BYTE GetAspiLibAspiError( void );

DWORD GetCDId( HCDROM hCD, char *buf, int maxBuf );
DWORD GetDriveInfo( BYTE ha, BYTE tgt, BYTE lun, LPCDREC cdrec );
DWORD ReadTOC( HCDROM hCD, LPTOC lpToc );
DWORD ReadCDAudioLBA( HCDROM hCD, LPTRACKBUF );
BOOL QueryCDParms( HCDROM hCD, int which, DWORD *pNum );
BOOL ModifyCDParms( HCDROM hCD, int which, DWORD val );
HCDROM GetCDHandle( LPGETCDHAND lpcd );
BOOL CloseCDHandle( HCDROM );
DWORD ReadCDAudioLBAEx( HCDROM hCD, LPTRACKBUF, LPTRACKBUF );
DWORD GetAKRipDllVersion( void );

/*
 * CDDB support
 */
typedef struct {
  char categ[12];
  char cddbId[9];
  BOOL bExact;
  char artist[81];
  char title[81];
} CDDBQUERYITEM, FAR *LPCDDBQUERYITEM;


typedef struct {
  int num;
  LPCDDBQUERYITEM q;
} CDDBQUERY, FAR *LPCDDBQUERY;


typedef struct {
  char szServer[81];
  BOOL bHTTP;
  int  iPort;
  char szCGI[81];
  char szNorth[16];
  char szSouth[16];
  char szLocation[81];
} CDDBSITE, FAR *LPCDDBSITE;


typedef struct {
  int num;
  LPCDDBSITE s;
} CDDBSITELIST, FAR *LPCDDBSITELIST;


DWORD GetCDDBDiskID( HCDROM hCD, DWORD *pID, int numEntries );
DWORD CDDBQuery( HCDROM hCD, LPCDDBQUERY lpq );
DWORD CDDBGetDiskInfo( LPCDDBQUERYITEM lpq, char *szCDDBEntry, int maxLen );
void CDDBSetOption( int what, char *szVal, int iVal );
DWORD CDDBGetOptionInt( int what, BOOL *bValid );
char *CDDBGetOptionText( int what, char *szBuf, int maxLen, BOOL *bValid );
DWORD CDDBGetServerList( LPCDDBSITELIST lpSiteList );
DWORD CDDBSubmit( DWORD dwDiscID, BOOL bTest, char *szEmail, char *szCategory,
		  char *szEntry );

/*
 * CDDA
 */
DWORD PlayTrack( HCDROM hCD, DWORD track_index );
DWORD PlayAudioRange( HCDROM hCD, DWORD From, DWORD Length );
DWORD startStopUnit( HCDROM hCD, BOOL bLoEj, BOOL bStart );
DWORD pauseResumeCD( HCDROM hCD, BOOL bPause );

#ifdef __cplusplus
}
#endif

#endif   /* _AKRIP32_H_ */
