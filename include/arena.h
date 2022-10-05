#ifndef ARENA_H_
#define ARENA_H_

#include <scl/scl.h>
#include <scl/types.h>

/**
 * SclArena allocator
 * Simple operations.
 * It is not possible to free random memory from the arena allocator.
 * It is not intended for fragment free allocation!
 */

typedef struct SclArena {
  void *heap;
  usize len;
  usize current;
  SclAlloc *alloc;
} SclArena;

// Create the arena
SclArena scl_arena_init(SclAlloc *alloc, usize len);

// Align the current address to n
void scl_arena_align(SclArena *a, usize n);

// SclAllocate memory from the arena
void *scl_arena_malloc(SclArena *a, usize len);
void *scl_arena_calloc(SclArena *a, usize len, usize stride);

// Free the arena
void scl_arena_clear(SclArena *a);

void scl_arena_free(SclArena *a);

#endif
