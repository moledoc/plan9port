/* C code produced by gperf version 3.0.3 */
/* Command-line: /Library/Developer/CommandLineTools/usr/bin/gperf -C -E -t -L C -N in_word_set_codetags keywords_codetags.gperf  */
/* Computed positions: -k'1,3' */

#if !((' ' == 32) && ('!' == 33) && ('"' == 34) && ('#' == 35) \
      && ('%' == 37) && ('&' == 38) && ('\'' == 39) && ('(' == 40) \
      && (')' == 41) && ('*' == 42) && ('+' == 43) && (',' == 44) \
      && ('-' == 45) && ('.' == 46) && ('/' == 47) && ('0' == 48) \
      && ('1' == 49) && ('2' == 50) && ('3' == 51) && ('4' == 52) \
      && ('5' == 53) && ('6' == 54) && ('7' == 55) && ('8' == 56) \
      && ('9' == 57) && (':' == 58) && (';' == 59) && ('<' == 60) \
      && ('=' == 61) && ('>' == 62) && ('?' == 63) && ('A' == 65) \
      && ('B' == 66) && ('C' == 67) && ('D' == 68) && ('E' == 69) \
      && ('F' == 70) && ('G' == 71) && ('H' == 72) && ('I' == 73) \
      && ('J' == 74) && ('K' == 75) && ('L' == 76) && ('M' == 77) \
      && ('N' == 78) && ('O' == 79) && ('P' == 80) && ('Q' == 81) \
      && ('R' == 82) && ('S' == 83) && ('T' == 84) && ('U' == 85) \
      && ('V' == 86) && ('W' == 87) && ('X' == 88) && ('Y' == 89) \
      && ('Z' == 90) && ('[' == 91) && ('\\' == 92) && (']' == 93) \
      && ('^' == 94) && ('_' == 95) && ('a' == 97) && ('b' == 98) \
      && ('c' == 99) && ('d' == 100) && ('e' == 101) && ('f' == 102) \
      && ('g' == 103) && ('h' == 104) && ('i' == 105) && ('j' == 106) \
      && ('k' == 107) && ('l' == 108) && ('m' == 109) && ('n' == 110) \
      && ('o' == 111) && ('p' == 112) && ('q' == 113) && ('r' == 114) \
      && ('s' == 115) && ('t' == 116) && ('u' == 117) && ('v' == 118) \
      && ('w' == 119) && ('x' == 120) && ('y' == 121) && ('z' == 122) \
      && ('{' == 123) && ('|' == 124) && ('}' == 125) && ('~' == 126))
/* The character set is not based on ISO-646.  */
error "gperf generated tables don't work with this execution character set. Please report a bug to <bug-gnu-gperf@gnu.org>."
#endif

#line 1 "keywords_codetags.gperf"

#include <string.h>
#line 5 "keywords_codetags.gperf"
# generate c code with gperf:
# gperf -C -E -t -L C -N in_word_set_codetags keywords_codetags.gperf > keywords_codetags_hash.c

struct keyword_codetags { const char *name; };
/* maximum key range = 94, duplicates = 0 */

#ifdef __GNUC__
__inline
#else
#ifdef __cplusplus
inline
#endif
#endif
static unsigned int
hash (str, len)
     register const char *str;
     register unsigned int len;
{
  static const unsigned char asso_values[] =
    {
      98, 98, 98, 98, 98, 98, 98, 98, 98, 98,
      98, 98, 98, 98, 98, 98, 98, 98, 98, 98,
      98, 98, 98, 98, 98, 98, 98, 98, 98, 98,
      98, 98, 98, 98, 98, 98, 98, 98, 98, 98,
      98, 98, 98, 98, 98, 98,  0, 98, 98, 98,
      98, 98, 98, 98, 98, 98, 98, 98, 98, 98,
      98, 98, 98, 98, 98,  0, 55, 30, 10,  5,
      35, 24, 26,  0, 40, 98, 40, 60, 30, 35,
       5,  5,  0, 20,  0, 20,  0, 35, 55, 15,
      50, 98, 98, 98, 98, 98, 98, 98, 98, 98,
      98, 98, 98, 98, 98, 98, 98, 98, 98, 98,
      98, 98, 98, 98, 98, 98, 98, 98, 98, 98,
      98, 98, 98, 98, 98, 98, 98, 98, 98, 98,
      98, 98, 98, 98, 98, 98, 98, 98, 98, 98,
      98, 98, 98, 98, 98, 98, 98, 98, 98, 98,
      98, 98, 98, 98, 98, 98, 98, 98, 98, 98,
      98, 98, 98, 98, 98, 98, 98, 98, 98, 98,
      98, 98, 98, 98, 98, 98, 98, 98, 98, 98,
      98, 98, 98, 98, 98, 98, 98, 98, 98, 98,
      98, 98, 98, 98, 98, 98, 98, 98, 98, 98,
      98, 98, 98, 98, 98, 98, 98, 98, 98, 98,
      98, 98, 98, 98, 98, 98, 98, 98, 98, 98,
      98, 98, 98, 98, 98, 98, 98, 98, 98, 98,
      98, 98, 98, 98, 98, 98, 98, 98, 98, 98,
      98, 98, 98, 98, 98, 98, 98, 98, 98, 98,
      98, 98, 98, 98, 98, 98, 98
    };
  return len + asso_values[(unsigned char)str[2]+1] + asso_values[(unsigned char)str[0]];
}

