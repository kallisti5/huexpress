/*
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 *  1. Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 * derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
 * SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT
 * OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
 * OF SUCH DAMAGE.
 */

#include "pce.h"
#include "utils.h"

UChar pce_cd_cmdcnt;

UInt32 pce_cd_sectoraddy;

UChar pce_cd_sectoraddress[3];

UChar pce_cd_temp_dirinfo[4];

UChar pce_cd_temp_play[4];

UChar pce_cd_temp_stop[4];

UChar pce_cd_dirinfo[4];

extern UChar pce_cd_adpcm_trans_done;

UChar cd_port_180b = 0;

UChar cd_fade;
// the byte set by the fade function

static void
pce_cd_set_sector_address (void)
{
  pce_cd_sectoraddy = pce_cd_sectoraddress[0] << 16;
  pce_cd_sectoraddy += pce_cd_sectoraddress[1] << 8;
  pce_cd_sectoraddy += pce_cd_sectoraddress[2];
}

static void
pce_cd_handle_command (void)
{

  if (pce_cd_cmdcnt)
    {
#ifdef CD_DEBUG
      fprintf (stderr, "Command arg received: 0x%02x.\n", io.cd_port_1801);
#endif

      if (--pce_cd_cmdcnt)
	io.cd_port_1800 = 0xd0;
      else
	io.cd_port_1800 = 0xc8;

      switch (pce_cd_curcmd)
	{
	case 0x08:
	  if (!pce_cd_cmdcnt)
	    {
#ifdef CD_DEBUG
	      fprintf (stderr, "Read command: %d sectors.\n", io.cd_port_1801);
	      fprintf (stderr, "Starting at %02x:%02x:%02x.\n",
		       pce_cd_sectoraddress[0], pce_cd_sectoraddress[1],
		       pce_cd_sectoraddress[2]);
	      fprintf (stderr, "MODE : %x\n", Rd6502 (0x20FF));
#endif

	      cd_sectorcnt = io.cd_port_1801;

              if (cd_sectorcnt == 0)
                {
                  fprintf(stderr, "cd_sectorcnt == 0 !!!");
                  Log("cd_sectorcnt == 0 !!!");
                }

	      pce_cd_set_sector_address ();
	      pce_cd_read_sector ();


	      /* TEST */
	      // cd_port_1800 = 0xD0; // Xanadu 2 doesn't block but still crash
	      /* TEST */

#ifdef CD_DEBUG
	      fprintf (stderr, "Result of reading : $1800 = 0X%02X\n\n\n",
		       io.cd_port_1800);
#endif

/* TEST ZEO
    if (Rd6502(0x20ff)==0xfe)
     cd_port_1800 = 0x98;
    else
     cd_port_1800 = 0xc8;
 * ******** */

	    }
	  else
	    pce_cd_sectoraddress[3 - pce_cd_cmdcnt] = io.cd_port_1801;

	  break;
	case 0xd8:

	  pce_cd_temp_play[pce_cd_cmdcnt] = io.cd_port_1801;

	  if (!pce_cd_cmdcnt)
	    {
	      io.cd_port_1800 = 0xd8;
	    }
	  break;
	case 0xd9:

	  pce_cd_temp_stop[pce_cd_cmdcnt] = io.cd_port_1801;

	  if (!pce_cd_cmdcnt)
	    {
	      io.cd_port_1800 = 0xd8;
/*
               if (pce_cd_temp_stop[3] == 1)
                 osd_cd_play_audio_track(bcdbin[pce_cd_temp_play[2]]);
               else
*/
	      if ((pce_cd_temp_play[0] |
		   pce_cd_temp_play[1] |
		   pce_cd_temp_stop[0] | pce_cd_temp_stop[1]) == 0)
		{
		  if (CD_emulation == 5)
		    HCD_play_track (bcdbin[pce_cd_temp_play[2]], 1);
		  else
		    osd_cd_play_audio_track (bcdbin[pce_cd_temp_play[2]]);
		}
	      else
		{
		  if (CD_emulation == 5)
		    HCD_play_sectors (Time2Frame (bcdbin[pce_cd_temp_play[2]],
						  bcdbin[pce_cd_temp_play[1]],
						  bcdbin[pce_cd_temp_play[0]]),
				      Time2Frame (bcdbin[pce_cd_temp_stop[2]],
						  bcdbin[pce_cd_temp_stop[1]],
						  bcdbin[pce_cd_temp_stop[0]]),
				      pce_cd_temp_stop[3] == 1);
		  else
		    osd_cd_play_audio_range (bcdbin[pce_cd_temp_play[2]],
					     bcdbin[pce_cd_temp_play[1]],
					     bcdbin[pce_cd_temp_play[0]],
					     bcdbin[pce_cd_temp_stop[2]],
					     bcdbin[pce_cd_temp_stop[1]],
					     bcdbin[pce_cd_temp_stop[0]]);
		}
	      Log ("play from %d:%d:%d:(%d) to %d:%d:%d:(%d)\nloop = %d\n",
		   bcdbin[pce_cd_temp_play[2]],
		   bcdbin[pce_cd_temp_play[1]],
		   bcdbin[pce_cd_temp_play[0]],
		   pce_cd_temp_play[3],
		   bcdbin[pce_cd_temp_stop[2]],
		   bcdbin[pce_cd_temp_stop[1]],
		   bcdbin[pce_cd_temp_stop[0]],
		   pce_cd_temp_stop[3], pce_cd_temp_stop[3] == 1);

	    }
	  break;
	case 0xde:

#ifdef CD_DEBUG
	  Log (" Arg for 0xde command is %X, command count is %d\n",
	       io.cd_port_1801, pce_cd_cmdcnt);
#endif

	  if (pce_cd_cmdcnt)
	    pce_cd_temp_dirinfo[pce_cd_cmdcnt] = io.cd_port_1801;
	  else
	    {
	      // We have received two arguments in pce_cd_temp_dirinfo
	      // We can use only one
	      // There's an argument indicating the kind of info we want
	      // and an optional argument for track number

	      pce_cd_temp_dirinfo[0] = io.cd_port_1801;

#ifdef CD_DEBUG
	      Log
		(" I'll answer to 0xde command request\nArguments are %x, %x, %x, %x\n",
		 pce_cd_temp_dirinfo[0], pce_cd_temp_dirinfo[1],
		 pce_cd_temp_dirinfo[2], pce_cd_temp_dirinfo[3]);
#endif

	      switch (pce_cd_temp_dirinfo[1])
		{
		case 0:
		  // We want info on number of first and last track

		  switch (CD_emulation)
		    {
		    case 2:
		    case 3:
		    case 4:
		      pce_cd_dirinfo[0] = binbcd[01];	// Number of first track  (BCD)
		      pce_cd_dirinfo[1] = binbcd[nb_max_track];	// Number of last track (BCD)
		      break;
		    case 1:
		      {
			int first_track, last_track;
			osd_cd_nb_tracks (&first_track, &last_track);
			pce_cd_dirinfo[0] = binbcd[first_track];
			pce_cd_dirinfo[1] = binbcd[last_track];
		      }
		      break;
		    case 5:
		      Log ("HCD: first track %d, last track %d\n",
			   HCD_first_track, HCD_last_track);
		      pce_cd_dirinfo[0] = binbcd[HCD_first_track];
		      pce_cd_dirinfo[1] = binbcd[HCD_last_track];
		      break;
		    }		// switch CD emulation

		  cd_read_buffer = pce_cd_dirinfo;
		  pce_cd_read_datacnt = 2;

#ifdef CD_DEBUG
		  Log (" Data resulting of 0xde request is %x and %x\n",
		       cd_read_buffer[0], cd_read_buffer[1]);
#endif
		  break;

		case 2:

		  // We want info on the track whose number is pce_cd_temp_dirinfo[0]

		  switch (CD_emulation)
		    {
		    case 2:
		    case 3:
		    case 4:
		    case 5:

		      pce_cd_dirinfo[0] =
			CD_track[bcdbin[pce_cd_temp_dirinfo[0]]].beg_min;
		      pce_cd_dirinfo[1] =
			CD_track[bcdbin[pce_cd_temp_dirinfo[0]]].beg_sec;
		      pce_cd_dirinfo[2] =
			CD_track[bcdbin[pce_cd_temp_dirinfo[0]]].beg_fra;
		      pce_cd_dirinfo[3] =
			CD_track[bcdbin[pce_cd_temp_dirinfo[0]]].type;

#ifdef CD_DEBUG
		      Log ("Type of track %d is %d\n",
			   bcdbin[pce_cd_temp_dirinfo[0]],
			   CD_track[bcdbin[pce_cd_temp_dirinfo[0]]].type);
#endif
		      break;
		    case 1:
		      {
			int Min, Sec, Fra, Ctrl;
			osd_cd_track_info (bcdbin[pce_cd_temp_dirinfo[0]],
					   &Min, &Sec, &Fra, &Ctrl);

			pce_cd_dirinfo[0] = binbcd[Min];
			pce_cd_dirinfo[1] = binbcd[Sec];
			pce_cd_dirinfo[2] = binbcd[Fra];
			pce_cd_dirinfo[3] = Ctrl;

			Log
			  ("The control byte of the audio track #%d is 0x%02X\n",
			   bcdbin[pce_cd_temp_dirinfo[0]], pce_cd_dirinfo[3]);

			break;

		      }		// case CD emulation = 1

		    }		// switch CD emulation

		  pce_cd_read_datacnt = 3;
		  cd_read_buffer = pce_cd_dirinfo;

		  break;

		case 1:

		  switch (CD_emulation)
		    {
		    case 1:
		      {

			int min, sec, fra;

			osd_cd_length (&min, &sec, &fra);

			pce_cd_dirinfo[0] = binbcd[min];
			pce_cd_dirinfo[1] = binbcd[sec];
			pce_cd_dirinfo[2] = binbcd[fra];

			break;
		      }		// case Cd emulation = 1
		    default:
		      pce_cd_dirinfo[0] = 0x25;
		      pce_cd_dirinfo[1] = 0x06;
		      pce_cd_dirinfo[2] = 0x00;
		    }		// switch CD emulation

		  pce_cd_read_datacnt = 3;
		  cd_read_buffer = pce_cd_dirinfo;

		  break;

		}		// switch command of request 0xde

	    }			// end if of request 0xde (receiving command or executing them)

	}			// switch of request

    }				// end if of command arg or new request
  else
    {

      // it's a command ID we're receiving

#ifdef CD_DEBUG
      fprintf (stderr, "Command byte received: 0x%02x.\n", io.cd_port_1801);
#endif

      switch (io.cd_port_1801)
	{
	case 0x00:
	  io.cd_port_1800 = 0xD8;
	  break;
	case 0x08:
	  pce_cd_curcmd = io.cd_port_1801;
	  pce_cd_cmdcnt = 4;
	  break;
	case 0xD8:
	  pce_cd_curcmd = io.cd_port_1801;
	  pce_cd_cmdcnt = 4;
	  break;
	case 0xD9:
	  pce_cd_curcmd = io.cd_port_1801;
	  pce_cd_cmdcnt = 4;
	  break;
	case 0xDA:
	  pce_cd_curcmd = io.cd_port_1801;
	  pce_cd_cmdcnt = 0;

	  if (CD_emulation == 1)
	    osd_cd_stop_audio ();
	  else if (CD_emulation == 5)
	    HCD_pause_playing ();

	  break;
	case 0xDE:
	  /* Get CD directory info */
	  /* First arg is command? */
	  /* Second arg is track? */
	  io.cd_port_1800 = 0xd0;
	  pce_cd_cmdcnt = 2;
	  pce_cd_read_datacnt = 3;	/* 4 bytes */
	  pce_cd_curcmd = io.cd_port_1801;
	  break;
	}

/*
        if (cd_port_1801 == 0x00) {
            cd_port_1800 = 0xd8;
        } else if (cd_port_1801 == 0x08) {
            pce_cd_curcmd = cd_port_1801;
            pce_cd_cmdcnt = 4;
        } else if (cd_port_1801 == 0xd8) {
            pce_cd_cmdcnt = 4;
            pce_cd_curcmd = cd_port_1801;
        } else if (cd_port_1801 == 0xd9) {
            pce_cd_cmdcnt = 4;
            pce_cd_curcmd = cd_port_1801;
        } else if (cd_port_1801 == 0xde) {
            // Get CD directory info
            // First arg is command?
            // Second arg is track?
            cd_port_1800 = 0xd0;
            pce_cd_cmdcnt = 2;
            pce_cd_read_datacnt = 3; // 4 bytes
            pce_cd_curcmd = cd_port_1801;
        }
*/

    }
}

