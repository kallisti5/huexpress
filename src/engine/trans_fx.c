/*
########################################
####  WILL MOVE IN THE GFX DLL/SO
########################################
*/

#include "trans_fx.h"

const char nb_fadein = 5;
const char nb_fadeout = 5;
// used to know how many functions do we have


#ifdef ALLEGRO

void special_fadein1 (BITMAP * to, unsigned xto, unsigned yto, unsigned xmax,
		      unsigned ymax);
void special_fadein2 (BITMAP * to, unsigned xto, unsigned yto, unsigned xmax,
		      unsigned ymax);
void special_fadein3 (BITMAP * to, unsigned xto, unsigned yto, unsigned xmax,
		      unsigned ymax);
void special_fadein4 (BITMAP * to, unsigned xto, unsigned yto, unsigned xmax,
		      unsigned ymax);
void special_fadein5 (BITMAP * to, unsigned xto, unsigned yto, unsigned xmax,
		      unsigned ymax);
// forward declaration for initialising the following tab

void (*fade_in_proc[5]) (BITMAP *, unsigned, unsigned, unsigned, unsigned) =
{
  special_fadein1,
    special_fadein2, special_fadein3, special_fadein4, special_fadein5};

#else

void (*fade_in_proc[5]) (UChar *, unsigned, unsigned, unsigned, unsigned) =
{};

#endif

// Array of function for random calls

#if defined(ALLEGRO)	
	
void special_fadeout1 (unsigned xto, unsigned yto, unsigned xmax,
		       unsigned ymax);
void special_fadeout2 (unsigned xto, unsigned yto, unsigned xmax,
		       unsigned ymax);
void special_fadeout3 (unsigned xto, unsigned yto, unsigned xmax,
		       unsigned ymax);
void special_fadeout4 (unsigned xto, unsigned yto, unsigned xmax,
		       unsigned ymax);
void special_fadeout5 (unsigned xto, unsigned yto, unsigned xmax,
		       unsigned ymax);
// forward declaration for initialising the following tab

void (*fade_out_proc[5]) (unsigned, unsigned, unsigned, unsigned) =
{
  special_fadeout1,
    special_fadeout2, special_fadeout3, special_fadeout4, special_fadeout5};

// Array of function for random calls

#else

void (*fade_out_proc[5]) (unsigned, unsigned, unsigned, unsigned) =
{};
	
	
#endif
	

#ifdef ALLEGRO


/*****************************************************************************

    Function: special_fadein1

    Description: fade in with spiral effect
    Parameters: the BITMAP to fade to,
	             xto,yto,xmax,ymax used like in blit
					 used like "blit(to,screen,0,0,xto,yto,xmax,ymax)"
    Return:nothing

*****************************************************************************/
void
special_fadein1 (BITMAP * to, unsigned xto, unsigned yto, unsigned xmax,
		 unsigned ymax)
{
  static char xinit[] = { 0, 1, 2, 3, 3, 3, 3, 2, 1, 0, 0, 0, 1, 2, 2, 1 };
  static char yinit[] = { 0, 0, 0, 0, 1, 2, 3, 3, 3, 3, 2, 1, 1, 1, 2, 2 };
  unsigned x = 0, y = 0;
  unsigned char index;
  UChar tmp_sync = 0;
  for (index = 0; index < 16; index++)
    {
      for (y = yinit[index]; y < ymax; y += 4)
	for (x = xinit[index]; x < xmax; x += 4)
	  putpixel (screen, xto + x, yto + y, getpixel (to, x, y));

      if (!use_eagle)
	vsync ();
      else if (tmp_sync = !tmp_sync)
	vsync ();

    }
  blit (to, screen, 0, 0, xto, yto, xmax, ymax);
  return;
}

/*****************************************************************************

    Function: special_fadeout1

    Description: fade out with spiral effect
    Parameters: xto,yto,xmax,ymax used like in blit
					 used like "rectfill(screen,xto,yto,xto+xmax,yto+ymax)"
    Return:nothing

*****************************************************************************/


