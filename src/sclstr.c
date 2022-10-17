#include "sclstr.h"
#include <stdlib.h>
#include <string.h>
#include "sclmem.h"
#include "sclalloc.h"

Str str_init(char *s, const usize len) { // NOLINT
  Str n = {s, len};

  return n;
}

bool str_eq(const Str left, const Str right) {
  if (left.len != right.len) {
    return FALSE;
  }

  return scl_strncmp(left.raw, right.raw, left.len) == 0;
}

bool str_eq_raw(const Str left, char *right) {
  return str_eq(left, str_init(right, scl_strlen(right)));
}

char *str_from_alloc(const char *d, SclAlloc a) {
  char *s = a.malloc(scl_strlen(d) + 1);
  scl_strncpy(s, d, scl_strlen(d));
  return s;
}

char *str_from(const char *d) { return str_from_alloc(d, scl_default_alloc()); }

char *str_to_str_alloc(const Str s, SclAlloc a) {
  char *n = a.malloc(s.len + 1);
  scl_memset(n, 0, s.len + 1);
  scl_strncpy(n, s.raw, s.len);

  return n;
}

char *str_to_str(const Str s) {
  return str_to_str_alloc(s, scl_default_alloc());
}

void str_free_alloc(const Str s, SclAlloc a) { a.free(s.raw); }

void str_free(const Str s) { str_free_alloc(s, scl_default_alloc()); }

bool str_starts_with_raw(const Str s, char *with) {
  usize len = scl_strlen(with);
  if (s.len < len) {
    return FALSE;
  }
  // now we just init 2 strings with the lenght of with and
  // then compare
  Str s1 = str_init(s.raw, len);
  Str s2 = str_init(with, len);

  return str_eq(s1, s2);
}

bool str_is_end(const Str s, const char *p) { return s.raw + s.len == p; }

usize scl_strlen(const char *str) { return strlen(str); }

char *scl_strncpy(char *d, const char *s, usize l) { return strncpy(d, s, l); }

i32 scl_strncmp(const char *d, const char *s, usize l) {
  return strncmp(d, s, l);
}
