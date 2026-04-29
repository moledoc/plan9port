/* C code produced by gperf version 3.0.3 */
/* Command-line: /Library/Developer/CommandLineTools/usr/bin/gperf -C -E -t -L C -N in_word_set_go keywords_go.gperf  */
/* Computed positions: -k'1-2,4,7,11,$' */

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

#line 1 "keywords_go.gperf"

#include <string.h>
#line 5 "keywords_go.gperf"
# generate c code with gperf:
# gperf -C -E -t -L C -N in_word_set_go keywords_go.gperf > keywords_go_hash.c

struct keyword_go { const char *name; };
/* maximum key range = 261, duplicates = 0 */

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
      269, 269, 269, 269, 269, 269, 269, 269, 269, 269,
      269, 269, 269, 269, 269, 269, 269, 269, 269, 269,
      269, 269, 269, 269, 269, 269, 269, 269, 269, 269,
      269, 269, 269, 269, 269, 269, 269, 269, 269, 269,
      269, 269, 269, 269, 269, 269,  20, 269, 269,  20,
       20,   5,   0, 269,  15, 269,   0, 269, 269, 269,
      269, 269, 269, 269, 269,  10, 269,  55, 269,  10,
      269,  70, 269, 269, 269, 269,  25, 269,  75,   0,
      269, 269,  10,  35, 269,  10, 269,  10, 269, 269,
      269, 269, 269, 269, 269, 269, 269,  15,  35,  65,
      105,  10,  10,  60,  55,   5,   5,  10,  10,  30,
        0,  15,  90,  55,   0,  15,   0,   5,  55,  85,
       10,  55, 269, 269, 269, 269, 269, 269, 269, 269,
      269, 269, 269, 269, 269, 269, 269, 269, 269, 269,
      269, 269, 269, 269, 269, 269, 269, 269, 269, 269,
      269, 269, 269, 269, 269, 269, 269, 269, 269, 269,
      269, 269, 269, 269, 269, 269, 269, 269, 269, 269,
      269, 269, 269, 269, 269, 269, 269, 269, 269, 269,
      269, 269, 269, 269, 269, 269, 269, 269, 269, 269,
      269, 269, 269, 269, 269, 269, 269, 269, 269, 269,
      269, 269, 269, 269, 269, 269, 269, 269, 269, 269,
      269, 269, 269, 269, 269, 269, 269, 269, 269, 269,
      269, 269, 269, 269, 269, 269, 269, 269, 269, 269,
      269, 269, 269, 269, 269, 269, 269, 269, 269, 269,
      269, 269, 269, 269, 269, 269, 269, 269, 269, 269,
      269, 269, 269, 269, 269, 269
    };
  register unsigned int hval = len;

  switch (hval)
    {
      default:
        hval += asso_values[(unsigned char)str[10]];
      /*FALLTHROUGH*/
      case 10:
      case 9:
      case 8:
      case 7:
        hval += asso_values[(unsigned char)str[6]];
      /*FALLTHROUGH*/
      case 6:
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
in_word_set_go (str, len)
     register const char *str;
     register unsigned int len;
{
  enum
    {
      TOTAL_KEYWORDS = 134,
      MIN_WORD_LENGTH = 2,
      MAX_WORD_LENGTH = 19,
      MIN_HASH_VALUE = 8,
      MAX_HASH_VALUE = 268
    };

  static const # generate c code with gperf: wordlist[] =
    {
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
#line 45 "keywords_go.gperf"
      {"int", 1},
#line 46 "keywords_go.gperf"
      {"int8", 1},
      {""}, {""}, {""}, {""},
#line 52 "keywords_go.gperf"
      {"uint", 1},
#line 53 "keywords_go.gperf"
      {"uint8", 1},
#line 56 "keywords_go.gperf"
      {"uint64", 1},
#line 57 "keywords_go.gperf"
      {"uintptr", 1},
#line 62 "keywords_go.gperf"
      {"nil", 1},
      {""}, {""},
#line 35 "keywords_go.gperf"
      {"return", 1},
      {""},
#line 71 "keywords_go.gperf"
      {"len", 1},
#line 59 "keywords_go.gperf"
      {"true", 1},
#line 49 "keywords_go.gperf"
      {"int64", 1},
#line 21 "keywords_go.gperf"
      {"struct", 1},
#line 29 "keywords_go.gperf"
      {"if", 1},
#line 33 "keywords_go.gperf"
      {"for", 1},
#line 50 "keywords_go.gperf"
      {"rune", 1},
#line 42 "keywords_go.gperf"
      {"error", 1},
#line 54 "keywords_go.gperf"
      {"uint16", 1},
#line 78 "keywords_go.gperf"
      {"recover", 1},
      {""},
#line 77 "keywords_go.gperf"
      {"real", 1},
#line 48 "keywords_go.gperf"
      {"int32", 1},
#line 55 "keywords_go.gperf"
      {"uint32", 1},
#line 88 "keywords_go.gperf"
      {"os.Open", 1},
#line 123 "keywords_go.gperf"
      {"time.Duration", 1},
#line 98 "keywords_go.gperf"
      {"io.Writer", 1},
#line 122 "keywords_go.gperf"
      {"time.Since", 1},
#line 16 "keywords_go.gperf"
      {"select", 1},
#line 44 "keywords_go.gperf"
      {"float64", 1},
      {""},
#line 23 "keywords_go.gperf"
      {"else", 1},
#line 47 "keywords_go.gperf"
      {"int16", 1},
      {""},
#line 90 "keywords_go.gperf"
      {"os.Exit", 1},
      {""},
#line 15 "keywords_go.gperf"
      {"interface", 1},
#line 121 "keywords_go.gperf"
      {"time.Parse", 1},
      {""},
#line 108 "keywords_go.gperf"
      {"strings.Join", 1},
#line 160 "keywords_go.gperf"
      {"filepath.Join", 1},
#line 61 "keywords_go.gperf"
      {"iota", 1},
#line 60 "keywords_go.gperf"
      {"false", 1},
#line 34 "keywords_go.gperf"
      {"import", 1},
      {""},
#line 107 "keywords_go.gperf"
      {"strings.Split", 1},
#line 151 "keywords_go.gperf"
      {"json.Unmarshal", 1},
#line 111 "keywords_go.gperf"
      {"strings.ToUpper", 1},
#line 153 "keywords_go.gperf"
      {"log.Println", 1},
      {""},
#line 161 "keywords_go.gperf"
      {"filepath.Base", 1},
#line 154 "keywords_go.gperf"
      {"log.Fatal", 1},
#line 12 "keywords_go.gperf"
      {"break", 1},
#line 106 "keywords_go.gperf"
      {"strings.Contains", 1},
#line 112 "keywords_go.gperf"
      {"strings.TrimSpace", 1},
#line 158 "keywords_go.gperf"
      {"regexp.MustCompile", 1},
#line 72 "keywords_go.gperf"
      {"make", 1},
#line 155 "keywords_go.gperf"
      {"log.Printf", 1},
      {""},
#line 150 "keywords_go.gperf"
      {"json.Marshal", 1},
#line 36 "keywords_go.gperf"
      {"var", 1},
#line 38 "keywords_go.gperf"
      {"bool", 1},
#line 110 "keywords_go.gperf"
      {"strings.ToLower", 1},
#line 80 "keywords_go.gperf"
      {"fmt.Println", 1},
#line 93 "keywords_go.gperf"
      {"os.Args", 1},
      {""},
#line 31 "keywords_go.gperf"
      {"type", 1},
#line 83 "keywords_go.gperf"
      {"fmt.Errorf", 1},
      {""},
#line 43 "keywords_go.gperf"
      {"float32", 1},
#line 84 "keywords_go.gperf"
      {"fmt.Scan", 1},
#line 95 "keywords_go.gperf"
      {"os.Stderr", 1},
#line 81 "keywords_go.gperf"
      {"fmt.Printf", 1},
#line 51 "keywords_go.gperf"
      {"string", 1},
      {""},
#line 164 "keywords_go.gperf"
      {"flag.Int", 1},
#line 94 "keywords_go.gperf"
      {"os.Stdout", 1},
#line 30 "keywords_go.gperf"
      {"range", 1},
#line 82 "keywords_go.gperf"
      {"fmt.Sprintf", 1},
#line 19 "keywords_go.gperf"
      {"go", 1},
#line 104 "keywords_go.gperf"
      {"bufio.Scanner", 1},
#line 85 "keywords_go.gperf"
      {"fmt.Scanf", 1},
#line 75 "keywords_go.gperf"
      {"print", 1},
      {""},
#line 76 "keywords_go.gperf"
      {"println", 1},
#line 73 "keywords_go.gperf"
      {"new", 1},
#line 143 "keywords_go.gperf"
      {"context.WithTimeout", 1},
#line 27 "keywords_go.gperf"
      {"const", 1},
      {""}, {""},
#line 32 "keywords_go.gperf"
      {"continue", 1},
#line 17 "keywords_go.gperf"
      {"case", 1},
#line 66 "keywords_go.gperf"
      {"close", 1},
      {""}, {""},
#line 142 "keywords_go.gperf"
      {"context.WithCancel", 1},
#line 24 "keywords_go.gperf"
      {"goto", 1},
      {""}, {""}, {""},
#line 131 "keywords_go.gperf"
      {"math.Min", 1},
#line 39 "keywords_go.gperf"
      {"byte", 1},
#line 165 "keywords_go.gperf"
      {"flag.Parse", 1},
      {""}, {""}, {""},
#line 89 "keywords_go.gperf"
      {"os.Create", 1},
#line 128 "keywords_go.gperf"
      {"math.Floor", 1},
      {""}, {""},
#line 119 "keywords_go.gperf"
      {"time.Now", 1},
#line 22 "keywords_go.gperf"
      {"chan", 1},
#line 120 "keywords_go.gperf"
      {"time.Sleep", 1},
      {""}, {""},
#line 133 "keywords_go.gperf"
      {"rand.Int", 1},
#line 129 "keywords_go.gperf"
      {"math.Ceil", 1},
#line 18 "keywords_go.gperf"
      {"defer", 1},
      {""}, {""},
#line 130 "keywords_go.gperf"
      {"math.Max", 1},
#line 86 "keywords_go.gperf"
      {"fmt.Sscan", 1},
#line 103 "keywords_go.gperf"
      {"bufio.NewWriter", 1},
      {""},
#line 13 "keywords_go.gperf"
      {"default", 1},
#line 20 "keywords_go.gperf"
      {"map", 1},
#line 92 "keywords_go.gperf"
      {"os.Setenv", 1},
      {""},
#line 69 "keywords_go.gperf"
      {"delete", 1},
#line 25 "keywords_go.gperf"
      {"package", 1},
      {""},
#line 97 "keywords_go.gperf"
      {"io.Reader", 1},
#line 102 "keywords_go.gperf"
      {"bufio.NewReader", 1},
      {""}, {""}, {""},
#line 14 "keywords_go.gperf"
      {"func", 1},
#line 109 "keywords_go.gperf"
      {"strings.Replace", 1},
      {""}, {""},
#line 116 "keywords_go.gperf"
      {"strconv.ParseFloat", 1},
#line 139 "keywords_go.gperf"
      {"sync.Once", 1},
#line 100 "keywords_go.gperf"
      {"io.ReadAll", 1},
#line 28 "keywords_go.gperf"
      {"fallthrough", 1},
#line 134 "keywords_go.gperf"
      {"rand.Float64", 1},
#line 125 "keywords_go.gperf"
      {"math.Abs", 1},
#line 70 "keywords_go.gperf"
      {"imag", 1},
#line 137 "keywords_go.gperf"
      {"sync.Mutex", 1},
#line 26 "keywords_go.gperf"
      {"switch", 1},
#line 117 "keywords_go.gperf"
      {"strconv.ParseBool", 1},
#line 145 "keywords_go.gperf"
      {"http.Get", 1},
#line 126 "keywords_go.gperf"
      {"math.Sqrt", 1},
      {""}, {""},
#line 114 "keywords_go.gperf"
      {"strconv.Atoi", 1},
      {""},
#line 146 "keywords_go.gperf"
      {"http.Post", 1},
      {""}, {""}, {""},
#line 65 "keywords_go.gperf"
      {"cap", 1},
#line 91 "keywords_go.gperf"
      {"os.Getenv", 1},
      {""}, {""},
#line 115 "keywords_go.gperf"
      {"strconv.Itoa", 1},
      {""},
#line 147 "keywords_go.gperf"
      {"http.ListenAndServe", 1},
#line 74 "keywords_go.gperf"
      {"panic", 1},
      {""}, {""},
#line 157 "keywords_go.gperf"
      {"regexp.MatchString", 1},
      {""}, {""}, {""}, {""}, {""},
#line 40 "keywords_go.gperf"
      {"complex64", 1},
#line 41 "keywords_go.gperf"
      {"complex128", 1},
      {""},
#line 99 "keywords_go.gperf"
      {"io.Copy", 1},
      {""},
#line 68 "keywords_go.gperf"
      {"copy", 1},
      {""}, {""},
#line 67 "keywords_go.gperf"
      {"complex", 1},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""},
#line 127 "keywords_go.gperf"
      {"math.Pow", 1},
      {""}, {""},
#line 163 "keywords_go.gperf"
      {"flag.String", 1},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""}, {""}, {""},
#line 64 "keywords_go.gperf"
      {"append", 1},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
#line 135 "keywords_go.gperf"
      {"rand.Seed", 1},
      {""}, {""}, {""}, {""}, {""},
#line 148 "keywords_go.gperf"
      {"http.HandleFunc", 1},
      {""}, {""}, {""},
#line 138 "keywords_go.gperf"
      {"sync.WaitGroup", 1},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""}, {""},
#line 141 "keywords_go.gperf"
      {"context.Background", 1}
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
