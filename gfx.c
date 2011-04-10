/*
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Library General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

/**************************************************************************/
/*                 Generic Graphic source file                            */
/*                                                                        */
/*         Adapted by Zeograd (Olivier Jolly) for using Allegro           */
/*                                                                        */
/**************************************************************************/

#include "pce.h"
#include "utils.h"
#include "config.h"

typedef struct {
  UChar r,g,b;
} rgb_map_struct;

rgb_map_struct rgb_map[256];

void SetPalette(void)
{
  UChar i;

  osd_gfx_set_color(255, 0x3f, 0x3f, 0x3f);
  rgb_map[255].r = 255;
  rgb_map[255].b = 255;
  rgb_map[255].g = 255;

  for (i = 0; i < 255; i++)
    {
      osd_gfx_set_color(i, (i & 0x1C) << 1, (i & 0xe0) >> 2, (i & 0x03) << 4);
      rgb_map[i].r = (i & 0x1C) << 3;
      rgb_map[i].g = (i & 0xe0);
      rgb_map[i].b = (i & 0x03) << 6;
    }
#if defined(SDL)

  olay_cmap[255].r = (Uint8) ((0.299 * 0xff) + (0.587 * 0xff) + (0.114 * 0xff));
  olay_cmap[255].g = (Uint8) ((0xff - olay_cmap[i].r) * 0.565 + 128);
  olay_cmap[255].b = (Uint8) ((0xff - olay_cmap[i].r) * 0.713 + 128);

  for (i = 0; i < 255; i++)
    {
      int r,g,b;
      r = (i & 0x1C) << 3;
      g = (i & 0xe0);
      b = (i & 0x03) << 6;
      olay_cmap[i].r = (Uint8)((0.299 * r) + (0.587 * g) + (0.114 * b));
      olay_cmap[i].g = (Uint8)((b - olay_cmap[i].r) * 0.565 + 128);
      olay_cmap[i].b = (Uint8)((r - olay_cmap[i].r) * 0.713 + 128);
    }

#endif
}


/*!
 * calc_fullscreen_aspect:
 * Generic utility that takes the width x height of the current output screen
 * and sets up a gfx lib independent struct generic_rect (gfx.h) with the
 * aspect-correct scaling values, provided option.want_fullscreen_aspect
 * has been set in the config or via the command line.
 */
void calc_fullscreen_aspect(unsigned short physical_screen_width,
                            unsigned short physical_screen_height,
                            struct generic_rect *rect,
                            unsigned short pce_screen_width,
                            unsigned short pce_screen_height)
{
  /*
   * Routine not called often so extra sanity checks pose no penalty.
   */
  if (physical_screen_height == 0)
    {
      printf("calc_fullscreen_aspect: physical_screen_height is 0!  Aborting . . .\n");
      exit(0);
    }

  if (pce_screen_width == 0)
    {
      printf("calc_fullscreen_aspect: pce_screen_width is 0!  Aborting . . .\n");
      exit(0);
    }

  if (option.want_fullscreen_aspect)
    {
      float physical_screen_ratio, pce_ratio;
      int new_size;

      physical_screen_ratio = (float) physical_screen_width / physical_screen_height;

      pce_ratio = (pce_screen_width / physical_screen_ratio) / pce_screen_height;

      if (pce_ratio < 1.0)
        {
          new_size = (int)(physical_screen_width * pce_ratio);

          (*rect).start_x = (unsigned short int)((physical_screen_width - new_size) / 2);
          (*rect).start_y = 0;
          (*rect).end_x = (unsigned short int)new_size;
          (*rect).end_y = physical_screen_height;
        }
      else
        {
          new_size = (int)(physical_screen_height / pce_ratio);

          (*rect).start_x = 0;
          (*rect).start_y = (unsigned short int)((physical_screen_height - new_size) / 2);
          (*rect).end_x = physical_screen_width;
          (*rect).end_y = (unsigned short int)new_size;
        }
    }
  else
    {
      (*rect).start_x = (*rect).start_y = 0;
      (*rect).end_x = physical_screen_width;
      (*rect).end_y = physical_screen_height;
    }
}

