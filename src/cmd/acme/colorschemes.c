#include <u.h>
#include <libc.h>
#include <draw.h>
#include <thread.h>
#include <cursor.h>
#include <mouse.h>
#include <keyboard.h>
#include <frame.h>
#include <fcall.h>
#include <plumb.h>
#include <libsec.h>
#include <complete.h>
#include "dat.h"
#include "fns.h"
#include <stdio.h> // REMOVEME:

Image		*syhl_light[SYHL_NCOL];
Image		*syhl_gruvbox_light[SYHL_NCOL];
Image		*syhl_gruvbox_dark[SYHL_NCOL];

void init_syhl_light(void) {
	textcols[BACK] = allocimagemix(display, DWhite, DWhite);
	textcols[HIGH] = allocimage(display, Rect(0,0,1,1), screen->chan, 1, DDarkyellow);
	textcols[BORD] = allocimage(display, Rect(0,0,1,1), screen->chan, 1, DGrey);
	textcols[TEXT] = display->black;
	textcols[HTEXT] = display->black;

	syhl_light[SYHL_CODETAG] = allocimage(display, Rect(0,0,1,1), screen->chan, 1, DYellowGold);
	syhl_light[SYHL_KEYWORD] = allocimage(display, Rect(0,0,1,1), screen->chan, 1, DBlue);
	syhl_light[SYHL_NUMBER] = allocimage(display, Rect(0,0,1,1), screen->chan, 1, DMagenta);
	syhl_light[SYHL_QUOTE] = allocimage(display, Rect(0,0,1,1), screen->chan, 1, DMedgreen);
	syhl_light[SYHL_COMMENT] = allocimage(display, Rect(0,0,1,1), screen->chan, 1, DGrey);
	syhl_light[SYHL_ESCAPE] = allocimage(display, Rect(0,0,1,1), screen->chan, 1, DRed);
	syhl_light[SYHL_PAREN] = allocimage(display, Rect(0,0,1,1), screen->chan, 1, DYellowgreen);
}

#define GRUVBOX_RED 0xCC241DFF
#define GRUVBOX_GREEN 0x98971AFF
#define GRUVBOX_YELLOW 0xD79921FF
#define GRUVBOX_BLUE 0x458588FF
#define GRUVBOX_PURPLE 0xB16286FF
#define GRUVBOX_AQUA 0x689D6AFF
#define GRUVBOX_GREY 0x7C6F64FF

#define GRUVBOX_LIGHT_BG 0xFBF1C7FF
#define GRUVBOX_LIGHT_BG_SEL 0xEBDBB2FF
#define GRUVBOX_LIGHT_FG 0x3C3836FF
#define GRUVBOX_LIGHT_FG_SEL 0x282828FF
#define GRUVBOX_LIGHT_BORD 0x282828FF

void init_syhl_gruvbox_light(void) {
	textcols[BACK] = allocimagemix(display, GRUVBOX_LIGHT_BG, GRUVBOX_LIGHT_BG);
	textcols[HIGH] = allocimage(display, Rect(0,0,1,1), screen->chan, 1, GRUVBOX_LIGHT_BG_SEL);
	textcols[BORD] = allocimage(display, Rect(0,0,1,1), screen->chan, 1, GRUVBOX_LIGHT_BORD);
	textcols[TEXT] = allocimage(display, Rect(0,0,1,1), screen->chan, 1, GRUVBOX_LIGHT_FG);
	textcols[HTEXT] = allocimage(display, Rect(0,0,1,1), screen->chan, 1, GRUVBOX_LIGHT_FG_SEL);

	syhl_gruvbox_light[SYHL_CODETAG] = allocimage(display, Rect(0,0,1,1), screen->chan, 1, GRUVBOX_YELLOW);
	syhl_gruvbox_light[SYHL_KEYWORD] = allocimage(display, Rect(0,0,1,1), screen->chan, 1, GRUVBOX_BLUE);
	syhl_gruvbox_light[SYHL_NUMBER] = allocimage(display, Rect(0,0,1,1), screen->chan, 1, GRUVBOX_PURPLE);
	syhl_gruvbox_light[SYHL_QUOTE] = allocimage(display, Rect(0,0,1,1), screen->chan, 1, GRUVBOX_GREEN);
	syhl_gruvbox_light[SYHL_COMMENT] = allocimage(display, Rect(0,0,1,1), screen->chan, 1, GRUVBOX_GREY);
	syhl_gruvbox_light[SYHL_ESCAPE] = allocimage(display, Rect(0,0,1,1), screen->chan, 1, GRUVBOX_RED);
	syhl_gruvbox_light[SYHL_PAREN] = allocimage(display, Rect(0,0,1,1), screen->chan, 1, GRUVBOX_AQUA);
}

#define GRUVBOX_DARK_BG 0x282828FF
#define GRUVBOX_DARK_BG_SEL 0x3C3836FF
#define GRUVBOX_DARK_FG 0xEBDBB2FF
#define GRUVBOX_DARK_FG_SEL 0xFBF1C7FF
#define GRUVBOX_DARK_BORD 0xFBF1C7FF

void init_syhl_gruvbox_dark(void) {
	textcols[BACK] = allocimagemix(display, GRUVBOX_DARK_BG, GRUVBOX_DARK_BG);
	textcols[HIGH] = allocimage(display, Rect(0,0,1,1), screen->chan, 1, GRUVBOX_DARK_BG_SEL);
	textcols[BORD] = allocimage(display, Rect(0,0,1,1), screen->chan, 1, GRUVBOX_DARK_BORD);
	textcols[TEXT] = allocimage(display, Rect(0,0,1,1), screen->chan, 1, GRUVBOX_DARK_FG);
	textcols[HTEXT] = allocimage(display, Rect(0,0,1,1), screen->chan, 1, GRUVBOX_DARK_FG_SEL);

	syhl_gruvbox_dark[SYHL_CODETAG] = allocimage(display, Rect(0,0,1,1), screen->chan, 1, GRUVBOX_YELLOW);
	syhl_gruvbox_dark[SYHL_KEYWORD] = allocimage(display, Rect(0,0,1,1), screen->chan, 1, GRUVBOX_BLUE);
	syhl_gruvbox_dark[SYHL_NUMBER] = allocimage(display, Rect(0,0,1,1), screen->chan, 1, GRUVBOX_PURPLE);
	syhl_gruvbox_dark[SYHL_QUOTE] = allocimage(display, Rect(0,0,1,1), screen->chan, 1, GRUVBOX_GREEN);
	syhl_gruvbox_dark[SYHL_COMMENT] = allocimage(display, Rect(0,0,1,1), screen->chan, 1, GRUVBOX_GREY);
	syhl_gruvbox_dark[SYHL_ESCAPE] = allocimage(display, Rect(0,0,1,1), screen->chan, 1, GRUVBOX_RED);
	syhl_gruvbox_dark[SYHL_PAREN] = allocimage(display, Rect(0,0,1,1), screen->chan, 1, GRUVBOX_AQUA);
}

void set_colorscheme(Image *colorscheme[SYHL_NCOL]) {
	for (int i=0; i<SYHL_NCOL; i++) {
		syhlcols[i] = colorscheme[i];
	}
}