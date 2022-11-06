#ifndef SCLSTR_H_
#define SCLSTR_H_

#include "scl/sclalloc.h"
#include "scl/types.h"
#include "scl/error.h"

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
char *str_from_alloc(const char *d, SclAlloc a);
char *str_from(const char *d);

// convert a str to a malloced c-string
char *str_to_str_alloc(const Str s, SclAlloc a);
char *str_to_str(const Str s);

void str_free_alloc(const Str s, SclAlloc a);
void str_free(const Str s);

bool str_starts_with_raw(const Str s, char *with);

usize scl_strlen(const char *str);
char *scl_strncpy(char *d, const char *s, usize l);
i32 scl_strncmp(const char *d, const char *s, usize l);

i64 str_to_i64_alloc(const Str so, const i32 base, SclError *error,
                     SclAlloc alloc);
i64 str_to_i64(const Str s, const i32 base, SclError *error);

#endif