//! Computes the new screen height and eventually change the screen mode
void change_pce_screen_height()
{
  //! minimal theorical line where to begin drawing
  int min_display;

  //! maximal theorical line where to end drawing
  int max_display;

  int cur_display;

  int temp_vds = io.VDC[VPR].B.h;
  int temp_vsw = io.VDC[VPR].B.l;
  int temp_vdw = (int)io.VDC[VDW].W;
  int temp_vcr = (int)io.VDC[VCR].W;

#if defined(GFX_DEBUG)
  printf("Changing pce screen mode\nVDS = %04x VSW = %04x VDW = %04x VCR = %04x\n",
         temp_vds,
         temp_vsw,
         temp_vdw,
         temp_vcr
         );
  // getchar();
#endif

  if (temp_vdw == 0)
    return;

  min_display = temp_vds + temp_vsw;

  max_display = cur_display = min_display;
  while (cur_display < 242 + 14)
    {
      cur_display += temp_vdw;
      max_display = cur_display;

      cur_display += 3 + temp_vcr;

#if defined(GFX_DEBUG)
      printf("Adding vdw to the height of graphics, cur_display = %d\n", cur_display);
#endif
    }

  min_display = (min_display > 14 ? min_display : 14);
  max_display = (max_display < 242 + 14 ? max_display : 242 + 14);


  /*
  if (option.want_television_size_emulation)
    {
      if (max_display - min_display >= 224)
        {
          int offset;

          offset = (max_display - min_display + 1 - 224) / 2;

          min_display += offset;
          max_display = min_display + 223;
        }
    }
  */

  io.vdc_min_display = (UInt16)min_display;
  io.vdc_max_display = (UInt16)max_display;

#if defined(GFX_DEBUG)
  // printf("min_display = %d\tmax_display = %d\n", min_display, max_display);
#endif

  //! Number of lines to render
  io.screen_h = max_display - min_display + 1;

#if defined(GFX_DEBUG)
  // printf("%d lines to render\n", io.screen_h);
#endif

  (*osd_gfx_driver_list[video_driver].mode) ();
}

#if defined(NEW_GFX_ENGINE)

#define MAX_GFX_CONTEXT_SLOT_NUMBER 2

static gfx_context saved_gfx_context[MAX_GFX_CONTEXT_SLOT_NUMBER];

//! Whether we need to draw pending lines
static int gfx_need_redraw;

//! Frame to skip before the next frame to render
static int UCount = 0;

//! Whether we should change video mode after drawing the current frame
int gfx_need_video_mode_change = 0;

void
save_gfx_context(int slot_number)
{

  gfx_context *destination_context;

  destination_context = saved_gfx_context + slot_number;

  if (slot_number == 0)
    {
      /*
      if ((destination_context->scroll_x == ScrollX) &&
          (destination_context->scroll_y == ScrollY) &&
          (destination_context->scroll_y_diff == ScrollYDiff) &&
          (destination_context->cr == io.VDC[CR].W))
        {
#if defined(GFX_DEBUG)
          gfx_debug_printf("Canceled primary context saving, nothing changed");
#endif
          return;
        }
      */

      if (gfx_need_redraw == 0)
        gfx_need_redraw = 1;
      else // Context is already saved and we haven't render the lines using it
        {
#if defined(GFX_DEBUG)
          gfx_debug_printf("Canceled context saving as a previous one wasn't consumed yet");
#endif
          return;
        }
    }
  if (slot_number >= MAX_GFX_CONTEXT_SLOT_NUMBER)
    {
      Log("Internal error in %s(%s), slot %d >= %d\n",
          __FUNCTION__,
          __FILE__,
          slot_number,
          MAX_GFX_CONTEXT_SLOT_NUMBER
          );

      return;
    }

#if defined(GFX_DEBUG)
  gfx_debug_printf("Saving context %d, scroll = (%d,%d,%d), CR = 0x%02d",
                   slot_number,
                   ScrollX,
                   ScrollY,
                   ScrollYDiff,
                   io.VDC[CR].W);
#endif

  destination_context->scroll_x = ScrollX;
  destination_context->scroll_y = ScrollY;
  destination_context->scroll_y_diff = ScrollYDiff;
  destination_context->cr = io.VDC[CR].W;
}