void
special_fadeout1 (unsigned xto, unsigned yto, unsigned xmax, unsigned ymax)
{
  static char xinit[] = { 0, 1, 2, 3, 3, 3, 3, 2, 1, 0, 0, 0, 1, 2, 2, 1 };
  static char yinit[] = { 0, 0, 0, 0, 1, 2, 3, 3, 3, 3, 2, 1, 1, 1, 2, 2 };
  unsigned x = 0, y = 0;
  unsigned char index;
  UChar tmp_sync = 0;
  for (index = 0; index < 16; index++)
    {
      for (y = yto + yinit[index]; y < yto + ymax; y += 4)
	for (x = xto + xinit[index]; x < xto + xmax; x += 4)
	  putpixel (screen, x, y, 0);

      if (!use_eagle)
	vsync ();
      else if (tmp_sync = !tmp_sync)
	vsync ();

    }
  rectfill (screen, xto, yto, xto + xmax, yto + ymax, 0);
  return;
}


/*****************************************************************************

    Function: special_fadeout2

    Description: fade out with slide effect
    Parameters: xto,yto,xmax,ymax used like in blit
					 used like "rectfill(screen,xto,yto,xto+xmax,yto+ymax,0)"
    Return:nothing

*****************************************************************************/


void
special_fadeout2 (unsigned xto, unsigned yto, unsigned xmax, unsigned ymax)
{
  int y = 0;
  int *diff, *act;
  int index, max_iter = (xmax - xto) / 8, iter = 0;
  UChar tmp_sync = 0;

  diff = (int *) alloca (sizeof (int) * ymax);
  act = (int *) alloca (sizeof (int) * ymax);
  memset (diff, 0, (ymax) * sizeof (int));
  memset (act, 0, ymax * sizeof (int));


  while (iter < max_iter)
    {
      for (index = 0; index < ymax; index++)
	{
	  act[index] += diff[index] = rand () % 4 + 6;
	  if (act[index] > xmax)
	    act[index] = xmax;
	}
      for (y = yto, index = 0; index < ymax; y++, index++)
	hline (screen, xto, y, xto + act[index], 0);

      iter++;
      if (!use_eagle)
	vsync ();
      else if (tmp_sync = !tmp_sync)
	vsync ();

    }
  rectfill (screen, xto, yto, xto + xmax, yto + ymax, 0);
  return;
}

/*****************************************************************************

    Function: special_fadein2

    Description: fade in with slide effect
    Parameters: xto,yto,xmax,ymax used like in blit
					 used like "blit(screen,to,0,0,xto,yto,xmax,ymax)"
    Return:nothing

*****************************************************************************/


void
special_fadein2 (BITMAP * to, unsigned xto, unsigned yto, unsigned xmax,
		 unsigned ymax)
{
  int y = 0;
  int *diff, *act;
  int index, max_iter = (xmax - xto) / 8, iter = 0;
  UChar tmp_sync = 0;

  diff = (int *) alloca (sizeof (int) * ymax);
  act = (int *) alloca (sizeof (int) * ymax);
  memset (diff, 0, (ymax) * sizeof (int));
  memset (act, 0, (ymax) * sizeof (int));


  while (iter < max_iter)
    {
      for (index = 0; index < ymax; index++)
	{
	  act[index] += diff[index] = rand () % 4 + 6;
	  if (act[index] >= xmax)
	    act[index] = xmax;

	}

      for (y = yto, index = 0; index < ymax; y++, index++)
	blit (to, screen, xmax - act[index], index, xto, y, act[index], 1);

      iter++;
      if (!use_eagle)
	vsync ();
      else if (tmp_sync = !tmp_sync)
	vsync ();

    }
  blit (to, screen, 0, 0, xto, yto, xmax, ymax);
  return;
}


/*****************************************************************************

    Function: special_fadein3

    Description: fade in with double slide effect
    Parameters: xto,yto,xmax,ymax used like in blit
					 used like "blit(screen,to,0,0,xto,yto,xmax,ymax)"
    Return:nothing

*****************************************************************************/