const # generate c code with gperf: *
in_word_set_codetags (str, len)
     register const char *str;
     register unsigned int len;
{
  enum
    {
      TOTAL_KEYWORDS = 61,
      MIN_WORD_LENGTH = 3,
      MAX_WORD_LENGTH = 14,
      MIN_HASH_VALUE = 4,
      MAX_HASH_VALUE = 97
    };

  static const # generate c code with gperf: wordlist[] =
    {
      {""}, {""}, {""}, {""},
#line 30 "keywords_codetags.gperf"
      {"TEST", 1},
#line 48 "keywords_codetags.gperf"
      {"ISSUE", 1},
      {""},
#line 31 "keywords_codetags.gperf"
      {"TESTING", 1},
#line 29 "keywords_codetags.gperf"
      {"TMP", 1},
#line 12 "keywords_codetags.gperf"
      {"TODO", 1},
#line 46 "keywords_codetags.gperf"
      {"ASSUMPTION", 1},
#line 68 "keywords_codetags.gperf"
      {"IN-PROGRESS", 1},
#line 54 "keywords_codetags.gperf"
      {"IMPROVE", 1},
#line 50 "keywords_codetags.gperf"
      {"TODO-LOW", 1},
#line 51 "keywords_codetags.gperf"
      {"TODO-HIGH", 1},
#line 49 "keywords_codetags.gperf"
      {"TODO-LATER", 1},
      {""}, {""},
#line 36 "keywords_codetags.gperf"
      {"POC", 1},
#line 37 "keywords_codetags.gperf"
      {"PROTOTYPE", 1},
#line 35 "keywords_codetags.gperf"
      {"EXPERIMENT", 1},
      {""}, {""},
#line 56 "keywords_codetags.gperf"
      {"DOC", 1},
#line 58 "keywords_codetags.gperf"
      {"DOCS", 1},
#line 20 "keywords_codetags.gperf"
      {"DEPRECATED", 1},
#line 70 "keywords_codetags.gperf"
      {"VERIFY", 1},
      {""},
#line 57 "keywords_codetags.gperf"
      {"DOCUMENT", 1},
#line 24 "keywords_codetags.gperf"
      {"PERF", 1},
#line 42 "keywords_codetags.gperf"
      {"PATCH", 1},
#line 21 "keywords_codetags.gperf"
      {"UNDONE", 1},
#line 27 "keywords_codetags.gperf"
      {"REFACTOR", 1},
#line 39 "keywords_codetags.gperf"
      {"SEC", 1},
#line 28 "keywords_codetags.gperf"
      {"TEMP", 1},
#line 45 "keywords_codetags.gperf"
      {"EDGE", 1},
#line 25 "keywords_codetags.gperf"
      {"PERFORMANCE", 1},
      {""},
#line 38 "keywords_codetags.gperf"
      {"SECURITY", 1},
#line 44 "keywords_codetags.gperf"
      {"EDGECASE", 1},
#line 16 "keywords_codetags.gperf"
      {"HACK", 1},
#line 22 "keywords_codetags.gperf"
      {"REVIEW", 1},
#line 53 "keywords_codetags.gperf"
      {"REVISIT", 1},
#line 67 "keywords_codetags.gperf"
      {"WIP", 1},
      {""},
#line 32 "keywords_codetags.gperf"
      {"DEBUG", 1},
      {""}, {""},
#line 47 "keywords_codetags.gperf"
      {"QUESTION", 1},
#line 69 "keywords_codetags.gperf"
      {"DONE", 1},
#line 40 "keywords_codetags.gperf"
      {"SAFETY", 1},
      {""}, {""},
#line 41 "keywords_codetags.gperf"
      {"FIX", 1},
#line 15 "keywords_codetags.gperf"
      {"NOTE", 1},
#line 13 "keywords_codetags.gperf"
      {"FIXME", 1},
      {""}, {""},
#line 55 "keywords_codetags.gperf"
      {"SIMPLIFY", 1},
#line 19 "keywords_codetags.gperf"
      {"WARN", 1},
#line 34 "keywords_codetags.gperf"
      {"TRACE", 1},
#line 61 "keywords_codetags.gperf"
      {"FORMAT", 1},
#line 18 "keywords_codetags.gperf"
      {"WARNING", 1},
#line 23 "keywords_codetags.gperf"
      {"OPTIMIZE", 1},
#line 63 "keywords_codetags.gperf"
      {"NOTE-IMPORTANT", 1},
#line 43 "keywords_codetags.gperf"
      {"WORKAROUND", 1},
      {""},
#line 52 "keywords_codetags.gperf"
      {"BLOCKER", 1},
#line 72 "keywords_codetags.gperf"
      {"VALIDATE", 1},
#line 33 "keywords_codetags.gperf"
      {"LOG", 1},
#line 71 "keywords_codetags.gperf"
      {"CHECK", 1},
#line 62 "keywords_codetags.gperf"
      {"CAVEAT", 1},
#line 26 "keywords_codetags.gperf"
      {"CLEANUP", 1},
#line 17 "keywords_codetags.gperf"
      {"XXX", 1},
#line 65 "keywords_codetags.gperf"
      {"NEED-INFO", 1},
#line 59 "keywords_codetags.gperf"
      {"STYLE", 1},
      {""}, {""},
#line 64 "keywords_codetags.gperf"
      {"FYI", 1},
#line 60 "keywords_codetags.gperf"
      {"LINT", 1},
      {""}, {""}, {""}, {""},
#line 14 "keywords_codetags.gperf"
      {"BUG", 1},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""},
#line 66 "keywords_codetags.gperf"
      {"HELP-WANTED", 1}
    };

  if (len <= MAX_WORD_LENGTH && len >= MIN_WORD_LENGTH)
    {
      unsigned int key = hash (str, len);

      if (key <= MAX_HASH_VALUE)
        {
          register const char *s = wordlist[key].name;

          if (*str == *s && !strcmp (str + 1, s + 1))
            return &wordlist[key];
        }
    }
  return 0;
}
