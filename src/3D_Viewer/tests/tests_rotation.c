#include <check.h>

#include "../backend.h"

START_TEST(rotate_x0) {
  float vertices[] = {
      //   x                  y             z
      -0.707107f,    1.20711f,  0.207107f,  -0.707107f,    0.5f, -0.5f,
      -4.76837e-07f, 1.70711f,  -0.292893f, -4.76837e-07f, 1.0f, -1.0f,
      0.0f,          0.707107f, 0.707107f,  0.0f,          0.0f, 0.0f,
      0.707106f,     1.20711f,  0.207107f,  0.707106f,     0.5f, -0.5f,
  };
  const int n_vertices = 8;
  const float xAngle = M_PI / 4;  // Rotate 45 degrees

  for (int i = 0; i < n_vertices * 3; i += 3) {
    float x = 0.0f, y = 0.0f, z = 0.0f;
    rotateX(xAngle, vertices[i + 0], vertices[i + 1], vertices[i + 2], &x, &y,
            &z);
    vertices[i + 0] = x;
    vertices[i + 1] = y;
    vertices[i + 2] = z;
  }

  const float vertices_expected[] = {
      // x                   y             z
      -0.707107f,    0.707107f, 1.0f, -0.707107f,    0.707107f, 0.0f,
      -4.76837e-07f, 1.41421f,  1.0f, -4.76837e-07f, 1.41421f,  0.0f,
      0.0f,          0.0f,      1.0f, 0.0f,          0.0f,      0.0f,
      0.707106f,     0.707107f, 1.0f, 0.707106f,     0.707107f, 0.0f,
  };

  for (int i = 0; i < n_vertices * 3; ++i)
    ck_assert_float_eq_tol(vertices[i], vertices_expected[i], 1e-5);
}
END_TEST

START_TEST(rotate_x1) {
  float vertices[] = {
      //   x                  y                   z
      -0.707107f,    -1.0f,         0.707106f,     -0.707107f, -3.09086e-08f,
      0.707107f,     -4.76837e-07f, -1.0f,         1.41421f,   -4.76837e-07f,
      -6.18172e-08f, 1.41421f,      0.0f,          -1.0f,      -4.37114e-08f,
      0.0f,          0.0f,          0.0f,          0.707106f,  -1.0f,
      0.707107f,     0.707106f,     -3.09086e-08f, 0.707107f,
  };
  const int n_vertices = 8;
  const float xAngle = M_PI / 2;  // Rotate 45 degrees

  for (int i = 0; i < n_vertices * 3; i += 3) {
    float x = 0.0f, y = 0.0f, z = 0.0f;
    rotateX(xAngle, vertices[i + 0], vertices[i + 1], vertices[i + 2], &x, &y,
            &z);
    vertices[i + 0] = x;
    vertices[i + 1] = y;
    vertices[i + 2] = z;
  }

  const float vertices_expected[] = {
      // x                   y                 z
      -0.707107f,    -0.707106f,    -1.0f,      -0.707107f,    -0.707107f,
      -6.18172e-08f, -4.76837e-07f, -1.41421f,  -1.0f,         -4.76837e-07f,
      -1.41421f,     -1.23634e-07f, 0.0f,       8.74228e-08f,  -1.0f,
      0.0f,          0.0f,          0.0f,       0.707106f,     -0.707107f,
      -1.0f,         0.707106f,     -0.707107f, -6.18173e-08f,
  };

  for (int i = 0; i < n_vertices * 3; ++i)
    ck_assert_float_eq_tol(vertices[i], vertices_expected[i], 1e-5);
}
END_TEST

