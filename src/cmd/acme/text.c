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
#include "keywords.h"
#include <stdio.h> // REMOVEME:
#include <time.h> // REMOVEME:

Image	*tagcols[NCOL];
Image	*textcols[NCOL];
static Rune Ldot[] = { '.', 0 };

enum{
	TABDIR = 3	/* width of tabs in directory windows */
};

Image 	*syhlcols[SYHL_NCOL];
int syntax_highlight_enabled = 1;

int levenshtein(const char *s1, const char *s2) {
    int len1 = strlen(s1);
    int len2 = strlen(s2);

    // allocate DP table
    int **dp = (int **)malloc((len1 + 1) * sizeof(int *));
    for (int i = 0; i <= len1; i++) {
        dp[i] = (int *)malloc((len2 + 1) * sizeof(int));
    }

    // base cases
    for (int i = 0; i <= len1; i++) dp[i][0] = i;
    for (int j = 0; j <= len2; j++) dp[0][j] = j;

    // fill table
    for (int i = 1; i <= len1; i++) {
        for (int j = 1; j <= len2; j++) {
            int cost = (s1[i - 1] == s2[j - 1]) ? 0 : 1;

            dp[i][j] = min(
                dp[i - 1][j] + 1,      // deletion
                dp[i][j - 1] + 1      // insertion
            );
            dp[i][j] = min(
                dp[i][j],
                dp[i - 1][j - 1] + cost // substitution
            );
        }
    }

    int result = dp[len1][len2];

    // free memory
    for (int i = 0; i <= len1; i++) {
        free(dp[i]);
    }
    free(dp);

    return result;
}

void lev_dist_1(char **kws, int kws_len, char *buf, Image **text, int *should_draw) {
	if (kws == NULL || kws_len == 0 || text == NULL || should_draw == NULL) {
		return;
	}
	for (int ii=0; ii<kws_len; ii++){
		int lev = levenshtein(kws[ii], buf);
		if (lev == 1) {
			*text = textcols[TEXT];
			*should_draw = 1;
			break;
		}
	}
}

Token *lex_line(Frame *f, Point pt, char* line, int line_len, int extension) {

	Token *head = NULL;
	Token *tail = NULL;

	static char offset_buf[1024] = {0};
	static char buf[128] = {0};
	int buf_len = 0;
	int offset = 0;
	int offset_s = offset;
	int should_draw = 0;

	for (char *ptr = line; offset < line_len && *ptr != '\0'; ptr++, offset++) {

		memset(offset_buf, 0, offset);
		memset(buf, 0, sizeof(buf));

		should_draw = 0;
		offset_s = offset;
		Image *text = NULL;
		enum TokenType typ = SYHL_NORMAL;

		if ('a' <= *ptr && *ptr <= 'z' || 'A' <= *ptr && *ptr <= 'Z' || *ptr == '_') {
			offset_s = offset;
			offset++;
			ptr++;
			for (; offset < line_len && *ptr != '\0' && 
				(('a' <= *ptr && *ptr <= 'z') ||
					('A' <= *ptr && *ptr <= 'Z') || 
					('0' <= *ptr && *ptr <= '9') || 
					*ptr == '_' || *ptr == '-'); ptr++, offset++) {}

			buf_len = offset-offset_s;
			memcpy(buf, line+offset_s, buf_len);

			if (in_word_set_codetags(buf, buf_len)) {
				text = syhlcols[SYHL_CODETAG];
				typ = SYHL_CODETAG;
				should_draw = 1;
			}

			switch (extension) {
				case EXT_C:
					if (in_word_set_c(buf, buf_len)) {
						text = syhlcols[SYHL_KEYWORD];
						typ = SYHL_KEYWORD;
						should_draw = 1;
					}
					break;
				case EXT_GO:
					if (in_word_set_go(buf, buf_len)) {
						text = syhlcols[SYHL_KEYWORD];
						typ = SYHL_KEYWORD;
						should_draw = 1;
					}
					break;
				case EXT_PYTHON:
					if (in_word_set_python(buf, buf_len)) {
						text = syhlcols[SYHL_KEYWORD];
						typ = SYHL_KEYWORD;
						should_draw = 1;
					}
					break;
				case EXT_JAVA:
					if (in_word_set_java(buf, buf_len)) {
						text = syhlcols[SYHL_KEYWORD];
						typ = SYHL_KEYWORD;
						should_draw = 1;
					}
					break;					
			}

			// NOTE: we passed end; step back
			offset--; ptr--;

		} else if ('0' <= *ptr && *ptr <= '9') {
			offset_s = offset;
			offset++;
			ptr++;
			for (; offset < line_len && *ptr != '\0' && 
				('0' <= *ptr && *ptr <= '9' || 
					*ptr == '.' ||
					// NOTE: include a-zA-Z, so that invalid nr will be filtered out; eg 0x7 - valid, 9l is not
					('a' <= *ptr && *ptr <= 'z') ||
					('A' <= *ptr && *ptr <= 'Z')); ptr++, offset++) {}

			buf_len = offset-offset_s;
			memcpy(buf, line+offset_s, buf_len);

			char *end;
			strtold(buf, &end);
			if (buf != end && *end == '\0') {
				should_draw = 1;
				text = syhlcols[SYHL_NUMBER];
				typ = SYHL_NUMBER;
			}

			// NOTE: we passed end; step back
			offset--; ptr--;
		} else if (*ptr == '"' || *ptr == '\'') {
			offset_s = offset;
			should_draw = 1;
			buf_len = 1;
			buf[0] = *ptr;
			text = syhlcols[SYHL_QUOTE];
			typ = SYHL_QUOTE;
		} else if (*ptr == '\\') {
			offset_s = offset;
			buf_len = 1;
			buf[0] = *ptr;
			if (offset+1 < line_len) {
				buf[1] = *(ptr+1);
				buf_len += 1;
				should_draw = 1;
			}
			text = syhlcols[SYHL_ESCAPE];
			typ = SYHL_ESCAPE;
			// NOTE: step over escape end

			offset++; ptr++;
		} else if (*ptr == '(' || *ptr == ')' || 
					*ptr == '[' || *ptr == ']' || 
					*ptr == '{' || *ptr == '}') {
			offset_s = offset;
			should_draw = 1;
			buf[0] = *ptr;
			buf_len = 1;
			text = syhlcols[SYHL_PAREN];
			typ = SYHL_PAREN;
		} else if ((*ptr == '/' && (offset+1 < line_len && *(ptr+1) == '/' || *(ptr+1) == '*') || (offset+1 < line_len && *ptr == '*' && *(ptr+1) == '/')) && (extension == EXT_C || extension == EXT_GO || extension == EXT_JAVA)) {
			offset_s = offset;
			buf_len = 1;
			buf[0] = *ptr;
			if (offset+1 < line_len) {
				buf[1] = *(ptr+1);
				buf_len += 1;
				should_draw = 1;
			}
			text = syhlcols[SYHL_COMMENT];
			typ = SYHL_COMMENT;
			// NOTE: step over comment end
			offset++; ptr++;
		} else if (extension == EXT_PYTHON && *ptr == '#') {
			offset_s = offset;
			buf_len = 1;
			buf[0] = *ptr;
			should_draw = 1;
			text = syhlcols[SYHL_COMMENT];
			typ = SYHL_COMMENT;
			// NOTE: step over comment end
			offset++; ptr++;
		}

		if (!should_draw || text == NULL) {
			continue;
		}

		memcpy(offset_buf, line, offset_s);
		int bufwid_offset = stringnwidth(f->font, offset_buf, offset_s);
		int bufwid_buf = stringnwidth(f->font, buf, buf_len);

		ulong p0 = frcharofpt(f, (Point){.x=pt.x+bufwid_offset, .y=pt.y});
		ulong p1 = frcharofpt(f, (Point){.x=pt.x+bufwid_offset+bufwid_buf, .y=pt.y});

		Token *tk = calloc(1, sizeof(Token));

		tk->p0 = p0;
		tk->p1 = p1;
		tk->s = calloc(buf_len+1, sizeof(char));
		memcpy(tk->s, buf, buf_len);
		tk->s_len = buf_len;
		tk->text = text;
		tk->typ = typ;

		if (head == NULL) {
			head = tk;
			tail = tk;
		} else {
			tail->next = tk;
			tail = tk;
		}
	}
	return head;	
}

void free_tokens(Token *tk) {
	while (tk != NULL) {
		Token *me = tk;
		tk = tk->next;
		if (me->s) free(me->s);
		free(me);
	}
}

void print_tokens(Token *tk) {
	while (tk != NULL) {
		printf("Token: {p0=%u, p1=%u, s=%s, typ=%d, next=%p}\n", tk->p0, tk->p1, tk->s, tk->typ, tk->next);
		tk = tk->next;
	}
}