void
load_gfx_context(int slot_number)
{

  gfx_context *source_context;

  if (slot_number >= MAX_GFX_CONTEXT_SLOT_NUMBER)
    {
      Log("Internal error in %s(%s), slot %d >= %d\n",
          __FUNCTION__,
          __FILE__,
          slot_number,
          MAX_GFX_CONTEXT_SLOT_NUMBER
          );

      return;
    }

  source_context = saved_gfx_context + slot_number;

  ScrollX = source_context->scroll_x;
  ScrollY = source_context->scroll_y;
  ScrollYDiff = source_context->scroll_y_diff;
  io.VDC[CR].W = source_context->cr;

#if defined(GFX_DEBUG)
  gfx_debug_printf("Restoring context %d, scroll = (%d,%d,%d), CR = 0x%02d",
                   slot_number,
                   ScrollX,
                   ScrollY,
                   ScrollYDiff,
                   io.VDC[CR].W);
#endif

}


//! render lines
/*
  render lines into the buffer from min_line to max_line, inclusive
        Refresh* draw things from min to max line given, with max exclusive
*/
void
render_lines(int min_line, int max_line)
{

#if !defined(FINAL_RELEASE)
  //printf("render lines %3d - %3d in %s\n", min_line, max_line, __FILE__);
#endif

  save_gfx_context(1);

  load_gfx_context(0);

  if (!UCount) // Either we're in frameskip = 0 or we're in the frame to draw
    {
      if (SpriteON && SPONSwitch)
        RefreshSpriteExact (min_line, max_line - 1, 0);

      RefreshLine (min_line, max_line - 1);

      if (SpriteON && SPONSwitch)
        RefreshSpriteExact (min_line, max_line - 1, 1);
    }

  load_gfx_context(1);

  gfx_need_redraw = 0;
}

