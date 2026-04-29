/* C code produced by gperf version 3.0.3 */
/* Command-line: /Library/Developer/CommandLineTools/usr/bin/gperf -C -E -t -L C -N in_word_set_java keywords_java.gperf  */
/* Computed positions: -k'1-2,6,9,$' */

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

#line 1 "keywords_java.gperf"

#include <string.h>
#line 5 "keywords_java.gperf"
# generate c code with gperf:
# gperf -C -E -t -L C -N in_word_set_java keywords_java.gperf > keywords_java_hash.c

struct keyword_java { const char *name; };
/* maximum key range = 551, duplicates = 0 */

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
      557, 557, 557, 557, 557, 557, 557, 557, 557, 557,
      557, 557, 557, 557, 557, 557, 557, 557, 557, 557,
      557, 557, 557, 557, 557, 557, 557, 557, 557, 557,
      557, 557, 557, 557, 557, 557, 557, 557, 557, 557,
      557, 557, 557, 557, 557, 557, 557, 557, 557, 557,
      557, 557, 557, 557, 557, 557, 557, 557, 557, 557,
      557, 557, 557, 557, 557,   5,   0,  65,  25, 135,
      145, 557,   0,  35, 557, 557,  90,   0, 557,   5,
        5,  15,   0,   5,  10, 557, 557,  15, 557, 557,
      557, 557, 557, 557, 557, 557, 557,  45,  55,   5,
       70,   0,  40, 110, 115,  15,   5,   0,  45,  10,
       20,  60,  85,   0,   5,   0,   5, 185,  40, 105,
       80,  35, 557, 557, 557, 557, 557, 557, 557, 557,
      557, 557, 557, 557, 557, 557, 557, 557, 557, 557,
      557, 557, 557, 557, 557, 557, 557, 557, 557, 557,
      557, 557, 557, 557, 557, 557, 557, 557, 557, 557,
      557, 557, 557, 557, 557, 557, 557, 557, 557, 557,
      557, 557, 557, 557, 557, 557, 557, 557, 557, 557,
      557, 557, 557, 557, 557, 557, 557, 557, 557, 557,
      557, 557, 557, 557, 557, 557, 557, 557, 557, 557,
      557, 557, 557, 557, 557, 557, 557, 557, 557, 557,
      557, 557, 557, 557, 557, 557, 557, 557, 557, 557,
      557, 557, 557, 557, 557, 557, 557, 557, 557, 557,
      557, 557, 557, 557, 557, 557, 557, 557, 557, 557,
      557, 557, 557, 557, 557, 557, 557, 557, 557, 557,
      557, 557, 557, 557, 557, 557
    };
  register unsigned int hval = len;

  switch (hval)
    {
      default:
        hval += asso_values[(unsigned char)str[8]];
      /*FALLTHROUGH*/
      case 8:
      case 7:
      case 6:
        hval += asso_values[(unsigned char)str[5]];
      /*FALLTHROUGH*/
      case 5:
      case 4:
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
in_word_set_java (str, len)
     register const char *str;
     register unsigned int len;
{
  enum
    {
      TOTAL_KEYWORDS = 156,
      MIN_WORD_LENGTH = 2,
      MAX_WORD_LENGTH = 24,
      MIN_HASH_VALUE = 6,
      MAX_HASH_VALUE = 556
    };

  static const # generate c code with gperf: wordlist[] =
    {
      {""}, {""}, {""}, {""}, {""}, {""},
#line 82 "keywords_java.gperf"
      {"equals", 1},
      {""},
#line 90 "keywords_java.gperf"
      {"set", 1},
      {""}, {""},
#line 88 "keywords_java.gperf"
      {"remove", 1},
      {""},
#line 141 "keywords_java.gperf"
      {"Set", 1},
#line 109 "keywords_java.gperf"
      {"true", 1},
#line 104 "keywords_java.gperf"
      {"start", 1},
#line 137 "keywords_java.gperf"
      {"Arrays", 1},
      {""}, {""},
#line 86 "keywords_java.gperf"
      {"size", 1},
      {""},
#line 49 "keywords_java.gperf"
      {"static", 1},
#line 161 "keywords_java.gperf"
      {"Scanner", 1},
      {""},
#line 173 "keywords_java.gperf"
      {"Predicate", 1},
      {""}, {""},
#line 149 "keywords_java.gperf"
      {"TreeSet", 1},
#line 99 "keywords_java.gperf"
      {"readLine", 1},
#line 94 "keywords_java.gperf"
      {"next", 1},
#line 143 "keywords_java.gperf"
      {"Deque", 1},
      {""}, {""}, {""},
#line 27 "keywords_java.gperf"
      {"enum", 1},
      {""},
#line 171 "keywords_java.gperf"
      {"Stream", 1},
      {""},
#line 93 "keywords_java.gperf"
      {"iterator", 1},
#line 68 "keywords_java.gperf"
      {"Byte", 1},
      {""},
#line 36 "keywords_java.gperf"
      {"import", 1},
      {""},
#line 38 "keywords_java.gperf"
      {"int", 1},
#line 57 "keywords_java.gperf"
      {"transient", 1},
      {""}, {""}, {""},
#line 58 "keywords_java.gperf"
      {"try", 1},
#line 26 "keywords_java.gperf"
      {"else", 1},
#line 35 "keywords_java.gperf"
      {"implements", 1},
#line 47 "keywords_java.gperf"
      {"return", 1},
      {""}, {""},
#line 17 "keywords_java.gperf"
      {"case", 1},
#line 20 "keywords_java.gperf"
      {"class", 1},
      {""},
#line 145 "keywords_java.gperf"
      {"HashSet", 1},
#line 127 "keywords_java.gperf"
      {"Math.cos", 1},
      {""}, {""},
#line 13 "keywords_java.gperf"
      {"assert", 1},
#line 92 "keywords_java.gperf"
      {"isEmpty", 1},
      {""},
#line 123 "keywords_java.gperf"
      {"Math.sqrt", 1},
#line 15 "keywords_java.gperf"
      {"break", 1},
#line 74 "keywords_java.gperf"
      {"System", 1},
#line 63 "keywords_java.gperf"
      {"Integer", 1},
      {""},
#line 116 "keywords_java.gperf"
      {"System.gc", 1},
#line 113 "keywords_java.gperf"
      {"System.err", 1},
#line 41 "keywords_java.gperf"
      {"native", 1},
      {""},
#line 126 "keywords_java.gperf"
      {"Math.sin", 1},
      {""},
#line 21 "keywords_java.gperf"
      {"const", 1},
#line 72 "keywords_java.gperf"
      {"Object", 1},
      {""},
#line 128 "keywords_java.gperf"
      {"Math.tan", 1},
#line 80 "keywords_java.gperf"
      {"main", 1},
      {""},
#line 157 "keywords_java.gperf"
      {"InputStream", 1},
      {""},
#line 122 "keywords_java.gperf"
      {"Math.min", 1},
#line 39 "keywords_java.gperf"
      {"interface", 1},
      {""},
#line 151 "keywords_java.gperf"
      {"IOException", 1},
      {""},
#line 91 "keywords_java.gperf"
      {"contains", 1},
#line 106 "keywords_java.gperf"
      {"join", 1},
#line 110 "keywords_java.gperf"
      {"false", 1},
#line 65 "keywords_java.gperf"
      {"Double", 1},
      {""},
#line 22 "keywords_java.gperf"
      {"continue", 1},
#line 16 "keywords_java.gperf"
      {"byte", 1},
#line 31 "keywords_java.gperf"
      {"float", 1},
      {""},
#line 34 "keywords_java.gperf"
      {"if", 1},
#line 120 "keywords_java.gperf"
      {"Math.abs", 1},
#line 114 "keywords_java.gperf"
      {"System.in", 1},
#line 97 "keywords_java.gperf"
      {"print", 1},
      {""},
#line 44 "keywords_java.gperf"
      {"private", 1},
#line 50 "keywords_java.gperf"
      {"strictfp", 1},
      {""},
#line 29 "keywords_java.gperf"
      {"final", 1},
      {""}, {""},
#line 32 "keywords_java.gperf"
      {"for", 1},
      {""},
#line 118 "keywords_java.gperf"
      {"System.nanoTime", 1},
      {""}, {""}, {""},
#line 139 "keywords_java.gperf"
      {"List", 1},
#line 73 "keywords_java.gperf"
      {"Class", 1},
      {""}, {""},
#line 89 "keywords_java.gperf"
      {"get", 1},
#line 146 "keywords_java.gperf"
      {"ArrayList", 1},
      {""}, {""}, {""},
#line 60 "keywords_java.gperf"
      {"volatile", 1},
#line 54 "keywords_java.gperf"
      {"this", 1},
#line 48 "keywords_java.gperf"
      {"short", 1},
#line 56 "keywords_java.gperf"
      {"throws", 1},
#line 23 "keywords_java.gperf"
      {"default", 1},
#line 42 "keywords_java.gperf"
      {"new", 1},
#line 19 "keywords_java.gperf"
      {"char", 1},
#line 69 "keywords_java.gperf"
      {"Short", 1},
      {""},
#line 67 "keywords_java.gperf"
      {"Boolean", 1},
#line 140 "keywords_java.gperf"
      {"Map", 1},
      {""},
#line 105 "keywords_java.gperf"
      {"sleep", 1},
#line 25 "keywords_java.gperf"
      {"double", 1},
#line 53 "keywords_java.gperf"
      {"synchronized", 1},
#line 130 "keywords_java.gperf"
      {"Math.exp", 1},
      {""}, {""},
#line 125 "keywords_java.gperf"
      {"Math.random", 1},
#line 30 "keywords_java.gperf"
      {"finally", 1},
#line 121 "keywords_java.gperf"
      {"Math.max", 1},
      {""},
#line 172 "keywords_java.gperf"
      {"Collectors", 1},
#line 115 "keywords_java.gperf"
      {"System.exit", 1},
      {""},
#line 175 "keywords_java.gperf"
      {"Consumer", 1},
#line 132 "keywords_java.gperf"
      {"Math.ceil", 1},
#line 133 "keywords_java.gperf"
      {"Math.round", 1},
      {""},
#line 148 "keywords_java.gperf"
      {"TreeMap", 1},
#line 135 "keywords_java.gperf"
      {"StringBuilder", 1},
      {""}, {""},
#line 101 "keywords_java.gperf"
      {"notify", 1},
#line 28 "keywords_java.gperf"
      {"extends", 1},
#line 12 "keywords_java.gperf"
      {"abstract", 1},
#line 100 "keywords_java.gperf"
      {"wait", 1},
#line 131 "keywords_java.gperf"
      {"Math.floor", 1},
      {""},
#line 96 "keywords_java.gperf"
      {"println", 1},
#line 170 "keywords_java.gperf"
      {"Optional", 1},
#line 152 "keywords_java.gperf"
      {"File", 1},
#line 37 "keywords_java.gperf"
      {"instanceof", 1},
      {""}, {""}, {""}, {""},
#line 18 "keywords_java.gperf"
      {"catch", 1},
      {""}, {""},
#line 164 "keywords_java.gperf"
      {"Callable", 1},
#line 59 "keywords_java.gperf"
      {"void", 1},
#line 153 "keywords_java.gperf"
      {"FileReader", 1},
#line 98 "keywords_java.gperf"
      {"printf", 1},
#line 136 "keywords_java.gperf"
      {"StringBuffer", 1},
      {""},
#line 78 "keywords_java.gperf"
      {"Throwable", 1},
#line 154 "keywords_java.gperf"
      {"FileWriter", 1},
      {""},
#line 144 "keywords_java.gperf"
      {"HashMap", 1},
      {""}, {""}, {""}, {""},
#line 14 "keywords_java.gperf"
      {"boolean", 1},
#line 87 "keywords_java.gperf"
      {"add", 1},
      {""},
#line 147 "keywords_java.gperf"
      {"LinkedList", 1},
      {""},
#line 24 "keywords_java.gperf"
      {"do", 1},
      {""}, {""},
#line 51 "keywords_java.gperf"
      {"super", 1},
      {""}, {""},
#line 81 "keywords_java.gperf"
      {"toString", 1},
#line 84 "keywords_java.gperf"
      {"compareTo", 1},
#line 66 "keywords_java.gperf"
      {"Float", 1},
#line 138 "keywords_java.gperf"
      {"Collections", 1},
      {""}, {""},
#line 70 "keywords_java.gperf"
      {"Character", 1},
#line 142 "keywords_java.gperf"
      {"Queue", 1},
      {""}, {""},
#line 129 "keywords_java.gperf"
      {"Math.log", 1},
#line 155 "keywords_java.gperf"
      {"BufferedReader", 1},
#line 159 "keywords_java.gperf"
      {"FileInputStream", 1},
      {""}, {""},
#line 103 "keywords_java.gperf"
      {"run", 1},
#line 102 "keywords_java.gperf"
      {"notifyAll", 1},
      {""}, {""}, {""},
#line 176 "keywords_java.gperf"
      {"Supplier", 1},
#line 40 "keywords_java.gperf"
      {"long", 1},
      {""}, {""},
#line 158 "keywords_java.gperf"
      {"OutputStream", 1},
      {""},
#line 156 "keywords_java.gperf"
      {"BufferedWriter", 1},
#line 61 "keywords_java.gperf"
      {"while", 1},
      {""}, {""},
#line 83 "keywords_java.gperf"
      {"hashCode", 1},
      {""},
#line 55 "keywords_java.gperf"
      {"throw", 1},
      {""}, {""},
#line 166 "keywords_java.gperf"
      {"Executor", 1},
#line 33 "keywords_java.gperf"
      {"goto", 1},
      {""},
#line 71 "keywords_java.gperf"
      {"String", 1},
      {""}, {""}, {""},
#line 167 "keywords_java.gperf"
      {"ExecutorService", 1},
      {""}, {""},
#line 124 "keywords_java.gperf"
      {"Math.pow", 1},
#line 45 "keywords_java.gperf"
      {"protected", 1},
      {""}, {""},
#line 43 "keywords_java.gperf"
      {"package", 1},
#line 163 "keywords_java.gperf"
      {"Runnable", 1},
      {""},
#line 112 "keywords_java.gperf"
      {"System.out", 1},
      {""},
#line 95 "keywords_java.gperf"
      {"hasNext", 1},
      {""},
#line 108 "keywords_java.gperf"
      {"null", 1},
      {""}, {""}, {""}, {""},
#line 117 "keywords_java.gperf"
      {"System.currentTimeMillis", 1},
      {""}, {""}, {""}, {""},
#line 64 "keywords_java.gperf"
      {"Long", 1},
      {""}, {""}, {""}, {""},
#line 76 "keywords_java.gperf"
      {"Exception", 1},
      {""},
#line 75 "keywords_java.gperf"
      {"Thread", 1},
      {""}, {""}, {""}, {""}, {""}, {""},
#line 168 "keywords_java.gperf"
      {"ThreadPoolExecutor", 1},
      {""}, {""},
#line 85 "keywords_java.gperf"
      {"length", 1},
      {""}, {""}, {""}, {""},
#line 46 "keywords_java.gperf"
      {"public", 1},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""}, {""}, {""}, {""},
#line 77 "keywords_java.gperf"
      {"RuntimeException", 1},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""}, {""}, {""}, {""},
#line 165 "keywords_java.gperf"
      {"Future", 1},
      {""}, {""}, {""}, {""},
#line 52 "keywords_java.gperf"
      {"switch", 1},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""}, {""},
#line 174 "keywords_java.gperf"
      {"Function", 1},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""},
#line 160 "keywords_java.gperf"
      {"FileOutputStream", 1}
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
