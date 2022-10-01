#include "sclmem.h"

void *scl_memcpy(void *dest, const void *src, usize n) {
  char *dp = dest;
  const char *sp = src;
  while (n--) {
    *dp++ = *sp++;
  }
  return dest;
}

void *scl_memset(void *ptr, const u8 value, usize n) {
  for (int i = 0; i < n; i++) {
    ((u8 *)(ptr))[i] = value;
  }
  return ptr;
}