void tokenizer(Text *t, Rune *r, uint p0, uint p1) {
	clock_t begin = clock();

	if (t->what != Body || !syntax_highlight_enabled || t->fr.nbox == 0) {
		frinsert(&t->fr, r, r+(p1-p0), p0);
		return;
	}


	Frbox *b;
	int nb;
	Token *tokens = NULL;
	Token *tail = NULL;

	Point pt = frptofchar(&t->fr, 0); // NOTE: get the starting Point of the frame
	for(nb=0,b=t->fr.box; nb<t->fr.nbox; nb++, b++){
		_frcklinewrap(&t->fr, &pt, b);
		if(!t->fr.noredraw && b->nrune >= 0) {
			uint pp0 = frcharofpt(&t->fr, pt);
			uint pp1 = frcharofpt(&t->fr, (Point){.x=pt.x+b->wid, .y=pt.y});
			if (!( // if not following, then skip line
				pp0 <= p0 && p0 <= pp1 || // drawing starts on this line
				pp0 <= p1 && p1 <= pp1 || // drawing ends on this line
				p0 <= pp0 && pp1 <= p1 // full line drawn
			)) {
				goto Continue;
			}
			Token *tk = lex_line(&t->fr, pt, (char*)b->ptr, b->nrune, t->extension);
			if (tk == NULL) goto Continue;
			if (tokens == NULL) {
				tokens = tk;
				tail = tk;
			} else {
				tail->next = tk;
				while (tk->next != NULL) {
					tk = tk->next;
				}
				tail = tk;
			}
		}
		Continue:
		pt.x += b->wid;
	}


	if (tokens == NULL) {	
		frinsert(&t->fr, r, r+(p1-p0), p0);
		goto CleanTokens;
	}

	Token *cur_token = tokens;
	uint pp = p0;
	while (cur_token != NULL) {
		int diff = cur_token->p0 - pp;
		printf("HERE: %u %u %u %d %u %u %u\n", p0, p1, pp, diff, pp-p0, pp-p0+diff, cur_token->p0);
		if (diff < 0) {
			break;
		} else if (diff == 0 || diff != 0 && pp > p1) {
			Point pptt = frptofchar(&t->fr, pp);
			stringnbg(t->fr.b, pptt, cur_token->text, ZP, t->fr.font, cur_token->s, cur_token->s_len, textcols[BACK], ZP);
			pp += cur_token->s_len;
			cur_token = cur_token->next;
		} else if (pp < p1) {
			frinsert(&t->fr, r+(pp-p0),r+(pp-p0)+diff, pp);
			pp += diff;
		}
	}
	if (pp < p1) {
		frinsert(&t->fr, r+(pp-p0),r+p1, pp);	
	}

	CleanTokens:
	print_tokens(tokens);
	free_tokens(tokens);



			clock_t end = clock();
			double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
			printf("tokenizer spent1: %f sec\n", time_spent);
}

// FIXME: moving with arrow keys doesn't properly redraw tick/cursor. Backspace to prev line also doesn't redraw the cursor.
// NOTE: levensthein distance check is expensive - do only when typing, i.e. inserting/deleting characters.
// KNOWN: the problem of not clearing syhl is also present for numbers and escape - that's because we don't redraw the chars after insertion/deletion. To do that, we'd need to redraw every char/word essentially which is bit too expensive. So this is left as known issue for now.
// KNOWN: execute `Edit =` twice - on the second time, the first line will be unselected, but no syhl on col number happens.

void _frsyhl(Frame *f, Point pt, Frbox *b, int extension, enum SYHL_ACTION action, uint start_sel, uint end_sel) {

	static char offset_buf[1024] = {0};
	static char buf[128] = {0};
	int buf_len = 0;
	int offset = 0;
	int offset_s = offset;
	int should_draw = 0;

	// printf("HERE: %s %d\n", (char *)b->ptr, action);

	for (char *ptr = (char *)b->ptr; offset < b->nrune && *ptr != '\0'; ptr++, offset++) {

		memset(offset_buf, 0, offset);
		memset(buf, 0, sizeof(buf));

		should_draw = 0;
		offset_s = offset;
		Image *text = NULL;

		if ('a' <= *ptr && *ptr <= 'z' || 'A' <= *ptr && *ptr <= 'Z' || *ptr == '_') {
			offset_s = offset;
			offset++;
			ptr++;
			for (; offset < b->nrune && *ptr != '\0' && 
				(('a' <= *ptr && *ptr <= 'z') ||
					('A' <= *ptr && *ptr <= 'Z') || 
					('0' <= *ptr && *ptr <= '9') || 
					*ptr == '_' || *ptr == '-'); ptr++, offset++) {}

			buf_len = offset-offset_s;
			memcpy(buf, (char *)b->ptr+offset_s, buf_len);

			if (in_word_set_codetags(buf, buf_len)) {
				text = syhlcols[SYHL_CODETAG];
				should_draw = 1;
			} else if (action == SYHL_ACTION_TYPING) {
				lev_dist_1((char **)keywords_codetags, sizeof(keywords_codetags)/sizeof(keywords_codetags[0]), buf, &text, &should_draw);
				for (int ii=0; 0 && ii<keywords_codetags_count; ii++){
					int lev = levenshtein(keywords_codetags[ii], buf);
					if (lev == 1) {
						text = textcols[TEXT];
						should_draw = 1;
						break;
					}
				}
			}

			switch (extension) {
				case EXT_C:
					if (in_word_set_c(buf, buf_len)) {
						text = syhlcols[SYHL_KEYWORD];
						should_draw = 1;
					} else if (action == SYHL_ACTION_TYPING) {
						lev_dist_1((char **)keywords_c, sizeof(keywords_c)/sizeof(keywords_c[0]), buf, &text, &should_draw);
						for (int ii=0; 0 && ii<keywords_c_count; ii++){
							int lev = levenshtein(keywords_c[ii], buf);
							if (lev == 1) {
								text = textcols[TEXT];
								should_draw = 1;
								break;
							}
						}
					}
					break;
				case EXT_GO:
					if (in_word_set_go(buf, buf_len)) {
						text = syhlcols[SYHL_KEYWORD];
						should_draw = 1;
					} else if (action == SYHL_ACTION_TYPING) {
						lev_dist_1((char **)keywords_go, sizeof(keywords_go)/sizeof(keywords_go[0]), buf, &text, &should_draw);
						for (int ii=0; 0 && ii<keywords_go_count; ii++){
							int lev = levenshtein(keywords_go[ii], buf);
							if (lev == 1) {
								text = textcols[TEXT];
								should_draw = 1;
								break;
							}
						}
					}
					break;
				case EXT_PYTHON:
					if (in_word_set_python(buf, buf_len)) {
						text = syhlcols[SYHL_KEYWORD];
						should_draw = 1;
					} else if (action == SYHL_ACTION_TYPING) {
						lev_dist_1((char **)keywords_python, sizeof(keywords_python)/sizeof(keywords_python[0]), buf, &text, &should_draw);
						for (int ii=0; 0 && ii<keywords_python_count; ii++){
							int lev = levenshtein(keywords_python[ii], buf);
							if (lev == 1) {
								text = textcols[TEXT];
								should_draw = 1;
								break;
							}
						}
					}
					break;
				case EXT_JAVA:
					if (in_word_set_java(buf, buf_len)) {
						text = syhlcols[SYHL_KEYWORD];
						should_draw = 1;
					} else if (action == SYHL_ACTION_TYPING) {
						lev_dist_1((char **)keywords_java, sizeof(keywords_java)/sizeof(keywords_java[0]), buf, &text, &should_draw);
						for (int ii=0; 0 && ii<keywords_java_count; ii++){
							int lev = levenshtein(keywords_java[ii], buf);
							if (lev == 1) {
								text = textcols[TEXT];
								should_draw = 1;
								break;
							}
						}
					}
					break;					
			}

			// NOTE: we passed end; step back
			offset--; ptr--;

		} else if ('0' <= *ptr && *ptr <= '9') {
			offset_s = offset;
			offset++;
			ptr++;
			for (; offset < b->nrune && *ptr != '\0' && 
				('0' <= *ptr && *ptr <= '9' || 
					*ptr == '.' ||
					// NOTE: include a-zA-Z, so that invalid nr will be filtered out; eg 0x7 - valid, 9l is not
					('a' <= *ptr && *ptr <= 'z') ||
					('A' <= *ptr && *ptr <= 'Z')); ptr++, offset++) {}

			buf_len = offset-offset_s;
			memcpy(buf, (char *)b->ptr+offset_s, buf_len);

			char *end;
			strtold(buf, &end);
			if (buf != end && *end == '\0') {
				should_draw = 1;
				text = syhlcols[SYHL_NUMBER];
			}

			// NOTE: we passed end; step back
			offset--; ptr--;
		} else if (*ptr == '"' || *ptr == '\'') {
			offset_s = offset;
			should_draw = 1;
			buf_len = 1;
			buf[0] = *ptr;
			text = syhlcols[SYHL_QUOTE];
		} else if (*ptr == '\\') {
			offset_s = offset;
			buf_len = 1;
			buf[0] = *ptr;
			if (offset+1 < b->nrune) {
				buf[1] = *(ptr+1);
				buf_len += 1;
				should_draw = 1;
			}
			text = syhlcols[SYHL_ESCAPE];
			// NOTE: step over escape end

			offset++; ptr++;
		} else if (*ptr == '(' || *ptr == ')' || 
					*ptr == '[' || *ptr == ']' || 
					*ptr == '{' || *ptr == '}') {
			offset_s = offset;
			should_draw = 1;
			buf[0] = *ptr;
			buf_len = 1;
			text = syhlcols[SYHL_PAREN];
		} else if ((*ptr == '/' && (offset+1 < b->nrune && *(ptr+1) == '/' || *(ptr+1) == '*') || (offset+1 < b->nrune && *ptr == '*' && *(ptr+1) == '/')) && (extension == EXT_C || extension == EXT_GO || extension == EXT_JAVA)) {
			offset_s = offset;
			buf_len = 1;
			buf[0] = *ptr;
			if (offset+1 < b->nrune) {
				buf[1] = *(ptr+1);
				buf_len += 1;
				should_draw = 1;
			}
			text = syhlcols[SYHL_COMMENT];
			// NOTE: step over comment end
			offset++; ptr++;
		} else if (extension == EXT_PYTHON && *ptr == '#') {
			offset_s = offset;
			buf_len = 1;
			buf[0] = *ptr;
			should_draw = 1;
			text = syhlcols[SYHL_COMMENT];
			// NOTE: step over comment end
			offset++; ptr++;
		}

		if (!should_draw || text == NULL) {
			continue;
		}


		memcpy(offset_buf, (char *)b->ptr, offset_s);
		int bufwid_offset = stringnwidth(f->font, offset_buf, offset_s);
		int bufwid_buf = stringnwidth(f->font, buf, buf_len);

		// stringn(f->b, (Point){.x=pt.x+bufwid_offset, .y=pt.y}, syhlcols[SYHL_CLEAN_FG], ZP, f->font, buf, buf_len);
		stringn(f->b, (Point){.x=pt.x+bufwid_offset, .y=pt.y}, text, ZP, f->font, buf, buf_len);
		continue;

		ulong p0 = frcharofpt(f, (Point){.x=pt.x+bufwid_offset, .y=pt.y});
		ulong p1 = frcharofpt(f, (Point){.x=pt.x+bufwid_offset+bufwid_buf, .y=pt.y});

// printf("---- f->p0=%lu f->p1=%lu vs p0=%lu p1=%lu vs f->p0=%u f->p1=%u action=%d buf=%s\n", f->p0, f->p1, p0, p1, f->p0, f->p1, action, buf);
		if (action == SYHL_ACTION_SELECTING && (start_sel <= p0 && p1 <= end_sel || f->p0 <= p0 && p1 <= f->p1)) { // everything in selection
			stringnbg(f->b, (Point){.x=pt.x+bufwid_offset, .y=pt.y}, text, ZP, f->font, buf, buf_len, textcols[HIGH], ZP);
			continue;	
		} else if (action == SYHL_ACTION_SELECTING && (start_sel <= p0 && p0 <= end_sel || start_sel <= p1 && p1 <= end_sel) && start_sel != end_sel && f->p0 != f->p1) { // partial selection

			// NOTE: inspiration from selrestore
			/* they now are known to overlap */
			/* before selection */
			int diff_before = 0;
			int diff_after = 0;
			if(p0 < start_sel && start_sel <= p1 && p1 <= end_sel){
				diff_before = start_sel-p0;
				stringnbg(f->b, (Point){.x=pt.x+bufwid_offset, .y=pt.y}, text, ZP, f->font, buf, diff_before, textcols[BACK], ZP);
			}
			/* after selection */
			if(end_sel < p1 && start_sel <= p0 && p0 <= end_sel){
				diff_after = p1-end_sel;
				int bufwid_until_after = stringnwidth(f->font, buf, buf_len-diff_after);
				stringnbg(f->b, (Point){.x=pt.x+bufwid_offset+bufwid_until_after, .y=pt.y}, text, ZP, f->font, buf+(buf_len-diff_after), diff_after, textcols[BACK], ZP);
			}
			/* inside selection */
			int bufwid_until_before = stringnwidth(f->font, buf, diff_before);
			stringnbg(f->b, (Point){.x=pt.x+bufwid_offset+bufwid_until_before, .y=pt.y}, text, ZP, f->font, buf+diff_before, buf_len-(diff_before+diff_after), textcols[HIGH], ZP);
		} else if (
			action == SYHL_ACTION_DRAW_FRAME && (f->p0 == f->p1 || f->p0 != f->p1 && (p0-1 > f->p1 || f->p0 > p1+1)) ||
			action == SYHL_ACTION_TYPING ||
			action == SYHL_ACTION_CLEAR_SELECTION && f->p0 != f->p1
		) { // not in selection
		stringnbg(f->b, (Point){.x=pt.x+bufwid_offset, .y=pt.y}, text, ZP, f->font, buf, buf_len, textcols[BACK], ZP);
		}
	}
}

