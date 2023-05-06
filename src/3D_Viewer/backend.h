#ifndef BACKEND_H
#define BACKEND_H

#ifdef __cplusplus
extern "C" {
#endif

void rotateX(float angle, float x, float y, float z, float* x_rezult,
             float* y_rezult, float* z_rezult);
void rotateY(float angle, float x, float y, float z, float* x_rezult,
             float* y_rezult, float* z_rezult);
void rotateZ(float angle, float x, float y, float z, float* x_rezult,
             float* y_rezult, float* z_rezult);

void scaleModelC(float* vertices, int vertices_count, float scaleFactor);
void moveModelC(float* vertices, int vertices_count, float x, float y, float z);

void parseObjFile(const char* filename, float** cubeVertices, int* n_vertices,
                  unsigned int** cubeIndices, int* n_indices);

#ifdef __cplusplus
}
#endif

#endif  // BACKEND_H
