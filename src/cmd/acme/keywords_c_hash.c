/* C code produced by gperf version 3.0.3 */
/* Command-line: /Library/Developer/CommandLineTools/usr/bin/gperf -C -E -t -L C -N in_word_set_c keywords_c.gperf  */
/* Computed positions: -k'1-2,4,6,$' */

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

#line 1 "keywords_c.gperf"

#include <string.h>
#line 5 "keywords_c.gperf"
# generate c code with gperf:
# gperf -C -E -t -L C -N in_word_set_c keywords_c.gperf > keywords_c_hash.c

struct keyword_c { const char *name; };
/* maximum key range = 548, duplicates = 0 */

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
  static const unsigned short asso_values[] =
    {
      562, 562, 562, 562, 562, 562, 562, 562, 562, 562,
      562, 562, 562, 562, 562, 562, 562, 562, 562, 562,
      562, 562, 562, 562, 562, 562, 562, 562, 562, 562,
      562, 562, 562, 562, 562, 562, 562, 562, 562, 562,
      562, 562, 562, 562, 562, 562, 562, 562,   0,  10,
       30,   0, 105, 562, 170, 562,   0, 562, 562, 562,
      562, 562, 562, 562, 562,  30, 120,   0,  30,  15,
       15,   0,   0,   0, 562, 165,   5,  50,   5,  25,
      562,   0,  75,   0,   0,  80, 562, 562,  25, 562,
        5, 562, 562, 562, 562,  95, 562,  40, 105, 125,
       70,   5,   5,  35,  95,  20, 562,  95,  60,  95,
       10,   0, 130,   0,  75,  10,   0,  75, 105,  80,
      165, 165, 562, 562, 562, 562, 562, 562, 562, 562,
      562, 562, 562, 562, 562, 562, 562, 562, 562, 562,
      562, 562, 562, 562, 562, 562, 562, 562, 562, 562,
      562, 562, 562, 562, 562, 562, 562, 562, 562, 562,
      562, 562, 562, 562, 562, 562, 562, 562, 562, 562,
      562, 562, 562, 562, 562, 562, 562, 562, 562, 562,
      562, 562, 562, 562, 562, 562, 562, 562, 562, 562,
      562, 562, 562, 562, 562, 562, 562, 562, 562, 562,
      562, 562, 562, 562, 562, 562, 562, 562, 562, 562,
      562, 562, 562, 562, 562, 562, 562, 562, 562, 562,
      562, 562, 562, 562, 562, 562, 562, 562, 562, 562,
      562, 562, 562, 562, 562, 562, 562, 562, 562, 562,
      562, 562, 562, 562, 562, 562, 562, 562, 562, 562,
      562, 562, 562, 562, 562, 562
    };
  register unsigned int hval = len;

  switch (hval)
    {
      default:
        hval += asso_values[(unsigned char)str[5]];
      /*FALLTHROUGH*/
      case 5:
      case 4:
        hval += asso_values[(unsigned char)str[3]];
      /*FALLTHROUGH*/
      case 3:
      case 2:
        hval += asso_values[(unsigned char)str[1]];
      /*FALLTHROUGH*/
      case 1:
        hval += asso_values[(unsigned char)str[0]];
        break;
    }
  return hval + asso_values[(unsigned char)str[len - 1]];
}

