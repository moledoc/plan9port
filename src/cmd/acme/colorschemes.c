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
Image		*syhl_groovebox_light[SYHL_NCOL];
Image		*syhl_groovebox_dark[SYHL_NCOL];

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

void set_colorscheme(Image *colorscheme[SYHL_NCOL]) {
	for (int i=0; i<SYHL_NCOL; i++) {
		syhlcols[i] = colorscheme[i];
	}
}