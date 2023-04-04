#include "glwidget.h"


double cubeVertices[24];
unsigned int cubeIndices[24];

// Vertex data for the cube
//const double cubeVertices[] = {
//    -0.5, -0.5, -0.5,
//     0.5, -0.5, -0.5,
//     0.5,  0.5, -0.5,
//    -0.5,  0.5, -0.5,
//    -0.5, -0.5,  0.5,
//     0.5, -0.5,  0.5,
//     0.5,  0.5,  0.5,
//    -0.5,  0.5,  0.5
//};

// Index data for the cube lines
//const unsigned int cubeIndices[] = {
//    0, 1, 1, 2, 2, 3, 3, 0, // Front face
//    4, 5, 5, 6, 6, 7, 7, 4, // Back face
//    0, 4, 1, 5, 2, 6, 3, 7  // Connecting front and back
//};

void parseObjFile(const char *filename) {
    int vertexIndex = 0;
    int faceIndex = 0;

    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file\n");
        return;
    }

    char* line = NULL;
    size_t len = 0;
    while (getline(&line, &len, file) != -1) {
        if (line[0] == 'v' && line[1] == ' ') {
            double x, y, z;
            sscanf(line, "v %lf %lf %lf", &x, &y, &z);
            cubeVertices[vertexIndex * 3] = x;
            cubeVertices[vertexIndex * 3 + 1] = y;
            cubeVertices[vertexIndex * 3 + 2] = z;
            vertexIndex++;
        } else if (line[0] == 'l' && line[1] == ' ') {
            int indices[2];
            sscanf(line, "l %d %d", &indices[0], &indices[1]);
            cubeIndices[faceIndex * 2] = indices[0] - 1;
            cubeIndices[faceIndex * 2 + 1] = indices[1] - 1;
            faceIndex++;
        }
    }
    fclose(file);
    if (line) {
        free(line);
    }
}




GLWidget::GLWidget(QWidget *parent)
    : QOpenGLWidget(parent)
{
    parseObjFile("/home/finchren/school/s21_3DViewer/src/3D_Viewer/cube.obj");
}

void GLWidget::initializeGL()
{
    initializeOpenGLFunctions();
    // Enable the use of vertex arrays for drawing
    glEnableClientState(GL_VERTEX_ARRAY);
    // Specify the format and the location of the vertex data in the array
    glVertexPointer(3, GL_DOUBLE, 0, cubeVertices);
}

void GLWidget::paintGL()
{
    // Set background color
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    // Clear the color buffer and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

//    parseObjFile("/home/finchren/school/s21_3DViewer/src/3D_Viewer/cube.obj");

    // Draw the points
    glDrawArrays(GL_POINTS, 0, sizeof(cubeVertices) / (3 * sizeof(double)));

    // Draw the lines
    glDrawElements(GL_LINES, sizeof(cubeIndices) / sizeof(GLuint), GL_UNSIGNED_INT, cubeIndices);
}

void GLWidget::resizeGL(int width, int height)
{
    glViewport(0, 0, width, height);
}
