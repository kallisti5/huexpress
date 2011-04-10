#include "osd_machine.h"
UChar* osd_gfx_buffer = NULL;

UChar gamepad = 0;
// gamepad detected ?

BITMAP *XBuf;
// The screen buffer where we draw before blitting it on screen

int gamepad_driver = 0;
// what kind of jypad must we have to handle

char dump_snd = 0;
// Do we write sound to file

char synchro;
// à fond, à fond, à fond? (french joke ;)

int vwidth, vheight;
// size of visible part of the screen (I got troubles with allegro screen->* values!)

int vmode = 0;
// video mode to use
// 1 -> first 224*240 then 256*240 then 256*256 then 320*240 and 320*200
// 2 -> first 256*240 then 256*256 then 320*240 and 320*200
// 3 -> first 256*256 then 320*240 and 320*200
// 4 -> first 320*240 and 320*200
// 5 -> only try 320*200
// 6 -> only 800*600
// If you think others modes would be interesting, let me know

int osd_init_machine()
{

  int result;

  Log ("\n--[ INITIALISE MACHINE ]--------------------------\n");
  check_cpu ();
  if (cpu_cpuid)
    Log ("Following cpu info are exact\n");
  else
    Log ("Following cpu info may be inaccurate\n");

  Log ("Machine is a %d56, sub model : %d\n", cpu_family, cpu_model);

  if (cpu_fpu)
    Log ("Machine got a fpu\n");
  else
    Log ("No fpu available\n");

  if (cpu_mmx)
    Log ("Machine got a MMX cpu\n");
  else
    Log ("Machine doesn't have a MMX cpu\n");

  if (cpu_3dnow)
    Log ("Machine got a 3dNow! cpu compatible\n");
  else
    Log ("Machine doesn't have a 3dNow! cpu compatible\n");

  Log ("Vendor : %s\n", cpu_vendor);

  set_gfx_mode (GFX_TEXT, 0, 0, 0, 0);
  printf (MESSAGE[language][init_allegro]);

  printf (MESSAGE[language][translated_by]);

  if (!(XBuf = create_bitmap (XBUF_WIDTH, XBUF_HEIGHT)))
    {
      printf (MESSAGE[language][failed_init]);
      return (0);
    }

  printf (MESSAGE[language][clear_buffer]);
  clear (XBuf);

/*
 switch (gamepad_driver)
   {
    case 0:
         result = install_joystick(JOY_TYPE_NONE);
         break;
    case 1:
         result = install_joystick(JOY_TYPE_STANDARD);
         break;
    case 2:
         result = install_joystick(JOY_TYPE_2PADS);
         break;
    case 3:
         result = install_joystick(JOY_TYPE_4BUTTON);
         break;
    case 4:
         result = install_joystick(JOY_TYPE_6BUTTON);
         break;
    case 5:
         result = install_joystick(JOY_TYPE_8BUTTON);
         break;
    case 6:
         result = install_joystick(JOY_TYPE_FSPRO);
         break;
    case 7:
         result = install_joystick(JOY_TYPE_WINGEX);
         break;
    case 8:
         result = install_joystick(JOY_TYPE_SIDEWINDER);
         break;
    case 9:
         result = install_joystick(JOY_TYPE_GAMEPAD_PRO);
         break;
    case 10:
         result = install_joystick(JOY_TYPE_SNESPAD_LPT1);
         break;
    case 11:
         result = install_joystick(JOY_TYPE_SNESPAD_LPT2);
         break;
    case 12:
         result = install_joystick(JOY_TYPE_SNESPAD_LPT3);
         break;
    case 13:
         result = install_joystick(JOY_TYPE_WINGWARRIOR);
         break;

    default: // in particular, for gamepad_driver == -1
    result = install_joystick(JOY_TYPE_AUTODETECT);
   }
*/
  result = install_joystick (gamepad_driver);

  if ((!result) && (joy_type != JOY_TYPE_NONE))
    {
      Log ("Joypad %d detected\n", joy_type);
      printf (MESSAGE[language][joy_detected]);
      gamepad = 1;
    }
  else
    {
      Log ("Joypad type %d NOT detected\n", joy_type);
      printf (MESSAGE[language][joy_no_detected]);
      gamepad = 0;
    }

  Log ("Allocating sprite array\n");
  printf (MESSAGE[language][alloc_spr]);
  {
    UInt32 x;
    for (x = 0; x < VRAMSIZE / 32; x++)
      {
	if (!(dirty_spr[x] = create_bitmap (16, 16)))
	  {
	    printf (MESSAGE[language][failed_init]);
	    return 0;
	  }
	clear (dirty_spr[x]);
      }
  }

  Log ("Initiating sound\n");
  printf (MESSAGE[language][init_sound]);
  InitSound ();

  if (use_eagle)
    {
      printf (MESSAGE[language][eagle_asked]);
      if (!set_gfx_mode (GFX_AUTODETECT, 640, 480, 0, 0))
	{
	  vwidth = 640;
	  vheight = 480;
	  blit_x = (320 - 256) / 2;
	  blit_y = (240 - 216) / 2;
	  screen_blit_x = (WIDTH - io.screen_h) / 2;
	  screen_blit_y = (HEIGHT - io.screen_w) / 2;
	  SetPalette ();

	  EAGLE_buf = create_bitmap (640, 480);
	}
      else
	printf (MESSAGE[language][eagle_mode_not_init]);
    }
  else if (!(*osd_gfx_driver_list[video_driver].init) ())
    {
      Log ("Can't set graphic mode\n");
      printf (MESSAGE[language][cant_set_gmode]);
      return 0;
    }

  text_mode (-1);
  install_keyboard ();
  clear (screen);

  osd_gfx_buffer = XBuf->line[0];

  Log ("End of initialisation of the machine\n");
  return 1;

}

/*****************************************************************************

    Function: osd_shut_machine

    Description: Deinitialize all stuff that have been inited in osd_int_machine
    Parameters: none
    Return: nothing

*****************************************************************************/
void
osd_shut_machine (void)
{

  destroy_bitmap (XBuf);

  if (OSD_MESSAGE_SPR)
    destroy_bitmap (OSD_MESSAGE_SPR);

  if (EAGLE_buf)
    destroy_bitmap (EAGLE_buf);

  if (sound_driver == 1)
    set_volume (0, 0);

  (*fade_out_proc[rand () % nb_fadeout]) (0, 0, vwidth, vheight);

  {
    UInt32 x;
    for (x = 0; x < VRAMSIZE / 32; x++)
      destroy_bitmap (dirty_spr[x]);
  }

  set_gfx_mode (GFX_TEXT, 0, 0, 0, 0);

  TrashSound ();

  allegro_exit ();

  return;
}

/*****************************************************************************

    Function: osd_keypressed

    Description: Tells if a key is available for future call of osd_readkey
    Parameters: none
    Return: 0 is no key is available
            else any non zero value

*****************************************************************************/
SChar osd_keypressed(void)
{
 return keypressed();
 }

/*****************************************************************************

    Function: osd_readkey

    Description: Return the first available key stroke, waiting if needed
    Parameters: none
    Return: the key value (currently, lower byte is ascii and higher is scancode)

*****************************************************************************/
UInt16 osd_readkey(void)
{
 return readkey();
 }

