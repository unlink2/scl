#ifndef SCLLOG_H_
#define SCLLOG_H_

#define str_fmt "%.*s"
#define str_out(str) str.len, str.raw

#define sclerr scl_err()
#define sclout scl_out()
#define sclin scl_in()

typedef enum LogLevel { OUTPUT, ERROR, INFO, DEBUG, LOG_LEVEL_LEN } LogLevel;

void scl_log_set_level(LogLevel level);

int scl_log_fprintf(void *f, const LogLevel level, const char *format, ...);

void *scl_err();
void *scl_out();
void *scl_in();

#define scl_log_(level, format, ...) scl_log_fprintf(sclerr, level, __VA_ARGS__)
#define scl_log_debug(format, ...) scl_log_(DEBUG, format, __VA_ARGS__)
#define scl_log_output(format, ...) scl_log_(OUTPUT, format, __VA_ARGS__)
#define scl_log_info(format, ...) scl_log_(INFO, format, __VA_ARGS__)
#define scl_log_error(format, ...) scl_log_(ERROR, format, __VA_ARGS__)

#endif
