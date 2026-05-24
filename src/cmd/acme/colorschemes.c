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

enum COLORSCHEME current_colorscheme = COLORSCHEME_ACME_LIGHT;
AcmeColors colorschemes[COLORSCHEMES_NCOL] = {0};

// MAYBE: unload old and load new scheme everytime?
void set_colorscheme(enum COLORSCHEME cse) {
	current_colorscheme = cse;
	AcmeColors acs = colorschemes[cse];
	if (acs.tagcols[BACK] == NULL) { // NOTE: if not loaded into mem yet, do it
		init_colorscheme(cse, &color_schemes[cse]);
		acs = colorschemes[cse];
	}
	for (int i=0; i<NCOL; i++) {
		tagcols[i] = acs.tagcols[i];
		textcols[i] = acs.textcols[i];
	}
	for (int i=0; i<SYHL_NCOL; i++) {
		syhlcols[i] = acs.syhlcols[i];
	}
	set_buttons();
}

void set_buttons() {
	AcmeColors acs = colorschemes[current_colorscheme];
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

	button = acs.button;
	draw(button, r, tagcols[BACK], nil, r.min);
	border(button, r, ButtonBorder, tagcols[BORD], ZP);

	r = button->r;
	modbutton = allocimage(display, r, screen->chan, 0, DNofill);
	draw(modbutton, r, tagcols[BACK], nil, r.min);
	border(modbutton, r, ButtonBorder, tagcols[BORD], ZP);
	r = insetrect(r, ButtonBorder);
	draw(modbutton, r, acs.modbutton, nil, ZP);

	r = button->r;
	colbutton = acs.colbutton;

	but2col = acs.but2col;
	but3col = acs.but3col;
}

