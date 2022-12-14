#include "scl/ini.h"
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

int scl_ini_on_value_default(SclIni *ini, Str key, Str vale) { return 0; }

int scl_ini_on_section_default(SclIni *ini, Str section) { return 0; }

SclIni scl_ini_init(SclOnIniVal on_val, SclOnIniSec on_sec) {
  SclIni ini = {on_val, on_sec};

  ini.section = str_init("[default]", 9);

  if (ini.on_val == NULL) {
    ini.on_val = scl_ini_on_value_default;
  }
  if (ini.on_sec == NULL) {
    ini.on_sec = scl_ini_on_section_default;
  }

  return ini;
}

SclIniRes scl_ini_parse(SclIni *ini, Str data) {
  SclIniRes res = {0, SCL_OK, 0};
  SclIniRes r;
  do {
    r = scl_ini_next(ini, data);
    data.raw += r.parsed;
    data.len -= r.parsed;

    res.parsed += r.parsed;
  } while ((r.err == SCL_OK && r.parsed != 0));
  res.err = r.err;

  return res;
}

SclIniRes scl_ini_next(SclIni *ini, Str data) {
  const char sep = '=';
  const char sec_start = '[';
  const char sec_end = ']';
  SclIniRes res = {0, SCL_OK, 0};

  char *current = data.raw;

  current = skip_whitespace(current);
  current = skip_comment(current);

  if (str_is_end(data, current)) {
    res.err = SCL_OK;
    return res;
  }

  // parse section or key=value
  if (*current != sec_start) {

    Str key;
    key.raw = current;
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

    if (key.len != 0) {
      res.usr_err = ini->on_val(ini, key, value);
    }
  } else {
    Str section;
    section.raw = current;
    section.len = 0;
    while (!is_end(*current) && *current != sec_end &&
           !str_is_end(data, current)) {
      current++;
      section.len++;
    }
    if (*current != sec_end) {
      res.err = SCL_ERR_INI_UNTERMINATED_SECTION;
      return res;
    }
    current++;
    section.len++;

    if (section.len != 0) {
      ini->section = section;
      res.usr_err = ini->on_sec(ini, section);
    }
  }
  res.parsed = current - data.raw;
  if (res.usr_err) {
    res.err = SCL_ERR_USR;
  }
  return res;
}

#ifdef TEST

#include <string.h>
#include "scl/macros.h"

typedef struct TestSclIni {
  SclIni ini;
  char *key;
  char *value;
  char *section;
} TestSclIni;

int test_on_value(SclIni *ini, Str key, Str value) {
  TestSclIni *i = (TestSclIni *)ini;

  if (i->key != NULL) {
    assert_int_equal(scl_strlen(i->key), key.len);
    assert_true(str_eq_raw(key, i->key));
  }

  if (i->value != NULL) {
    assert_int_equal(scl_strlen(i->value), value.len);
    assert_true(str_eq_raw(value, i->value));
  }

  return 0;
}

int test_on_section(SclIni *ini, Str sec) {
  TestSclIni *i = (TestSclIni *)ini;

  if (i->section != NULL) {
    assert_int_equal(scl_strlen(i->section), sec.len);
    assert_true(str_eq_raw(sec, i->section));
  }

  return 0;
}

void test_ini_parse(void **state) {
  // ok value
  {
    Str test;
    test.raw = "key=value";
    test.len = scl_strlen(test.raw);

    TestSclIni i;
    i.ini = scl_ini_init(test_on_value, test_on_section);
    i.key = "key";
    i.value = "value";
    i.section = "test";

    SclIniRes r = scl_ini_next((SclIni *)&i, test);
    assert_int_equal(SCL_OK, r.err);
    assert_int_equal(scl_strlen(test.raw), r.parsed);
    assert_true(str_eq_raw(i.ini.section, "[default]"));
  }
  // ok section
  {
    Str test;
    test.raw = "[test]";
    test.len = scl_strlen(test.raw);

    TestSclIni i;
    i.ini = scl_ini_init(test_on_value, test_on_section);
    i.key = "key";
    i.value = "value";
    i.section = "[test]";

    SclIniRes r = scl_ini_next((SclIni *)&i, test);
    assert_int_equal(SCL_OK, r.err);
    assert_int_equal(scl_strlen(test.raw), r.parsed);
    assert_true(str_eq_raw(i.ini.section, "[test]"));
  }

  // fail value
  {
    Str test;
    test.raw = "key";
    test.len = scl_strlen(test.raw);

    TestSclIni i;
    i.ini = scl_ini_init(test_on_value, test_on_section);

    SclIniRes r = scl_ini_next((SclIni *)&i, test);
    assert_int_equal(SCL_ERR_INI_NO_VALUE, r.err);
  }
  // fail section
  {
    Str test;
    test.raw = "[test";
    test.len = scl_strlen(test.raw);

    TestSclIni i;
    i.ini = scl_ini_init(test_on_value, test_on_section);

    SclIniRes r = scl_ini_next((SclIni *)&i, test);
    assert_int_equal(SCL_ERR_INI_UNTERMINATED_SECTION, r.err);
  }
  // complete
  {
    Str test;
    test.raw = "[test]\nkey=value\ntest=123\n # comment\n scl=test";
    test.len = scl_strlen(test.raw);

    TestSclIni i;
    i.ini = scl_ini_init(test_on_value, test_on_section);
    i.key = NULL;
    i.value = NULL;
    i.section = NULL;

    SclIniRes r = scl_ini_parse((SclIni *)&i, test);
    assert_int_equal(SCL_OK, r.err);
    assert_int_equal(scl_strlen(test.raw), r.parsed);
  }
}

#endif