void tsyhl(Text *t, enum SYHL_ACTION action, uint start_draw, uint end_draw) {
	clock_t begin = clock();

	if (t->what != Body || !syntax_highlight_enabled) {
		return;
	}

	Frbox *b;
	int nb;

	uint start_sel = t->fr.p0;
	uint end_sel = t->fr.p1;

	Point pt = frptofchar(&t->fr, 0); // NOTE: get the starting Point of the frame
	for(nb=0,b=t->fr.box; nb<t->fr.nbox; nb++, b++){
		_frcklinewrap(&t->fr, &pt, b);
		if(!t->fr.noredraw && b->nrune >= 0) {
			uint p0 = frcharofpt(&t->fr, pt);
			uint p1 = frcharofpt(&t->fr, (Point){.x=pt.x+b->wid, .y=pt.y});
			if (!( // if not following, then skip line
				p0 <= start_draw && start_draw <= p1 || // drawing starts on this line
				p0 <= end_draw && end_draw <= p1 || // drawing ends on this line
				start_draw <= p0 && p1 <= end_draw // full line drawn
			)) {
				goto Continue;
			}
			if (action == SYHL_ACTION_SELECTING) {
				start_sel = start_draw;
				end_sel = end_draw;
			}
			_frsyhl(&t->fr, pt, b, t->extension, action, start_sel, end_sel);
		}
		Continue:
		pt.x += b->wid;
	}

			clock_t end = clock();
			double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
			// printf("_frsyhl spent1: %f sec\n", time_spent);
}



void
textinit(Text *t, File *f, Rectangle r, Reffont *rf, Image *cols[NCOL])
{
	t->file = f;
	t->all = r;
	t->scrollr = r;
	t->scrollr.max.x = r.min.x+Scrollwid;
	t->lastsr = nullrect;
	r.min.x += Scrollwid+Scrollgap;
	t->eq0 = ~0;
	t->ncache = 0;
	t->reffont = rf;
	t->tabstop = maxtab;
	memmove(t->fr.cols, cols, sizeof t->fr.cols);
	textredraw(t, r, rf->f, screen, -1);
}

void
textredraw(Text *t, Rectangle r, Font *f, Image *b, int odx)
{
	int maxt;
	Rectangle rr;

	frinit(&t->fr, r, f, b, t->fr.cols);
	rr = t->fr.r;
	rr.min.x -= Scrollwid+Scrollgap;	/* back fill to scroll bar */
	if(!t->fr.noredraw)
		draw(t->fr.b, rr, t->fr.cols[BACK], nil, ZP);
	/* use no wider than 3-space tabs in a directory */
	maxt = maxtab;
	if(t->what == Body){
		if(t->w->isdir)
			maxt = min(TABDIR, maxtab);
		else
			maxt = t->tabstop;
	}
	t->fr.maxtab = maxt*stringwidth(f, "0");
	if(t->what==Body && t->w->isdir && odx!=Dx(t->all)){
		if(t->fr.maxlines > 0){
			textreset(t);
			textcolumnate(t, t->w->dlp,  t->w->ndl);
			textshow(t, 0, 0, 1);
		}
	}else{
		textfill(t);
		textsetselect(t, t->q0, t->q1);
	}
}

int
textresize(Text *t, Rectangle r, int keepextra)
{
	int odx;

	if(Dy(r) <= 0)
		r.max.y = r.min.y;
	else if(!keepextra)
		r.max.y -= Dy(r)%t->fr.font->height;
	odx = Dx(t->all);
	t->all = r;
	t->scrollr = r;
	t->scrollr.max.x = r.min.x+Scrollwid;
	t->lastsr = nullrect;
	r.min.x += Scrollwid+Scrollgap;
	frclear(&t->fr, 0);
	textredraw(t, r, t->fr.font, t->fr.b, odx);
	if(keepextra && t->fr.r.max.y < t->all.max.y && !t->fr.noredraw){
		/* draw background in bottom fringe of window */
		r.min.x -= Scrollgap;
		r.min.y = t->fr.r.max.y;
		r.max.y = t->all.max.y;
		draw(screen, r, t->fr.cols[BACK], nil, ZP);
	}
	return t->all.max.y;
}

void
textclose(Text *t)
{
	free(t->cache);
	frclear(&t->fr, 1);
	filedeltext(t->file, t);
	t->file = nil;
	rfclose(t->reffont);
	if(argtext == t)
		argtext = nil;
	if(typetext == t)
		typetext = nil;
	if(seltext == t)
		seltext = nil;
	if(mousetext == t)
		mousetext = nil;
	if(barttext == t)
		barttext = nil;
}

int
dircmp(const void *a, const void *b)
{
	Dirlist *da, *db;
	int i, n;

	da = *(Dirlist**)a;
	db = *(Dirlist**)b;
	n = min(da->nr, db->nr);
	i = memcmp(da->r, db->r, n*sizeof(Rune));
	if(i)
		return i;
	return da->nr - db->nr;
}

void
textcolumnate(Text *t, Dirlist **dlp, int ndl)
{
	int i, j, w, colw, mint, maxt, ncol, nrow;
	Dirlist *dl;
	uint q1;
	static Rune Lnl[] = { '\n', 0 };
	static Rune Ltab[] = { '\t', 0 };

	if(t->file->ntext > 1)
		return;
	mint = stringwidth(t->fr.font, "0");
	/* go for narrower tabs if set more than 3 wide */
	t->fr.maxtab = min(maxtab, TABDIR)*mint;
	maxt = t->fr.maxtab;
	colw = 0;
	for(i=0; i<ndl; i++){
		dl = dlp[i];
		w = dl->wid;
		if(maxt-w%maxt < mint || w%maxt==0)
			w += mint;
		if(w % maxt)
			w += maxt-(w%maxt);
		if(w > colw)
			colw = w;
	}
	if(colw == 0)
		ncol = 1;
	else
		ncol = max(1, Dx(t->fr.r)/colw);
	nrow = (ndl+ncol-1)/ncol;

	q1 = 0;
	for(i=0; i<nrow; i++){
		for(j=i; j<ndl; j+=nrow){
			dl = dlp[j];
			fileinsert(t->file, q1, dl->r, dl->nr);
			q1 += dl->nr;
			if(j+nrow >= ndl)
				break;
			w = dl->wid;
			if(maxt-w%maxt < mint){
				fileinsert(t->file, q1, Ltab, 1);
				q1++;
				w += mint;
			}
			do{
				fileinsert(t->file, q1, Ltab, 1);
				q1++;
				w += maxt-(w%maxt);
			}while(w < colw);
		}
		fileinsert(t->file, q1, Lnl, 1);
		q1++;
	}
}

