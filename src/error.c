#include "scl/error.h"
#include "scl/types.h"

char *scl_error_to_str(SclError err) {
  switch (err) {
  case SCL_ERR_BUFFER:
    return "Buffer error";
  case SCL_ERR_FILE_OPEN:
    return "File open error";
  case SCL_OK:
    return NULL;
  default:
    return "Unknown error";
  }
}
