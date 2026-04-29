/* C code produced by gperf version 3.0.3 */
/* Command-line: /Library/Developer/CommandLineTools/usr/bin/gperf -C -E -t -L C -N in_word_set_py keywords_py.gperf  */
/* Computed positions: -k'1,3,6,8,$' */

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

#line 1 "keywords_py.gperf"

#include <string.h>
#line 5 "keywords_py.gperf"
# generate c code with gperf:
# gperf -C -E -t -L C -N in_word_set_py keywords_py.gperf > keywords_py_hash.c

struct keyword_py { const char *name; };
/* maximum key range = 363, duplicates = 0 */

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
      369, 369, 369, 369, 369, 369, 369, 369, 369, 369,
      369, 369, 369, 369, 369, 369, 369, 369, 369, 369,
      369, 369, 369, 369, 369, 369, 369, 369, 369, 369,
      369, 369, 369, 369, 369, 369, 369, 369, 369, 369,
      369, 369, 369, 369, 369, 369,   0,   0, 369, 369,
      369, 369, 369, 369, 369, 369, 369, 369, 369, 369,
      369, 369, 369, 369, 369,  65, 369, 369,   5, 165,
        5, 369, 369,  20, 369,  65,   0, 369,  45,   0,
      369, 369, 369, 369,   0,   0,  10, 369, 369, 369,
        0, 369, 369, 369, 369, 369, 369,  90,   5,  50,
       10,   5,   0, 110,  60,  20,  35,   0,  80,   0,
       15,  50,  85, 125,   0,   5,   0,  35,  90, 120,
      155,  25,  85, 369, 369, 369, 369, 369, 369, 369,
      369, 369, 369, 369, 369, 369, 369, 369, 369, 369,
      369, 369, 369, 369, 369, 369, 369, 369, 369, 369,
      369, 369, 369, 369, 369, 369, 369, 369, 369, 369,
      369, 369, 369, 369, 369, 369, 369, 369, 369, 369,
      369, 369, 369, 369, 369, 369, 369, 369, 369, 369,
      369, 369, 369, 369, 369, 369, 369, 369, 369, 369,
      369, 369, 369, 369, 369, 369, 369, 369, 369, 369,
      369, 369, 369, 369, 369, 369, 369, 369, 369, 369,
      369, 369, 369, 369, 369, 369, 369, 369, 369, 369,
      369, 369, 369, 369, 369, 369, 369, 369, 369, 369,
      369, 369, 369, 369, 369, 369, 369, 369, 369, 369,
      369, 369, 369, 369, 369, 369, 369, 369, 369, 369,
      369, 369, 369, 369, 369, 369, 369
    };
  register unsigned int hval = len;

  switch (hval)
    {
      default:
        hval += asso_values[(unsigned char)str[7]];
      /*FALLTHROUGH*/
      case 7:
      case 6:
        hval += asso_values[(unsigned char)str[5]];
      /*FALLTHROUGH*/
      case 5:
      case 4:
      case 3:
        hval += asso_values[(unsigned char)str[2]+1];
      /*FALLTHROUGH*/
      case 2:
      case 1:
        hval += asso_values[(unsigned char)str[0]];
        break;
    }
  return hval + asso_values[(unsigned char)str[len - 1]];
}