int
textload(Text *t, uint q0, char *file, int setqid)
{
	Rune *rp;
	Dirlist *dl, **dlp;
	int fd, i, j, n, ndl, nulls;
	uint q, q1;
	Dir *d, *dbuf;
	char *tmp;
	Text *u;
	DigestState *h;

	if(t->ncache!=0 || t->file->b.nc || t->w==nil || t!=&t->w->body)
		error("text.load");
	if(t->w->isdir && t->file->nname==0){
		warning(nil, "empty directory name");
		return -1;
	}
	if(ismtpt(file)){
		warning(nil, "will not open self mount point %s\n", file);
		return -1;
	}
	fd = open(file, OREAD);
	if(fd < 0){
		warning(nil, "can't open %s: %r\n", file);
		return -1;
	}
	d = dirfstat(fd);
	if(d == nil){
		warning(nil, "can't fstat %s: %r\n", file);
		goto Rescue;
	}
	nulls = FALSE;
	h = nil;
	if(d->qid.type & QTDIR){
		/* this is checked in get() but it's possible the file changed underfoot */
		if(t->file->ntext > 1){
			warning(nil, "%s is a directory; can't read with multiple windows on it\n", file);
			goto Rescue;
		}
		t->w->isdir = TRUE;
		t->w->filemenu = FALSE;
		if(t->file->nname > 0 && t->file->name[t->file->nname-1] != '/'){
			rp = runemalloc(t->file->nname+1);
			runemove(rp, t->file->name, t->file->nname);
			rp[t->file->nname] = '/';
			winsetname(t->w, rp, t->file->nname+1);
			free(rp);
		}
		dlp = nil;
		ndl = 0;
		dbuf = nil;
		while((n=dirread(fd, &dbuf)) > 0){
			for(i=0; i<n; i++){
				dl = emalloc(sizeof(Dirlist));
				j = strlen(dbuf[i].name);
				tmp = emalloc(j+1+1);
				memmove(tmp, dbuf[i].name, j);
				if(dbuf[i].qid.type & QTDIR)
					tmp[j++] = '/';
				tmp[j] = '\0';
				dl->r = bytetorune(tmp, &dl->nr);
				dl->wid = stringwidth(t->fr.font, tmp);
				free(tmp);
				ndl++;
				dlp = realloc(dlp, ndl*sizeof(Dirlist*));
				dlp[ndl-1] = dl;
			}
			free(dbuf);
		}
		qsort(dlp, ndl, sizeof(Dirlist*), dircmp);
		t->w->dlp = dlp;
		t->w->ndl = ndl;
		textcolumnate(t, dlp, ndl);
		q1 = t->file->b.nc;
	}else{
		t->w->isdir = FALSE;
		t->w->filemenu = TRUE;
		if(q0 == 0)
			h = sha1(nil, 0, nil, nil);
		q1 = q0 + fileload(t->file, q0, fd, &nulls, h);
	}
	if(setqid){
		if(h != nil) {
			sha1(nil, 0, t->file->sha1, h);
			h = nil;
		} else {
			memset(t->file->sha1, 0, sizeof t->file->sha1);
		}
		t->file->dev = d->dev;
		t->file->mtime = d->mtime;
		t->file->qidpath = d->qid.path;
	}
	close(fd);
	rp = fbufalloc();
	for(q=q0; q<q1; q+=n){
		n = q1-q;
		if(n > RBUFSIZE)
			n = RBUFSIZE;
		bufread(&t->file->b, q, rp, n);
		if(q < t->org)
			t->org += n;
		else if(q <= t->org+t->fr.nchars) {
			frinsert(&t->fr, rp, rp+n, q-t->org);
			tsyhl(t, SYHL_ACTION_DRAW_FRAME, 0, t->fr.nchars);
			// tokenizer(t, rp, q-t->org, q-t->org+n);
		}
		if(t->fr.lastlinefull)
			break;
	}
	fbuffree(rp);
	for(i=0; i<t->file->ntext; i++){
		u = t->file->text[i];
		if(u != t){
			if(u->org > u->file->b.nc)	/* will be 0 because of reset(), but safety first */
				u->org = 0;
			textresize(u, u->all, TRUE);
			textbacknl(u, u->org, 0);	/* go to beginning of line */
		}
		textsetselect(u, q0, q0);
	}

	if(nulls)
		warning(nil, "%s: NUL bytes elided\n", file);
	free(d);


	return q1-q0;

    Rescue:
	close(fd);
	return -1;
}

uint
textbsinsert(Text *t, uint q0, Rune *r, uint n, int tofile, int *nrp)
{
	Rune *bp, *tp, *up;
	int i, initial;

	if(t->what == Tag){	/* can't happen but safety first: mustn't backspace over file name */
    Err:
		textinsert(t, q0, r, n, tofile);
		*nrp = n;
		return q0;
	}
	bp = r;
	for(i=0; i<n; i++)
		if(*bp++ == '\b'){
			--bp;
			initial = 0;
			tp = runemalloc(n);
			runemove(tp, r, i);
			up = tp+i;
			for(; i<n; i++){
				*up = *bp++;
				if(*up == '\b')
					if(up == tp)
						initial++;
					else
						--up;
				else
					up++;
			}
			if(initial){
				if(initial > q0)
					initial = q0;
				q0 -= initial;
				textdelete(t, q0, q0+initial, tofile);
			}
			n = up-tp;
			textinsert(t, q0, tp, n, tofile);
			free(tp);
			*nrp = n;
			return q0;
		}
	goto Err;
}

void
textinsert(Text *t, uint q0, Rune *r, uint n, int tofile)
{
	int c, i;
	Text *u;

	if(tofile && t->ncache != 0)
		error("text.insert");
	if(n == 0)
		return;
	if(tofile){
		fileinsert(t->file, q0, r, n);
		if(t->what == Body){
			t->w->dirty = TRUE;
			t->w->utflastqid = -1;
		}
		if(t->file->ntext > 1)
			for(i=0; i<t->file->ntext; i++){
				u = t->file->text[i];
				if(u != t){
					u->w->dirty = TRUE;	/* always a body */
					textinsert(u, q0, r, n, FALSE);
					textsetselect(u, u->q0, u->q1);
					textscrdraw(u);
				}
			}
	}
	if(q0 < t->iq1)
		t->iq1 += n;
	if(q0 < t->q1)
		t->q1 += n;
	if(q0 < t->q0)
		t->q0 += n;
	if(q0 < t->org)
		t->org += n;
	else if(q0 <= t->org+t->fr.nchars) {
		// tokenizer(t, r, q0-t->org, q0-t->org+n);
		frinsert(&t->fr, r, r+n, q0-t->org);
		tsyhl(t, SYHL_ACTION_TYPING, q0-t->org, q0-t->org+n);
	}
	if(t->w){
		c = 'i';
		if(t->what == Body)
			c = 'I';
		if(n <= EVENTSIZE)
			winevent(t->w, "%c%d %d 0 %d %.*S\n", c, q0, q0+n, n, n, r);
		else
			winevent(t->w, "%c%d %d 0 0 \n", c, q0, q0+n, n);
	}
}

void
typecommit(Text *t)
{
	if(t->w != nil)
		wincommit(t->w, t);
	else
		textcommit(t, TRUE);
}

void
textfill(Text *t)
{
	Rune *rp;
	int i, n, m, nl;

	if(t->fr.lastlinefull || t->nofill)
		return;
	if(t->ncache > 0)
		typecommit(t);
	rp = fbufalloc();
	do{
		n = t->file->b.nc-(t->org+t->fr.nchars);
		if(n == 0)
			break;
		if(n > 2000)	/* educated guess at reasonable amount */
			n = 2000;
		bufread(&t->file->b, t->org+t->fr.nchars, rp, n);
		/*
		 * it's expensive to frinsert more than we need, so
		 * count newlines.
		 */
		nl = t->fr.maxlines-t->fr.nlines;
		m = 0;
		for(i=0; i<n; ){
			if(rp[i++] == '\n'){
				m++;
				if(m >= nl)
					break;
			}
		}
		// tokenizer(t, rp, t->fr.nchars, t->fr.nchars+i);
		frinsert(&t->fr, rp, rp+i, t->fr.nchars);
		tsyhl(t, SYHL_ACTION_DRAW_FRAME, 0, t->fr.nchars);
	}while(t->fr.lastlinefull == FALSE);
	fbuffree(rp);
}

void
textdelete(Text *t, uint q0, uint q1, int tofile)
{
	uint n, p0, p1;
	int i, c;
	Text *u;

	if(tofile && t->ncache != 0)
		error("text.delete");
	n = q1-q0;
	if(n == 0)
		return;
	if(tofile){
		filedelete(t->file, q0, q1);
		if(t->what == Body){
			t->w->dirty = TRUE;
			t->w->utflastqid = -1;
		}
		if(t->file->ntext > 1)
			for(i=0; i<t->file->ntext; i++){
				u = t->file->text[i];
				if(u != t){
					u->w->dirty = TRUE;	/* always a body */
					textdelete(u, q0, q1, FALSE);
					textsetselect(u, u->q0, u->q1);
					textscrdraw(u);
				}
			}
	}
	if(q0 < t->iq1)
		t->iq1 -= min(n, t->iq1-q0);
	if(q0 < t->q0)
		t->q0 -= min(n, t->q0-q0);
	if(q0 < t->q1)
		t->q1 -= min(n, t->q1-q0);
	if(q1 <= t->org)
		t->org -= n;
	else if(q0 < t->org+t->fr.nchars){
		p1 = q1 - t->org;
		if(p1 > t->fr.nchars)
			p1 = t->fr.nchars;
		if(q0 < t->org){
			t->org = q0;
			p0 = 0;
		}else
			p0 = q0 - t->org;
		frdelete(&t->fr, p0, p1);
		tsyhl(t, SYHL_ACTION_TYPING, p0, p1);
		textfill(t);
	}
	if(t->w){
		c = 'd';
		if(t->what == Body)
			c = 'D';
		winevent(t->w, "%c%d %d 0 0 \n", c, q0, q1);
	}
}

void
textconstrain(Text *t, uint q0, uint q1, uint *p0, uint *p1)
{
	*p0 = min(q0, t->file->b.nc);
	*p1 = min(q1, t->file->b.nc);
}

