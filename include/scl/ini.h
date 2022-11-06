#ifndef INI_H_
#define INI_H_

#include "scl/sclstr.h"
#include "scl/error.h"

typedef struct SclIni SclIni;
typedef int (*SclOnIniVal)(SclIni *ini, Str key, Str val);
typedef int (*SclOnIniSec)(SclIni *ini, Str name);

typedef struct SclIni {
  SclOnIniVal on_val;
  SclOnIniSec on_sec;
  Str section;
} SclIni;

typedef struct SclIniRes {
  // hoow many bytes were parsed?
  usize parsed;
  SclError err;
  int usr_err;
} SclIniRes;

SclIni scl_ini_init(SclOnIniVal on_val, SclOnIniSec on_sec);

// Parses the entire ini file until the input string is exhausted
// or an error occurs
SclIniRes scl_ini_parse(SclIni *ini, Str data);

// Attempts to parse the next section or key-value pair in the data
// Calls on_val and on_sec, returns an error code when any error occurs
SclIniRes scl_ini_next(SclIni *ini, Str data);

#ifdef TEST

void test_ini_parse(void **state);

#endif
#endif
