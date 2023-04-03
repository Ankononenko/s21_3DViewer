#include "glwidget.h"

// Vertex data for the cube
const double cubeVertices[] = {
    -0.5, -0.5, -0.5,
     0.5, -0.5, -0.5,
     0.5,  0.5, -0.5,
    -0.5,  0.5, -0.5,
    -0.5, -0.5,  0.5,
     0.5, -0.5,  0.5,
     0.5,  0.5,  0.5,
    -0.5,  0.5,  0.5
};

// Index data for the cube lines
const unsigned int cubeIndices[] = {
    0, 1, 1, 2, 2, 3, 3, 0, // Front face
    4, 5, 5, 6, 6, 7, 7, 4, // Back face
    0, 4, 1, 5, 2, 6, 3, 7  // Connecting front and back
};

GLWidget::GLWidget(QWidget *parent)
    : QOpenGLWidget(parent)
{
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

    // Draw the points
    glDrawArrays(GL_POINTS, 0, sizeof(cubeVertices) / (3 * sizeof(double)));

    // Draw the lines
    glDrawElements(GL_LINES, sizeof(cubeIndices) / sizeof(GLuint), GL_UNSIGNED_INT, cubeIndices);
}

void GLWidget::resizeGL(int width, int height)
{
    glViewport(0, 0, width, height);
}