START_TEST(rotate_x2) {
  float vertices[] = {
      //   x                  y             z
      -0.707107f,   0.707106f,     1.0f,      -0.707107f,    0.707107f,
      1.23634e-07f, -4.76837e-07f, 1.41421f,  1.0f,          -4.76837e-07f,
      1.41421f,     2.47269e-07f,  0.0f,      -1.74846e-07f, 1.0f,
      0.0f,         0.0f,          0.0f,      0.707106f,     0.707107f,
      1.0f,         0.707106f,     0.707107f, 1.23635e-07f,
  };
  const int n_vertices = 8;
  const float xAngle = M_PI;  // Rotate 180 degrees

  for (int i = 0; i < n_vertices * 3; i += 3) {
    float x = 0.0f, y = 0.0f, z = 0.0f;
    rotateX(xAngle, vertices[i + 0], vertices[i + 1], vertices[i + 2], &x, &y,
            &z);
    vertices[i + 0] = x;
    vertices[i + 1] = y;
    vertices[i + 2] = z;
  }

  const float vertices_expected[] = {
      // x                   y             z
      -0.707107f,    -0.707106f,    -1.0f,      -0.707107f,    -0.707107f,
      -1.85452e-07f, -4.76837e-07f, -1.41421f,  -1.0f,         -4.76837e-07f,
      -1.41421f,     -3.70903e-07f, 0.0f,       2.62268e-07f,  -1.0f,
      0.0f,          0.0f,          0.0f,       0.707106f,     -0.707107f,
      -1.0f,         0.707106f,     -0.707107f, -1.85452e-07f,
  };

  for (int i = 0; i < n_vertices * 3; ++i)
    ck_assert_float_eq_tol(vertices[i], vertices_expected[i], 1e-5);
}
END_TEST

START_TEST(rotate_y0) {
  float vertices[] = {
      //   x                  y             z
      0.707107f, 1.0f, -0.707107f,    0.707107f, 0.0f, -0.707107f,
      1.41421f,  1.0f, -4.76837e-07f, 1.41421f,  0.0f, -4.76837e-07f,
      0.0f,      1.0f, 0.0f,          0.0f,      0.0f, 0.0f,
      0.707107f, 1.0f, 0.707106f,     0.707107f, 0.0f, 0.707106f,
  };
  const int n_vertices = 8;
  const float yAngle = M_PI / 4;  // Rotate 45 degrees

  for (int i = 0; i < n_vertices * 3; i += 3) {
    float x = 0.0f, y = 0.0f, z = 0.0f;
    rotateY(yAngle, vertices[i + 0], vertices[i + 1], vertices[i + 2], &x, &y,
            &z);
    vertices[i + 0] = x;
    vertices[i + 1] = y;
    vertices[i + 2] = z;
  }

  const float vertices_expected[] = {
      // x                   y             z
      -3.57628e-07f, 1.0f, -1.0f,         -3.57628e-07f, 0.0f, -1.0f,
      1.0f,          1.0f, -1.0f,         1.0f,          0.0f, -1.0f,
      0.0f,          1.0f, 0.0f,          0.0f,          0.0f, 0.0f,
      1.0f,          1.0f, -3.57628e-07f, 1.0f,          0.0f, -3.57628e-07f,
  };

  for (int i = 0; i < n_vertices * 3; ++i)
    ck_assert_float_eq_tol(vertices[i], vertices_expected[i], 1e-5);
}
END_TEST

START_TEST(rotate_y1) {
  float vertices[] = {
      //   x                  y          z
      1.0f, 1.0f, -1.61929e-07f, 1.0f, 0.0f, -1.74846e-07f, 1.0f, 1.0f,
      1.0f, 1.0f, 0.0f,          1.0f, 0.0f, 1.0f,          0.0f, 0.0f,
      0.0f, 0.0f, 1.74846e-07f,  1.0f, 1.0f, 1.74846e-07f,  0.0f, 1.0f,
  };
  const int n_vertices = 8;
  const float yAngle = M_PI;  // Rotate 180 degrees

  for (int i = 0; i < n_vertices * 3; i += 3) {
    float x = 0.0f, y = 0.0f, z = 0.0f;
    rotateY(yAngle, vertices[i + 0], vertices[i + 1], vertices[i + 2], &x, &y,
            &z);
    vertices[i + 0] = x;
    vertices[i + 1] = y;
    vertices[i + 2] = z;
  }

  const float vertices_expected[] = {
      // x                   y             z
      -1.0f, 1.0f,  2.49351e-07f,  -1.0f, 0.0f,  2.62268e-07f,  -1.0f, 1.0f,
      -1.0f, -1.0f, 0.0f,          -1.0f, 0.0f,  1.0f,          0.0f,  0.0f,
      0.0f,  0.0f,  -2.62268e-07f, 1.0f,  -1.0f, -2.62268e-07f, 0.0f,  -1.0f,
  };

  for (int i = 0; i < n_vertices * 3; ++i)
    ck_assert_float_eq_tol(vertices[i], vertices_expected[i], 1e-5);
}
END_TEST