Rune
textreadc(Text *t, uint q)
{
	Rune r;

	if(t->cq0<=q && q<t->cq0+t->ncache)
		r = t->cache[q-t->cq0];
	else
		bufread(&t->file->b, q, &r, 1);
	return r;
}

int
textbswidth(Text *t, Rune c)
{
	uint q, eq;
	Rune r;
	int skipping;

	/* there is known to be at least one character to erase */
	if(c == 0x08)	/* ^H: erase character */
		return 1;
	q = t->q0;
	skipping = TRUE;
	while(q > 0){
		r = textreadc(t, q-1);
		if(r == '\n'){		/* eat at most one more character */
			if(q == t->q0)	/* eat the newline */
				--q;
			break;
		}
		if(c == 0x17){
			eq = isalnum(r);
			if(eq && skipping)	/* found one; stop skipping */
				skipping = FALSE;
			else if(!eq && !skipping)
				break;
		}
		--q;
	}
	return t->q0-q;
}

int
textfilewidth(Text *t, uint q0, int oneelement)
{
	uint q;
	Rune r;

	q = q0;
	while(q > 0){
		r = textreadc(t, q-1);
		if(r <= ' ')
			break;
		if(oneelement && r=='/')
			break;
		--q;
	}
	return q0-q;
}

Rune*
textcomplete(Text *t)
{
	int i, nstr, npath;
	uint q;
	Rune tmp[200];
	Rune *str, *path;
	Rune *rp;
	Completion *c;
	char *s, *dirs;
	Runestr dir;

	/* control-f: filename completion; works back to white space or / */
	if(t->q0<t->file->b.nc && textreadc(t, t->q0)>' ')	/* must be at end of word */
		return nil;
	nstr = textfilewidth(t, t->q0, TRUE);
	str = runemalloc(nstr);
	npath = textfilewidth(t, t->q0-nstr, FALSE);
	path = runemalloc(npath);

	c = nil;
	rp = nil;
	dirs = nil;

	q = t->q0-nstr;
	for(i=0; i<nstr; i++)
		str[i] = textreadc(t, q++);
	q = t->q0-nstr-npath;
	for(i=0; i<npath; i++)
		path[i] = textreadc(t, q++);
	/* is path rooted? if not, we need to make it relative to window path */
	if(npath>0 && path[0]=='/')
		dir = runestr(path, npath);
	else{
		dir = dirname(t, nil, 0);
		if(dir.nr + 1 + npath > nelem(tmp)){
			free(dir.r);
			goto Return;
		}
		if(dir.nr == 0){
			dir.nr = 1;
			dir.r = runestrdup(Ldot);
		}
		runemove(tmp, dir.r, dir.nr);
		tmp[dir.nr] = '/';
		runemove(tmp+dir.nr+1, path, npath);
		free(dir.r);
		dir.r = tmp;
		dir.nr += 1+npath;
		dir = cleanrname(dir);
	}

	s = smprint("%.*S", nstr, str);
	dirs = smprint("%.*S", dir.nr, dir.r);
	c = complete(dirs, s);
	free(s);
	if(c == nil){
		warning(nil, "error attempting completion: %r\n");
		goto Return;
	}

	if(!c->advance){
		warning(nil, "%.*S%s%.*S*%s\n",
			dir.nr, dir.r,
			dir.nr>0 && dir.r[dir.nr-1]!='/' ? "/" : "",
			nstr, str,
			c->nmatch ? "" : ": no matches in:");
		for(i=0; i<c->nfile; i++)
			warning(nil, " %s\n", c->filename[i]);
	}

	if(c->advance)
		rp = runesmprint("%s", c->string);
	else
		rp = nil;
  Return:
	freecompletion(c);
	free(dirs);
	free(str);
	free(path);
	return rp;
}

void
texttype(Text *t, Rune r)
{
	uint q0, q1;
	int nnb, nb, n, i;
	int nr;
	Rune *rp;
	Text *u;

	if(t->what!=Body && t->what!=Tag && r=='\n')
		return;
	if(t->what == Tag)
		t->w->tagsafe = FALSE;

	nr = 1;
	rp = &r;
	switch(r){
	case Kleft:
		typecommit(t);
		if(t->q0 > 0)
			textshow(t, t->q0-1, t->q0-1, TRUE);
		return;
	case Kright:
		typecommit(t);
		if(t->q1 < t->file->b.nc)
			textshow(t, t->q1+1, t->q1+1, TRUE);
		return;
	case Kdown:
		if(t->what == Tag)
			goto Tagdown;
		n = t->fr.maxlines/3;
		goto case_Down;
	case Kscrollonedown:
		if(t->what == Tag)
			goto Tagdown;
		n = mousescrollsize(t->fr.maxlines);
		if(n <= 0)
			n = 1;
		goto case_Down;
	case Kpgdown:
		n = 2*t->fr.maxlines/3;
	case_Down:
		q0 = t->org+frcharofpt(&t->fr, Pt(t->fr.r.min.x, t->fr.r.min.y+n*t->fr.font->height));
		textsetorigin(t, q0, TRUE);
		return;
	case Kup:
		if(t->what == Tag)
			goto Tagup;
		n = t->fr.maxlines/3;
		goto case_Up;
	case Kscrolloneup:
		if(t->what == Tag)
			goto Tagup;
		n = mousescrollsize(t->fr.maxlines);
		goto case_Up;
	case Kpgup:
		n = 2*t->fr.maxlines/3;
	case_Up:
		q0 = textbacknl(t, t->org, n);
		textsetorigin(t, q0, TRUE);
		return;
	case Khome:
		typecommit(t);
		if(t->org > t->iq1) {
			q0 = textbacknl(t, t->iq1, 1);
			textsetorigin(t, q0, TRUE);
		} else
			textshow(t, 0, 0, FALSE);
		return;
	case Kend:
		typecommit(t);
		if(t->iq1 > t->org+t->fr.nchars) {
			if(t->iq1 > t->file->b.nc) {
				// should not happen, but does. and it will crash textbacknl.
				t->iq1 = t->file->b.nc;
			}
			q0 = textbacknl(t, t->iq1, 1);
			textsetorigin(t, q0, TRUE);
		} else
			textshow(t, t->file->b.nc, t->file->b.nc, FALSE);
		return;
	case 0x01:	/* ^A: beginning of line */
		typecommit(t);
		/* go to where ^U would erase, if not already at BOL */
		nnb = 0;
		if(t->q0>0 && textreadc(t, t->q0-1)!='\n')
			nnb = textbswidth(t, 0x15);
		textshow(t, t->q0-nnb, t->q0-nnb, TRUE);
		return;
	case 0x05:	/* ^E: end of line */
		typecommit(t);
		q0 = t->q0;
		while(q0<t->file->b.nc && textreadc(t, q0)!='\n')
			q0++;
		textshow(t, q0, q0, TRUE);
		return;
	case Kcmd+'c':	/* %C: copy */
		typecommit(t);
		cut(t, t, nil, TRUE, FALSE, nil, 0);
		return;
	case Kcmd+'z':	/* %Z: undo */
	 	typecommit(t);
		undo(t, nil, nil, TRUE, 0, nil, 0);
		return;
	case Kcmd+'Z':	/* %-shift-Z: redo */
	 	typecommit(t);
		undo(t, nil, nil, FALSE, 0, nil, 0);
		return;
	case Kcmd+'.':	/* %-.: toggle syntax highlighting */
	 	syntax_highlight_enabled = (syntax_highlight_enabled+1)%2;
		textredraw(t, t->fr.r, t->fr.font, t->fr.b, Dx(t->all)); // FIXME: over-draws the scrollbar, need to tweak the rectangle or redraw scrollbar
		return;

	Tagdown:
		/* expand tag to show all text */
		if(!t->w->tagexpand){
			t->w->tagexpand = TRUE;
			winresize(t->w, t->w->r, FALSE, TRUE);
		}
		return;

	Tagup:
		/* shrink tag to single line */
		if(t->w->tagexpand){
			t->w->tagexpand = FALSE;
			t->w->taglines = 1;
			winresize(t->w, t->w->r, FALSE, TRUE);
		}
		return;
	}
	if(t->what == Body){
		seq++;
		filemark(t->file);
	}
	/* cut/paste must be done after the seq++/filemark */
	switch(r){
	case Kcmd+'x':	/* %X: cut */
		typecommit(t);
		if(t->what == Body){
			seq++;
			filemark(t->file);
		}
		cut(t, t, nil, TRUE, TRUE, nil, 0);
		textshow(t, t->q0, t->q0, 1);
		t->iq1 = t->q0;
		return;
	case Kcmd+'v':	/* %V: paste */
		typecommit(t);
		if(t->what == Body){
			seq++;
			filemark(t->file);
		}
		paste(t, t, nil, TRUE, FALSE, nil, 0);
		textshow(t, t->q0, t->q1, 1);
		t->iq1 = t->q1;
		return;
	}
	if(t->q1 > t->q0){
		if(t->ncache != 0)
			error("text.type");
		cut(t, t, nil, TRUE, TRUE, nil, 0);
		t->eq0 = ~0;
	}
	textshow(t, t->q0, t->q0, 1);
	switch(r){
	case 0x06:	/* ^F: complete */
	case Kins:
		typecommit(t);
		rp = textcomplete(t);
		if(rp == nil)
			return;
		nr = runestrlen(rp);
		break;	/* fall through to normal insertion case */
	case 0x1B: /* escape */
		if(t->eq0 != ~0) {
			if(t->eq0 <= t->q0)
				textsetselect(t, t->eq0, t->q0);
			else
				textsetselect(t, t->q0, t->eq0);
		}
		if(t->ncache > 0)
			typecommit(t);
		t->iq1 = t->q0;
		return;
	case 0x08:	/* ^H: erase character */
	case 0x15:	/* ^U: erase line */
	case 0x17:	/* ^W: erase word */
		if(t->q0 == 0)	/* nothing to erase */
			return;
		nnb = textbswidth(t, r);
		q1 = t->q0;
		q0 = q1-nnb;
		/* if selection is at beginning of window, avoid deleting invisible text */
		if(q0 < t->org){
			q0 = t->org;
			nnb = q1-q0;
		}
		if(nnb <= 0)
			return;
		for(i=0; i<t->file->ntext; i++){
			u = t->file->text[i];
			u->nofill = TRUE;
			nb = nnb;
			n = u->ncache;
			if(n > 0){
				if(q1 != u->cq0+n)
					error("text.type backspace");
				if(n > nb)
					n = nb;
				u->ncache -= n;
				textdelete(u, q1-n, q1, FALSE);
				nb -= n;
			}
			if(u->eq0==q1 || u->eq0==~0)
				u->eq0 = q0;
			if(nb && u==t)
				textdelete(u, q0, q0+nb, TRUE);
			if(u != t)
				textsetselect(u, u->q0, u->q1);
			else
				textsetselect(t, q0, q0);
			u->nofill = FALSE;
		}
		for(i=0; i<t->file->ntext; i++)
			textfill(t->file->text[i]);
		t->iq1 = t->q0;
		return;
	case '\n':
		if(t->w->autoindent){
			/* find beginning of previous line using backspace code */
			nnb = textbswidth(t, 0x15); /* ^U case */
			rp = runemalloc(nnb + 1);
			nr = 0;
			rp[nr++] = r;
			for(i=0; i<nnb; i++){
				r = textreadc(t, t->q0-nnb+i);
				if(r != ' ' && r != '\t')
					break;
				rp[nr++] = r;
			}
		}
		break; /* fall through to normal code */
	}
	/* otherwise ordinary character; just insert, typically in caches of all texts */
	for(i=0; i<t->file->ntext; i++){
		u = t->file->text[i];
		if(u->eq0 == ~0)
			u->eq0 = t->q0;
		if(u->ncache == 0)
			u->cq0 = t->q0;
		else if(t->q0 != u->cq0+u->ncache)
			error("text.type cq1");
		/*
		 * Change the tag before we add to ncache,
		 * so that if the window body is resized the
		 * commit will not find anything in ncache.
		 */
		if(u->what==Body && u->ncache == 0){
			u->needundo = TRUE;
			winsettag(t->w);
			u->needundo = FALSE;
		}
		textinsert(u, t->q0, rp, nr, FALSE);
		if(u != t)
			textsetselect(u, u->q0, u->q1);
		if(u->ncache+nr > u->ncachealloc){
			u->ncachealloc += 10 + nr;
			u->cache = runerealloc(u->cache, u->ncachealloc);
		}
		runemove(u->cache+u->ncache, rp, nr);
		u->ncache += nr;
	}
	if(rp != &r)
		free(rp);
	textsetselect(t, t->q0+nr, t->q0+nr);
	if(r=='\n' && t->w!=nil)
		wincommit(t->w, t);
	t->iq1 = t->q0;
}