//! Rewritten version of Loop6502 from scratch, called when each line drawing should occur
/* TODO:
   - sprite #0 collision checking (occur as soon as the sprite #0 is shown and overlap another sprite
   - frame skipping to test
*/
UChar
Loop6502()
{
  static int video_dump_countdown = 0;
  static int display_counter = 0;
  static int last_display_counter = 0;
  static int satb_dma_counter = 0;
  UChar return_value = INT_NONE;

  io.vdc_status &= ~(VDC_RasHit | VDC_SATBfinish);

  // Count dma delay

  if (satb_dma_counter > 0)
    {
      // A dma is in progress
      satb_dma_counter --;

      if (!satb_dma_counter)
        {
          // dma has just finished
          if (SATBIntON)
            {
              io.vdc_status |= VDC_SATBfinish;
              return_value = INT_IRQ;
            }
        }
    }

  // Test raster hit
  if (RasHitON)
    {
      if (((io.VDC[RCR].W & 0x3FF) >= 0x40) && ((io.VDC[RCR].W & 0x3FF) <= 0x146))
        {
          UInt16 temp_rcr = (UInt16)((io.VDC[RCR].W & 0x3FF) - 0x40);

          if (scanline == (temp_rcr + io.VDC[VPR].B.l + io.VDC[VPR].B.h) % 263)
            {
              // printf("\n---------------------\nRASTER HIT (%d)\n----------------------\n", scanline);
              io.vdc_status |= VDC_RasHit;
              return_value = INT_IRQ;
            }

        }
      else
        {
          // printf("Raster counter out of bounds (%d)\n", io.VDC[RCR].W);
        }
    }
  //  else
  //    printf("Raster disabled\n");

  // Rendering of tiles / sprites

  if (scanline < 14)
    {
      gfx_need_redraw = 0;
    }
  else if (scanline < 14 + 242)
    {

      if (scanline == 14)
        {

          last_display_counter = 0;
          display_counter = 0;
          ScrollYDiff = 0;
          oldScrollYDiff = 0;

          // Signal that we've left the VBlank area
          io.vdc_status &= ~VDC_InVBlank;
#if defined(GFX_DEBUG)
          gfx_debug_printf("Cleaning VBlank bit from vdc_status (now, 0x%02x)", io.vdc_status);
#endif
        }

      if (scanline == io.vdc_min_display)
        {
          gfx_need_redraw = 0;

          save_gfx_context(0);

#if defined(GFX_DEBUG) && !defined(FINAL_RELEASE)
          printf("FORCED SAVE OF GFX CONTEXT\n");
#endif

        }

      if ((scanline >= io.vdc_min_display) && (scanline <= io.vdc_max_display))
        {
          if (gfx_need_redraw) // && scanline > io.vdc_min_display) // We got render things before being on the second line
            {
              render_lines(last_display_counter, display_counter);
              last_display_counter = display_counter;
            }

          display_counter ++;
        }
    }
  else if (scanline < 14 + 242 + 4)
    {

      if (scanline == 14 + 242)
        {

          save_gfx_context(0);

          render_lines(last_display_counter, display_counter);

          if (video_dump_flag)
            {
              if (video_dump_countdown)
                video_dump_countdown--;
              else
                {
                  dump_video_frame();
                  video_dump_countdown = 3;
                }
            }

          if (gfx_need_video_mode_change)
            {
              gfx_need_video_mode_change = 0;
              change_pce_screen_height();
            }

          if (osd_keyboard ())
            return INT_QUIT;

          if (!UCount)
            RefreshScreen();

#if defined(GTK)
          /*@ -unrecog */
          while (gtk_events_pending())
	    {
	      if (gtk_main_iteration())
		{
		  return INT_QUIT;
		}
	    }
          /*@ =unrecog */
#endif
          /*@-preproc */
#warning "place this better"
          /*@=preproc */
          if (CheckSprites ())
            io.vdc_status |= VDC_SpHit;
          else
            io.vdc_status &= ~VDC_SpHit;

          if (!UCount)
            {
#if defined(ENABLE_NETPLAY)
              if (option.want_netplay != INTERNET_PROTOCOL)
                {
                  /* When in internet protocol mode, it's the server which is in charge of throlling */
                  wait_next_vsync();
                }
#else
              wait_next_vsync();
#endif /* NETPLAY_ENABLE */

              UCount = UPeriod;
            }
          else
            UCount--;

          /* VRAM to SATB DMA */
          if (io.vdc_satb == 1 || io.VDC[DCR].W & 0x0010)
            {
#if defined(WORDS_BIGENDIAN)
              swab(VRAM + io.VDC[SATB].W * 2, SPRAM, 64 * 8);
#else
              memcpy (SPRAM, VRAM + io.VDC[SATB].W * 2, 64 * 8);
#endif
              io.vdc_satb = 1;
              io.vdc_status &= ~VDC_SATBfinish;

              // Mark satb dma end interuption to happen in 4 scanlines
              satb_dma_counter = 4;
            }

          if (return_value == INT_IRQ)
            io.vdc_pendvsync = 1;
          else
            {
              if (VBlankON)
                {
                  io.vdc_status |= VDC_InVBlank;
                  return_value = INT_IRQ;
                }
            }
        }

    }
  else
    {
      //Three last lines of ntsc scanlining
    }

  // Incrementing the scanline

  scanline ++;

  if (scanline >= 263)
    scanline = 0;

  if ((return_value != INT_IRQ) && io.vdc_pendvsync)
    {
      io.vdc_status |= VDC_InVBlank;
      return_value = INT_IRQ;
      io.vdc_pendvsync = 0;
    }

  if (return_value == INT_IRQ)
    {
      if (!(io.irq_mask & IRQ1))
        {
          io.irq_status |= IRQ1;
          return return_value;
        }
    }

  return INT_NONE;
}
#endif

int video_dump_flag = 0;

//! Raw dump the current frame into the buffer, for video output purposes
void dump_uyvy_frame(char* output_buffer)
{
  int x,y;
  UChar* xbuf_pointer;

  xbuf_pointer = osd_gfx_buffer;

  for (y = 0; y < io.screen_h; y++, xbuf_pointer += XBUF_WIDTH - io.screen_w)
    for (x = 0; x < io.screen_w - 1; x+=2, xbuf_pointer+=2)
      {
        *(output_buffer++) = (char)olay_cmap[*xbuf_pointer].g;
        *(output_buffer++) = (char)olay_cmap[*xbuf_pointer].r;
        *(output_buffer++) = (char)olay_cmap[*xbuf_pointer].b;
        *(output_buffer++) = (char)olay_cmap[*(xbuf_pointer+1)].r;
      }
}


