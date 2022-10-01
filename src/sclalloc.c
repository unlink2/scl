#include "sclalloc.h"

SclAlloc alloc_init(SclMalloc malloc, SclFree free) {
  SclAlloc alloc = {malloc, free};

  return alloc;
}
