#include "scllog.h"
#include <stdarg.h>
#include <stdio.h>

LogLevel LOG_LEVEL = OUTPUT;

void scl_log_set_level(LogLevel level) { LOG_LEVEL = level; }

int scl_log_fprintf(void *f, const LogLevel level, const char *format, ...) {
  va_list argptr;
  va_start(argptr, format);

  if (level > LOG_LEVEL) {
    return 0;
  }
  int len = vfprintf(f, format, argptr);

  va_end(argptr);

  return len;
}