void
textcommit(Text *t, int tofile)
{
	if(t->ncache == 0)
		return;
	if(tofile)
		fileinsert(t->file, t->cq0, t->cache, t->ncache);
	if(t->what == Body){
		t->w->dirty = TRUE;
		t->w->utflastqid = -1;
	}
	t->ncache = 0;
}

static	Text	*clicktext;
static	uint	clickmsec;
static	Text	*selecttext;
static	uint	selectq;

/*
 * called from frame library
 */
void
framescroll(Frame *f, int dl)
{
	if(f != &selecttext->fr)
		error("frameselect not right frame");
	textframescroll(selecttext, dl);
}

void
textframescroll(Text *t, int dl)
{
	uint q0;

	if(dl == 0){
		scrsleep(100);
		return;
	}
	if(dl < 0){
		q0 = textbacknl(t, t->org, -dl);
		if(selectq > t->org+t->fr.p0)
			textsetselect(t, t->org+t->fr.p0, selectq);
		else
			textsetselect(t, selectq, t->org+t->fr.p0);
	}else{
		if(t->org+t->fr.nchars == t->file->b.nc)
			return;
		q0 = t->org+frcharofpt(&t->fr, Pt(t->fr.r.min.x, t->fr.r.min.y+dl*t->fr.font->height));
		if(selectq > t->org+t->fr.p1)
			textsetselect(t, t->org+t->fr.p1, selectq);
		else
			textsetselect(t, selectq, t->org+t->fr.p1);
	}
	textsetorigin(t, q0, TRUE);
}

static
int
region(int a, int b)
{
	if(a < b)
		return -1;
	if(a == b)
		return 0;
	return 1;
}

// NOTE: copied from src/libframe/frselect.c to be able to call tsyhl in the loop
void
_local_frselect(Frame *f, Mousectl *mc, Text *t)	/* when called, button 1 is down */
{
	ulong p0, p1, q;
	Point mp, pt0, pt1, qt;
	int reg, b, scrled;

	mp = mc->m.xy;
	b = mc->m.buttons;

	f->modified = 0;
	frdrawsel(f, frptofchar(f, f->p0), f->p0, f->p1, 0);
	tsyhl(t, SYHL_ACTION_CLEAR_SELECTION, f->p0, f->p1);
	p0 = p1 = frcharofpt(f, mp);
	f->p0 = p0;
	f->p1 = p1;
	pt0 = frptofchar(f, p0);
	pt1 = frptofchar(f, p1);
	frdrawsel(f, pt0, p0, p1, 1);
	tsyhl(t, SYHL_ACTION_SELECTING, f->p0, f->p1);
	reg = 0;
	do{
		scrled = 0;
		if(f->scroll){
			if(mp.y < f->r.min.y){
				(*f->scroll)(f, -(f->r.min.y-mp.y)/(int)f->font->height-1);
				p0 = f->p1;
				p1 = f->p0;
				scrled = 1;
			}else if(mp.y > f->r.max.y){
				(*f->scroll)(f, (mp.y-f->r.max.y)/(int)f->font->height+1);
				p0 = f->p0;
				p1 = f->p1;
				scrled = 1;
			}
			if(scrled){
				if(reg != region(p1, p0))
					q = p0, p0 = p1, p1 = q;	/* undo the swap that will happen below */
				pt0 = frptofchar(f, p0);
				pt1 = frptofchar(f, p1);
				reg = region(p1, p0);
			}
		}
		q = frcharofpt(f, mp);
		if(p1 != q){
			if(reg != region(q, p0)){	/* crossed starting point; reset */
				if(reg > 0) {
					frdrawsel(f, pt0, p0, p1, 0);
					tsyhl(t, SYHL_ACTION_CLEAR_SELECTION, p0, p1);
				}
				else if(reg < 0) {
					frdrawsel(f, pt1, p1, p0, 0);
					tsyhl(t, SYHL_ACTION_CLEAR_SELECTION, p1, p0);
				}
				p1 = p0;
				pt1 = pt0;
				reg = region(q, p0);
				if(reg == 0) {
					frdrawsel(f, pt0, p0, p1, 1);
					tsyhl(t, SYHL_ACTION_SELECTING, p0, p1);
				}
			}
			qt = frptofchar(f, q);
			if(reg > 0){
				if(q > p1) {
					frdrawsel(f, pt1, p1, q, 1);
					tsyhl(t, SYHL_ACTION_SELECTING, p1, q);
				}
				else if(q < p1) {
					frdrawsel(f, qt, q, p1, 0);
					tsyhl(t, SYHL_ACTION_CLEAR_SELECTION, q, p1);
				}
			}else if(reg < 0){
				if(q > p1) {
					frdrawsel(f, pt1, p1, q, 0);
					tsyhl(t, SYHL_ACTION_CLEAR_SELECTION, p1, q);
				}
				else {
					frdrawsel(f, qt, q, p1, 1);
					tsyhl(t, SYHL_ACTION_SELECTING, q, p1);
				}
			}
			p1 = q;
			pt1 = qt;
		}
		f->modified = 0;
		if(p0 < p1) {
			f->p0 = p0;
			f->p1 = p1;
		}
		else {
			f->p0 = p1;
			f->p1 = p0;
		}
		if(scrled)
			(*f->scroll)(f, 0);
		// NOTE: redraw, because some incremental checks will unselect syhl. But can't only rely on this, because otherwise moving back and forth with the selection doesn't draw syhl.
		// tsyhl(t, SYHL_ACTION_CLEAR_SELECTION, 0, f->p0-1);
		// tsyhl(t, SYHL_ACTION_SELECTING, f->p0, f->p1);
		// tsyhl(t, SYHL_ACTION_CLEAR_SELECTION, f->p1+1, f->nchars);
		flushimage(f->display, 1);
		if(!scrled)
			readmouse(mc);
		mp = mc->m.xy;
	}while(mc->m.buttons == b);
}


