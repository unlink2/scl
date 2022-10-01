#ifndef SCL_ERROR_H_
#define SCL_ERROR_H_

typedef enum SclError {
  SCL_OK,
  SCL_ERR_BUFFER,
  SCL_ERR_UNKNOWN,
  SCL_ERR_FILE_OPEN,
} SclError;

char *scl_error_to_str(SclError err);

#endif