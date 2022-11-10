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

int scl_putchar(char c);

void *scl_err();
void *scl_out();
void *scl_in();

#define scl_log_(level, ...) scl_log_fprintf(sclerr, level, __VA_ARGS__)
#define scl_log_debug(...) scl_log_(DEBUG, __VA_ARGS__)
#define scl_log_output(...) scl_log_fprintf(sclout, OUTPUT, __VA_ARGS__)
#define scl_log_info(...) scl_log_(INFO, __VA_ARGS__)
#define scl_log_error(...) scl_log_(ERROR, __VA_ARGS__)

#endif