const # generate c code with gperf: *
in_word_set_c (str, len)
     register const char *str;
     register unsigned int len;
{
  enum
    {
      TOTAL_KEYWORDS = 221,
      MIN_WORD_LENGTH = 2,
      MAX_WORD_LENGTH = 14,
      MIN_HASH_VALUE = 14,
      MAX_HASH_VALUE = 561
    };

  static const # generate c code with gperf: wordlist[] =
    {
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""}, {""}, {""},
#line 199 "keywords_c.gperf"
      {"sqrt", 1},
      {""}, {""}, {""}, {""},
#line 220 "keywords_c.gperf"
      {"CLOCKS_PER_SEC", 1},
      {""},
#line 241 "keywords_c.gperf"
      {"EILSEQ", 1},
      {""}, {""}, {""},
#line 88 "keywords_c.gperf"
      {"fopen", 1},
#line 130 "keywords_c.gperf"
      {"strtof", 1},
      {""},
#line 246 "keywords_c.gperf"
      {"offsetof", 1},
      {""}, {""},
#line 73 "keywords_c.gperf"
      {"time_t", 1},
#line 27 "keywords_c.gperf"
      {"if", 1},
#line 29 "keywords_c.gperf"
      {"int", 1},
#line 175 "keywords_c.gperf"
      {"time", 1},
      {""},
#line 61 "keywords_c.gperf"
      {"int8_t", 1},
      {""}, {""},
#line 26 "keywords_c.gperf"
      {"goto", 1},
      {""},
#line 57 "keywords_c.gperf"
      {"size_t", 1},
      {""},
#line 185 "keywords_c.gperf"
      {"sin", 1},
      {""}, {""},
#line 154 "keywords_c.gperf"
      {"strspn", 1},
      {""},
#line 179 "keywords_c.gperf"
      {"strftime", 1},
#line 71 "keywords_c.gperf"
      {"FILE", 1},
      {""},
#line 36 "keywords_c.gperf"
      {"sizeof", 1},
#line 217 "keywords_c.gperf"
      {"EXIT_SUCCESS", 1},
#line 187 "keywords_c.gperf"
      {"tan", 1},
#line 125 "keywords_c.gperf"
      {"atof", 1},
#line 93 "keywords_c.gperf"
      {"fgets", 1},
      {""}, {""},
#line 208 "keywords_c.gperf"
      {"EOF", 1},
      {""}, {""},
#line 205 "keywords_c.gperf"
      {"assert", 1},
      {""}, {""},
#line 190 "keywords_c.gperf"
      {"atan", 1},
#line 244 "keywords_c.gperf"
      {"false", 1},
#line 28 "keywords_c.gperf"
      {"inline", 1},
#line 147 "keywords_c.gperf"
      {"strncat", 1},
      {""},
#line 202 "keywords_c.gperf"
      {"fabs", 1},
      {""},
#line 86 "keywords_c.gperf"
      {"fscanf", 1},
#line 19 "keywords_c.gperf"
      {"do", 1},
#line 118 "keywords_c.gperf"
      {"at_quick_exit", 1},
#line 188 "keywords_c.gperf"
      {"asin", 1},
#line 197 "keywords_c.gperf"
      {"log10", 1},
#line 87 "keywords_c.gperf"
      {"sscanf", 1},
#line 165 "keywords_c.gperf"
      {"isdigit", 1},
      {""},
#line 21 "keywords_c.gperf"
      {"else", 1},
      {""}, {""},
#line 218 "keywords_c.gperf"
      {"EXIT_FAILURE", 1},
#line 25 "keywords_c.gperf"
      {"for", 1},
#line 122 "keywords_c.gperf"
      {"atoi", 1},
#line 191 "keywords_c.gperf"
      {"atan2", 1},
      {""},
#line 172 "keywords_c.gperf"
      {"tolower", 1},
      {""},
#line 243 "keywords_c.gperf"
      {"true", 1},
#line 135 "keywords_c.gperf"
      {"qsort", 1},
#line 38 "keywords_c.gperf"
      {"struct", 1},
      {""},
#line 225 "keywords_c.gperf"
      {"LONG_MIN", 1},
#line 111 "keywords_c.gperf"
      {"free", 1},
#line 238 "keywords_c.gperf"
      {"errno", 1},
#line 143 "keywords_c.gperf"
      {"strlen", 1},
#line 209 "keywords_c.gperf"
      {"FILENAME_MAX", 1},
#line 196 "keywords_c.gperf"
      {"log", 1},
#line 207 "keywords_c.gperf"
      {"NULL", 1},
#line 41 "keywords_c.gperf"
      {"union", 1},
      {""},
#line 89 "keywords_c.gperf"
      {"freopen", 1},
#line 236 "keywords_c.gperf"
      {"LDBL_MIN", 1},
#line 70 "keywords_c.gperf"
      {"uintptr_t", 1},
      {""},
#line 60 "keywords_c.gperf"
      {"wint_t", 1},
      {""},
#line 32 "keywords_c.gperf"
      {"restrict", 1},
      {""},
#line 24 "keywords_c.gperf"
      {"float", 1},
      {""},
#line 223 "keywords_c.gperf"
      {"INT_MIN", 1},
#line 224 "keywords_c.gperf"
      {"LONG_MAX", 1},
#line 180 "keywords_c.gperf"
      {"localtime", 1},
      {""},
#line 161 "keywords_c.gperf"
      {"memset", 1},
#line 166 "keywords_c.gperf"
      {"islower", 1},
#line 84 "keywords_c.gperf"
      {"snprintf", 1},
#line 12 "keywords_c.gperf"
      {"auto", 1},
#line 103 "keywords_c.gperf"
      {"fseek", 1},
#line 102 "keywords_c.gperf"
      {"fwrite", 1},
#line 169 "keywords_c.gperf"
      {"isprint", 1},
#line 235 "keywords_c.gperf"
      {"LDBL_MAX", 1},
#line 137 "keywords_c.gperf"
      {"labs", 1},
      {""}, {""},
#line 232 "keywords_c.gperf"
      {"FLT_MIN", 1},
#line 177 "keywords_c.gperf"
      {"difftime", 1},
      {""},
#line 104 "keywords_c.gperf"
      {"ftell", 1},
#line 240 "keywords_c.gperf"
      {"ERANGE", 1},
#line 63 "keywords_c.gperf"
      {"int32_t", 1},
#line 67 "keywords_c.gperf"
      {"uint32_t", 1},
#line 30 "keywords_c.gperf"
      {"long", 1},
#line 115 "keywords_c.gperf"
      {"_Exit", 1},
#line 126 "keywords_c.gperf"
      {"strtol", 1},
#line 127 "keywords_c.gperf"
      {"strtoll", 1},
#line 186 "keywords_c.gperf"
      {"cos", 1},
#line 227 "keywords_c.gperf"
      {"SCHAR_MIN", 1},
#line 16 "keywords_c.gperf"
      {"const", 1},
#line 146 "keywords_c.gperf"
      {"strcat", 1},
#line 62 "keywords_c.gperf"
      {"int16_t", 1},
#line 171 "keywords_c.gperf"
      {"isxdigit", 1},
      {""},
#line 201 "keywords_c.gperf"
      {"floor", 1},
#line 90 "keywords_c.gperf"
      {"fclose", 1},
#line 132 "keywords_c.gperf"
      {"strtold", 1},
#line 17 "keywords_c.gperf"
      {"continue", 1},
#line 239 "keywords_c.gperf"
      {"EDOM", 1},
#line 95 "keywords_c.gperf"
      {"fputs", 1},
#line 72 "keywords_c.gperf"
      {"fpos_t", 1},
#line 128 "keywords_c.gperf"
      {"strtoul", 1},
#line 129 "keywords_c.gperf"
      {"strtoull", 1},
      {""},
#line 85 "keywords_c.gperf"
      {"scanf", 1},
#line 131 "keywords_c.gperf"
      {"strtod", 1},
#line 182 "keywords_c.gperf"
      {"asctime", 1},
#line 136 "keywords_c.gperf"
      {"abs", 1},
#line 226 "keywords_c.gperf"
      {"SCHAR_MAX", 1},
      {""}, {""},
#line 222 "keywords_c.gperf"
      {"INT_MAX", 1},
#line 229 "keywords_c.gperf"
      {"UINT_MAX", 1},
#line 123 "keywords_c.gperf"
      {"atol", 1},
#line 124 "keywords_c.gperf"
      {"atoll", 1},
#line 181 "keywords_c.gperf"
      {"gmtime", 1},
#line 82 "keywords_c.gperf"
      {"fprintf", 1},
#line 47 "keywords_c.gperf"
      {"_Alignof", 1},
#line 54 "keywords_c.gperf"
      {"_Static_assert", 1},
#line 92 "keywords_c.gperf"
      {"fgetc", 1},
      {""},
#line 83 "keywords_c.gperf"
      {"sprintf", 1},
#line 46 "keywords_c.gperf"
      {"_Alignas", 1},
#line 113 "keywords_c.gperf"
      {"exit", 1},
      {""},
#line 152 "keywords_c.gperf"
      {"strstr", 1},
#line 231 "keywords_c.gperf"
      {"FLT_MAX", 1},
#line 44 "keywords_c.gperf"
      {"volatile", 1},
#line 14 "keywords_c.gperf"
      {"case", 1},
      {""},
#line 33 "keywords_c.gperf"
      {"return", 1},
#line 18 "keywords_c.gperf"
      {"default", 1},
#line 31 "keywords_c.gperf"
      {"register", 1},
#line 210 "keywords_c.gperf"
      {"FOPEN_MAX", 1},
#line 34 "keywords_c.gperf"
      {"short", 1},
#line 35 "keywords_c.gperf"
      {"signed", 1},
#line 40 "keywords_c.gperf"
      {"typedef", 1},
#line 214 "keywords_c.gperf"
      {"SEEK_SET", 1},
#line 189 "keywords_c.gperf"
      {"acos", 1},
#line 77 "keywords_c.gperf"
      {"div_t", 1},
#line 20 "keywords_c.gperf"
      {"double", 1},
#line 75 "keywords_c.gperf"
      {"tm", 1},
#line 42 "keywords_c.gperf"
      {"unsigned", 1},
#line 53 "keywords_c.gperf"
      {"_Noreturn", 1},
#line 101 "keywords_c.gperf"
      {"fread", 1},
      {""},
#line 65 "keywords_c.gperf"
      {"uint8_t", 1},
#line 139 "keywords_c.gperf"
      {"div", 1},
      {""}, {""},
#line 23 "keywords_c.gperf"
      {"extern", 1},
      {""},
#line 221 "keywords_c.gperf"
      {"CHAR_BIT", 1},
      {""}, {""},
#line 153 "keywords_c.gperf"
      {"strtok", 1},
#line 211 "keywords_c.gperf"
      {"TMP_MAX", 1},
#line 68 "keywords_c.gperf"
      {"uint64_t", 1},
#line 22 "keywords_c.gperf"
      {"enum", 1},
      {""},
#line 117 "keywords_c.gperf"
      {"atexit", 1},
      {""},
#line 198 "keywords_c.gperf"
      {"pow", 1},
#line 58 "keywords_c.gperf"
      {"ptrdiff_t", 1},
      {""},
#line 213 "keywords_c.gperf"
      {"BUFSIZ", 1},
#line 173 "keywords_c.gperf"
      {"toupper", 1},
#line 219 "keywords_c.gperf"
      {"RAND_MAX", 1},
#line 230 "keywords_c.gperf"
      {"ULONG_MAX", 1},
      {""}, {""},
#line 76 "keywords_c.gperf"
      {"va_list", 1},
      {""},
#line 192 "keywords_c.gperf"
      {"sinh", 1},
#line 116 "keywords_c.gperf"
      {"abort", 1},
#line 178 "keywords_c.gperf"
      {"mktime", 1},
      {""}, {""},
#line 100 "keywords_c.gperf"
      {"puts", 1},
#line 183 "keywords_c.gperf"
      {"ctime", 1},
#line 81 "keywords_c.gperf"
      {"printf", 1},
#line 164 "keywords_c.gperf"
      {"isalpha", 1},
#line 216 "keywords_c.gperf"
      {"SEEK_END", 1},
#line 194 "keywords_c.gperf"
      {"tanh", 1},
      {""}, {""},
#line 170 "keywords_c.gperf"
      {"ispunct", 1},
      {""},
#line 228 "keywords_c.gperf"
      {"UCHAR_MAX", 1},
#line 138 "keywords_c.gperf"
      {"llabs", 1},
#line 78 "keywords_c.gperf"
      {"ldiv_t", 1},
#line 79 "keywords_c.gperf"
      {"lldiv_t", 1},
#line 69 "keywords_c.gperf"
      {"intptr_t", 1},
#line 203 "keywords_c.gperf"
      {"fmod", 1},
#line 45 "keywords_c.gperf"
      {"while", 1},
#line 105 "keywords_c.gperf"
      {"rewind", 1},
#line 167 "keywords_c.gperf"
      {"isupper", 1},
      {""},
#line 43 "keywords_c.gperf"
      {"void", 1},
#line 141 "keywords_c.gperf"
      {"lldiv", 1},
      {""},
#line 149 "keywords_c.gperf"
      {"strncmp", 1},
      {""},
#line 200 "keywords_c.gperf"
      {"ceil", 1},
      {""}, {""},
#line 234 "keywords_c.gperf"
      {"DBL_MIN", 1},
      {""}, {""}, {""},
#line 120 "keywords_c.gperf"
      {"getenv", 1},
#line 151 "keywords_c.gperf"
      {"strrchr", 1},
#line 215 "keywords_c.gperf"
      {"SEEK_CUR", 1},
      {""},
#line 94 "keywords_c.gperf"
      {"fputc", 1},
#line 37 "keywords_c.gperf"
      {"static", 1},
#line 163 "keywords_c.gperf"
      {"isalnum", 1},
      {""}, {""}, {""}, {""},
#line 110 "keywords_c.gperf"
      {"realloc", 1},
#line 66 "keywords_c.gperf"
      {"uint16_t", 1},
      {""}, {""}, {""},
#line 48 "keywords_c.gperf"
      {"_Atomic", 1},
#line 112 "keywords_c.gperf"
      {"aligned_alloc", 1},
      {""},
#line 49 "keywords_c.gperf"
      {"_Bool", 1},
#line 91 "keywords_c.gperf"
      {"fflush", 1},
#line 155 "keywords_c.gperf"
      {"strcspn", 1},
#line 55 "keywords_c.gperf"
      {"_Thread_local", 1},
      {""}, {""},
#line 39 "keywords_c.gperf"
      {"switch", 1},
#line 97 "keywords_c.gperf"
      {"getchar", 1},
      {""}, {""}, {""},
#line 150 "keywords_c.gperf"
      {"strchr", 1},
      {""}, {""},
#line 96 "keywords_c.gperf"
      {"getc", 1},
      {""}, {""},
#line 168 "keywords_c.gperf"
      {"isspace", 1},
      {""}, {""}, {""}, {""},
#line 64 "keywords_c.gperf"
      {"int64_t", 1},
#line 195 "keywords_c.gperf"
      {"exp", 1},
      {""},
#line 114 "keywords_c.gperf"
      {"quick_exit", 1},
      {""},
#line 233 "keywords_c.gperf"
      {"DBL_MAX", 1},
#line 212 "keywords_c.gperf"
      {"L_tmpnam", 1},
      {""}, {""}, {""},
#line 158 "keywords_c.gperf"
      {"memmove", 1},
#line 51 "keywords_c.gperf"
      {"_Generic", 1},
      {""}, {""}, {""},
#line 156 "keywords_c.gperf"
      {"strpbrk", 1},
      {""},
#line 193 "keywords_c.gperf"
      {"cosh", 1},
#line 13 "keywords_c.gperf"
      {"break", 1},
      {""},
#line 145 "keywords_c.gperf"
      {"strncpy", 1},
      {""}, {""}, {""}, {""}, {""}, {""}, {""},
#line 52 "keywords_c.gperf"
      {"_Imaginary", 1},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""}, {""},
