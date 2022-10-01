#ifndef SCLLOG_H_
#define SCLLOG_H_

typedef enum LogLevel { OUTPUT, ERROR, INFO, DEBUG, LOG_LEVEL_LEN } LogLevel;

void scl_log_set_level(LogLevel level);

int scl_log_fprintf(void *f, const LogLevel level, const char *format, ...);

#endif
