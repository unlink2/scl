#include "scl/sclalloc.h"
#include <stdlib.h>

SclAlloc scl_alloc_init(SclMalloc malloc, SclFree free) {
  SclAlloc alloc = {malloc, free};

  return alloc;
}

SclAlloc scl_default_alloc() { return scl_alloc_init(malloc, free); }
