#ifndef LINENR_H
#define LINENR_H

// NOTE: Linenrwid makes room for number containing 'Linenrwid_len' digits for rownumber drawing.
// NOTE: /2 because stringwid("0") gives 2 with the fonts I tried.
// NOTE: defaults to 32 if no access to font. With the font I'm currently running, it should be enough (3 digits).
#define Linenrwid_len 3
#define Linenrwid scalesize(display, t && t->fr.font ? (Linenrwid_len+(Linenrwid_len%2!=0))*stringwidth(t->fr.font, "0")/2 : 32)

void linenrdraw(Text *);

#endif // LINENR_H