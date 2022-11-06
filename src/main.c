
/**
 * When built without test
 */
#ifndef TEST

/// only use main if binary
#if TYPE == bin

#include <stdio.h>

int scl_test_main(int argc, char **argv) {
  printf("Hello world!\n");
  return 0;
}

#endif
#endif

/**
 * When built with test
 */
#ifdef TEST

#include "scl/scl.h"

#ifdef SCL_TEST
int main(int argc, char **argv) {
#else
int scl_test_main(int argc, char **argv) {
#endif
  const struct CMUnitTest tests[] = {cmocka_unit_test(test_strbuf_resize),
                                     cmocka_unit_test(test_ini_parse)};
  return cmocka_run_group_tests(tests, NULL, NULL);
}

#endif