void update_frame_colorscheme(Frame *tag, Frame *body) {
	AcmeColors acs = colorschemes[current_colorscheme];
	for (int i=0; i<NCOL; i++) {
		if (tag) {
			tag->cols[i] = acs.tagcols[i];
		}
		if (body) {
			body->cols[i] = acs.textcols[i];
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

enum COLORSCHEME cs_mapping(char *theme) {
	for (enum COLORSCHEME i = 0; i < COLORSCHEMES_NCOL; i++) {
		_str cs_name = colorscheme_names[i];
		if (strncmp(theme, cs_name.s, cs_name.len) == 0) {
			return i;
		}
	}
	return current_colorscheme;
}

void init_colorscheme(enum COLORSCHEME cse, ColorScheme *cs) {
	AcmeColors *acs = &colorschemes[cse];

	acs->tagcols[BACK] = allocimage(display, Rect(0,0,1,1), screen->chan, 1, cs->tag_bg);
	acs->tagcols[HIGH] = allocimage(display, Rect(0,0,1,1), screen->chan, 1, cs->tag_sel);
	acs->tagcols[BORD] = allocimage(display, Rect(0,0,1,1), screen->chan, 1, cs->tag_bord);
	acs->tagcols[TEXT] = allocimage(display, Rect(0,0,1,1), screen->chan, 1, cs->tag_fg);
	acs->tagcols[HTEXT] = allocimage(display, Rect(0,0,1,1), screen->chan, 1, cs->tag_fg);

	acs->textcols[BACK] = allocimage(display, Rect(0,0,1,1), screen->chan, 1, cs->text_bg);
	acs->textcols[HIGH] = allocimage(display, Rect(0,0,1,1), screen->chan, 1, cs->text_sel);
	acs->textcols[BORD] = allocimage(display, Rect(0,0,1,1), screen->chan, 1, cs->text_bord);
	acs->textcols[TEXT] = allocimage(display, Rect(0,0,1,1), screen->chan, 1, cs->text_fg);
	acs->textcols[HTEXT] = allocimage(display, Rect(0,0,1,1), screen->chan, 1, cs->text_fg);

	acs->syhlcols[SYHL_CODETAG] = allocimage(display, Rect(0,0,1,1), screen->chan, 1, cs->yellow);
	acs->syhlcols[SYHL_KEYWORD] = allocimage(display, Rect(0,0,1,1), screen->chan, 1, cs->blue);
	acs->syhlcols[SYHL_NUMBER] = allocimage(display, Rect(0,0,1,1), screen->chan, 1, cs->magenta);
	acs->syhlcols[SYHL_QUOTE] = allocimage(display, Rect(0,0,1,1), screen->chan, 1, cs->green);
	acs->syhlcols[SYHL_COMMENT] = allocimage(display, Rect(0,0,1,1), screen->chan, 1, cs->grey);
	acs->syhlcols[SYHL_ESCAPE] = allocimage(display, Rect(0,0,1,1), screen->chan, 1, cs->red);
	acs->syhlcols[SYHL_PAREN] = allocimage(display, Rect(0,0,1,1), screen->chan, 1, cs->cyan);

	Rectangle r = Rect(0, 0, Scrollwid, font->height+1);
	acs->button = allocimage(display, r, screen->chan, 0, DNofill);
	acs->modbutton = allocimage(display, r, screen->chan, 1, cs->blue);
	acs->colbutton = allocimage(display, r, screen->chan, 0, cs->purple);
	acs->but2col = allocimage(display, r, screen->chan, 1, cs->red);
	acs->but3col = allocimage(display, r, screen->chan, 1, cs->green);
}

ColorScheme color_schemes[COLORSCHEMES_NCOL] = {
	// COLORSCHEME_ACME_LIGHT
	{
        .tag_bg    = 0xFFFFEAFF,
        .tag_fg    = 0x000000FF,
        .tag_sel   = 0xDADADAFF,
        .tag_bord  = 0x999999FF,

        .text_bg   = 0xFFFFEAFF,
        .text_fg   = 0x000000FF,
        .text_sel  = 0xD6E8F8FF,
        .text_bord = 0xAAAAAAFF,

        .red       = 0xC24A4AFF,
        .yellow    = 0xC99A2EFF,
        .green     = 0x4F7F4FFF,
        .blue      = 0x4A63B8FF,
        .purple    = 0x7A56A6FF,
        .magenta   = 0xA6547CFF,
        .grey      = 0x777777FF,
        .cyan      = 0x4F9A9AFF
    },

	// COLORSCHEME_ACME_DARK
    {
        .tag_bg    = 0x1A1A1AFF,
        .tag_fg    = 0xCFCFCFFF,
        .tag_sel   = 0x333333FF,
        .tag_bord  = 0x555555FF,

        .text_bg   = 0x101010FF,
        .text_fg   = 0xD0D0D0FF,
        .text_sel  = 0x2A3B4DFF,
        .text_bord = 0x444444FF,

        .red       = 0xC75A5AFF,
        .yellow    = 0xC9A24AFF,
        .green     = 0x5A8A5AFF,
        .blue      = 0x5A74C9FF,
        .purple    = 0x8A63C2FF,
        .magenta   = 0xC2638CFF,
        .grey      = 0x888888FF,
        .cyan      = 0x5AA6A6FF
    },

	// COLORSCHEME_DRACULA_DARK
	{
		.tag_bg    = 0x44475AFF,
		.tag_fg    = 0xBFBFBFFF,
		.tag_sel   = 0x6272A4FF,
		.tag_bord  = 0x6272A4FF,

		.text_bg   = 0x282A36FF,
		.text_fg   = 0xF8F8F2FF,
		.text_sel  = 0x44475AFF,
		.text_bord = 0x44475AFF,

		.red       = 0xFF5555FF,
		.yellow    = 0xF1FA8CFF,
		.green     = 0x50FA7BFF,
		.blue      = 0x6272A4FF,
		.purple    = 0xBD93F9FF,
		.magenta   = 0xFF79C6FF,
		.grey      = 0x808080FF,
		.cyan      = 0x8BE9FDFF
	},

	// COLORSCHEME_ONE_DARK
	{
		.tag_bg    = 0x353B45FF,
		.tag_fg    = 0x828997FF,
		.tag_sel   = 0x4B5263FF,
		.tag_bord  = 0x4B5263FF,

		.text_bg   = 0x282C34FF,
		.text_fg   = 0xABB2BFFF,
		.text_sel  = 0x3E4451FF,
		.text_bord = 0x3E4451FF,

		.red       = 0xE06C75FF,
		.yellow    = 0xE5C07BFF,
		.green     = 0x98C379FF,
		.blue      = 0x61AFEFFF,
		.purple    = 0xC678DDFF,
		.magenta   = 0xBE80BFFF,
		.grey      = 0x5C6370FF,
		.cyan      = 0x56B6C2FF
	},

	// COLORSCHEME_TOKYO_NIGHT_DARK
	{
		.tag_bg    = 0x24283BFF,
		.tag_fg    = 0x9AA5CEFF,
		.tag_sel   = 0x3B4261FF,
		.tag_bord  = 0x3B4261FF,

		.text_bg   = 0x1A1B26FF,
		.text_fg   = 0xC0CAF5FF,
		.text_sel  = 0x33467CFF,
		.text_bord = 0x33467CFF,

		.red       = 0xF7768EFF,
		.yellow    = 0xE0AF68FF,
		.green     = 0x9ECE6AFF,
		.blue      = 0x7AA2F7FF,
		.purple    = 0xBB9AF7FF,
		.magenta   = 0xFF007CFF,
		.grey      = 0x565F89FF,
		.cyan      = 0x7DCFFFFF
	},

	// COLORSCHEME_TOKYO_NIGHT_LIGHT
	{
		.tag_bg    = 0xCBCCD1FF,
		.tag_fg    = 0x565F89FF,
		.tag_sel   = 0xA8AECBFF,
		.tag_bord  = 0xA8AECBFF,

		.text_bg   = 0xD5D6DBFF,
		.text_fg   = 0x343B58FF,
		.text_sel  = 0xB4D0E9FF,
		.text_bord = 0xB4D0E9FF,

		.red       = 0x8C4351FF,
		.yellow    = 0x8F5E15FF,
		.green     = 0x485E30FF,
		.blue      = 0x34548AFF,
		.purple    = 0x5A4A78FF,
		.magenta   = 0x9854F1FF,
		.grey      = 0x848CB5FF,
		.cyan      = 0x166775FF
	},

	// COLORSCHEME_NORD_DARK
	{
		.tag_bg    = 0x3B4252FF,
		.tag_fg    = 0x81A1C1FF,
		.tag_sel   = 0x4C566AFF,
		.tag_bord  = 0x4C566AFF,

		.text_bg   = 0x2E3440FF,
		.text_fg   = 0xD8DEE9FF,
		.text_sel  = 0x434C5EFF,
		.text_bord = 0x434C5EFF,

		.red       = 0xBF616AFF,
		.yellow    = 0xEBCB8BFF,
		.green     = 0xA3BE8CFF,
		.blue      = 0x81A1C1FF,
		.purple    = 0xB48EADFF,
		.magenta   = 0xD087C0FF,
		.grey      = 0x616E88FF,
		.cyan      = 0x88C0D0FF
	},

	// COLORSCHEME_CATPPUCCIN_MOCHA
	{
		.tag_bg    = 0x313244FF,
		.tag_fg    = 0xA6ADC8FF,
		.tag_sel   = 0x585B70FF,
		.tag_bord  = 0x585B70FF,

		.text_bg   = 0x1E1E2EFF,
		.text_fg   = 0xCDD6F4FF,
		.text_sel  = 0x45475AFF,
		.text_bord = 0x45475AFF,

		.red       = 0xF38BA8FF,
		.yellow    = 0xF9E2AFFF,
		.green     = 0xA6E3A1FF,
		.blue      = 0x89B4FAFF,
		.purple    = 0xCBA6F7FF,
		.magenta   = 0xF5C2E7FF,
		.grey      = 0x7F849CFF,
		.cyan      = 0x94E2D5FF
	},

	// COLORSCHEME_CATPPUCCIN_LATTE
	{
		.tag_bg    = 0xDCE0E8FF,
		.tag_fg    = 0x6C6F85FF,
		.tag_sel   = 0xACB0BEFF,
		.tag_bord  = 0xACB0BEFF,

		.text_bg   = 0xEFF1F5FF,
		.text_fg   = 0x4C4F69FF,
		.text_sel  = 0xBCC0CCFF,
		.text_bord = 0xBCC0CCFF,

		.red       = 0xD20F39FF,
		.yellow    = 0xDF8E1DFF,
		.green     = 0x40A02BFF,
		.blue      = 0x1E66F5FF,
		.purple    = 0x8839EAFF,
		.magenta   = 0xEA76CBFF,
		.grey      = 0x9CA0B0FF,
		.cyan      = 0x179299FF
	},

	// COLORSCHEME_MONOKAI_DARK
	{
		.tag_bg    = 0x3E3D32FF,
		.tag_fg    = 0xB3B3ADFF,
		.tag_sel   = 0x5A594DFF,
		.tag_bord  = 0x5A594DFF,

		.text_bg   = 0x272822FF,
		.text_fg   = 0xF8F8F2FF,
		.text_sel  = 0x49483EFF,
		.text_bord = 0x49483EFF,

		.red       = 0xF92672FF,
		.yellow    = 0xE6DB74FF,
		.green     = 0xA6E22EFF,
		.blue      = 0x669BEFFF,
		.purple    = 0xAE81FFFF,
		.magenta   = 0xFD5FF1FF,
		.grey      = 0x75715EFF,
		.cyan      = 0x66D9EFFF
	},

	// COLORSCHEME_MATERIAL_DARK
	{
		.tag_bg    = 0x2B2B2BFF,
		.tag_fg    = 0xB0BEC5FF,
		.tag_sel   = 0x4F5B62FF,
		.tag_bord  = 0x4F5B62FF,

		.text_bg   = 0x212121FF,
		.text_fg   = 0xEEFFFFFF,
		.text_sel  = 0x404040FF,
		.text_bord = 0x404040FF,

		.red       = 0xF07178FF,
		.yellow    = 0xFFCB6BFF,
		.green     = 0xC3E88DFF,
		.blue      = 0x82AAFFFF,
		.purple    = 0xC792EAFF,
		.magenta   = 0xFF5370FF,
		.grey      = 0x546E7AFF,
		.cyan      = 0x89DDFFFF
	},

	// COLORSCHEME_MATERIAL_LIGHT
	{
		.tag_bg    = 0xE7EAECFF,
		.tag_fg    = 0x90A4AEFF,
		.tag_sel   = 0xB0BEC5FF,
		.tag_bord  = 0xB0BEC5FF,

		.text_bg   = 0xFAFAFAFF,
		.text_fg   = 0x546E7AFF,
		.text_sel  = 0xCCD7DAFF,
		.text_bord = 0xCCD7DAFF,

		.red       = 0xE53935FF,
		.yellow    = 0xFFB62CFF,
		.green     = 0x91B859FF,
		.blue      = 0x6182B8FF,
		.purple    = 0x7C4DFFFF,
		.magenta   = 0xC792EAFF,
		.grey      = 0x90A4AEFF,
		.cyan      = 0x39ADB5FF
	},

	// COLORSCHEME_NIGHT_OWL_DARK
	{
		.tag_bg    = 0x0B253AFF,
		.tag_fg    = 0x7F8C98FF,
		.tag_sel   = 0x2C4A63FF,
		.tag_bord  = 0x2C4A63FF,

		.text_bg   = 0x011627FF,
		.text_fg   = 0xD6DEEBFF,
		.text_sel  = 0x1D3B53FF,
		.text_bord = 0x1D3B53FF,

		.red       = 0xEF5350FF,
		.yellow    = 0xECC48DFF,
		.green     = 0x22DA6EFF,
		.blue      = 0x82AAFFFF,
		.purple    = 0xC792EAFF,
		.magenta   = 0xFF5874FF,
		.grey      = 0x637777FF,
		.cyan      = 0x7FDBCAFF
	},

	// COLORSCHEME_AYU_DARK
	{
		.tag_bg    = 0x11151CFF,
		.tag_fg    = 0x6C7680FF,
		.tag_sel   = 0x273747FF,
		.tag_bord  = 0x273747FF,

		.text_bg   = 0x0A0E14FF,
		.text_fg   = 0xB3B1ADFF,
		.text_sel  = 0x1B2733FF,
		.text_bord = 0x1B2733FF,

		.red       = 0xF07178FF,
		.yellow    = 0xFFB454FF,
		.green     = 0xB8CC52FF,
		.blue      = 0x59C2FFFF,
		.purple    = 0xD2A6FFFF,
		.magenta   = 0xFF8F40FF,
		.grey      = 0x6C7680FF,
		.cyan      = 0x95E6CBFF
	},

	// COLORSCHEME_AYU_LIGHT
	{
		.tag_bg    = 0xF0F0F0FF,
		.tag_fg    = 0x787B80FF,
		.tag_sel   = 0xC2C2C2FF,
		.tag_bord  = 0xC2C2C2FF,

		.text_bg   = 0xFAFAFAFF,
		.text_fg   = 0x5C6166FF,
		.text_sel  = 0xD7D8D9FF,
		.text_bord = 0xD7D8D9FF,

		.red       = 0xF51818FF,
		.yellow    = 0xF2AE49FF,
		.green     = 0x86B300FF,
		.blue      = 0x399EE6FF,
		.purple    = 0xA37ACCFF,
		.magenta   = 0xE06C75FF,
		.grey      = 0x8A9199FF,
		.cyan      = 0x4CBF99FF
	},

	// COLORSCHEME_GRUVBOX_DARK
	{
		.tag_bg    = 0x3C3836FF,
		.tag_fg    = 0xA89984FF,
		.tag_sel   = 0x504945FF,
		.tag_bord  = 0x665C54FF,

		.text_bg   = 0x282828FF,
		.text_fg   = 0xEBDBB2FF,
		.text_sel  = 0x3C3836FF,
		.text_bord = 0x504945FF,

		.red       = 0xFB4934FF,
		.yellow    = 0xFABD2FFF,
		.green     = 0xB8BB26FF,
		.blue      = 0x83A598FF,
		.purple    = 0xD3869BFF,
		.magenta   = 0xD3869BFF,
		.grey      = 0x928374FF,
		.cyan      = 0x8EC07CFF
	},

	// COLORSCHEME_GRUVBOX_LIGHT
	{
		.tag_bg    = 0xD5C4A1FF,
		.tag_fg    = 0x7C6F64FF,
		.tag_sel   = 0xBDAE93FF,
		.tag_bord  = 0xA89984FF,

		.text_bg   = 0xFBF1C7FF,
		.text_fg   = 0x3C3836FF,
		.text_sel  = 0xE2CCA9FF,
		.text_bord = 0xD5C4A1FF,

		.red       = 0xCC241DFF,
		.yellow    = 0xD79921FF,
		.green     = 0x98971AFF,
		.blue      = 0x458588FF,
		.purple    = 0xB16286FF,
		.magenta   = 0xB16286FF,
		.grey      = 0x928374FF,
		.cyan      = 0x689D6AFF
	},

	// COLORSCHEME_SOLARIZED_DARK
	{
		.tag_bg    = 0x073642FF,
		.tag_fg    = 0x93A1A1FF,
		.tag_sel   = 0x586E75FF,
		.tag_bord  = 0x657B83FF,

		.text_bg   = 0x002B36FF,
		.text_fg   = 0x839496FF,
		.text_sel  = 0x073642FF,
		.text_bord = 0x586E75FF,

		.red       = 0xDC322FFF,
		.yellow    = 0xB58900FF,
		.green     = 0x859900FF,
		.blue      = 0x268BD2FF,
		.purple    = 0x6C71C4FF,
		.magenta   = 0xD33682FF,
		.grey      = 0x657B83FF,
		.cyan      = 0x2AA198FF
	},

	// COLORSCHEME_SOLARIZED_LIGHT
	{
		.tag_bg    = 0xEEE8D5FF,
		.tag_fg    = 0x657B83FF,
		.tag_sel   = 0x93A1A1FF,
		.tag_bord  = 0x93A1A1FF,

		.text_bg   = 0xFDF6E3FF,
		.text_fg   = 0x586E75FF,
		.text_sel  = 0xEEE8D5FF,
		.text_bord = 0x93A1A1FF,

		.red       = 0xDC322FFF,
		.yellow    = 0xB58900FF,
		.green     = 0x859900FF,
		.blue      = 0x268BD2FF,
		.purple    = 0x6C71C4FF,
		.magenta   = 0xD33682FF,
		.grey      = 0x93A1A1FF,
		.cyan      = 0x2AA198FF
	}
};