void
special_fadein3 (BITMAP * to, unsigned xto, unsigned yto, unsigned xmax,
		 unsigned ymax)
{
  int y = 0;
  int *diff, *act;
  int index, max_iter = (xmax - xto) / 10, iter = 0;
  UChar tmp_sync = 0;

  diff = (int *) alloca (sizeof (int) * ymax);
  act = (int *) alloca (sizeof (int) * ymax);
  memset (diff, 0, (ymax) * sizeof (int));
  memset (act, 0, (ymax) * sizeof (int));

  while (iter < max_iter)
    {

      for (index = 0; index < ymax; index++)
	act[index] += 10;

      for (y = yto, index = 0; index < ymax; y += 2, index += 2)
	blit (to, screen, xmax - act[index], index, xto, y, act[index], 1);

      for (y = yto + 1, index = 1; index < ymax; y += 2, index += 2)
	blit (to, screen, 0, index, xto + xmax - act[index], y, act[index],
	      1);

      iter++;
      if (!use_eagle)
	vsync ();
      else if (tmp_sync = !tmp_sync)
	vsync ();
    }
  blit (to, screen, 0, 0, xto, yto, xmax, ymax);
  return;
}


/*****************************************************************************

    Function: special_fadeout3

    Description: fade in with double slide effect
    Parameters: xto,yto,xmax,ymax used like in blit
					 used like "rectfill(screen,xto,yto,xto+xmax,yto+ymax)"
    Return:nothing

*****************************************************************************/


void
special_fadeout3 (unsigned xto, unsigned yto, unsigned xmax, unsigned ymax)
{
  int y = 0;
  int *diff, *act;
  int index, max_iter = (xmax - xto) / 10, iter = 0;
  UChar tmp_sync = 0;

  diff = (int *) alloca (sizeof (int) * ymax);
  act = (int *) alloca (sizeof (int) * ymax);
  memset (diff, 0, (ymax) * sizeof (int));
  memset (act, 0, (ymax) * sizeof (int));

  while (iter < max_iter)
    {

      for (index = 0; index < ymax; index++)
	act[index] += 10;

      for (y = yto, index = 0; index < ymax; y += 2, index += 2)
	hline (screen, act[index] - 10, y, act[index], 0);

      for (y = yto + 1, index = 1; index < ymax; y += 2, index += 2)
	hline (screen, xto + xmax - act[index] + 10, y,
	       xto + xmax - act[index], 0);

      iter++;

      if (!use_eagle)
	vsync ();
      else if (tmp_sync = !tmp_sync)
	vsync ();

    }
  rectfill (screen, xto, yto, xto + xmax, yto + ymax, 0);
  return;
}

/*****************************************************************************

    Function: special_fadein4

    Description: fade in with diagonal effect
    Parameters: the BITMAP to fade to,
	             xto,yto,xmax,ymax used like in blit
					 used like "blit(to,screen,0,0,xto,yto,xmax,ymax)"
    Return:nothing

*****************************************************************************/
void
special_fadein4 (BITMAP * to, unsigned xto, unsigned yto, unsigned xmax,
		 unsigned ymax)
{
  static char xinit[] = { 0, 2, 0, 2, 1, 3, 1, 3, 1, 3, 1, 3, 2, 0, 2, 0 };
  static char yinit[] = { 0, 0, 1, 1, 2, 2, 3, 3, 0, 0, 1, 1, 2, 2, 3, 3 };
  unsigned x = 0, y = 0;
  unsigned char index;
  UChar tmp_sync = 0;
  for (index = 0; index < 16; index++)
    {
      for (y = yinit[index]; y < ymax; y += 4)
	for (x = xinit[index]; x < xmax; x += 4)
	  putpixel (screen, xto + x, yto + y, getpixel (to, x, y));

      if (!use_eagle)
	vsync ();
      else if (tmp_sync = !tmp_sync)
	vsync ();

    }
  blit (to, screen, 0, 0, xto, yto, xmax, ymax);
  return;
}

