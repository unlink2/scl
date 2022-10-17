#ifndef SCLBUFFER_H_
#define SCLBUFFER_H_

#include "error.h"
#include "sclalloc.h"
#include "sclstr.h"
#include "types.h"

// A buffer is an expanding wrapper
// around Str that allows auto-resizing
typedef struct StrBuffer {
  Str str;

  // where is the buffer currently at?
  usize cap;
  SclError err;

  SclAlloc alloc;
} StrBuffer;

StrBuffer strbuf_init_alloc(usize len, SclAlloc alloc);
StrBuffer strbuf_init(usize len);

// Resize buffer and copy from old to new location
void strbuf_resize(StrBuffer *buffer, usize len);

// get next len for buffer
usize strbuf_next_len(StrBuffer *buffer);

// Returns true if the next wite would overflow the buffer
bool strbuf_full(StrBuffer *buffer);

void strbuf_write(StrBuffer *buffer, char c);

void strbuf_append_raw(StrBuffer *buffer, char *s);

void strbuf_clear(StrBuffer *buffer);

void strbuf_free(StrBuffer *buffer);

#ifdef TEST

void test_strbuf_resize(void **state);

#endif
#endif