//! Raw dump the current frame into the buffer, for video output purposes
void dump_yyuv_frame(char* output_buffer)
{
  int x,y;
  UChar* xbuf_pointer;

  xbuf_pointer = osd_gfx_buffer;

  for (y = 0; y < io.screen_h; y++, xbuf_pointer += XBUF_WIDTH - io.screen_w)
    for (x = 0; x < io.screen_w - 1; x+=2, xbuf_pointer+=2)
      {
        *(output_buffer++) = (char)olay_cmap[*xbuf_pointer].r;
        *(output_buffer++) = (char)olay_cmap[*(xbuf_pointer+1)].r;
        *(output_buffer++) = (char)olay_cmap[*xbuf_pointer].g;
        *(output_buffer++) = (char)olay_cmap[*xbuf_pointer].b;
      }
}

//! Raw dump the current frame into the buffer, for video output purposes
void dump_rgb_frame(char* output_buffer)
{
  int x,y;
  UChar* xbuf_pointer;

  xbuf_pointer = osd_gfx_buffer;

  for (y = 0; y < io.screen_h; y++, xbuf_pointer += XBUF_WIDTH - io.screen_w)
    for (x = 0; x < io.screen_w; x++, xbuf_pointer++)
      {
        *(output_buffer++) = (char)rgb_map[*xbuf_pointer].r;
        *(output_buffer++) = (char)rgb_map[*xbuf_pointer].g;
        *(output_buffer++) = (char)rgb_map[*xbuf_pointer].b;
      }
}

//! Raw dump the current frame into the buffer, for video output purposes
void dump_raw_frame(char* output_buffer)
{
  int y;
  UChar* xbuf_pointer;

  xbuf_pointer = osd_gfx_buffer;

  for (y = 0; y < (io.screen_h & 0xFFFE); y++, xbuf_pointer += XBUF_WIDTH, output_buffer += (io.screen_w & 0xFFFE))
    memcpy(output_buffer, xbuf_pointer, (size_t)(io.screen_w & 0xFFFE));
}


//! Raw dump the current frame into the buffers, for video output purposes
void dump_uyv_frame_separated(char* output_buffer_u, char* output_buffer_y, char* output_buffer_v)
{
  int x,y;
  UChar* xbuf_pointer;

  xbuf_pointer = osd_gfx_buffer;

  for (y = 0; y < (io.screen_h & 0xFFFE); y++, xbuf_pointer += XBUF_WIDTH - io.screen_w)
    for (x = 0; x < io.screen_w - 1; x+=2, xbuf_pointer+=2)
      {
        *(output_buffer_u++) = (char)olay_cmap[*xbuf_pointer].g;
        *(output_buffer_y++) = (char)olay_cmap[*xbuf_pointer].r;
        *(output_buffer_v++) = (char)olay_cmap[*xbuf_pointer].b;
        *(output_buffer_y++) = (char)olay_cmap[*(xbuf_pointer+1)].r;
      }
}

#if defined(DUMP_UYVY_SINGLE_FILE)

static FILE* video_output_file = NULL;

//! Start the video dump process
//! return 1 if video dumping began, else 0
int start_dump_video()
{
  char video_output_filename[PATH_MAX];
  struct tm * tm_current_time;
  time_t time_t_current_time;

  if (video_output_file != NULL)
    return 0;

  time(&time_t_current_time);
  tm_current_time = localtime(&time_t_current_time);

  snprintf(video_output_filename, PATH_MAX, "%svideo-%04d-%02d-%02d %02d-%02d-%02d",
           video_path,
           tm_current_time->tm_year + 1900,
           tm_current_time->tm_mon,
           tm_current_time->tm_mday,
           tm_current_time->tm_hour,
           tm_current_time->tm_min,
           tm_current_time->tm_sec);

  video_output_file = fopen(video_output_filename, "wb");

  return (video_output_file != NULL ? 1 : 0);
}