#line 140 "keywords_c.gperf"
      {"ldiv", 1},
      {""}, {""},
#line 59 "keywords_c.gperf"
      {"wchar_t", 1},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
#line 106 "keywords_c.gperf"
      {"perror", 1},
      {""}, {""}, {""}, {""},
#line 119 "keywords_c.gperf"
      {"system", 1},
      {""}, {""},
#line 15 "keywords_c.gperf"
      {"char", 1},
      {""}, {""}, {""}, {""}, {""}, {""},
#line 160 "keywords_c.gperf"
      {"memchr", 1},
#line 134 "keywords_c.gperf"
      {"bsearch", 1},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
#line 148 "keywords_c.gperf"
      {"strcmp", 1},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
#line 176 "keywords_c.gperf"
      {"clock", 1},
      {""},
#line 74 "keywords_c.gperf"
      {"clock_t", 1},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""},
#line 50 "keywords_c.gperf"
      {"_Complex", 1},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
#line 108 "keywords_c.gperf"
      {"malloc", 1},
#line 99 "keywords_c.gperf"
      {"putchar", 1},
      {""}, {""}, {""}, {""}, {""}, {""},
#line 98 "keywords_c.gperf"
      {"putc", 1},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""},
#line 144 "keywords_c.gperf"
      {"strcpy", 1},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
#line 109 "keywords_c.gperf"
      {"calloc", 1},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
#line 159 "keywords_c.gperf"
      {"memcmp", 1},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""}, {""}, {""}, {""},
#line 157 "keywords_c.gperf"
      {"memcpy", 1}
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
