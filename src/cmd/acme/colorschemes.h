#ifndef COLORSCHEMES_H
#define COLORSCHEMES_H

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
#include "dat.h"
#include "fns.h"
#include "tsyhl.h"

typedef struct ColorScheme
{
	Image *tagcols[NCOL];
	Image *textcols[NCOL];
	Image *syhlcols[SYHL_NCOL];
	Image *button;
	Image *modbutton;
	Image *colbutton;
	Image *but2col;
	Image *but3col;
} ColorScheme;

enum COLORSCHEME {
	COLORSCHEME_LIGHT,
	COLORSCHEME_GRUVBOX_LIGHT,
	COLORSCHEME_GRUVBOX_DARK,
	COLORSCHEME_SOLARIZED_LIGHT,
	COLORSCHEME_SOLARIZED_DARK,
	COLORSCHEMES_NCOL
};

typedef void (*init_colorscheme_funcs_t)(void);

extern ColorScheme colorschemes[COLORSCHEMES_NCOL];
extern enum COLORSCHEME current_colorscheme;
extern init_colorscheme_funcs_t init_colorscheme_funcs[COLORSCHEMES_NCOL];

enum COLORSCHEME cs_mapping(char *);

// void init_colorschemes(void);
void set_colorscheme(enum COLORSCHEME);
void set_buttons();
void update_frame_colorscheme(Frame *, Frame *);
void redraw_acme();

void init_colorscheme_light(void);
void init_colorscheme_gruvbox_light(void);
void init_colorscheme_gruvbox_dark(void);
void init_colorscheme_solarized_light(void);
void init_colorscheme_solarized_dark(void);


#endif // COLORSCHEMES_H