START_TEST(rotate_y2) {
  float vertices[] = {
      //   x                y          z
      -4.37114e-08f, 1.0f, -1.0f,         -4.37114e-08f, 0.0f, -1.0f,
      1.0f,          1.0f, -1.0f,         1.0f,          0.0f, -1.0f,
      0.0f,          1.0f, 0.0f,          0.0f,          0.0f, 0.0f,
      1.0f,          1.0f, -4.37114e-08f, 1.0f,          0.0f, -4.37114e-08f,
  };
  const int n_vertices = 8;
  const float yAngle = M_PI / 2;  // Rotate 90 degrees

  for (int i = 0; i < n_vertices * 3; i += 3) {
    float x = 0.0f, y = 0.0f, z = 0.0f;
    rotateY(yAngle, vertices[i + 0], vertices[i + 1], vertices[i + 2], &x, &y,
            &z);
    vertices[i + 0] = x;
    vertices[i + 1] = y;
    vertices[i + 2] = z;
  }

  const float vertices_expected[] = {
      // x                   y             z
      -1.0f, 1.0f,  8.74228e-08f,  -1.0f, 0.0f,  8.74228e-08f,  -1.0f, 1.0f,
      -1.0f, -1.0f, 0.0f,          -1.0f, 0.0f,  1.0f,          0.0f,  0.0f,
      0.0f,  0.0f,  -8.74228e-08f, 1.0f,  -1.0f, -8.74228e-08f, 0.0f,  -1.0f,
  };

  for (int i = 0; i < n_vertices * 3; ++i)
    ck_assert_float_eq_tol(vertices[i], vertices_expected[i], 1e-5);
}
END_TEST

START_TEST(rotate_z0) {
  float vertices[] = {
      //   x                  y                     z
      -5.66244e-07f, 1.0f,         1.0f,          -3.57628e-07f, 1.0f,
      2.47269e-07f,  0.999999f,    1.0f,          1.0f,          1.0f,
      1.0f,          4.94538e-07f, -2.47269e-07f, -2.47269e-07f, 1.0f,
      0.0f,          0.0f,         0.0f,          1.0f,          1.49012e-07f,
      1.0f,          1.0f,         3.57628e-07f,  2.47269e-07f,
  };
  const int n_vertices = 8;
  const float zAngle = M_PI / 4;  // Rotate 45 degrees

  for (int i = 0; i < n_vertices * 3; i += 3) {
    float x = 0.0f, y = 0.0f, z = 0.0f;
    rotateZ(zAngle, vertices[i + 0], vertices[i + 1], vertices[i + 2], &x, &y,
            &z);
    vertices[i + 0] = x;
    vertices[i + 1] = y;
    vertices[i + 2] = z;
  }

  const float vertices_expected[] = {
      // x                     y                 z
      0.707106f,     0.707107f,    1.0f, 0.707107f, 0.707107f,    2.47269e-07f,
      1.41421f,      5.36442e-07f, 1.0f, 1.41421f,  5.36442e-07f, 4.94538e-07f,
      -3.49691e-07f, 0.0f,         1.0f, 0.0f,      0.0f,         0.0f,
      0.707107f,     -0.707106f,   1.0f, 0.707107f, -0.707106f,   2.47269e-07f,
  };

  for (int i = 0; i < n_vertices * 3; ++i)
    ck_assert_float_eq_tol(vertices[i], vertices_expected[i], 1e-5);
}
END_TEST

