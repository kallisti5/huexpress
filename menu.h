#include "fonts.h"

#define BGCOLOR 254
#define FGCOLOR 255

#define FONT_DIM 7 /* Fonts are 7x7 (5x5 + space) */
#define LINE_SPACE 8 /* Space from line to line (in pixels) */
#define CURSOR_SPACE 10 /* Left space for the menu cursor */

extern char *tela;

extern char ogl_ctable[256][3];
extern void fb2gl_palette(int index, int r, int g, int b);
extern void fb2gl_set_palette();

SDL_Event menu_event;
SDL_Event clean_event;
Uint8 *menu_key;
int halfx, halfy;

struct {
	char newf;
	int x,y;
	int hw,hh; /* half width and half height */
	int lines;
	char quit;
	char open;
} menu;

struct {
	int r,g,b;
} old_bg, old_fg; /* Old BG color and FG color */

char pos=0; /* Position of select cursor */
char old_pos=4; /* Old Cursor Position */

void add_item(char *text) { /* Add item to the menu */
  int i=0;
  int j,k;
  unsigned char *p;
  int sp; /* Space */
  char draw=1;
  static int x,y;
 
  if (menu.newf) { /* New menu drawn? */
	menu.newf=0;
	x=menu.x + CURSOR_SPACE; /* Enough space for the menu cursor */
	y=menu.y + 2; /* Space from frame */
  }
  else {
	y+=LINE_SPACE; /* Space beetwen vertical text */
  }
  
  sp=i=0;
  while (text[i]!='\0') {
	switch (text[i]) {
		case 'A': case 'a': p=font_a; break;
		case 'B': case 'b': p=font_b; break;
		case 'C': case 'c': p=font_c; break;
		case 'D': case 'd': p=font_d; break;
		case 'E': case 'e': p=font_e; break;
		case 'F': case 'f': p=font_f; break;
		case 'G': case 'g': p=font_g; break;
		case 'H': case 'h': p=font_h; break;
		case 'I': case 'i': p=font_i; break;
		case 'J': case 'j': p=font_j; break;
		case 'K': case 'k': p=font_k; break;
		case 'L': case 'l': p=font_l; break;
		case 'M': case 'm': p=font_m; break;
		case 'N': case 'n': p=font_n; break;
		case 'O': case 'o': p=font_o; break;
		case 'P': case 'p': p=font_p; break;
		case 'Q': case 'q': p=font_q; break;
		case 'R': case 'r': p=font_r; break;
		case 'S': case 's': p=font_s; break;
		case 'T': case 't': p=font_t; break;
		case 'U': case 'u': p=font_u; break;
		case 'V': case 'v': p=font_v; break;
		case 'W': case 'w': p=font_w; break;
		case 'X': case 'x': p=font_x; break;
		case 'Y': case 'y': p=font_y; break;
		case 'Z': case 'z': p=font_z; break;
		case '0': p=font_0; break;
		case '1': p=font_1; break;
		case '2': p=font_2; break;
		case '3': p=font_3; break;
		case '4': p=font_4; break;
		case '5': p=font_5; break;
		case '6': p=font_6; break;
		case '7': p=font_7; break;
		case '8': p=font_8; break;
		case '9': p=font_9; break;
		case '*': p=font_ast; break;
		case '.': p = font_per; break;
		case '\"': p=font_quot; break;
		case '!': p=font_ex; break;
		case '\'': p=font_apos; break;
		case ' ': draw=0; break;
		default: draw=0; break;
        };
	if (draw) {
		for (j=0;j<5;j++)
		  for (k=0;k<5;k++)
		    if (p[k+j*5]) tela[(k+x+sp)+(j+y)*io.screen_w] = FGCOLOR;			
	}
	else draw=1;
	sp+=7;
	i++;
  }
}

