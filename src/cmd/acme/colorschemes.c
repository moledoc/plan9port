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
#include "tsyhl.h"
#include "colorschemes.h"
#include <stdio.h> // REMOVEME:

// MAYBE: unload old and load new scheme everytime?

init_colorscheme_funcs_t init_colorscheme_funcs[COLORSCHEMES_NCOL] = {
	init_colorscheme_light,
	init_colorscheme_gruvbox_light,
	init_colorscheme_gruvbox_dark,
	init_colorscheme_light, // NOTE: just in case, consider like default
};

/*
void init_colorschemes(void) {
	init_colorscheme_light();
	init_colorscheme_gruvbox_light();
	init_colorscheme_gruvbox_dark();
}
*/

void set_colorscheme(enum COLORSCHEME cse) {
	current_colorscheme = cse;
	ColorScheme cs = colorschemes[cse];
	if (cs.tagcols[BACK] == NULL) { // NOTE: if not loaded into mem yet, do it
		init_colorscheme_funcs[cse]();
		cs = colorschemes[cse];
	}
	for (int i=0; i<NCOL; i++) {
		tagcols[i] = cs.tagcols[i];
		textcols[i] = cs.textcols[i];
	}
	for (int i=0; i<SYHL_NCOL; i++) {
		syhlcols[i] = cs.syhlcols[i];
	}
	set_buttons();
}

void set_buttons() {
	ColorScheme cs = colorschemes[current_colorscheme];
	Rectangle r = Rect(0, 0, Scrollwid, font->height+1);
	/*
	if(button){
		freeimage(button);
		freeimage(modbutton);
		freeimage(colbutton);
	}
	*/
	if (modbutton) {
		freeimage(modbutton);
	}

	button = cs.button;
	draw(button, r, tagcols[BACK], nil, r.min);
	border(button, r, ButtonBorder, tagcols[BORD], ZP);

	r = button->r;
	modbutton = allocimage(display, r, screen->chan, 0, DNofill);
	draw(modbutton, r, tagcols[BACK], nil, r.min);
	border(modbutton, r, ButtonBorder, tagcols[BORD], ZP);
	r = insetrect(r, ButtonBorder);
	draw(modbutton, r, cs.modbutton, nil, ZP);

	r = button->r;
	colbutton = cs.colbutton;

	but2col = cs.but2col;
	but3col = cs.but3col;
}

void update_frame_colorscheme(Frame *tag, Frame *body) {
	ColorScheme cs = colorschemes[current_colorscheme];
	for (int i=0; i<NCOL; i++) {
		if (tag) {
			tag->cols[i] = cs.tagcols[i];
		}
		if (body) {
			body->cols[i] = cs.textcols[i];
		}
	}
}

void redraw_acme() {
	Column *col;
	Window *w;
	for (int i = 0; i<row.ncol; i++) {
		col = row.col[i];
		for (int j = 0; j<col->nw; j++) {
			w = col->w[j];
			update_frame_colorscheme(&w->tag.fr, &w->body.fr);
			frinittick(&w->tag.fr);
			frinittick(&w->body.fr);
		}
		update_frame_colorscheme(&col->tag.fr, NULL);
		frinittick(&col->tag.fr);
	}
	update_frame_colorscheme(&row.tag.fr, NULL);
	frinittick(&row.tag.fr);
	rowresize(&row, row.r);
	set_buttons();
	flushimage(display, 1);
}



// TODO: add more colorschemes
// TODO: implement 'Theme' cmd (like Font, Edit etc) to change colorscheme. eg `Theme gruvbox-dark`

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

	Rectangle r = Rect(0, 0, Scrollwid, font->height+1);
	colorscheme_light->button = allocimage(display, r, screen->chan, 0, DNofill);
	colorscheme_light->modbutton = allocimage(display, r, screen->chan, 1, DMedblue);
	colorscheme_light->colbutton = allocimage(display, r, screen->chan, 0, DPurpleblue);
	colorscheme_light->but2col = allocimage(display, r, screen->chan, 1, 0xAA0000FF);
	colorscheme_light->but3col = allocimage(display, r, screen->chan, 1, 0x006600FF);
}

#define GRUVBOX_RED 0xCC241DFF
#define GRUVBOX_GREEN 0x98971AFF
#define GRUVBOX_YELLOW 0xD79921FF
#define GRUVBOX_BLUE 0x458588FF
#define GRUVBOX_PURPLE 0xB16286FF
#define GRUVBOX_AQUA 0x689D6AFF
#define GRUVBOX_GREY 0x7C6F64FF
#define GRUVBOX_GREY2 0x928374FF

#define GRUVBOX_LIGHT_TAG_BG 0xD5C4A1FF
#define GRUVBOX_LIGHT_TAG_BG_SEL 0xEBDBB2FF
#define GRUVBOX_LIGHT_TAG_BORD 0x076678FF
#define GRUVBOX_LIGHT_TAG_FG 0x3C3836FF
#define GRUVBOX_LIGHT_TAG_FG_SEL 0x282828FF

