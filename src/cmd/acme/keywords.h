#ifndef KEYWORDS_H
#define KEYWORDS_H

#include <stddef.h>
#include "keywords_codetags.h"
#include "keywords_c.h"
#include "keywords_go.h"
#include "keywords_python.h"
#include "keywords_java.h"
#include "keywords_sql.h"
#include "keywords_js.h"

struct keyword {
    const char *name;
};

const struct keyword *in_word_set_codetags(const char *str, size_t len);
const struct keyword *in_word_set_c(const char *str, size_t len);
const struct keyword *in_word_set_go(const char *str, size_t len);
const struct keyword *in_word_set_python(const char *str, size_t len);
const struct keyword *in_word_set_java(const char *str, size_t len);
const struct keyword *in_word_set_sql(const char *str, size_t len);
const struct keyword *in_word_set_js(const char *str, size_t len);

#endif // KEYWORDS_H