void create_menu(int letters, int lines) {
	int i,j;
	int half_let = (CURSOR_SPACE+letters*FONT_DIM)/2;
	int half_lin = lines*LINE_SPACE/2;

	halfx = io.screen_w/2;
	halfy = io.screen_h/2;

	menu.newf = 1; /* It's a new Menu */
	menu.quit = 0;
	menu.x = halfx - half_let;
	menu.y = halfy - half_lin;
	menu.hw = half_let;
	menu.hh = half_lin;
	menu.lines = lines;

	menu.open=1;
	pos=0;
	old_pos=menu.lines-1;
	
	/* Backup old RGB for color BGCOLOR (index == 0) */
	old_bg.r = ogl_ctable[BGCOLOR][0];
	old_bg.g = ogl_ctable[BGCOLOR][1];
	old_bg.b = ogl_ctable[BGCOLOR][2];
	
	/* Backup old RGB for color FGCOLOR (index == 1) */
	old_fg.r = ogl_ctable[FGCOLOR][0];
	old_fg.g = ogl_ctable[FGCOLOR][1];
	old_fg.b = ogl_ctable[FGCOLOR][2];
	
	fb2gl_palette(BGCOLOR,50,50,50); /* Set RGB for BGCOLOR */
	fb2gl_palette(FGCOLOR,255,255,255); /* Set RGB for FGCOLOR */
	fb2gl_set_palette(); /* Update video palette */
	

	/* Clear the background and add a frame with the FGCOLOR */
	for (j=halfy-half_lin; j<halfy+half_lin+1; j++) {
		for (i=halfx-half_let; i<halfx+half_let+1; i++) {
			tela[i+j*(io.screen_w)] = BGCOLOR; /* Clearing Bg */
			if ( j == halfy - half_lin || j == halfy + half_lin || 
			     i == halfx - half_let || i == halfx + half_let )
			{
			     tela[i+j*(io.screen_w)] = FGCOLOR; /* Frame */
			}
		}
	}

}

void draw_menu_cursor(int pos) {
	int i,j;
	for (j=0;j<5;j++)
	  for (i=0;i<5;i++) {
	    if (font_ast[i+j*5]) { /* +2 is to keep away from the frame */
	      tela[ ( i + menu.x + 2 ) +
		   ( j + menu.y + 2 + (pos*LINE_SPACE) ) * 
		   io.screen_w ] = FGCOLOR;
	    }
	    /* Clean the old cursor */
	    tela[ ( i + menu.x + 2) + 
		  ( j + menu.y + 2 + (old_pos*8) ) *
		  io.screen_w] = BGCOLOR;	
	  }

}

void update_menu() {
	draw_menu_cursor(pos);
	fb2gl_update(tela,io.screen_w,io.screen_h,io.screen_w,0,0);
}

void menu_wait(int this_key) {
	SDL_PumpEvents();
	menu_key=SDL_GetKeyState(NULL);
	while (menu_key[this_key] != SDL_RELEASED) {
		SDL_PumpEvents();
		menu_key=SDL_GetKeyState(NULL);
	}
}

void list_rom() {
	printf("List ROMs in dir\n");
}

int menu_handle_select(int p) {
	// switch(menu_level) {
	switch(p) {
		case 0: list_rom(); break;
		case 4: menu.quit=1; break;
		default: menu.open=0;
	};
	// menu_level
}

void menu_main_loop() {

	menu_wait(SDLK_ESCAPE);

	while (menu.open) {
		SDL_PumpEvents();
		menu_key=SDL_GetKeyState(NULL);
		if(menu_key[SDLK_ESCAPE] == SDL_PRESSED) {
			menu.open=0;
			menu_wait(SDLK_ESCAPE);
		}
		if(menu_key[SDLK_DOWN] == SDL_PRESSED) {
			old_pos=pos;
			pos++;
			if (pos>menu.lines-1) pos=0;
			update_menu();
			menu_wait(SDLK_DOWN);
		}
		if(menu_key[SDLK_UP] == SDL_PRESSED) {
			old_pos=pos;
			pos--;
			if (pos<0) pos=menu.lines-1;
			update_menu();
			menu_wait(SDLK_UP);
		}
		if(menu_key[SDLK_RETURN] == SDL_PRESSED) {
			menu_handle_select(pos);
			menu_wait(SDLK_RETURN);
			if (menu.quit) return;
		}

	}

}


int open_menu() {

	create_menu(10,5);
	add_item("load rom");
	add_item("save state");
	add_item("load state");
	add_item("options");
	add_item("quit");
	update_menu();

	menu_main_loop();

	fb2gl_palette(BGCOLOR,old_bg.r,old_bg.g,old_bg.b);
	fb2gl_palette(FGCOLOR,old_fg.r,old_fg.g,old_fg.b); 
	fb2gl_set_palette();

	if (menu.quit) return 0; /* Leave the emulator */
	else return 1;

}