START_TEST(rotate_z1) {
  float vertices[] = {
      //   x                  y                     z
      -0.707106f,    -0.707107f,   1.0f,          -0.707107f,   -0.707107f,
      2.47269e-07f,  -1.41421f,    -4.12807e-07f, 1.0f,         -1.41421f,
      -4.12807e-07f, 4.94538e-07f, 3.49691e-07f,  -3.0571e-14f, 1.0f,
      0.0f,          0.0f,         0.0f,          -0.707107f,   0.707107f,
      1.0f,          -0.707107f,   0.707107f,     2.47269e-07f,
  };
  const int n_vertices = 8;
  const float zAngle = M_PI / 2;  // Rotate 90 degrees

  for (int i = 0; i < n_vertices * 3; i += 3) {
    float x = 0.0f, y = 0.0f, z = 0.0f;
    rotateZ(zAngle, vertices[i + 0], vertices[i + 1], vertices[i + 2], &x, &y,
            &z);
    vertices[i + 0] = x;
    vertices[i + 1] = y;
    vertices[i + 2] = z;
  }

  const float vertices_expected[] = {
      // x                     y                 z
      -0.707107f,    0.707106f,     1.0f, -0.707107f,   0.707107f, 2.47269e-07f,
      -3.5099e-07f,  1.41421f,      1.0f, -3.5099e-07f, 1.41421f,  4.94538e-07f,
      -4.58564e-14f, -3.49691e-07f, 1.0f, 0.0f,         0.0f,      0.0f,
      0.707107f,     0.707106f,     1.0f, 0.707107f,    0.707107f, 2.47269e-07f,
  };

  for (int i = 0; i < n_vertices * 3; ++i)
    ck_assert_float_eq_tol(vertices[i], vertices_expected[i], 1e-5);
}
END_TEST

START_TEST(rotate_z2) {
  float vertices[] = {
      //   x                  y                     z
      1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
      0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
  };
  const int n_vertices = 8;
  const float zAngle = M_PI;  // Rotate 180 degrees

  for (int i = 0; i < n_vertices * 3; i += 3) {
    float x = 0.0f, y = 0.0f, z = 0.0f;
    rotateZ(zAngle, vertices[i + 0], vertices[i + 1], vertices[i + 2], &x, &y,
            &z);
    vertices[i + 0] = x;
    vertices[i + 1] = y;
    vertices[i + 2] = z;
  }

  const float vertices_expected[] = {
      // x                     y                 z
      -1.0f, -1.0f, 0.0f,          -1.0f, 8.74228e-08f,  0.0f,  -1.0f, -1.0f,
      1.0f,  -1.0f, 8.74228e-08f,  1.0f,  -8.74228e-08f, -1.0f, 0.0f,  0.0f,
      0.0f,  0.0f,  -8.74228e-08f, -1.0f, 1.0f,          0.0f,  0.0f,  1.0f,
  };

  for (int i = 0; i < n_vertices * 3; ++i)
    ck_assert_float_eq_tol(vertices[i], vertices_expected[i], 1e-5);
}
END_TEST

Suite *rotation_suite(void) {
  Suite *s = suite_create("ROTATE");
  TCase *tc = tcase_create("rotate");

  tcase_add_test(tc, rotate_x0);
  tcase_add_test(tc, rotate_x1);
  tcase_add_test(tc, rotate_x2);
  tcase_add_test(tc, rotate_y0);
  tcase_add_test(tc, rotate_y1);
  tcase_add_test(tc, rotate_y2);
  tcase_add_test(tc, rotate_z0);
  tcase_add_test(tc, rotate_z1);
  tcase_add_test(tc, rotate_z2);

  suite_add_tcase(s, tc);

  return s;
}