#define GRUVBOX_LIGHT_BG 0xFBF1C7FF
#define GRUVBOX_LIGHT_BG_SEL 0xEBDBB2FF
#define GRUVBOX_LIGHT_BORD 0x282828FF
#define GRUVBOX_LIGHT_FG 0x3C3836FF
#define GRUVBOX_LIGHT_FG_SEL 0x282828FF

void init_colorscheme_gruvbox_light(void) {
	ColorScheme *colorscheme_gruvbox_light = &colorschemes[COLORSCHEME_GRUVBOX_LIGHT];

	colorscheme_gruvbox_light->tagcols[BACK] = allocimagemix(display, GRUVBOX_LIGHT_TAG_BG, GRUVBOX_LIGHT_TAG_BG);
	colorscheme_gruvbox_light->tagcols[HIGH] = allocimage(display, Rect(0,0,1,1), screen->chan, 1, GRUVBOX_LIGHT_TAG_BG_SEL);
	colorscheme_gruvbox_light->tagcols[BORD] = allocimage(display, Rect(0,0,1,1), screen->chan, 1, GRUVBOX_LIGHT_TAG_BORD);
	colorscheme_gruvbox_light->tagcols[TEXT] = allocimage(display, Rect(0,0,1,1), screen->chan, 1, GRUVBOX_LIGHT_TAG_FG);
	colorscheme_gruvbox_light->tagcols[HTEXT] = allocimage(display, Rect(0,0,1,1), screen->chan, 1, GRUVBOX_LIGHT_TAG_FG_SEL);

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

	Rectangle r = Rect(0, 0, Scrollwid, font->height+1);
	colorscheme_gruvbox_light->button = allocimage(display, r, screen->chan, 0, DNofill);
	colorscheme_gruvbox_light->modbutton = allocimage(display, r, screen->chan, 1, GRUVBOX_BLUE);
	colorscheme_gruvbox_light->colbutton = allocimage(display, r, screen->chan, 0, GRUVBOX_PURPLE);
	colorscheme_gruvbox_light->but2col = allocimage(display, r, screen->chan, 1, GRUVBOX_RED);
	colorscheme_gruvbox_light->but3col = allocimage(display, r, screen->chan, 1, GRUVBOX_GREEN);
}


#define GRUVBOX_DARK_TAG_BG 0x504945FF
#define GRUVBOX_DARK_TAG_BG_SEL 0x3C3836FF
#define GRUVBOX_DARK_TAG_BORD 0x83A58FF
#define GRUVBOX_DARK_TAG_FG 0xEBDBB2FF
#define GRUVBOX_DARK_TAG_FG_SEL 0xFBF1C7FF

#define GRUVBOX_DARK_BG 0x282828FF
#define GRUVBOX_DARK_BG_SEL 0x3C3836FF
#define GRUVBOX_DARK_BORD 0xFBF1C7FF
#define GRUVBOX_DARK_FG 0xEBDBB2FF
#define GRUVBOX_DARK_FG_SEL 0xFBF1C7FF

void init_colorscheme_gruvbox_dark(void) {
	ColorScheme *colorscheme_gruvbox_dark = &colorschemes[COLORSCHEME_GRUVBOX_DARK];

	colorscheme_gruvbox_dark->tagcols[BACK] = allocimagemix(display, GRUVBOX_DARK_TAG_BG, GRUVBOX_DARK_TAG_BG);
	colorscheme_gruvbox_dark->tagcols[HIGH] = allocimage(display, Rect(0,0,1,1), screen->chan, 1, GRUVBOX_DARK_TAG_BG_SEL);
	colorscheme_gruvbox_dark->tagcols[BORD] = allocimage(display, Rect(0,0,1,1), screen->chan, 1, GRUVBOX_DARK_TAG_BORD);
	colorscheme_gruvbox_dark->tagcols[TEXT] = allocimage(display, Rect(0,0,1,1), screen->chan, 1, GRUVBOX_DARK_TAG_FG);
	colorscheme_gruvbox_dark->tagcols[HTEXT] = allocimage(display, Rect(0,0,1,1), screen->chan, 1, GRUVBOX_DARK_TAG_FG_SEL);

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

	Rectangle r = Rect(0, 0, Scrollwid, font->height+1);
	colorscheme_gruvbox_dark->button = allocimage(display, r, screen->chan, 0, DNofill);
	colorscheme_gruvbox_dark->modbutton = allocimage(display, r, screen->chan, 1, GRUVBOX_BLUE);
	colorscheme_gruvbox_dark->colbutton = allocimage(display, r, screen->chan, 0, GRUVBOX_PURPLE);
	colorscheme_gruvbox_dark->but2col = allocimage(display, r, screen->chan, 1, GRUVBOX_RED);
	colorscheme_gruvbox_dark->but3col = allocimage(display, r, screen->chan, 1, GRUVBOX_GREEN);
}
