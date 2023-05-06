#include <check.h>

#include "../backend.h"

START_TEST(scale_up) {
  float vertices[] = {
      //   x     y     z
      1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
      0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
  };
  const int n_vertices = 8;
  const float scaleFactor = 2.0f;

  // call to scaleModelC
  scaleModelC(vertices, n_vertices, scaleFactor);

  const float vertices_expected[] = {
      //   x     y     z
      2.0f, 2.0f, 0.0f, 2.0f, 0.0f, 0.0f, 2.0f, 2.0f, 2.0f, 2.0f, 0.0f, 2.0f,
      0.0f, 2.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 2.0f, 2.0f, 0.0f, 0.0f, 2.0f,
  };

  for (int i = 0; i < n_vertices * 3; ++i)
    ck_assert_float_eq_tol(vertices[i], vertices_expected[i], 1e-6);
}
END_TEST

START_TEST(scale_down) {
  float vertices[] = {
      //   x     y     z
      1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
      0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
  };
  const int n_vertices = 8;
  const float scaleFactor = 0.5f;

  scaleModelC(vertices, n_vertices, scaleFactor);

  const float vertices_expected[] = {
      //   x     y     z
      0.5f, 0.5f, 0.0f, 0.5f, 0.0f, 0.0f, 0.5f, 0.5f, 0.5f, 0.5f, 0.0f, 0.5f,
      0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.5f, 0.5f, 0.0f, 0.0f, 0.5f,
  };

  for (int i = 0; i < n_vertices * 3; ++i)
    ck_assert_float_eq_tol(vertices[i], vertices_expected[i], 1e-6);
}
END_TEST

Suite *scale_suite(void) {
  Suite *s = suite_create("SCALE");
  TCase *tc = tcase_create("scale");

  tcase_add_test(tc, scale_up);
  tcase_add_test(tc, scale_down);

  suite_add_tcase(s, tc);

  return s;
}