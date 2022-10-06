#ifndef SCLSTR_H_
#define SCLSTR_H_

#include "types.h"

typedef struct Str {
  char *raw;
  usize len;
} Str;

// Create an unmanaged tr string from an existing pointer
// You supply the data!
Str str_init(char *s, const usize len);

// Compare a str for equality
bool str_eq(const Str left, const Str right);

bool str_eq_raw(const Str left, char *right);

// Returns whether the char pointer is the end of the Str
bool str_is_end(const Str s, const char *p);

// create an owned C string copy from the input string
char *str_from(const char *d);

// convert a str to a malloced c-string
char *str_to_str(const Str s);

bool str_starts_with_raw(const Str s, char *with);

#endif
