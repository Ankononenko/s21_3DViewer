#include "tests_main.h"

#include <check.h>

int main() {
  Suite *s1 = move_suite();
  Suite *s2 = scale_suite();
  Suite *s3 = rotation_suite();
  Suite *s4 = parse_suite();

  SRunner *runner1 = srunner_create(s1);
  srunner_run_all(runner1, CK_ENV);
  srunner_ntests_failed(runner1);
  srunner_free(runner1);

  SRunner *runner2 = srunner_create(s2);
  srunner_run_all(runner2, CK_ENV);
  srunner_ntests_failed(runner2);
  srunner_free(runner2);

  SRunner *runner3 = srunner_create(s3);
  srunner_run_all(runner3, CK_ENV);
  srunner_ntests_failed(runner3);
  srunner_free(runner3);

  SRunner *runner4 = srunner_create(s4);
  srunner_run_all(runner4, CK_ENV);
  srunner_ntests_failed(runner4);
  srunner_free(runner4);

  return 0;
}
