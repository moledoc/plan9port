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
	ulong tag_bg;
	ulong tag_fg;
	ulong tag_sel;
	ulong tag_bord;

	ulong text_bg;
	ulong text_fg;
	ulong text_sel;
	ulong text_bord;

	ulong bord;

	ulong red;
	ulong yellow;
	ulong green;
	ulong blue;
	ulong purple;
	ulong magenta;
	ulong grey;
	ulong cyan;
} ColorScheme;

typedef struct AcmeColors
{
	Image *tagcols[NCOL];
	Image *textcols[NCOL];
	Image *syhlcols[SYHL_NCOL];
	Image *button;
	Image *modbutton;
	Image *colbutton;
	Image *but2col;
	Image *but3col;
} AcmeColors;

enum COLORSCHEME {
	COLORSCHEME_ACME_LIGHT,
	COLORSCHEME_ACME_DARK,
	COLORSCHEME_DRACULA_DARK,
	COLORSCHEME_ONE_DARK,
	COLORSCHEME_TOKYO_NIGHT_DARK,
	COLORSCHEME_TOKYO_NIGHT_LIGHT,
	COLORSCHEME_NORD_DARK,
	COLORSCHEME_CATPPUCCIN_MOCHA,
	COLORSCHEME_CATPPUCCIN_LATTE,
	COLORSCHEME_MONOKAI_DARK,
	COLORSCHEME_MATERIAL_DARK,
	COLORSCHEME_MATERIAL_LIGHT,
	COLORSCHEME_NIGHT_OWL_DARK,
	COLORSCHEME_AYU_DARK,
	COLORSCHEME_AYU_LIGHT,
	COLORSCHEME_GRUVBOX_DARK,
	COLORSCHEME_GRUVBOX_LIGHT,
	COLORSCHEME_SOLARIZED_DARK,
	COLORSCHEME_SOLARIZED_LIGHT,
	COLORSCHEMES_NCOL
};

typedef struct _str
{
	char *s;
	uint len;
} _str;

static const _str colorscheme_names[COLORSCHEMES_NCOL] = {
	{.s="acme-light", .len=10},
	{.s="acme-dark", .len=9},
	{.s="dracula-dark", .len=13},
	{.s="one-dark", .len=8},
	{.s="tokyo-night-dark", .len=17},
	{.s="tokyo-night-light", .len=18},
	{.s="nord-dark", .len=9},
	{.s="catppuccin-mocha", .len=16},
	{.s="catppuccin-latte", .len=16},
	{.s="monokai-dark", .len=13},
	{.s="material-dark", .len=13},
	{.s="material-light", .len=14},
	{.s="night-owl-dark", .len=15},
	{.s="ayu-dark", .len=8},
	{.s="ayu-light", .len=9},
	{.s="gruvbox-dark", .len=13},
	{.s="gruvbox-light", .len=14},
	{.s="solarized-dark", .len=15},
	{.s="solarized-light", .len=16},
};

extern AcmeColors colorschemes[COLORSCHEMES_NCOL];
extern enum COLORSCHEME current_colorscheme;

enum COLORSCHEME cs_mapping(char *);

void init_colorscheme(enum COLORSCHEME, ColorScheme *);

void set_colorscheme(enum COLORSCHEME);
void set_buttons();
void update_frame_colorscheme(Frame *, Frame *);
void redraw_acme();

extern ColorScheme color_schemes[COLORSCHEMES_NCOL];

#endif // COLORSCHEMES_H