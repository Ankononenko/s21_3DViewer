#include <assert.h>
#include <check.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>

#include "../backend.h"

bool float_arrays_equal(const float *a, const float *b, int len, float epsilon);

START_TEST(parse_f) {
  const char *testFilename = "tests/test_f.obj";
  float *testVertices = NULL;
  int n_vertices = 0;
  unsigned int *testIndices = NULL;
  int n_indices = 0;

  parseObjFile(testFilename, &testVertices, &n_vertices, &testIndices,
               &n_indices);

  int expectedVerticesCount = 8;
  float expectedVertices[] = {0.00, 0.00, 0.00, 1.00, 0.00, 0.00, 1.00, 1.00,
                              0.00, 0.00, 1.00, 0.00, 0.00, 0.00, 1.00, 1.00,
                              0.00, 1.00, 1.00, 1.00, 1.00, 0.00, 1.00, 1.00};

  ck_assert_int_eq(n_vertices, expectedVerticesCount);
  ck_assert(
      float_arrays_equal(testVertices, expectedVertices, n_vertices * 3, 1e-6));

  int expectedIndicesCount = 72;
  unsigned int expectedIndices[] = {
      4, 2, 2, 0, 0, 4, 2, 7, 7, 3, 3, 2, 6, 5, 5, 7, 7, 6, 1, 7, 7, 5, 5, 1,
      0, 3, 3, 1, 1, 0, 4, 1, 1, 5, 5, 4, 4, 6, 6, 2, 2, 4, 2, 6, 6, 7, 7, 2,
      6, 4, 4, 5, 5, 6, 1, 3, 3, 7, 7, 1, 0, 2, 2, 3, 3, 0, 4, 0, 0, 1, 1, 4};

  ck_assert_int_eq(n_vertices, expectedVerticesCount);
  ck_assert(
      float_arrays_equal(testVertices, expectedVertices, n_vertices * 3, 1e-6));

  free(testVertices);
  free(testIndices);
}
END_TEST

START_TEST(parse_l) {
  const char *testFilename = "tests/test_l.obj";
  float *testVertices = NULL;
  int n_vertices = 0;
  unsigned int *testIndices = NULL;
  int n_indices = 0;

  parseObjFile(testFilename, &testVertices, &n_vertices, &testIndices,
               &n_indices);

  int expectedVerticesCount = 8;
  float expectedVertices[] = {1.00, 1.00, 1.00, 1.00, 0.00, 1.00, 0.00, 0.00,
                              1.00, 0.00, 1.00, 1.00, 1.00, 1.00, 0.00, 1.00,
                              0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 1.00, 0.00};

  ck_assert_int_eq(n_vertices, expectedVerticesCount);
  ck_assert(
      float_arrays_equal(testVertices, expectedVertices, n_vertices * 3, 1e-6));

  int expectedIndicesCount = 24;
  unsigned int expectedIndices[] = {0, 1, 1, 2, 2, 3, 3, 0, 4, 5, 5, 6,
                                    6, 7, 7, 4, 0, 4, 1, 5, 2, 6, 3, 7};

  ck_assert_int_eq(n_indices, expectedIndicesCount);
  ck_assert(
      float_arrays_equal(testVertices, expectedVertices, n_vertices * 3, 1e-6));

  free(testVertices);
  free(testIndices);
}
END_TEST

START_TEST(parse_f_dashes) {
  const char *testFilename = "tests/test_f_dashes.obj";
  float *testVertices = NULL;
  int n_vertices = 0;
  unsigned int *testIndices = NULL;
  int n_indices = 0;

  parseObjFile(testFilename, &testVertices, &n_vertices, &testIndices,
               &n_indices);

  int expectedVerticesCount = 8;
  float expectedVertices[] = {1.00, 0.00, 0.00, 1.00, 0.00, 1.00, 0.00, 0.00,
                              1.00, 0.00, 0.00, 0.00, 1.00, 1.00, 0.00, 1.00,
                              1.00, 1.00, 0.00, 1.00, 1.00, 0.00, 1.00, 0.00};

  ck_assert_int_eq(n_vertices, expectedVerticesCount);
  ck_assert(
      float_arrays_equal(testVertices, expectedVertices, n_vertices * 3, 1e-6));

  int expectedIndicesCount = 72;
  unsigned int expectedIndices[] = {
      1, 2, 2, 3, 3, 1, 7, 6, 6, 5, 5, 7, 4, 5, 5, 1, 1, 4, 5, 6, 6, 2, 2, 5,
      2, 6, 6, 7, 7, 2, 0, 3, 3, 7, 7, 0, 0, 1, 1, 3, 3, 0, 4, 7, 7, 5, 5, 4,
      0, 4, 4, 1, 1, 0, 1, 5, 5, 2, 2, 1, 3, 2, 2, 7, 7, 3, 4, 0, 0, 7, 7, 4};

  ck_assert_int_eq(n_indices, expectedIndicesCount);
  ck_assert(
      float_arrays_equal(testVertices, expectedVertices, n_vertices * 3, 1e-6));

  free(testVertices);
  free(testIndices);
}
END_TEST

Suite *parse_suite(void) {
  Suite *s = suite_create("PARSE");
  TCase *tc = tcase_create("parse");

  tcase_add_test(tc, parse_f);
  tcase_add_test(tc, parse_l);
  tcase_add_test(tc, parse_f_dashes);

  suite_add_tcase(s, tc);

  return s;
}

bool float_arrays_equal(const float *a, const float *b, int len,
                        float epsilon) {
  for (int i = 0; i < len; i++) {
    if (fabs(a[i] - b[i]) > epsilon) {
      return false;
    }
  }
  return true;
}
