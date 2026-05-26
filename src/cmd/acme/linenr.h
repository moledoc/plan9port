#ifndef LINENR_H
#define LINENR_H

#define Linenrwid_len 3
#define Linenrwid scalesize(display, t && t->fr.font ? (Linenrwid_len+1)*stringwidth(t->fr.font, "0")/2 : 32) // NOTE: fit Linenrwid_seed nr of digit in the number; /2, because stringwidth(,"0") will fit 2 instead of 1; +1 because with this func otherwise fits seed-1. // NOTE: requires access to Text *t.

void linenrdraw(Text *);

#endif // LINENR_H