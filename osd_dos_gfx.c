#include "osd_gfx.h"

BITMAP* OSD_MESSAGE_SPR = NULL;

int blit_x,blit_y;
// where must we blit the screen buffer on screen

int screen_blit_x, screen_blit_y;
// where on the screen we must blit XBuf

BITMAP *EAGLE_buf=NULL;
// the buffer where we will put eagleized video

int osd_gfx_init_normal_mode();
void osd_gfx_put_image_normal();

int osd_gfx_init_eagle_mode();
void osd_gfx_put_image_eagle();

int osd_gfx_init_scanline_mode();
void osd_gfx_put_image_scanline();

void osd_gfx_dummy_func();

osd_gfx_driver osd_gfx_driver_list[3] =
 {
  {osd_gfx_init_normal_mode, osd_gfx_put_image_normal, osd_gfx_dummy_func},
  {osd_gfx_init_eagle_mode, osd_gfx_put_image_eagle, osd_gfx_dummy_func},
  {osd_gfx_init_scanline_mode, osd_gfx_put_image_scanline, osd_gfx_dummy_func}
  };

void osd_gfx_dummy_func(void)
{
 return;
 }

/*****************************************************************************

    Function: osd_gfx_put_image_normal

    Description: draw the raw computed picture to screen, without any effect
       trying to center it (I bet there is still some work on this, maybe not
                            in this function)
    Parameters: none
    Return: nothing

*****************************************************************************/
void osd_gfx_put_image_normal(void)
{

 int dum;

 if (video_dump)
   {
     char filename[256];
     BITMAP *bmp;
     BITMAP *final = create_bitmap(256,240);
     PALETTE pal;
          
     get_palette(pal);
     clear(final);
     bmp = create_sub_bitmap(XBuf, screen_blit_x, screen_blit_y, io.screen_w,io.screen_h);

     blit(bmp,final,0,0, (256 - io.screen_w) >> 1, (240 - io.screen_h) >>1,
                        io.screen_w, io.screen_h);

     sprintf(filename, "%s/%08X.pcx", video_path, last_generated_image++);
     save_bitmap(filename, final, pal);
     destroy_bitmap(bmp);
     destroy_bitmap(final);
   }

 if (message_delay)
   draw_sprite(XBuf,OSD_MESSAGE_SPR,screen_blit_x + 8,min(io.screen_h,vheight)-16);

 blit(XBuf,screen,screen_blit_x,screen_blit_y,blit_x,blit_y - 8,io.screen_w,io.screen_h);

}

/*****************************************************************************

    Function: osd_gfx_put_image_scanline

    Description: draw the raw computed picture to the screen using a 50% scanline algo
    Parameters: none
    Return: nothing
    Remark: Adapted from Vlendr'it 's code
*****************************************************************************/
void osd_gfx_put_image_scanline(void)
{
 int dum;
 int i,y = 0;

 BITMAP *temp = create_bitmap(io.screen_w * 2, io.screen_h * 2);

 if (message_delay)
   draw_sprite(XBuf,OSD_MESSAGE_SPR,screen_blit_x+8,min(io.screen_h,vheight)-16);

   clear(temp);

   for(i = 0; i < io.screen_h; i++)
   {
      stretch_blit(XBuf, temp, screen_blit_x - 8, i, io.screen_w, 1, 0, y, io.screen_w << 1, 1);
      y += 2;
   } 

   /* blit the bitmap onto the screen */

   blit(temp, screen, 0, 0, blit_x ,
             blit_y, temp->w, temp->h);
   destroy_bitmap(temp);

 }

/*****************************************************************************

    Function: osd_gfx_put_image_eagle

    Description: draw the raw computed image on screen using the eagle lib
    Parameters: none
    Return: nothing

*****************************************************************************/
void osd_gfx_put_image_eagle(void)
{
 int dum;

 if (message_delay)
   draw_sprite(XBuf,OSD_MESSAGE_SPR,screen_blit_x+8,min(io.screen_h,vheight)-16);

 for (dum=0;dum<io.screen_h-1;dum++)
    {
      // Eagle-blit piccy to the screen 
      eagle (
             (unsigned long*)(XBuf->line[dum]+screen_blit_x - 8)                  // First line of piccy  (320 pixels)
            ,(unsigned long*)(XBuf->line[dum+1]+screen_blit_x - 8)              // 2nd line of piccy (320 pixels)
            ,io.screen_w
            ,EAGLE_buf->seg
            ,(int)EAGLE_buf->line[dum*2] //  + ( ( (x   <<1) * piccy->w ) << 1)           // First eagled line = 320x2 = 640 pixels
            ,(int)EAGLE_buf->line[1+(dum*2)] // + (( ( (x+1)<<1) * piccy->w ) << 1)       // 2nd eagled line = 320x2 = 640 pixels
           );    
    }

    blit(EAGLE_buf,screen,0,0,blit_x,blit_y,io.screen_w<<1,(io.screen_h-1)<<1);

 }


/*****************************************************************************

    Function: osd_gfx_set_message

    Description: compute the message that will be displayed to create a sprite
       to blit on screen
    Parameters: char* mess, the message to display
    Return: nothing but set OSD_MESSAGE_SPR

*****************************************************************************/
void osd_gfx_set_message(char* mess)
{

 if (OSD_MESSAGE_SPR)
   destroy_bitmap(OSD_MESSAGE_SPR);

 OSD_MESSAGE_SPR=create_bitmap(text_length(font,mess)+1,text_height(font)+1);
 clear(OSD_MESSAGE_SPR);
 textout(OSD_MESSAGE_SPR,font,mess,1,1,3);
 textout(OSD_MESSAGE_SPR,font,mess,0,0,255);
 return;

 }

