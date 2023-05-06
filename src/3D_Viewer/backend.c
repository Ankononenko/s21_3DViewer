#include <math.h>
#include <float.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "backend.h"
#include "my_getline.h"

/*!
* \brief Matrix4x4_t
*
* Fixed size matrix 4x4 struct for affine transformations.
*
*/
typedef struct Matrix4x4_t {
    float _data[4][4];
} Matrix4x4_t;

/*!
* \brief Point3D_t
*
* Struct to reprezent point in 3-dimensional space.
*
*/
typedef struct Point3D_t {
    float _x;
    float _y;
    float _z;
} Point3D_t;

static void __multiplyMatrixVector(const Point3D_t* in, Point3D_t* out, const Matrix4x4_t* m) {
    out->_x = in->_x * m->_data[0][0] + in->_y * m->_data[1][0] + in->_z * m->_data[2][0] + m->_data[3][0];
    out->_y = in->_x * m->_data[0][1] + in->_y * m->_data[1][1] + in->_z * m->_data[2][1] + m->_data[3][1];
    out->_z = in->_x * m->_data[0][2] + in->_y * m->_data[1][2] + in->_z * m->_data[2][2] + m->_data[3][2];

    const float w = in->_x * m->_data[0][3] + in->_y * m->_data[1][3] + in->_z * m->_data[2][3] + m->_data[3][3];

    if (fabs(w) > 1e-12) 
    {
        out->_x /= w;
        out->_y /= w;
        out->_z /= w;
    }
}

void rotateX(float angle, float x, float y, float z, float* x_rezult, float* y_rezult, float* z_rezult) {
    static Matrix4x4_t m;

    for (int row = 0; row < 4; ++row)
        for (int column = 0; column < 4; ++column)
            m._data[row][column] = 0.0f;

    m._data[0][0] = 1;
    m._data[1][1] = cosf(angle);
    m._data[1][2] = sinf(angle);
    m._data[2][1] = -sinf(angle);
    m._data[2][2] = cosf(angle);
    m._data[3][3] = 1;

    Point3D_t in;
    in._x = x;
    in._y = y;
    in._z = z;
    Point3D_t out;
    out._x = 0.0f;
    out._y = 0.0f;
    out._z = 0.0f;

    __multiplyMatrixVector(&in, &out, &m);

    *x_rezult = out._x;
    *y_rezult = out._y;
    *z_rezult = out._z;
}

void rotateY(float angle, float x, float y, float z, float* x_rezult, float* y_rezult, float* z_rezult) {
    static Matrix4x4_t m;

    for (int row = 0; row < 4; ++row)
        for (int column = 0; column < 4; ++column)
            m._data[row][column] = 0.0f;

    m._data[0][0] = cosf(angle);
    m._data[0][2] = -sinf(angle);
    m._data[1][1] = 1;
    m._data[2][0] = sinf(angle);
    m._data[2][2] = cosf(angle);
    m._data[3][3] = 1;

    Point3D_t in;
    in._x = x;
    in._y = y;
    in._z = z;
    Point3D_t out;
    out._x = 0.0f;
    out._y = 0.0f;
    out._z = 0.0f;

    __multiplyMatrixVector(&in, &out, &m);

    *x_rezult = out._x;
    *y_rezult = out._y;
    *z_rezult = out._z;
}

void rotateZ(float angle, float x, float y, float z, float* x_rezult, float* y_rezult, float* z_rezult) {
    static Matrix4x4_t m;

    for (int row = 0; row < 4; ++row)
        for (int column = 0; column < 4; ++column)
            m._data[row][column] = 0.0f;

    m._data[0][0] = cosf(angle);
    m._data[0][1] = -sinf(angle);
    m._data[1][0] = sinf(angle);
    m._data[1][1] = cosf(angle);
    m._data[2][2] = 1;
    m._data[3][3] = 1;

    Point3D_t in;
    in._x = x;
    in._y = y;
    in._z = z;
    Point3D_t out;
    out._x = 0.0f;
    out._y = 0.0f;
    out._z = 0.0f;

    __multiplyMatrixVector(&in, &out, &m);

    *x_rezult = out._x;
    *y_rezult = out._y;
    *z_rezult = out._z;
}

