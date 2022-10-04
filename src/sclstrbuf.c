#include "sclstrbuf.h"
#include "macros.h"
#include <stdlib.h>
#include <string.h>
#include "sclmem.h"

StrBuffer strbuf_init(usize len) {
  StrBuffer buffer;
  scl_memset(&buffer, 0, sizeof(StrBuffer));

  buffer.str.raw = malloc(len);
  buffer.str.len = 0;
  scl_memset(buffer.str.raw, 0, len);

  buffer.cap = len;
  return buffer;
}

void strbuf_resize(StrBuffer *buffer, usize len) {
  char *old = buffer->str.raw;
  usize old_len = buffer->cap;

  // new buffeer
  buffer->str.raw = malloc(len);
  scl_memset(buffer->str.raw, 0, len);
  buffer->cap = len;

  if (old) {
    memcpy(buffer->str.raw, old, MIN(old_len, len));
    free(old);
  }
}

usize strbuf_next_len(StrBuffer *buffer) { return buffer->cap * 2; }

bool strbuf_full(StrBuffer *buffer) {
  return buffer->str.len >= buffer->cap - 1;
}

void strbuf_write(StrBuffer *buffer, char c) {
  if (strbuf_full(buffer)) {
    strbuf_resize(buffer, strbuf_next_len(buffer));
  }
  buffer->str.raw[buffer->str.len++] = c;
}

void strbuf_append_raw(StrBuffer *buffer, char *s) {
  while (*s != '\0') {
    strbuf_write(buffer, *s);
    s++;
  }
}

void strbuf_clear(StrBuffer *buffer) { buffer->str.len = 0; }

void strbuf_free(StrBuffer *buffer) {
  if (buffer->str.raw) {
    free(buffer->str.raw);
  }
}

#ifdef TEST

#include "macros.h"

void test_strbuf_resize(void **state) {
  StrBuffer b = strbuf_init(4);

  assert_int_equal(4, b.cap);
  assert_int_equal(0, b.str.len);

  for (int i = 0; i < 10; i++) {
    strbuf_write(&b, '0' + i);
  }

  // should have resized twice!
  assert_int_equal(16, b.cap);
  assert_int_equal(10, b.str.len);
  assert_true(str_eq_raw(b.str, "0123456789"));

  strbuf_free(&b);
}

#endif