//! Dump the current frame into the video file
void dump_video_frame()
{
  char* frame_buffer;

  if (video_output_file == NULL)
    return;

  frame_buffer = malloc(4 * io.screen_w * io.screen_h);

  if (frame_buffer == NULL)
    return;

  dump_uyvy_frame(frame_buffer);

  fwrite(frame_buffer, 4 * io.screen_w * io.screen_h, 1, video_output_file);

  free(frame_buffer);
}

//! Stop the dump video process
void stop_dump_video()
{
  if (video_output_file != NULL)
    fclose(video_output_file);

  printf("Video dump finished on a %dx%d resolution\n", io.screen_w, io.screen_h & 0xFFFE);
}

#elif defined(DUMP_UYVY_MULTI_FILE)

static char video_output_base_filename[PATH_MAX];
static int video_output_frame_count;

//! Start the video dump process
//! return 1 if video dumping began, else 0
int start_dump_video()
{
  struct tm * tm_current_time;
  time_t time_t_current_time;

  if (video_dump_flag)
    return 0;

  time(&time_t_current_time);
  tm_current_time = localtime(&time_t_current_time);

  snprintf(video_output_base_filename, PATH_MAX, "%svideo-%04d-%02d-%02d %02d-%02d-%02d",
           video_path,
           tm_current_time->tm_year + 1900,
           tm_current_time->tm_mon,
           tm_current_time->tm_mday,
           tm_current_time->tm_hour,
           tm_current_time->tm_min,
           tm_current_time->tm_sec);

  video_output_frame_count = 0;

  // We can't do much in this case, as we don't open a global handle for dumping
  return 1;
}

//! Dump the current frame into the video file
void dump_video_frame()
{
  char *frame_buffer_u;
  char *frame_buffer_v;
  char *frame_buffer_y;

  char video_output_filename_u[PATH_MAX];
  char video_output_filename_v[PATH_MAX];
  char video_output_filename_y[PATH_MAX];

  FILE* tmp_video_output_file;

  snprintf(video_output_filename_u, PATH_MAX, "%s-%d.U",
           video_output_base_filename,
           video_output_frame_count);

  snprintf(video_output_filename_v, PATH_MAX, "%s-%d.V",
           video_output_base_filename,
           video_output_frame_count);

  snprintf(video_output_filename_y, PATH_MAX, "%s-%d.Y",
           video_output_base_filename,
           video_output_frame_count);

  frame_buffer_u = malloc((io.screen_w & 0xFFFE) * (io.screen_h & 0xFFFE));
  frame_buffer_v = malloc((io.screen_w & 0xFFFE) * (io.screen_h & 0xFFFE));
  frame_buffer_y = malloc(2 * (io.screen_w & 0xFFFE) * (io.screen_h & 0xFFFE));

  if ((frame_buffer_u == NULL) || (frame_buffer_v == NULL) || (frame_buffer_y == NULL))
    return;

  dump_uyv_frame_separated(frame_buffer_u, frame_buffer_y, frame_buffer_v);

  tmp_video_output_file = fopen(video_output_filename_u, "wb");
  if (tmp_video_output_file != NULL)
    {
      fwrite(frame_buffer_u, (io.screen_w & 0xFFFE) * (io.screen_h & 0xFFFE), 1, tmp_video_output_file);
      fclose(tmp_video_output_file);
    }

  tmp_video_output_file = fopen(video_output_filename_y, "wb");
  if (tmp_video_output_file != NULL)
    {
      fwrite(frame_buffer_y, 2 * (io.screen_w & 0xFFFE) * (io.screen_h & 0xFFFE), 1, tmp_video_output_file);
      fclose(tmp_video_output_file);
    }

  tmp_video_output_file = fopen(video_output_filename_v, "wb");
  if (tmp_video_output_file != NULL)
    {
      fwrite(frame_buffer_v,(io.screen_w & 0xFFFE) * (io.screen_h & 0xFFFE), 1, tmp_video_output_file);
      fclose(tmp_video_output_file);
    }

  video_output_frame_count ++;

  free(frame_buffer_u);
  free(frame_buffer_v);
  free(frame_buffer_y);
}

