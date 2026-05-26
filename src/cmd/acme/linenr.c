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
#include <stdio.h>
#include "dat.h"
#include "fns.h"
#include "tsyhl.h"
#include "linenr.h"

void linenrdraw(Text *t) {
	if (t->what != Body) return;

	Rectangle r;
	char linenr_buf[Linenrwid_len+1] = {0};

	// NOTE: draw linenr bg
	r = t->scrollr;
	r.min.x += Scrollwid;
	r.max.x += Linenrwid;
	draw(t->fr.b, r, t->fr.cols[BACK], nil, ZP);

	Point pt = Pt(r.min.x, r.min.y); // NOTE: where numbers are started to be drawn

	for (int i=0; i<t->fr.maxlines; i++) {
		memset(linenr_buf, 0, Linenrwid_len+1);
		snprintf(linenr_buf, Linenrwid_len+1, "%d", i+1);
		stringn(screen, pt, syhlcols[SYHL_NUMBER], ZP, t->fr.font, linenr_buf, Linenrwid_len);
		pt.y += t->fr.font->height;
	}

	// NOTE: draw linenr border
	r = t->scrollr;
	r.min.x += Scrollwid+Linenrwid-1;
	r.max.x += Linenrwid;
	draw(t->fr.b, r, t->fr.cols[BORD], nil, ZP);
}
