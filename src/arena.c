#include "scl/arena.h"

#define align(n) ((n) + (sizeof(usize) - ((n) % sizeof(usize))))

SclArena scl_arena_init(SclAlloc *alloc, usize len) {
  SclArena a;

  // make sure the heap is aligned!
  a.heap = alloc->malloc(len);
  a.current = 0;
  a.len = len;
  a.alloc = alloc;

  return a;
}

void scl_arena_align(SclArena *a, usize n) {
  // make sure both current and current+heap are aligned correctly!
  while ((usize)(a->current + (u8 *)a->heap) % n != 0) {
    a->current++;
  }
}

void *scl_arena_malloc(SclArena *a, usize len) {
  // scl_arena_align(a, (len + 7) / 8);
  //  out of space
  if (a->current + len >= a->len) {
    return NULL;
  }

  void *next = (u8 *)a->heap + a->current;
  a->current += len;
  return next;
}

void *scl_arena_calloc(SclArena *a, usize len, usize stride) {
  return scl_arena_malloc(a, len * stride);
}

void scl_arena_clear(SclArena *a) { a->current = 0; }

void scl_arena_free(SclArena *a) { a->alloc->free(a->heap); }
