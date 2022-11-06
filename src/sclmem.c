#include "scl/sclmem.h"
#include <string.h>

void *scl_memcpy(void *dest, const void *src, usize n) {
  return memcpy(dest, src, n);
}

void *scl_memset(void *ptr, const u8 value, usize n) {
  return memset(ptr, value, n);
}
