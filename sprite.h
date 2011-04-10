#ifndef _SPRITE_H_
#define _SPRITE_H_

#include "pce.h"
#include "cleantyp.h"
#include "mix.h"

typedef	struct {
	short y,x,no,atr;
} SPR;
/* Sprite structure
 * y,x = pos
 * no = address of the pattern in the Video ram
 * atr = attributes
 * bit 0-4 : number of the palette to be used
 * bit 7 : background sprite
 *          0 -> must be drawn behind tiles
 *          1 -> must be drawn in front of tiles
 * bit 8 : width
 *          0 -> 16 pixels
 *          1 -> 32 pixels
 * bit 11 : horizontal flip
 *          0 -> normal shape
 *          1 -> must be draw horizontaly flipped
 * bit 13-12 : heigth
 *          00 -> 16 pixels
 *          01 -> 32 pixels
 *          10 -> 48 pixels
 *          11 -> 64 pixels
 * bit 15 : vertical flip
 *          0 -> normal shape
 *          1 -> must be drawn verticaly flipped
 */

extern UChar BGONSwitch;
/* do we have to draw background ? */

extern UChar SPONSwitch;
/* Do we have to draw sprites ? */

#define	PAL(c)	R[c]
#define	SPal	(Pal+256)

#define	MinLine	io.minline
#define	MaxLine	io.maxline

//#define ScrollX	io.scroll_x
//#define ScrollY io.scroll_y
#define	ScrollX	io.VDC[BXR].W
#define	ScrollY	io.VDC[BYR].W
extern int	ScrollYDiff;

extern int	oldScrollX;
extern int	oldScrollY;
extern int	oldScrollYDiff;

extern UInt32 spr_init_pos[1024];
// cooked initial position of sprite

#if !defined(NEW_GFX_ENGINE)
extern UChar SPM[WIDTH*HEIGHT];
#endif

/*
####################################
####################################
####################################
####################################
2KILL :: BEGIN
####################################
####################################
####################################
####################################
*/
#ifdef ALLEGRO

extern BITMAP* dirty_spr[0x20000/32];
// Used for precalculation of sprites, VRAMSIZE/32 is for # of sprite

#endif
/*
####################################
####################################
####################################
####################################
2KILL :: END
####################################
####################################
####################################
####################################
*/

extern char exact_putspritem;
// do we use a slow but precise function to draw certain sprites

extern int frame;
// number of frame displayed

//extern void (*PutSpriteMaskedFunction)(byte *P,byte *C,unsigned	long *C2,byte *R,int h,int inc,byte *M,byte pr);
// the general function for *masked

//extern void (*PutSpriteMakeMaskedFunction)(byte *P,byte *C,unsigned	long *C2,byte *R,int h,int inc,byte *M,byte pr);
// the general function for *makemasked*

//extern void PutSpriteM(byte *P,byte *C,unsigned	long *C2,byte *R,int h,int inc,byte *M,byte pr);
// the exact function

//extern void PutSpriteMakeMask(byte *P,byte *C,unsigned	long *C2,byte *R,int h,int inc,byte *M,byte pr);
// the exact function

//extern void PutSprite(byte *P,byte *C,unsigned	long *C2,byte *R,int h,int inc);
// the simplified function

extern void RefreshSpriteExact(int,int,unsigned char);
// The true refreshing function

extern void (*RefreshSprite)(int Y1,int Y2,unsigned char bg);
// The pointer toward the used function

#endif
