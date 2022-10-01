#ifndef SCL_MEM_H_
#define SCL_MEM_H_

#include "types.h"

void *scl_memcpy(void *dest, const void *src, usize n);

void *scl_memset(void *ptr, const u8 value, usize n);

#endif
