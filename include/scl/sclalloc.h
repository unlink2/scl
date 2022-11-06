#ifndef SCL_ALLOC_H_
#define SCL_ALLOC_H_

#include "scl/types.h"

typedef void *(*SclMalloc)(usize);
typedef void (*SclFree)(void *);

typedef struct SclAlloc {
  SclMalloc malloc;
  SclFree free;
} SclAlloc;

SclAlloc scl_alloc_init(SclMalloc malloc, SclFree free);

SclAlloc scl_default_alloc();

#endif
