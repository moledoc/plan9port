#ifndef KEYWORDS_H
#define KEYWORDS_H

#include <stddef.h>

struct keyword {
    const char *name;
    int token;
};

const struct keyword *in_word_set_codetags(const char *str, size_t len);
const struct keyword *in_word_set_c(const char *str, size_t len);
const struct keyword *in_word_set_go(const char *str, size_t len);
const struct keyword *in_word_set_python(const char *str, size_t len);
const struct keyword *in_word_set_java(const char *str, size_t len);

#endif