/*****************************************************************************

    Function:  osd_gfx_init_normal_mode

    Description: initialize the classic 256*224 video mode for normal video_driver
    Parameters: none
    Return: 0 on error
            1 on success

*****************************************************************************/
int osd_gfx_init_normal_mode()
{
  if (vmode==5)
    return !osd_gfx_set_hugo_mode(GFX_AUTODETECT,800,600);

  if (io.screen_w==40*8)
    {
      if (!osd_gfx_set_hugo_mode(GFX_AUTODETECT,320,240))
        return 1;
    }

  if (io.screen_w>40*8)
    {
      if (!osd_gfx_set_hugo_mode(GFX_AUTODETECT,360,240))
        return 1;
    }

  if ((vmode==0) && (!osd_gfx_set_hugo_mode(GFX_VGA,256,224)));
   else
  if ((vmode<=1) && (!osd_gfx_set_hugo_mode(GFX_AUTODETECT,256,240)));
   else
  if ((vmode<=2) && (!osd_gfx_set_hugo_mode(GFX_AUTODETECT,256,256)));
   else
  if ((vmode<=3) && (!osd_gfx_set_hugo_mode(GFX_AUTODETECT,320,240)));
   else
  if ((vmode<=4) && (!osd_gfx_set_hugo_mode(GFX_AUTODETECT,320,200)));
   else
          return 0;

 return 1;
 }

/*****************************************************************************

    Function: osd_gfx_init_scanline_mode

    Description: Initialize screen for use with the scanline displaying
    Parameters: none
    Return: nothing

*****************************************************************************/
int osd_gfx_init_scanline_mode(void)
{
  if (!(set_gfx_mode(GFX_AUTODETECT,640,480,0,0)))
            {
             vwidth=640;
             vheight=480;
             blit_x=(320-io.screen_w);
             blit_y=(240-io.screen_h);
             screen_blit_x=(WIDTH-io.screen_h)/2;
             screen_blit_y=(HEIGHT-io.screen_w)/2;

             SetPalette();
             return 1;
             }
  return 0;
 }


/*****************************************************************************

    Function: osd_gfx_init_eagle_mode

    Description: Initialize the screen for use with eagle displaying (i.e. 640x480x8)
    Parameters: none
    Return: 1 on success
    	    0 on error

*****************************************************************************/
int osd_gfx_init_eagle_mode(void)
{
  if (!(set_gfx_mode(GFX_AUTODETECT,640,480,0,0)))
            {
             vwidth=640;
             vheight=480;
             blit_x=(320-io.screen_w);
             blit_y=(240-io.screen_h) + 1;
             screen_blit_x=(WIDTH-io.screen_h)/2;
             screen_blit_y=(HEIGHT-io.screen_w)/2;

             SetPalette();
             return 1;
             }
  return 0;

}


/*****************************************************************************

    Function: osd_gfx_savepict

    Description: save a picture in the current directory
    Parameters: none
    Return: the numeric part of the created filename, 0xFFFF meaning that no more
      names were available

*****************************************************************************/
UInt16 osd_gfx_savepict()
  {
          BITMAP *bmp;
          PALETTE pal;
          char* final="PICT0000.PCX";
          short unsigned tmp=0;

          while ((tmp!=0xFFFF) && (exists(final)))
              sprintf(final,"PICT%04X.PCX",++tmp);
          if (tmp==0xFFFF)
            return tmp;

          get_palette(pal);

          if ((use_eagle) || (use_scanline))
            bmp = create_sub_bitmap(screen,
                                    blit_x,
                                    blit_y,
                                    io.screen_w * 2,
                                    io.screen_h * 2);
 	  else
            bmp = create_sub_bitmap(screen,
                                    blit_x,
                                    blit_y,
                                    io.screen_w,
                                    io.screen_h);

          save_bitmap(final, bmp, pal);

          destroy_bitmap(bmp);

          return tmp;
   }

/*****************************************************************************

    Function:  osd_gfx_set_hugo_mode

    Description: change the video mode
    Parameters: mode : mode of video screen
                width, height : minimum size of screen required
    Return: 0 on success
                 1 on error

*****************************************************************************/
SInt32 osd_gfx_set_hugo_mode(SInt32 mode,SInt32 width,SInt32 height)
{

 if (!set_gfx_mode(mode,width,height,0,0))
            {
             Log("Changing video mode to %dx%d\nPCE screen size is %dx%d\n",
                 width,
                 height,
                 io.screen_w,
                 io.screen_h);
             vwidth=width;
             vheight=height;

             blit_x=(width-io.screen_w)/2;
             blit_y=(height-io.screen_h)/2;

             screen_blit_x=(WIDTH-io.screen_w)/2;
             screen_blit_y=(224-io.screen_h)/2;

             Log("Now blit_x = %d\nblit_y = %d\nscreen_blit_x = %d\nscreen_blit_y = %d\n\n",
                 blit_x,
                 blit_y,
                 screen_blit_x,
                 screen_blit_y);

             SetPalette();
             return 0;
             }
 return 1;
 }

/*****************************************************************************

    Function: osd_gfx_set_color

    Description: Change the component of the choosen color
    Parameters: UChar index : index of the color to change
    		UChar r	: new red component of the color
                UChar g : new green component of the color
                UChar b : new blue component of the color
    Return:

*****************************************************************************/
void osd_gfx_set_color(UChar index,
                       UChar r,
                       UChar g,
                       UChar b)
{

 RGB R;
 R.r=r;
 R.g=g;
 R.b=b;

 set_color(index, &R);

 }