//! Stop the dump video process
void stop_dump_video()
{
  printf("Video dump finished on a %dx%d resolution\n", io.screen_w & 0xFFFE, io.screen_h & 0xFFFE);
}

#elif defined(DUMP_YYUV_SINGLE_FILE)

static FILE* video_output_file = NULL;

//! Start the video dump process
//! return 1 if video dumping began, else 0
int start_dump_video()
{
  char video_output_filename[PATH_MAX];
  struct tm * tm_current_time;
  time_t time_t_current_time;

  if (video_output_file != NULL)
    return 0;

  time(&time_t_current_time);
  tm_current_time = localtime(&time_t_current_time);

  snprintf(video_output_filename, PATH_MAX, "%svideo-%04d-%02d-%02d %02d-%02d-%02d",
           video_path,
           tm_current_time->tm_year + 1900,
           tm_current_time->tm_mon,
           tm_current_time->tm_mday,
           tm_current_time->tm_hour,
           tm_current_time->tm_min,
           tm_current_time->tm_sec);

  video_output_file = fopen(video_output_filename, "wb");

  return (video_output_file != NULL ? 1 : 0);
}

//! Dump the current frame into the video file
void dump_video_frame()
{
  char* frame_buffer;

  if (video_output_file == NULL)
    return;

  frame_buffer = malloc(4 * io.screen_w * io.screen_h);

  if (frame_buffer == NULL)
    return;

  dump_yyuv_frame(frame_buffer);

  fwrite(frame_buffer, 4 * io.screen_w * io.screen_h, 1, video_output_file);

  free(frame_buffer);
}

//! Stop the dump video process
void stop_dump_video()
{
  if (video_output_file != NULL)
    fclose(video_output_file);

  printf("Video dump finished on a %dx%d resolution\n", io.screen_w, io.screen_h & 0xFFFE);
}

#elif defined(DUMP_PPM_MULTI_FILE)

static char video_output_base_filename[PATH_MAX];
static int video_output_frame_count;

//! Start the video dump process
//! return 1 if video dumping began, else 0
int start_dump_video()
{
  struct tm * tm_current_time;
  time_t time_t_current_time;

  if (video_dump_flag)
    return 0;

  time(&time_t_current_time);
  tm_current_time = localtime(&time_t_current_time);

  snprintf(video_output_base_filename, PATH_MAX, "%svideo-%04d-%02d-%02d %02d-%02d-%02d",
           video_path,
           tm_current_time->tm_year + 1900,
           tm_current_time->tm_mon,
           tm_current_time->tm_mday,
           tm_current_time->tm_hour,
           tm_current_time->tm_min,
           tm_current_time->tm_sec);

  video_output_frame_count = 0;

  // We can't do much in this case, as we don't open a global handle for dumping
  return 1;
}

//! Dump the current frame into the video file
void dump_video_frame()
{
  char *frame_buffer;
  char video_output_filename[PATH_MAX];
  FILE* tmp_video_output_file;

  snprintf(video_output_filename, PATH_MAX, "%s-%d.ppm",
           video_output_base_filename,
           video_output_frame_count);

  frame_buffer = malloc(3 * (io.screen_w & 0xFFFE) * (io.screen_h & 0xFFFE));

  if (frame_buffer == NULL)
    return;

  dump_rgb_frame(frame_buffer);

  tmp_video_output_file = fopen(video_output_filename, "wb");
  if (tmp_video_output_file != NULL)
    {
      char buf[100];

      snprintf(buf, sizeof(buf),
               "P6\n%d %d\n%d\n",
               io.screen_w & 0xFFFE, io.screen_h & 0xFFFE, 255);
      fwrite(buf, strlen(buf), 1, tmp_video_output_file);
      fwrite(frame_buffer, 3 * (io.screen_w & 0xFFFE) * (io.screen_h & 0xFFFE), 1, tmp_video_output_file);
      fclose(tmp_video_output_file);
    }

  video_output_frame_count ++;

  free(frame_buffer);
}

