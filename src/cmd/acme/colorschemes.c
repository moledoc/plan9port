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

enum COLORSCHEME current_colorscheme = COLORSCHEME_LIGHT;
ColorScheme colorschemes[COLORSCHEMES_NCOL] = {0};

void init_colorscheme_light(void) {
	ColorScheme *colorscheme_light = &colorschemes[COLORSCHEME_LIGHT];

	colorscheme_light->tagcols[BACK] = allocimagemix(display, DPalebluegreen, DWhite);
	colorscheme_light->tagcols[HIGH] = allocimage(display, Rect(0,0,1,1), screen->chan, 1, DPalegreygreen);
	colorscheme_light->tagcols[BORD] = allocimage(display, Rect(0,0,1,1), screen->chan, 1, DPurpleblue);
	colorscheme_light->tagcols[TEXT] = display->black;
	colorscheme_light->tagcols[HTEXT] = display->black;

	colorscheme_light->textcols[BACK] = allocimagemix(display, DWhite, DWhite);
	colorscheme_light->textcols[HIGH] = allocimage(display, Rect(0,0,1,1), screen->chan, 1, DDarkyellow);
	colorscheme_light->textcols[BORD] = allocimage(display, Rect(0,0,1,1), screen->chan, 1, DGrey);
	colorscheme_light->textcols[TEXT] = display->black;
	colorscheme_light->textcols[HTEXT] = display->black;

	colorscheme_light->syhlcols[SYHL_CODETAG] = allocimage(display, Rect(0,0,1,1), screen->chan, 1, DYellowGold);
	colorscheme_light->syhlcols[SYHL_KEYWORD] = allocimage(display, Rect(0,0,1,1), screen->chan, 1, DBlue);
	colorscheme_light->syhlcols[SYHL_NUMBER] = allocimage(display, Rect(0,0,1,1), screen->chan, 1, DMagenta);
	colorscheme_light->syhlcols[SYHL_QUOTE] = allocimage(display, Rect(0,0,1,1), screen->chan, 1, DMedgreen);
	colorscheme_light->syhlcols[SYHL_COMMENT] = allocimage(display, Rect(0,0,1,1), screen->chan, 1, DGrey);
	colorscheme_light->syhlcols[SYHL_ESCAPE] = allocimage(display, Rect(0,0,1,1), screen->chan, 1, DRed);
	colorscheme_light->syhlcols[SYHL_PAREN] = allocimage(display, Rect(0,0,1,1), screen->chan, 1, DYellowgreen);
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

void init_colorscheme_gruvbox_light(void) {
	ColorScheme *colorscheme_gruvbox_light = &colorschemes[COLORSCHEME_GRUVBOX_LIGHT];

	colorscheme_gruvbox_light->tagcols[BACK] = allocimagemix(display, DPalebluegreen, DWhite);
	colorscheme_gruvbox_light->tagcols[HIGH] = allocimage(display, Rect(0,0,1,1), screen->chan, 1, DPalegreygreen);
	colorscheme_gruvbox_light->tagcols[BORD] = allocimage(display, Rect(0,0,1,1), screen->chan, 1, DPurpleblue);
	colorscheme_gruvbox_light->tagcols[TEXT] = display->black;
	colorscheme_gruvbox_light->tagcols[HTEXT] = display->black;


	colorscheme_gruvbox_light->textcols[BACK] = allocimagemix(display, GRUVBOX_LIGHT_BG, GRUVBOX_LIGHT_BG);
	colorscheme_gruvbox_light->textcols[HIGH] = allocimage(display, Rect(0,0,1,1), screen->chan, 1, GRUVBOX_LIGHT_BG_SEL);
	colorscheme_gruvbox_light->textcols[BORD] = allocimage(display, Rect(0,0,1,1), screen->chan, 1, GRUVBOX_LIGHT_BORD);
	colorscheme_gruvbox_light->textcols[TEXT] = allocimage(display, Rect(0,0,1,1), screen->chan, 1, GRUVBOX_LIGHT_FG);
	colorscheme_gruvbox_light->textcols[HTEXT] = allocimage(display, Rect(0,0,1,1), screen->chan, 1, GRUVBOX_LIGHT_FG_SEL);

	colorscheme_gruvbox_light->syhlcols[SYHL_CODETAG] = allocimage(display, Rect(0,0,1,1), screen->chan, 1, GRUVBOX_YELLOW);
	colorscheme_gruvbox_light->syhlcols[SYHL_KEYWORD] = allocimage(display, Rect(0,0,1,1), screen->chan, 1, GRUVBOX_BLUE);
	colorscheme_gruvbox_light->syhlcols[SYHL_NUMBER] = allocimage(display, Rect(0,0,1,1), screen->chan, 1, GRUVBOX_PURPLE);
	colorscheme_gruvbox_light->syhlcols[SYHL_QUOTE] = allocimage(display, Rect(0,0,1,1), screen->chan, 1, GRUVBOX_GREEN);
	colorscheme_gruvbox_light->syhlcols[SYHL_COMMENT] = allocimage(display, Rect(0,0,1,1), screen->chan, 1, GRUVBOX_GREY);
	colorscheme_gruvbox_light->syhlcols[SYHL_ESCAPE] = allocimage(display, Rect(0,0,1,1), screen->chan, 1, GRUVBOX_RED);
	colorscheme_gruvbox_light->syhlcols[SYHL_PAREN] = allocimage(display, Rect(0,0,1,1), screen->chan, 1, GRUVBOX_AQUA);
}

#define GRUVBOX_DARK_BG 0x282828FF
#define GRUVBOX_DARK_BG_SEL 0x3C3836FF
#define GRUVBOX_DARK_FG 0xEBDBB2FF
#define GRUVBOX_DARK_FG_SEL 0xFBF1C7FF
#define GRUVBOX_DARK_BORD 0xFBF1C7FF

void init_colorscheme_gruvbox_dark(void) {
	ColorScheme *colorscheme_gruvbox_dark = &colorschemes[COLORSCHEME_GRUVBOX_DARK];

	colorscheme_gruvbox_dark->tagcols[BACK] = allocimagemix(display, DPalebluegreen, DWhite);
	colorscheme_gruvbox_dark->tagcols[HIGH] = allocimage(display, Rect(0,0,1,1), screen->chan, 1, DPalegreygreen);
	colorscheme_gruvbox_dark->tagcols[BORD] = allocimage(display, Rect(0,0,1,1), screen->chan, 1, DPurpleblue);
	colorscheme_gruvbox_dark->tagcols[TEXT] = display->black;
	colorscheme_gruvbox_dark->tagcols[HTEXT] = display->black;

	colorscheme_gruvbox_dark->textcols[BACK] = allocimagemix(display, GRUVBOX_DARK_BG, GRUVBOX_DARK_BG);
	colorscheme_gruvbox_dark->textcols[HIGH] = allocimage(display, Rect(0,0,1,1), screen->chan, 1, GRUVBOX_DARK_BG_SEL);
	colorscheme_gruvbox_dark->textcols[BORD] = allocimage(display, Rect(0,0,1,1), screen->chan, 1, GRUVBOX_DARK_BORD);
	colorscheme_gruvbox_dark->textcols[TEXT] = allocimage(display, Rect(0,0,1,1), screen->chan, 1, GRUVBOX_DARK_FG);
	colorscheme_gruvbox_dark->textcols[HTEXT] = allocimage(display, Rect(0,0,1,1), screen->chan, 1, GRUVBOX_DARK_FG_SEL);

	colorscheme_gruvbox_dark->syhlcols[SYHL_CODETAG] = allocimage(display, Rect(0,0,1,1), screen->chan, 1, GRUVBOX_YELLOW);
	colorscheme_gruvbox_dark->syhlcols[SYHL_KEYWORD] = allocimage(display, Rect(0,0,1,1), screen->chan, 1, GRUVBOX_BLUE);
	colorscheme_gruvbox_dark->syhlcols[SYHL_NUMBER] = allocimage(display, Rect(0,0,1,1), screen->chan, 1, GRUVBOX_PURPLE);
	colorscheme_gruvbox_dark->syhlcols[SYHL_QUOTE] = allocimage(display, Rect(0,0,1,1), screen->chan, 1, GRUVBOX_GREEN);
	colorscheme_gruvbox_dark->syhlcols[SYHL_COMMENT] = allocimage(display, Rect(0,0,1,1), screen->chan, 1, GRUVBOX_GREY);
	colorscheme_gruvbox_dark->syhlcols[SYHL_ESCAPE] = allocimage(display, Rect(0,0,1,1), screen->chan, 1, GRUVBOX_RED);
	colorscheme_gruvbox_dark->syhlcols[SYHL_PAREN] = allocimage(display, Rect(0,0,1,1), screen->chan, 1, GRUVBOX_AQUA);
}


void init_colorschemes(void) {
	init_colorscheme_light();
	init_colorscheme_gruvbox_light();
	init_colorscheme_gruvbox_dark();
}


void set_colorscheme(enum COLORSCHEME cse) {
	ColorScheme cs = colorschemes[cse];
	for (int i=0; i<NCOL; i++) {
		tagcols[i] = cs.tagcols[i];
		textcols[i] = cs.textcols[i];
	}
	for (int i=0; i<SYHL_NCOL; i++) {
		syhlcols[i] = cs.syhlcols[i];
	}
}