void
textselect(Text *t)
{
	uint q0, q1;
	int b, x, y;
	int state;
	enum { None, Cut, Paste };

	selecttext = t;
	/*
	 * To have double-clicking and chording, we double-click
	 * immediately if it might make sense.
	 */
	b = mouse->buttons;
	q0 = t->q0;
	q1 = t->q1;
	selectq = t->org+frcharofpt(&t->fr, mouse->xy);
	if(clicktext==t && mouse->msec-clickmsec<500)
	if(q0==q1 && selectq==q0){
		textdoubleclick(t, &q0, &q1);
		textsetselect(t, q0, q1);
		flushimage(display, 1);
		x = mouse->xy.x;
		y = mouse->xy.y;
		/* stay here until something interesting happens */
		do
			readmouse(mousectl);
		while(mouse->buttons==b && abs(mouse->xy.x-x)<3 && abs(mouse->xy.y-y)<3);
		mouse->xy.x = x;	/* in case we're calling frselect */
		mouse->xy.y = y;
		q0 = t->q0;	/* may have changed */
		q1 = t->q1;
		selectq = q0;
	}
	if(mouse->buttons == b){
		t->fr.scroll = framescroll;
		_local_frselect(&t->fr, mousectl, t);
		/* horrible botch: while asleep, may have lost selection altogether */
		if(selectq > t->file->b.nc)
			selectq = t->org + t->fr.p0;
		t->fr.scroll = nil;
		if(selectq < t->org)
			q0 = selectq;
		else
			q0 = t->org + t->fr.p0;
		if(selectq > t->org+t->fr.nchars)
			q1 = selectq;
		else
			q1 = t->org+t->fr.p1;
	}
	if(q0 == q1){
		if(q0==t->q0 && clicktext==t && mouse->msec-clickmsec<500){
			textdoubleclick(t, &q0, &q1);
			clicktext = nil;
		}else{
			clicktext = t;
			clickmsec = mouse->msec;
		}
	}else
		clicktext = nil;
	textsetselect(t, q0, q1);
	flushimage(display, 1);
	state = None;	/* what we've done; undo when possible */
	while(mouse->buttons){
		mouse->msec = 0;
		b = mouse->buttons;
		if((b&1) && (b&6)){
			if(state==None && t->what==Body){
				seq++;
				filemark(t->w->body.file);
			}
			if(b & 2){
				if(state==Paste && t->what==Body){
					winundo(t->w, TRUE);
					textsetselect(t, q0, t->q1);
					state = None;
				}else if(state != Cut){
					cut(t, t, nil, TRUE, TRUE, nil, 0);
					state = Cut;
				}
			}else{
				if(state==Cut && t->what==Body){
					winundo(t->w, TRUE);
					textsetselect(t, q0, t->q1);
					state = None;
				}else if(state != Paste){
					paste(t, t, nil, TRUE, FALSE, nil, 0);
					state = Paste;
					tsyhl(t, SYHL_ACTION_SELECTING, q0, q1);
				}
			}
			textscrdraw(t);
			clearmouse();
		}
		flushimage(display, 1);
		while(mouse->buttons == b)
			readmouse(mousectl);
		clicktext = nil;
	}
}

void
textshow(Text *t, uint q0, uint q1, int doselect)
{
	int qe;
	int nl;
	int tsd;
	int nc;
	uint q;

	if(t->what != Body){
		if(doselect)
			textsetselect(t, q0, q1);
		return;
	}
	if(t->w!=nil && t->fr.maxlines==0)
		colgrow(t->col, t->w, 1);
	if(doselect)
		textsetselect(t, q0, q1);
	qe = t->org+t->fr.nchars;
	tsd = FALSE;	/* do we call textscrdraw? */
	nc = t->file->b.nc+t->ncache;
	if(t->org <= q0){
		if(nc==0 || q0<qe)
			tsd = TRUE;
		else if(q0==qe && qe==nc){
			if(textreadc(t, nc-1) == '\n'){
				if(t->fr.nlines<t->fr.maxlines)
					tsd = TRUE;
			}else
				tsd = TRUE;
		}
	}
	if(tsd) {
		textscrdraw(t);
	} else{
		if(t->w->nopen[QWevent] > 0)
			nl = 3*t->fr.maxlines/4;
		else
			nl = t->fr.maxlines/4;
		q = textbacknl(t, q0, nl);
		/* avoid going backwards if trying to go forwards - long lines! */
		if(!(q0>t->org && q<t->org))
			textsetorigin(t, q, TRUE);
		while(q0 > t->org+t->fr.nchars)
			textsetorigin(t, t->org+1, FALSE);
	}
}

void
selrestore(Text *t, Frame *f, Point pt0, uint p0, uint p1)
{
	if(p1<=f->p0 || p0>=f->p1){
		/* no overlap */
		frdrawsel0(f, pt0, p0, p1, f->cols[BACK], f->cols[TEXT]);
		tsyhl(t, SYHL_ACTION_CLEAR_SELECTION, p0, p1);
		return;
	}
	if(p0>=f->p0 && p1<=f->p1){
		/* entirely inside */
		frdrawsel0(f, pt0, p0, p1, f->cols[HIGH], f->cols[HTEXT]);
		tsyhl(t, SYHL_ACTION_SELECTING, p0, p1);
		return;
	}

	/* they now are known to overlap */

	/* before selection */
	if(p0 < f->p0){
		frdrawsel0(f, pt0, p0, f->p0, f->cols[BACK], f->cols[TEXT]);
		tsyhl(t, SYHL_ACTION_CLEAR_SELECTION, p0, f->p0);
		p0 = f->p0;
		pt0 = frptofchar(f, p0);
	}
	/* after selection */
	if(p1 > f->p1){
		frdrawsel0(f, frptofchar(f, f->p1), f->p1, p1, f->cols[BACK], f->cols[TEXT]);
		tsyhl(t, SYHL_ACTION_CLEAR_SELECTION, f->p1, p1);
		p1 = f->p1;
	}
	/* inside selection */
	frdrawsel0(f, pt0, p0, p1, f->cols[HIGH], f->cols[HTEXT]);
	tsyhl(t, SYHL_ACTION_SELECTING, p0, p1);
}

void
textsetselect(Text *t, uint q0, uint q1)
{
	int p0, p1, ticked;

	/* t->fr.p0 and t->fr.p1 are always right; t->q0 and t->q1 may be off */
	t->q0 = q0;
	t->q1 = q1;
	/* compute desired p0,p1 from q0,q1 */
	p0 = q0-t->org;
	p1 = q1-t->org;
	ticked = 1;
	if(p0 < 0){
		ticked = 0;
		p0 = 0;
	}
	if(p1 < 0)
		p1 = 0;
	if(p0 > t->fr.nchars)
		p0 = t->fr.nchars;
	if(p1 > t->fr.nchars){
		ticked = 0;
		p1 = t->fr.nchars;
	}
	if(p0==t->fr.p0 && p1==t->fr.p1){
		if(p0 == p1 && ticked != t->fr.ticked)
			frtick(&t->fr, frptofchar(&t->fr, p0), ticked);
		return;
	}
	if(p0 > p1)
		sysfatal("acme: textsetselect p0=%d p1=%d q0=%ud q1=%ud t->org=%d nchars=%d", p0, p1, q0, q1, (int)t->org, (int)t->fr.nchars);
	/* screen disagrees with desired selection */
	if(t->fr.p1<=p0 || p1<=t->fr.p0 || p0==p1 || t->fr.p1==t->fr.p0){
		/* no overlap or too easy to bother trying */
		frdrawsel(&t->fr, frptofchar(&t->fr, t->fr.p0), t->fr.p0, t->fr.p1, 0);
		tsyhl(t, SYHL_ACTION_CLEAR_SELECTION, t->fr.p0, t->fr.p1);
		if(p0 != p1 || ticked) {
			frdrawsel(&t->fr, frptofchar(&t->fr, p0), p0, p1, 1);
			tsyhl(t, SYHL_ACTION_SELECTING, p0, p1);
		}
		goto Return;
	}
	/* overlap; avoid unnecessary painting */
	if(p0 < t->fr.p0){
		/* extend selection backwards */
		frdrawsel(&t->fr, frptofchar(&t->fr, p0), p0, t->fr.p0, 1);
		tsyhl(t, SYHL_ACTION_SELECTING, p0, t->fr.p0);
	}else if(p0 > t->fr.p0){
		/* trim first part of selection */
		frdrawsel(&t->fr, frptofchar(&t->fr, t->fr.p0), t->fr.p0, p0, 0);
		tsyhl(t, SYHL_ACTION_CLEAR_SELECTION, t->fr.p0, p0);
	}
	if(p1 > t->fr.p1){
		/* extend selection forwards */
		frdrawsel(&t->fr, frptofchar(&t->fr, t->fr.p1), t->fr.p1, p1, 1);
		tsyhl(t, SYHL_ACTION_SELECTING, t->fr.p1, p1);
	}else if(p1 < t->fr.p1){
		/* trim last part of selection */
		frdrawsel(&t->fr, frptofchar(&t->fr, p1), p1, t->fr.p1, 0);
		tsyhl(t, SYHL_ACTION_CLEAR_SELECTION, p1, t->fr.p1);
	}

    Return:
	t->fr.p0 = p0;
	t->fr.p1 = p1;
	tsyhl(t, SYHL_ACTION_SELECTING, t->fr.p0, t->fr.p1);
}

/*
 * Release the button in less than DELAY ms and it's considered a null selection
 * if the mouse hardly moved, regardless of whether it crossed a char boundary.
 */
enum {
	DELAY = 2,
	MINMOVE = 4
};

// KNOWN: when there is selection and mousebtn2 or mousebtn3 is selected such that it overlaps with selection, then restoring the highlighted syhl is not always correct. Will fix if it turns out to occur and annoy during usage. This happens when cancelling btn2 and btn3 or when going through with btn3 execution. Again, the text under it needs to be selected for this to happen.
uint

