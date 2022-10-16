#ifndef SCLLOG_H_
#define SCLLOG_H_

#define str_fmt "%.*s"
#define str_out(str) str.len, str.raw

#include <stdio.h>

#define sclerr stderr 
#define sclout stdout 
#define sclin stdin

typedef enum LogLevel { OUTPUT, ERROR, INFO, DEBUG, LOG_LEVEL_LEN } LogLevel;

void scl_log_set_level(LogLevel level);

int scl_log_fprintf(void *f, const LogLevel level, const char *format, ...);

#endif