UChar pce_cd_handle_read_1800(UInt16 A)
{
  switch (A & 15)
    {
    case 0:
      return io.cd_port_1800;
    case 1:
      {
        UChar retval;

        if (cd_read_buffer)
          {
            retval = *cd_read_buffer++;
            if (pce_cd_read_datacnt == 2048)
              {
                pce_cd_read_datacnt--;

#ifndef FINAL_RELEASE
                fprintf (stderr, "Data count fudge\n");
#endif

              }
            if (!pce_cd_read_datacnt)
              cd_read_buffer = 0;
          }
        else
          retval = 0;
        return retval;
      }

    case 2:
      return io.cd_port_1802;

    case 3:

      {

        static UChar tmp_res = 0x02;

        tmp_res = 0x02 - tmp_res;

        io.backup = DISABLE;

        /* TEST */// return 0x20;

        return tmp_res | 0x20;

      }

      /* TEST */
    case 4:
      return io.cd_port_1804;

      /* TEST */
    case 5:
      return 0x50;

      /* TEST */
    case 6:
      return 0x05;

    case 0x0A:
#ifndef FINAL_RELEASE
      Log ("HARD : Read %x from ADPCM[%04X] to VRAM : 0X%04X\n", PCM[io.adpcm_rptr], io.adpcm_rptr, io.VDC[MAWR].W * 2);
#endif

      if (!io.adpcm_firstread)
        return PCM[io.adpcm_rptr++];
      else
        {
          io.adpcm_firstread--;
          return NODATA;
        }

    case 0x0B:	/* TEST */
      return 0x00;
    case 0x0C:	/* TEST */
      return 0x01;	// 0x89
    case 0x0D:	/* TEST */
      return 0x00;

    case 8:
      if (pce_cd_read_datacnt)
        {
          UChar retval;

          if (cd_read_buffer)
            retval = *cd_read_buffer++;
          else
            retval = 0;

          if (!--pce_cd_read_datacnt)
            {
              cd_read_buffer = 0;
              if (!--cd_sectorcnt)
                {
#ifndef FINAL_RELEASE
                  fprintf (stderr,
                           "Sector data count over.\n");
#endif
                  io.cd_port_1800 |= 0x10;
                  pce_cd_curcmd = 0;
                }
              else
                {
#ifndef FINAL_RELEASE
                  fprintf (stderr,
                           "Sector data count %d.\n",
                           cd_sectorcnt);
#endif
                  pce_cd_read_sector ();
                }
            }
          return retval;
        }
      break;
    }
  // FIXME: what to return here?
  return 0;
}