//! Stop the dump video process
void stop_dump_video()
{
  printf("Video dump finished on a %dx%d resolution\n", io.screen_w & 0xFFFE, io.screen_h & 0xFFFE);
}

#else

static FILE* video_output_file = NULL;
static unsigned int old_dump_crc = (unsigned)-1;
static UInt16 old_screen_w, old_screen_h;

static int video_frame_total, video_frame_skipped;

//! Start the video dump process
//! return 1 if video dumping began, else 0
int start_dump_video()
{
  char video_output_filename[PATH_MAX];
  struct tm * tm_current_time;
  time_t time_t_current_time;

  if (video_output_file != NULL)
    return 0;

  (void)time(&time_t_current_time);
  tm_current_time = localtime(&time_t_current_time);

  snprintf(video_output_filename, PATH_MAX, "%svideo-%04d-%02d-%02d %02d-%02d-%02d",
           video_path,
           tm_current_time->tm_year + 1900,
           tm_current_time->tm_mon + 1,
           tm_current_time->tm_mday,
           tm_current_time->tm_hour,
           tm_current_time->tm_min,
           tm_current_time->tm_sec);

  video_output_file = fopen(video_output_filename, "wb");

  old_dump_crc = (unsigned)-1;
  old_screen_w = -1;
  old_screen_h = -1;

  video_frame_total = 0;
  video_frame_skipped = 0;

  return (video_output_file != NULL ? 1 : 0);
}

//! Dump the current frame into the video file
void dump_video_frame()
{
  char* frame_buffer;
  int index;
  unsigned char tmp_data;
  unsigned int CRC = (unsigned)0xFFFFFFFF;

  if (video_output_file == NULL)
    return;

  frame_buffer = malloc((size_t)((io.screen_w & ~1) * (io.screen_h & ~1)));

  if (frame_buffer == NULL)
    return;

  dump_raw_frame(frame_buffer);

  // Compute the rendered buffer CRC
  for (index = 0; index < ((io.screen_w & ~1) * (io.screen_h & ~1)); index++)
    {
      tmp_data = (unsigned char)frame_buffer[index];
      tmp_data ^= CRC;
      CRC >>= 8;
      CRC ^= TAB_CONST[tmp_data];
    }

  if ((old_screen_w != (UInt16)(io.screen_w & ~1)) || (old_screen_h != (UInt16)(io.screen_h & ~1)) || (CRC != old_dump_crc))
    {
      UInt16 dum;

      dum = htons(io.screen_w & ~1);
      (void)fwrite(&dum, 2, 1, video_output_file);

      dum = htons(io.screen_h & ~1);
      (void)fwrite(&dum, 2, 1, video_output_file);

      (void)fwrite(frame_buffer, (size_t)((io.screen_w & ~1) * (io.screen_h & ~1)), 1, video_output_file);

    }
  else
    {
      UInt32 dum;

      dum = 0;

      (void)fwrite(&dum, 4, 1, video_output_file);

      video_frame_skipped ++;
    }

  free(frame_buffer);
  old_screen_h = (UInt16)(io.screen_h & ~1);
  old_screen_w = (UInt16)(io.screen_w & ~1);
  old_dump_crc = CRC;
  video_frame_total ++;
}

//! Stop the dump video process
void stop_dump_video()
{
  char finish_message[100];

  if (video_output_file != NULL)
    fclose(video_output_file);

  snprintf(finish_message, 100, "Video dump finished, %d frames dumped, %d frames compressed (%.2f%% compression)",
           video_frame_total,
           video_frame_skipped,
           (video_frame_total != 0 ? 100.0 * video_frame_skipped / video_frame_total : 100));

  osd_gfx_set_message(finish_message);
}

#endif

#if defined(GFX_DEBUG)
void gfx_debug_printf(char *format, ...)
{
  FILE *log_file;
  char buf[256];

  va_list ap;
  va_start (ap, format);
  vsprintf (buf, format, ap);
  va_end (ap);

  fprintf (stderr, "%3d: ", scanline);
  fprintf (stderr, buf);
  fprintf (stderr, "\n");

  fflush (stderr);
}
#endif