xselect(Text *t, Frame *f, Mousectl *mc, Image *col, uint *p1p)	/* when called, button is down */
{
	uint p0, p1, q, tmp;
	ulong msec;
	Point mp, pt0, pt1, qt;
	int reg, b;

	mp = mc->m.xy;
	b = mc->m.buttons;
	msec = mc->m.msec;

	/* remove tick */
	if(f->p0 == f->p1)
		frtick(f, frptofchar(f, f->p0), 0);
	p0 = p1 = frcharofpt(f, mp);
	pt0 = frptofchar(f, p0);
	pt1 = frptofchar(f, p1);
	reg = 0;
	frtick(f, pt0, 1);
	do{
		q = frcharofpt(f, mc->m.xy);
		if(p1 != q){
			if(p0 == p1)
				frtick(f, pt0, 0);
			if(reg != region(q, p0)){	/* crossed starting point; reset */
				if(reg > 0)
					selrestore(t, f, pt0, p0, p1);
				else if(reg < 0)
					selrestore(t, f, pt1, p1, p0);
				p1 = p0;
				pt1 = pt0;
				reg = region(q, p0);
				if(reg == 0)
					frdrawsel0(f, pt0, p0, p1, col, display->white);
			}
			qt = frptofchar(f, q);
			if(reg > 0){
				if(q > p1)
					frdrawsel0(f, pt1, p1, q, col, display->white);

				else if(q < p1)
					selrestore(t, f, qt, q, p1);
			}else if(reg < 0){
				if(q > p1)
					selrestore(t, f, pt1, p1, q);
				else
					frdrawsel0(f, qt, q, p1, col, display->white);
			}
			p1 = q;
			pt1 = qt;
		}
		if(p0 == p1)
			frtick(f, pt0, 1);
		flushimage(f->display, 1);
		readmouse(mc);
	}while(mc->m.buttons == b);
	if(mc->m.msec-msec < DELAY && p0!=p1
	&& abs(mp.x-mc->m.xy.x)<MINMOVE
	&& abs(mp.y-mc->m.xy.y)<MINMOVE) {
		if(reg > 0)
			selrestore(t, f, pt0, p0, p1);
		else if(reg < 0)
			selrestore(t, f, pt1, p1, p0);
		p1 = p0;
	}
	if(p1 < p0){
		tmp = p0;
		p0 = p1;
		p1 = tmp;
	}
	pt0 = frptofchar(f, p0);
	if(p0 == p1)
		frtick(f, pt0, 0);
	selrestore(t, f, pt0, p0, p1);
	/* restore tick */
	if(f->p0 == f->p1)
		frtick(f, frptofchar(f, f->p0), 1);
	flushimage(f->display, 1);
	*p1p = p1;
	return p0;
}

int
textselect23(Text *t, uint *q0, uint *q1, Image *high, int mask)
{
	uint p0, p1;
	int buts;

	p0 = xselect(t, &t->fr, mousectl, high, &p1);
	buts = mousectl->m.buttons;
	if((buts & mask) == 0){
		*q0 = p0+t->org;
		*q1 = p1+t->org;
	}

	int once = 1;
	while(mousectl->m.buttons) {
		readmouse(mousectl);
		if (!once) {
			tsyhl(t, SYHL_ACTION_SELECTING, t->fr.p0, t->fr.p1);
		}
	}
	return buts;
}

int
textselect2(Text *t, uint *q0, uint *q1, Text **tp)
{
	int buts;

	*tp = nil;
	buts = textselect23(t, q0, q1, but2col, 4);
	if(buts & 4)
		return 0;
	if(buts & 1){	/* pick up argument */
		*tp = argtext;
		return 1;
	}
	return 1;
}

int
textselect3(Text *t, uint *q0, uint *q1)
{
	int h;

	h = (textselect23(t, q0, q1, but3col, 1|2) == 0);
	return h;
}

static Rune left1[] =  { '{', '[', '(', '<', 0xab, 0 };
static Rune right1[] = { '}', ']', ')', '>', 0xbb, 0 };
static Rune left2[] =  { '\n', 0 };
static Rune left3[] =  { '\'', '"', '`', 0 };

static
Rune *left[] = {
	left1,
	left2,
	left3,
	nil
};
static
Rune *right[] = {
	right1,
	left2,
	left3,
	nil
};

void
textdoubleclick(Text *t, uint *q0, uint *q1)
{
	int c, i;
	Rune *r, *l, *p;
	uint q;

	if(textclickhtmlmatch(t, q0, q1))
		return;

	for(i=0; left[i]!=nil; i++){
		q = *q0;
		l = left[i];
		r = right[i];
		/* try matching character to left, looking right */
		if(q == 0)
			c = '\n';
		else
			c = textreadc(t, q-1);
		p = runestrchr(l, c);
		if(p != nil){
			if(textclickmatch(t, c, r[p-l], 1, &q))
				*q1 = q-(c!='\n');
			return;
		}
		/* try matching character to right, looking left */
		if(q == t->file->b.nc)
			c = '\n';
		else
			c = textreadc(t, q);
		p = runestrchr(r, c);
		if(p != nil){
			if(textclickmatch(t, c, l[p-r], -1, &q)){
				*q1 = *q0+(*q0<t->file->b.nc && c=='\n');
				*q0 = q;
				if(c!='\n' || q!=0 || textreadc(t, 0)=='\n')
					(*q0)++;
			}
			return;
		}
	}

	/* try filling out word to right */
	while(*q1<t->file->b.nc && isalnum(textreadc(t, *q1)))
		(*q1)++;
	/* try filling out word to left */
	while(*q0>0 && isalnum(textreadc(t, *q0-1)))
		(*q0)--;
}

int
textclickmatch(Text *t, int cl, int cr, int dir, uint *q)
{
	Rune c;
	int nest;

	nest = 1;
	for(;;){
		if(dir > 0){
			if(*q == t->file->b.nc)
				break;
			c = textreadc(t, *q);
			(*q)++;
		}else{
			if(*q == 0)
				break;
			(*q)--;
			c = textreadc(t, *q);
		}
		if(c == cr){
			if(--nest==0)
				return 1;
		}else if(c == cl)
			nest++;
	}
	return cl=='\n' && nest==1;
}

// Is the text starting at location q an html tag?
// Return 1 for <a>, -1 for </a>, 0 for no tag or <a />.
// Set *q1, if non-nil, to the location after the tag.
static int
ishtmlstart(Text *t, uint q, uint *q1)
{
	int c, c1, c2;

	if(q+2 > t->file->b.nc)
		return 0;
	if(textreadc(t, q++) != '<')
		return 0;
	c = textreadc(t, q++);
	c1 = c;
	c2 = c;
	while(c != '>') {
		if(q >= t->file->b.nc)
			return 0;
		c2 = c;
		c = textreadc(t, q++);
	}
	if(q1)
		*q1 = q;
	if(c1 == '/')	// closing tag
		return -1;
	if(c2 == '/' || c2 == '!')	// open + close tag or comment
		return 0;
	return 1;
}

// Is the text ending at location q an html tag?
// Return 1 for <a>, -1 for </a>, 0 for no tag or <a />.
// Set *q0, if non-nil, to the start of the tag.
static int
ishtmlend(Text *t, uint q, uint *q0)
{
	int c, c1, c2;

	if(q < 2)
		return 0;
	if(textreadc(t, --q) != '>')
		return 0;
	c = textreadc(t, --q);
	c1 = c;
	c2 = c;
	while(c != '<') {
		if(q == 0)
			return 0;
		c1 = c;
		c = textreadc(t, --q);
	}
	if(q0)
		*q0 = q;
	if(c1 == '/')	// closing tag
		return -1;
	if(c2 == '/' || c2 == '!')	// open + close tag or comment
		return 0;
	return 1;
}

int
textclickhtmlmatch(Text *t, uint *q0, uint *q1)
{
	int depth, n;
	uint q, nq;

	q = *q0;
	// after opening tag?  scan forward for closing tag
	if(ishtmlend(t, q, nil) == 1) {
		depth = 1;
		while(q < t->file->b.nc) {
			n = ishtmlstart(t, q, &nq);
			if(n != 0) {
				depth += n;
				if(depth == 0) {
					*q1 = q;
					return 1;
				}
				q = nq;
				continue;
			}
			q++;
		}
	}

	// before closing tag?  scan backward for opening tag
	if(ishtmlstart(t, q, nil) == -1) {
		depth = -1;
		while(q > 0) {
			n = ishtmlend(t, q, &nq);
			if(n != 0) {
				depth += n;
				if(depth == 0) {
					*q0 = q;
					return 1;
				}
				q = nq;
				continue;
			}
			q--;
		}
	}

	return 0;
}

uint
textbacknl(Text *t, uint p, uint n)
{
	int i, j;

	/* look for start of this line if n==0 */
	if(n==0 && p>0 && textreadc(t, p-1)!='\n')
		n = 1;
	i = n;
	while(i-->0 && p>0){
		--p;	/* it's at a newline now; back over it */
		if(p == 0)
			break;
		/* at 128 chars, call it a line anyway */
		for(j=128; --j>0 && p>0; p--)
			if(textreadc(t, p-1)=='\n')
				break;
	}
	return p;
}

void
textsetorigin(Text *t, uint org, int exact)
{
	int i, a, fixup;
	Rune *r;
	uint n;

	if(org>0 && !exact && textreadc(t, org-1) != '\n'){
		/* org is an estimate of the char posn; find a newline */
		/* don't try harder than 256 chars */
		for(i=0; i<256 && org<t->file->b.nc; i++){
			if(textreadc(t, org) == '\n'){
				org++;
				break;
			}
			org++;
		}
	}
	a = org-t->org;
	fixup = 0;
	if(a>=0 && a<t->fr.nchars){
		frdelete(&t->fr, 0, a);
		fixup = 1;	/* frdelete can leave end of last line in wrong selection mode; it doesn't know what follows */
	}
	else if(a<0 && -a<t->fr.nchars){
		n = t->org - org;
		r = runemalloc(n);
		bufread(&t->file->b, org, r, n);
		// tokenizer(t, r, 0, n);
		frinsert(&t->fr, r, r+n, 0);
		tsyhl(t, SYHL_ACTION_DRAW_FRAME, 0, t->fr.nchars);
		free(r);
	}else
		frdelete(&t->fr, 0, t->fr.nchars);
	t->org = org;
	textfill(t);
	textscrdraw(t);
	textsetselect(t, t->q0, t->q1);
	if(fixup && t->fr.p1 > t->fr.p0) {
		frdrawsel(&t->fr, frptofchar(&t->fr, t->fr.p1-1), t->fr.p1-1, t->fr.p1, 1);
		tsyhl(t, SYHL_ACTION_SELECTING, t->fr.p0, t->fr.p1);
	}
}

void
textreset(Text *t)
{
	t->file->seq = 0;
	t->eq0 = ~0;
	/* do t->delete(0, t->nc, TRUE) without building backup stuff */
	textsetselect(t, t->org, t->org);
	frdelete(&t->fr, 0, t->fr.nchars);
	t->org = 0;
	t->q0 = 0;
	t->q1 = 0;
	filereset(t->file);
	bufreset(&t->file->b);
}