void scaleModelC(float* vertices, int vertices_count, float scaleFactor) {
    for (int i = 0; i < vertices_count * 3; ++i)
        vertices[i] *= scaleFactor;
}

void moveModelC(float* vertices, int vertices_count, float dx, float dy, float dz)
{
    for (int i = 0; i < vertices_count * 3; i += 3) {
        vertices[i] += dx;
        vertices[i + 1] += dy;
        vertices[i + 2] += dz;
    }
}

void parseObjFile(const char *filename, float** cubeVertices, int* n_vertices, unsigned int** cubeIndices, int* n_indices) {
    int vertexIndex = 0;
    int faceIndex = 0;

    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file\n");
        return;
    }

    char* line = NULL;
    size_t len = 0;

    float min_x = FLT_MAX, min_y = FLT_MAX, min_z = FLT_MAX;
    float max_x = FLT_MIN, max_y = FLT_MIN, max_z = FLT_MIN;

    while (my_getline_allocate(&line, &len, file) != -1) {
        if (line[0] == 'v' && line[1] == ' ') {
            (*n_vertices)++;
            float x, y, z;
            sscanf(line, "v %f %f %f", &x, &y, &z);
            min_x = fmin(min_x, x);
            min_y = fmin(min_y, y);
            min_z = fmin(min_z, z);
            max_x = fmax(max_x, x);
            max_y = fmax(max_y, y);
            max_z = fmax(max_z, z);
        } else if (line[0] == 'l' && line[1] == ' ') {
            (*n_indices) += 2;
        } else if (line[0] == 'f' && line[1] == ' ') {
            (*n_indices) += 6;
        }
    }

    rewind(file);

    float max_range = fmax(fmax(max_x - min_x, max_y - min_y), max_z - min_z);

    *cubeVertices = (float*)malloc((*n_vertices) * 3 * sizeof(float));
    *cubeIndices = (unsigned int*)malloc((*n_indices) * sizeof(unsigned int));

    while (my_getline_allocate(&line, &len, file) != -1) {
        if (line[0] == 'v' && line[1] == ' ') {
            float x, y, z;
            sscanf(line, "v %f %f %f", &x, &y, &z);
            (*cubeVertices)[vertexIndex++] = (x - min_x) / max_range;
            (*cubeVertices)[vertexIndex++] = (y - min_y) / max_range;
            (*cubeVertices)[vertexIndex++] = (z - min_z) / max_range;
        }
        // Parse the line-style obj file
          else if (line[0] == 'l' && line[1] == ' ') {
            int indices[2];
            sscanf(line, "l %d %d", &indices[0], &indices[1]);
            (*cubeIndices)[faceIndex++] = indices[0] - 1;
            (*cubeIndices)[faceIndex++] = indices[1] - 1;
        }
        // Parse the perfect face-style obj file
          else if (line[0] == 'f' && line[1] == ' ') {
            int indices[3];
            if (strchr(line, '/') == NULL) {
                sscanf(line, "f %d %d %d", &indices[0], &indices[1], &indices[2]);
            } else {
                sscanf(line, "f %d/%*d/%*d %d/%*d/%*d %d/%*d/%*d", &indices[0], &indices[1], &indices[2]);
            }
            for (int i = 0; i < 3; i++) {
                // Convert to zero-based index
                --indices[i];
            }
            // Triangulate and convert to line segments
            (*cubeIndices)[faceIndex++] = indices[0];
            (*cubeIndices)[faceIndex++] = indices[1];
            (*cubeIndices)[faceIndex++] = indices[1];
            (*cubeIndices)[faceIndex++] = indices[2];
            (*cubeIndices)[faceIndex++] = indices[2];
            (*cubeIndices)[faceIndex++] = indices[0];
        }
    }
    fclose(file);
    if (line) {
        free(line);
    }
}