void pce_cd_handle_write_1800(UInt16 A, UChar V)
{
  switch (A & 15)
    {

    case 7:
      io.backup = ENABLE;
      return;

    case 0:
      if (V == 0x81)
        io.cd_port_1800 = 0xD0;
      return;
    case 1:
      io.cd_port_1801 = V;
      if (!pce_cd_cmdcnt)
        switch (V)
          {
          case 0:
            /*
              #ifndef FINAL_RELEASE
              fprintf(stderr,"RESET? command at 1801\n");
              #endif
            */
            return;
          case 3:
            /*
              #ifndef FINAL_RELEASE
              fprintf(stderr,"GET SYSTEM STATUS? command at 1801\n");
              #endif
            */
            return;
          case 8:
            /*
              #ifndef FINAL_RELEASE
              fprintf(stderr,"READ SECTOR command at 1801\n");
              #endif*/
            return;
          case 0x81:
            /*
              #ifndef FINAL_RELEASE
              fprintf(stderr,"ANOTHER RESET? command at 1801\n");
              #endif
            */
            io.cd_port_1800 = 0x40;
            return;
          case 0xD8:
          case 0xD9:
            /*
              #ifndef FINAL_RELEASE
              fprintf(stderr,"PLAY AUDIO? command at 1801\n");
              #endif
            */
            return;

          case 0xDA:
            /*
              #ifndef FINAL_RELEASE
              fprintf(stderr,"PAUSE AUDIO PLAYING? command at 1801\n");
              #endif
            */
            return;

          case 0xDD:
            /*
              #ifndef FINAL_RELEASE
              fprintf(stderr,"READ Q CHANNEL? command at 1801\n");
              #endif
            */
            return;
          case 0xDE:
            /*
              #ifndef FINAL_RELEASE
              fprintf(stderr,"GET DIRECTORY INFO? command at 1801\n");
              #endif
            */
            return;

          default:
            /*
              #ifndef FINAL_RELEASE
              if (!pce_cd_cmdcnt)
              fprintf(stderr,"ERROR, unknown command %x at 1801\n",V);
              #endif
            */
            return;
          }

      return;

    case 2:
#ifndef FINAL_RELEASE
      // fprintf(stderr,"trying to access port 1802 in write\n");
#endif

      if ((!(io.cd_port_1802 & 0x80)) && (V & 0x80))
        {
          io.cd_port_1800 &= ~0x40;
        }
      else if ((io.cd_port_1802 & 0x80) && (!(V & 0x80)))
        {
          io.cd_port_1800 |= 0x40;

#ifndef FINAL_RELEASE
          Log ("ADPCM trans = %d\n", pce_cd_adpcm_trans_done);
#endif
          if (pce_cd_adpcm_trans_done)
            {

#ifndef FINAL_RELEASE
              Log ("ack the DMA transfert of ADPCM data\n");
#endif

              io.cd_port_1800 |= 0x10;
              pce_cd_curcmd = 0x00;
              pce_cd_adpcm_trans_done = 0;

            }

          if (io.cd_port_1800 & 0x08)
            {
              /*              deb_printf("pce_cd: data byte acknowledged.\n"); */
              if (io.cd_port_1800 & 0x20)
                {
                  io.cd_port_1800 &= ~0x80;
                }
              else if (!pce_cd_read_datacnt)
                {
                  if (pce_cd_curcmd == 0x08)
                    {
                      if (!--cd_sectorcnt)
                        {
#ifndef FINAL_RELEASE
                          fprintf (stderr, "sector data count over.\n");
#endif
                          io.cd_port_1800 |= 0x10;	/* wrong */
                          pce_cd_curcmd = 0x00;
                        }
                      else
                        {
#ifndef FINAL_RELEASE
                          fprintf (stderr, "sector data count %d.\n",
                                   cd_sectorcnt);
#endif
                          pce_cd_read_sector ();
                        }
                    }
                  else
                    {
                      if (io.cd_port_1800 & 0x10)
                        {
                          io.cd_port_1800 |= 0x20;
                        }
                      else
                        {
                          io.cd_port_1800 |= 0x10;
                        }
                    }
                }
              else
                {
                  pce_cd_read_datacnt--;
                }
            }
          else
            {
              pce_cd_handle_command ();
            }
        }

      io.cd_port_1802 = V;
      return;
    case 4:
      if (V & 2)
        {			// Reset asked
          // do nothing for now
#ifndef FINAL_RELEASE
          fprintf (stderr, "Reset mode for CD asked\n");
#endif

          switch (CD_emulation)
            {
            case 1:
              if (osd_cd_init (ISO_filename) != 0)
                {
                  Log ("CD rom drive couldn't be initialised\n");
                  exit (4);
                }
              break;
            case 2:
            case 3:
            case 4:
              fill_cd_info ();
              break;

            case 5:
              fill_HCD_info(ISO_filename);
              break;
            }

          Wr6502 (0x222D, 1);
          // This byte is set to 1 if a disc if present

          //cd_port_1800 &= ~0x40;
          io.cd_port_1804 = V;
        }
      else
        {			// Normal utilisation
#ifndef FINAL_RELEASE
          fprintf (stderr, "Normal mode for CD asked\n");
#endif
          io.cd_port_1804 = V;
          // cd_port_1800 |= 0x40; // Maybe the previous reset is enough
          // cd_port_1800 |= 0xD0;
          // Indicates that the Hardware is ready after such a reset
        }
      return;

    case 8:
      io.adpcm_ptr.B.l = V;
      return;
    case 9:
      io.adpcm_ptr.B.h = V;
      return;

    case 0x0A:
      PCM[io.adpcm_wptr++] = V;
#ifndef FINAL_RELEASE
      fprintf (stderr, "Wrote %02X to ADPCM buffer[%04X]\n", V,
               io.adpcm_wptr - 1);
      Log ("wrote to ADPCM, %02X at PCM[0X%04X]\n", V, io.adpcm_wptr - 1);
#endif
      return;
    case 0x0B:		// DMA enable ?

      if ((V & 2) && (!(cd_port_180b & 2)))
        {
          issue_ADPCM_dma ();
          cd_port_180b = V;
          return;
        }


      /* TEST */
      if (!V)
        {
          io.cd_port_1800 &= ~0xF8;
          io.cd_port_1800 |= 0xD8;
        }

      cd_port_180b = V;

      return;

    case 0x0D:

      if ((V & 0x03) == 0x03)
        {
          io.adpcm_dmaptr = io.adpcm_ptr.W;	// set DMA pointer
#ifndef FINAL_RELEASE
          fprintf (stderr, "Set DMA pointer to %x\n", io.adpcm_dmaptr);
#endif
        }

      if (V & 0x04)
        {
          io.adpcm_wptr = io.adpcm_ptr.W;	// set write pointer
#ifndef FINAL_RELEASE
          fprintf (stderr, "Set write pointer to %x\n", io.adpcm_wptr);
#endif
        }

      if (V & 0x08)		// set read pointer
        {
          io.adpcm_rptr = io.adpcm_ptr.W;
          io.adpcm_firstread = 2;

#ifndef FINAL_RELEASE
          fprintf (stderr, "Set read pointer to %x\n", io.adpcm_rptr);
#endif

        }

      /* TEST
         else { io.adpcm_rptr = io.adpcm_ptr.W; io.adpcm_firstread = TRUE; }
      */
      /* TEST */
      //if (V&0x08) io.

      if (V & 0x80)
        {			// ADPCM reset
#ifndef FINAL_RELEASE
          fprintf (stderr, "Reset mode for ADPCM\n");
#endif
        }
      else
        {			// Normal ADPCM utilisation
#ifndef FINAL_RELEASE
          fprintf (stderr, "Normal mode for ADPCM\n");
#endif
        }



      return;

    case 0xe:		// Set ADPCM playback rate
      io.adpcm_rate = 32 / (16 - (V & 15));

#ifndef FINAL_RELEASE
      fprintf (stderr, "ADPCM rate set to %d kHz\n", io.adpcm_rate);
#endif
      return;

    case 0xf:		// don't know how to use it
#ifndef FINAL_RELEASE
      fprintf (stderr, "Fade setting to %d\n", V);
#endif

      cd_fade = V;
      return;
    }			// A&15 switch, i.e. CD ports
}
