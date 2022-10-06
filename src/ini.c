#include "ini.h"
#include <ctype.h>

bool is_end(char c) { return c == '\0' || c == '\n' || c == '\r'; }

char *skip_whitespace(char *input) {
  // skip leading whitespaces
  while (isspace(input[0])) {
    input++;
  }

  return input;
}

char *skip_comment(char *input) {
  input = skip_whitespace(input);
  while (input[0] == '#') {
    // loop until next line
    while (input[0] != '\n' && !is_end(input[0])) {
      input++;
    }
    input = skip_whitespace(input);
  }
  return input;
}

SclIni scl_ini_init(SclOnIniVal on_val, SclOnIniSec on_sec) {
  SclIni ini = {on_val, on_sec};

  return ini;
}

SclIniRes scl_ini_parse(SclIni *ini, Str data) {
  SclIniRes res = {0, SCL_OK};

  return res;
}

SclIniRes scl_ini_next(SclIni *ini, Str data) {
  const char sep = '=';
  SclIniRes res = {0, SCL_OK};

  char *current = data.raw;

  current = skip_whitespace(current);
  current = skip_comment(current);

  if (str_is_end(data, current)) {
    res.err = SCL_OK;
    return res;
  }

  // parse section or key=value
  if (*current != '[') {

    Str key;
    key.raw = data.raw;
    key.len = 0;

    while (!is_end(*current) && *current != sep && !str_is_end(data, current)) {
      key.len++;
      current++;
    }

    if (*current != '=') {
      res.err = SCL_ERR_INI_NO_VALUE;
      return res;
    }
    current++;

    Str value;
    value.raw = current;
    value.len = 0;

    while (!is_end(*current) && *current != sep && !str_is_end(data, current)) {
      value.len++;
      current++;
    }
    ini->on_val(key, value);
  } else {
    Str section;
    section.raw = current;
    section.len = 0;
    while (!is_end(*current) && *current != ']' && !str_is_end(data, current)) {
      current++;
      section.len++;
    }

    ini->on_sec(section);
  }
  res.parsed = current - data.raw;
  return res;
}

#ifdef TEST

void test_ini_parse(void **state) {}

#endif
