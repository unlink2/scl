#include "sclalloc.h"

SclAlloc scl_alloc_init(SclMalloc malloc, SclFree free) {
  SclAlloc alloc = {malloc, free};

  return alloc;
}
