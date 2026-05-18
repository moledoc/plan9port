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
#include "keywords.h"

Image 	*syhlcols[SYHL_NCOL];

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

// NOTE: calculating background color is quite expensive
Image*
bgmatch(Point p)
{
    uchar px[4];
    uchar back[4];
    uchar high[4];

    /* read screen pixel */
    unloadimage(screen, Rect(p.x, p.y, p.x+1, p.y+1), px, 4);

    /* read BACK color pixel */
    unloadimage(textcols[BACK], Rect(0,0,1,1), back, 4);

    /* read HIGH color pixel */
    unloadimage(textcols[HIGH], Rect(0,0,1,1), high, 4);

    /* compare against BACK */
    if(px[0]==back[0] && px[1]==back[1] && px[2]==back[2])
        return textcols[BACK];

    /* compare against HIGH */
    if(px[0]==high[0] && px[1]==high[1] && px[2]==high[2])
        return textcols[HIGH];

    return textcols[BACK];
}

void _bsyhl(Frame *f, Point pt, Frbox *b, uint p0, uint p1, int extension, enum SYHL_ACTION action) {

	static char offset_buf[1024] = {0};
	static char buf[128] = {0};
	int buf_len = 0;
	int offset = 0;
	int offset_s = offset;
	int should_draw = 0;

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
			}

			switch (extension) {
				case EXT_C:
					if (in_word_set_c(buf, buf_len)) {
						text = syhlcols[SYHL_KEYWORD];
						should_draw = 1;
					} else if (action == SYHL_ACTION_TYPING) {
						lev_dist_1((char **)keywords_c, sizeof(keywords_c)/sizeof(keywords_c[0]), buf, &text, &should_draw);
					}
					break;
				case EXT_GO:
					if (in_word_set_go(buf, buf_len)) {
						text = syhlcols[SYHL_KEYWORD];
						should_draw = 1;
					} else if (action == SYHL_ACTION_TYPING) {
						lev_dist_1((char **)keywords_go, sizeof(keywords_go)/sizeof(keywords_go[0]), buf, &text, &should_draw);
					}
					break;
				case EXT_PYTHON:
					if (in_word_set_python(buf, buf_len)) {
						text = syhlcols[SYHL_KEYWORD];
						should_draw = 1;
					} else if (action == SYHL_ACTION_TYPING) {
						lev_dist_1((char **)keywords_python, sizeof(keywords_python)/sizeof(keywords_python[0]), buf, &text, &should_draw);
					}
					break;
				case EXT_JAVA:
					if (in_word_set_java(buf, buf_len)) {
						text = syhlcols[SYHL_KEYWORD];
						should_draw = 1;
					} else if (action == SYHL_ACTION_TYPING) {
						lev_dist_1((char **)keywords_java, sizeof(keywords_java)/sizeof(keywords_java[0]), buf, &text, &should_draw);
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

		Point p =  Pt(pt.x+bufwid_offset, pt.y);

		// fix boarder

		// NOTE: expensive, but 100% correct
		Image *back = bgmatch(p);

		// NOTE: simplified: fast, but not 100% correct - when selection, then all lines that have highlight will have the boarder fixed, regardless if it's actually in the selection or not
		// Image *back = action == SYHL_ACTION_SELECTING && p0 != p1 ? textcols[HIGH] : textcols[BACK];

		// MAYBE: use `border` from ../../libdraw/border.c instead (but it seems to do the same thing essentially, but for rect, so might not be exactly suitable)
		stringn(screen, addpt(p, Pt(-1, 0)), back, ZP, f->font, buf, buf_len);
		stringn(screen, addpt(p, Pt( 1, 0)), back, ZP, f->font, buf, buf_len);
		stringn(screen, addpt(p, Pt( 0,-1)), back, ZP, f->font, buf, buf_len);
		stringn(screen, addpt(p, Pt( 0, 1)), back, ZP, f->font, buf, buf_len);

		// draw inside
		stringn(f->b, p, text, ZP, f->font, buf, buf_len);
	}
}


void tsyhl(Text *t, uint p0, uint p1, enum SYHL_ACTION action) {
	if (t->what != Body) {
		return;
	}

	Frbox *b;
	int nb;

	Point pt = frptofchar(&t->fr, 0); // NOTE: get the starting Point of the frame
	for(nb=0,b=t->fr.box; nb<t->fr.nbox; nb++, b++){
		_frcklinewrap(&t->fr, &pt, b);
		if(!t->fr.noredraw && b->nrune >= 0) {
			uint lp0 = frcharofpt(&t->fr, pt);
			uint lp1 = frcharofpt(&t->fr, (Point){.x=pt.x+b->wid, .y=pt.y});
			if (p1 < lp0) break;
			if (!( // if not following, then skip line
				lp0 <= p0 && p0 <= lp1 || // NOTE: drawing starts on this line
				lp0 <= p1 && p1 <= lp1 || // NOTE: drawing ends on this line
				p0 <= lp0 && lp1 <= p1 // NOTE: full line drawn
			)) {
				goto Continue;
			}
			_bsyhl(&t->fr, pt, b, p0, p1, t->extension, action);
		}
		Continue:
		pt.x += b->wid;
	}
}
