#ifndef SRC_TESTS_MAIN_H_
#define SRC_TESTS_MAIN_H_

#include <check.h>
#include <stdlib.h>
#include <time.h>

#include "../backend.h"

Suite *move_suite(void);
Suite *scale_suite(void);
Suite *rotation_suite(void);

Suite *parse_suite(void);

#endif  // SRC_TESTS_CHECK_MATRIX_H_