const # generate c code with gperf: *
in_word_set_py (str, len)
     register const char *str;
     register unsigned int len;
{
  enum
    {
      TOTAL_KEYWORDS = 140,
      MIN_WORD_LENGTH = 2,
      MAX_WORD_LENGTH = 23,
      MIN_HASH_VALUE = 6,
      MAX_HASH_VALUE = 368
    };

  static const # generate c code with gperf: wordlist[] =
    {
      {""}, {""}, {""}, {""}, {""}, {""},
#line 70 "keywords_py.gperf"
      {"filter", 1},
      {""},
#line 30 "keywords_py.gperf"
      {"for", 1},
#line 167 "keywords_py.gperf"
      {"file", 1},
#line 21 "keywords_py.gperf"
      {"break", 1},
#line 84 "keywords_py.gperf"
      {"format", 1},
      {""},
#line 52 "keywords_py.gperf"
      {"str", 1},
#line 27 "keywords_py.gperf"
      {"else", 1},
#line 12 "keywords_py.gperf"
      {"False", 1},
#line 125 "keywords_py.gperf"
      {"re.sub", 1},
      {""},
#line 86 "keywords_py.gperf"
      {"dir", 1},
      {""}, {""},
#line 28 "keywords_py.gperf"
      {"except", 1},
#line 33 "keywords_py.gperf"
      {"if", 1},
#line 71 "keywords_py.gperf"
      {"sum", 1},
#line 55 "keywords_py.gperf"
      {"dict", 1},
      {""}, {""},
#line 36 "keywords_py.gperf"
      {"is", 1},
      {""},
#line 110 "keywords_py.gperf"
      {"time.time", 1},
      {""}, {""},
#line 87 "keywords_py.gperf"
      {"id", 1},
      {""}, {""},
#line 126 "keywords_py.gperf"
      {"re.compile", 1},
#line 74 "keywords_py.gperf"
      {"sorted", 1},
#line 35 "keywords_py.gperf"
      {"in", 1},
#line 112 "keywords_py.gperf"
      {"time.strftime", 1},
#line 163 "keywords_py.gperf"
      {"name", 1},
#line 47 "keywords_py.gperf"
      {"yield", 1},
      {""}, {""},
#line 56 "keywords_py.gperf"
      {"set", 1},
#line 26 "keywords_py.gperf"
      {"elif", 1},
#line 42 "keywords_py.gperf"
      {"raise", 1},
      {""}, {""}, {""},
#line 102 "keywords_py.gperf"
      {"math.sqrt", 1},
#line 58 "keywords_py.gperf"
      {"bytes", 1},
      {""},
#line 40 "keywords_py.gperf"
      {"or", 1},
#line 39 "keywords_py.gperf"
      {"not", 1},
#line 164 "keywords_py.gperf"
      {"main", 1},
      {""}, {""}, {""},
#line 49 "keywords_py.gperf"
      {"int", 1},
#line 165 "keywords_py.gperf"
      {"init", 1},
#line 66 "keywords_py.gperf"
      {"range", 1},
      {""},
#line 161 "keywords_py.gperf"
      {"ZeroDivisionError", 1},
#line 128 "keywords_py.gperf"
      {"random.random", 1},
#line 129 "keywords_py.gperf"
      {"random.randint", 1},
#line 22 "keywords_py.gperf"
      {"class", 1},
      {""}, {""},
#line 72 "keywords_py.gperf"
      {"min", 1},
#line 82 "keywords_py.gperf"
      {"open", 1},
      {""},
#line 43 "keywords_py.gperf"
      {"return", 1},
      {""},
#line 106 "keywords_py.gperf"
      {"math.tan", 1},
#line 131 "keywords_py.gperf"
      {"random.shuffle", 1},
#line 97 "keywords_py.gperf"
      {"os.listdir", 1},
#line 153 "keywords_py.gperf"
      {"classmethod", 1},
#line 98 "keywords_py.gperf"
      {"os.path.join", 1},
#line 104 "keywords_py.gperf"
      {"math.sin", 1},
#line 100 "keywords_py.gperf"
      {"os.rename", 1},
      {""}, {""}, {""}, {""},
#line 53 "keywords_py.gperf"
      {"list", 1},
#line 65 "keywords_py.gperf"
      {"isinstance", 1},
      {""},
#line 152 "keywords_py.gperf"
      {"staticmethod", 1},
#line 114 "keywords_py.gperf"
      {"datetime.date", 1},
#line 31 "keywords_py.gperf"
      {"from", 1},
#line 50 "keywords_py.gperf"
      {"float", 1},
      {""},
#line 113 "keywords_py.gperf"
      {"datetime.datetime", 1},
#line 25 "keywords_py.gperf"
      {"del", 1},
#line 41 "keywords_py.gperf"
      {"pass", 1},
      {""},
#line 18 "keywords_py.gperf"
      {"assert", 1},
#line 17 "keywords_py.gperf"
      {"as", 1},
#line 78 "keywords_py.gperf"
      {"abs", 1},
#line 13 "keywords_py.gperf"
      {"True", 1},
#line 20 "keywords_py.gperf"
      {"await", 1},
      {""}, {""},
#line 105 "keywords_py.gperf"
      {"math.cos", 1},
#line 14 "keywords_py.gperf"
      {"None", 1},
#line 79 "keywords_py.gperf"
      {"round", 1},
      {""}, {""},
#line 16 "keywords_py.gperf"
      {"and", 1},
#line 67 "keywords_py.gperf"
      {"enumerate", 1},
      {""}, {""}, {""},
#line 44 "keywords_py.gperf"
      {"try", 1},
#line 57 "keywords_py.gperf"
      {"frozenset", 1},
      {""}, {""}, {""},
#line 130 "keywords_py.gperf"
      {"random.choice", 1},
#line 160 "keywords_py.gperf"
      {"AttributeError", 1},
#line 111 "keywords_py.gperf"
      {"time.sleep", 1},
      {""}, {""},
#line 24 "keywords_py.gperf"
      {"def", 1},
#line 88 "keywords_py.gperf"
      {"hash", 1},
#line 62 "keywords_py.gperf"
      {"print", 1},
      {""}, {""},
#line 122 "keywords_py.gperf"
      {"re.match", 1},
#line 166 "keywords_py.gperf"
      {"repr", 1},
      {""}, {""}, {""},
#line 23 "keywords_py.gperf"
      {"continue", 1},
#line 64 "keywords_py.gperf"
      {"type", 1},
#line 54 "keywords_py.gperf"
      {"tuple", 1},
      {""}, {""},
#line 90 "keywords_py.gperf"
      {"NoneType", 1},
#line 133 "keywords_py.gperf"
      {"collections.Counter", 1},
      {""}, {""},
#line 135 "keywords_py.gperf"
      {"collections.deque", 1},
#line 134 "keywords_py.gperf"
      {"collections.defaultdict", 1},
#line 150 "keywords_py.gperf"
      {"dataclass", 1},
#line 120 "keywords_py.gperf"
      {"json.dumps", 1},
      {""}, {""},
#line 63 "keywords_py.gperf"
      {"len", 1},
#line 85 "keywords_py.gperf"
      {"help", 1},
#line 83 "keywords_py.gperf"
      {"input", 1},
#line 34 "keywords_py.gperf"
      {"import", 1},
      {""},
#line 75 "keywords_py.gperf"
      {"reversed", 1},
#line 99 "keywords_py.gperf"
      {"os.remove", 1},
      {""}, {""}, {""},
#line 159 "keywords_py.gperf"
      {"KeyError", 1},
      {""}, {""}, {""},
#line 29 "keywords_py.gperf"
      {"finally", 1},
      {""},
#line 59 "keywords_py.gperf"
      {"bytearray", 1},
#line 45 "keywords_py.gperf"
      {"while", 1},
      {""},
#line 138 "keywords_py.gperf"
      {"itertools.product", 1},
#line 92 "keywords_py.gperf"
      {"sys.exit", 1},
      {""}, {""}, {""}, {""},
#line 77 "keywords_py.gperf"
      {"all", 1},
#line 51 "keywords_py.gperf"
      {"bool", 1},
#line 171 "keywords_py.gperf"
      {"debug", 1},
      {""},
#line 139 "keywords_py.gperf"
      {"itertools.permutations", 1},
#line 115 "keywords_py.gperf"
      {"datetime.timedelta", 1},
      {""},
#line 137 "keywords_py.gperf"
      {"itertools.chain", 1},
      {""}, {""},
#line 73 "keywords_py.gperf"
      {"max", 1},
#line 157 "keywords_py.gperf"
      {"TypeError", 1},
#line 156 "keywords_py.gperf"
      {"ValueError", 1},
      {""}, {""},
#line 169 "keywords_py.gperf"
      {"Ellipsis", 1},
#line 96 "keywords_py.gperf"
      {"os.getcwd", 1},
#line 60 "keywords_py.gperf"
      {"memoryview", 1},
      {""}, {""},
#line 93 "keywords_py.gperf"
      {"sys.argv", 1},
#line 170 "keywords_py.gperf"
      {"NotImplemented", 1},
#line 124 "keywords_py.gperf"
      {"re.findall", 1},
      {""}, {""}, {""}, {""},
#line 158 "keywords_py.gperf"
      {"IndexError", 1},
      {""}, {""},
#line 76 "keywords_py.gperf"
      {"any", 1},
#line 141 "keywords_py.gperf"
      {"functools.lru_cache", 1},
      {""}, {""}, {""}, {""},
#line 123 "keywords_py.gperf"
      {"re.search", 1},
      {""}, {""}, {""},
#line 69 "keywords_py.gperf"
      {"map", 1},
      {""}, {""}, {""}, {""},
#line 108 "keywords_py.gperf"
      {"math.exp", 1},
#line 46 "keywords_py.gperf"
      {"with", 1},
      {""}, {""}, {""},
#line 94 "keywords_py.gperf"
      {"sys.path", 1},
#line 118 "keywords_py.gperf"
      {"json.dump", 1},
      {""}, {""}, {""},
#line 151 "keywords_py.gperf"
      {"property", 1},
      {""},
#line 19 "keywords_py.gperf"
      {"async", 1},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""}, {""}, {""}, {""},
#line 144 "keywords_py.gperf"
      {"typing.List", 1},
      {""}, {""},
#line 155 "keywords_py.gperf"
      {"Exception", 1},
      {""},
#line 145 "keywords_py.gperf"
      {"typing.Dict", 1},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""},
