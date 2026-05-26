#ifndef TSYHL_H
#define TSYHL_H

enum	/* Text.extension */
{
	EXT_NONE,
	EXT_C,
	EXT_GO,
	EXT_PYTHON,
	EXT_JAVA,
	EXT_SQL,
	EXT_COUNT
};

enum { /* syntax_highlighting tokens */
	SYHL_CODETAG,
	SYHL_KEYWORD,
	SYHL_NUMBER,
	SYHL_QUOTE,
	SYHL_COMMENT,
	SYHL_ESCAPE,
	SYHL_PAREN,
	SYHL_NCOL
};

enum SYHL_ACTION { /* syhl action */
	SYHL_ACTION_DEFAULT,
	SYHL_ACTION_TYPING,
	SYHL_ACTION_SELECTING,
	SYHL_ACTION_COUNT
};

extern Image		*syhlcols[SYHL_NCOL];

void tsyhl(Text *, uint, uint, enum SYHL_ACTION);

#endif // TSYHL_H