/*****************************************************************************

    Function: special_fadeout4

    Description: fade out with diagonal effect
    Parameters: xto,yto,xmax,ymax used like in blit
					 used like "rectfill(screen,xto,yto,xto+xmax,yto+ymax)"
    Return:nothing

*****************************************************************************/


void
special_fadeout4 (unsigned xto, unsigned yto, unsigned xmax, unsigned ymax)
{
  static char xinit[] = { 0, 2, 0, 2, 1, 3, 1, 3, 1, 3, 1, 3, 2, 0, 2, 0 };
  static char yinit[] = { 0, 0, 1, 1, 2, 2, 3, 3, 0, 0, 1, 1, 2, 2, 3, 3 };
  unsigned x = 0, y = 0;
  unsigned char index;
  UChar tmp_sync = 0;
  for (index = 0; index < 16; index++)
    {
      for (y = yto + yinit[index]; y < yto + ymax; y += 4)
	for (x = xto + xinit[index]; x < xto + xmax; x += 4)
	  putpixel (screen, x, y, 0);

      if (!use_eagle)
	vsync ();
      else if (tmp_sync = !tmp_sync)
	vsync ();

    }
  rectfill (screen, xto, yto, xto + xmax, yto + ymax, 0);
  return;
}


/*****************************************************************************

    Function: special_fadein5

    Description: fade in with spiral effect
    Parameters: the BITMAP to fade to,
	             xto,yto,xmax,ymax used like in blit
					 used like "blit(to,screen,0,0,xto,yto,xmax,ymax)"
    Return:nothing

*****************************************************************************/
void
special_fadein5 (BITMAP * to, unsigned xto, unsigned yto, unsigned xmax,
		 unsigned ymax)
{
  static char xinit[] = { 3, 2, 2, 1, 1, 0, 0, 0, 1, 0, 1, 2, 2, 3, 3, 3 };
  static char yinit[] = { 0, 1, 0, 0, 1, 0, 1, 2, 2, 3, 3, 3, 2, 3, 2, 1 };
  unsigned x = 0, y = 0;
  unsigned char index;
  UChar tmp_sync = 0;
  for (index = 0; index < 16; index++)
    {
      for (y = yinit[index]; y < ymax; y += 4)
	for (x = xinit[index]; x < xmax; x += 4)
	  putpixel (screen, xto + x, yto + y, getpixel (to, x, y));

      if (!use_eagle)
	vsync ();
      else if (tmp_sync = !tmp_sync)
	vsync ();

    }
  blit (to, screen, 0, 0, xto, yto, xmax, ymax);
  return;
}


/*****************************************************************************

    Function: special_fadeout5

    Description: fade out with spiral effect
    Parameters: xto,yto,xmax,ymax used like in blit
					 used like "rectfill(screen,xto,yto,xto+xmax,yto+ymax)"
    Return:nothing

*****************************************************************************/


void
special_fadeout5 (unsigned xto, unsigned yto, unsigned xmax, unsigned ymax)
{
  static char xinit[] = { 3, 2, 2, 1, 1, 0, 0, 0, 1, 0, 1, 2, 2, 3, 3, 3 };
  static char yinit[] = { 0, 1, 0, 0, 1, 0, 1, 2, 2, 3, 3, 3, 2, 3, 2, 1 };
  unsigned x = 0, y = 0;
  unsigned char index;
  UChar tmp_sync = 0;
  for (index = 0; index < 16; index++)
    {
      for (y = yto + yinit[index]; y < yto + ymax; y += 4)
	for (x = xto + xinit[index]; x < xto + xmax; x += 4)
	  putpixel (screen, x, y, 0);

      if (!use_eagle)
	vsync ();
      else if (tmp_sync = !tmp_sync)
	vsync ();

    }
  rectfill (screen, xto, yto, xto + xmax, yto + ymax, 0);
  return;
}

#endif