#line 147 "keywords_py.gperf"
      {"typing.Union", 1},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""}, {""}, {""},
#line 142 "keywords_py.gperf"
      {"functools.partial", 1},
      {""}, {""}, {""},
#line 37 "keywords_py.gperf"
      {"lambda", 1},
      {""},
#line 38 "keywords_py.gperf"
      {"nonlocal", 1},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""}, {""}, {""},
#line 68 "keywords_py.gperf"
      {"zip", 1},
      {""}, {""}, {""}, {""}, {""}, {""},
#line 119 "keywords_py.gperf"
      {"json.loads", 1},
      {""}, {""}, {""},
#line 117 "keywords_py.gperf"
      {"json.load", 1},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""},
#line 146 "keywords_py.gperf"
      {"typing.Optional", 1},
      {""}, {""}, {""}, {""},
#line 148 "keywords_py.gperf"
      {"typing.Any", 1},
      {""}, {""}, {""}, {""}, {""}, {""}, {""},
#line 107 "keywords_py.gperf"
      {"math.log", 1},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
#line 32 "keywords_py.gperf"
      {"global", 1},
      {""},
#line 80 "keywords_py.gperf"
      {"pow", 1},
      {""}, {""}, {""}, {""},
#line 103 "keywords_py.gperf"
      {"math.pow", 1}
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
