#include <check.h>

#include "../backend.h"

START_TEST(positive_move_x) {
  float vertices[] = {
      //   x     y     z
      1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
      0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
  };
  const int n_vertices = 8;
  const float dx = 1.0f;

  moveModelC(vertices, n_vertices, dx, 0.0f, 0.0f);

  const float vertices_expected[] = {
      //   x     y     z
      2.0f, 1.0f, 0.0f, 2.0f, 0.0f, 0.0f, 2.0f, 1.0f, 1.0f, 2.0f, 0.0f, 1.0f,
      1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
  };

  for (int i = 0; i < n_vertices * 3; ++i)
    ck_assert_float_eq_tol(vertices[i], vertices_expected[i], 1e-12);
}
END_TEST

START_TEST(positive_move_y) {
  float vertices[] = {
      //   x     y     z
      1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
      0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
  };
  const int n_vertices = 8;
  const float dy = 1.0f;

  moveModelC(vertices, n_vertices, 0.0f, dy, 0.0f);

  const float vertices_expected[] = {
      //   x     y     z
      1.0f, 2.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 2.0f, 1.0f, 1.0f, 1.0f, 1.0f,
      0.0f, 2.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 2.0f, 1.0f, 0.0f, 1.0f, 1.0f,
  };

  for (int i = 0; i < n_vertices * 3; ++i)
    ck_assert_float_eq_tol(vertices[i], vertices_expected[i], 1e-12);
}
END_TEST

START_TEST(positive_move_z) {
  float vertices[] = {
      //   x     y     z
      1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
      0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
  };
  const int n_vertices = 8;
  const float dz = 1.0f;

  moveModelC(vertices, n_vertices, 0.0f, 0.0f, dz);

  const float vertices_expected[] = {
      //   x     y     z
      1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 2.0f, 1.0f, 0.0f, 2.0f,
      0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 2.0f, 0.0f, 0.0f, 2.0f,
  };

  for (int i = 0; i < n_vertices * 3; ++i)
    ck_assert_float_eq_tol(vertices[i], vertices_expected[i], 1e-12);
}
END_TEST

START_TEST(negative_move_x) {
  float vertices[] = {
      //   x     y     z
      1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
      0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
  };
  const int n_vertices = 8;
  const float dx = -1.0f;

  moveModelC(vertices, n_vertices, dx, 0.0f, 0.0f);

  const float vertices_expected[] = {
      //   x     y     z
      0.0f, 1.0f, 0.0f,  0.0f, 0.0f,  0.0f,  0.0f, 1.0f,
      1.0f, 0.0f, 0.0f,  1.0f, -1.0f, 1.0f,  0.0f, -1.0f,
      0.0f, 0.0f, -1.0f, 1.0f, 1.0f,  -1.0f, 0.0f, 1.0f,
  };

  for (int i = 0; i < n_vertices * 3; ++i)
    ck_assert_float_eq_tol(vertices[i], vertices_expected[i], 1e-12);
}
END_TEST

START_TEST(negative_move_y) {
  float vertices[] = {
      //   x     y     z
      1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
      0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
  };
  const int n_vertices = 8;
  const float dy = -1.0f;

  moveModelC(vertices, n_vertices, 0.0f, dy, 0.0f);

  const float vertices_expected[] = {
      //   x     y     z
      1.0f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, -1.0f, 1.0f,
      0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, -1.0f, 1.0f,
  };

  for (int i = 0; i < n_vertices * 3; ++i)
    ck_assert_float_eq_tol(vertices[i], vertices_expected[i], 1e-12);
}
END_TEST

START_TEST(negative_move_z) {
  float vertices[] = {
      //   x     y     z
      1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
      0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
  };
  const int n_vertices = 8;
  const float dz = -1.0f;

  moveModelC(vertices, n_vertices, 0.0f, 0.0f, dz);

  const float vertices_expected[] = {
      //   x     y     z
      1.0f, 1.0f, -1.0f, 1.0f, 0.0f, -1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
      0.0f, 1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
  };

  for (int i = 0; i < n_vertices * 3; ++i)
    ck_assert_float_eq_tol(vertices[i], vertices_expected[i], 1e-12);
}
END_TEST

Suite *move_suite(void) {
  Suite *s = suite_create("MOVE");
  TCase *tc = tcase_create("move");

  tcase_add_test(tc, positive_move_x);
  tcase_add_test(tc, positive_move_y);
  tcase_add_test(tc, positive_move_z);
  tcase_add_test(tc, negative_move_x);
  tcase_add_test(tc, negative_move_y);
  tcase_add_test(tc, negative_move_z);

  suite_add_tcase(s, tc);

  return s;
}