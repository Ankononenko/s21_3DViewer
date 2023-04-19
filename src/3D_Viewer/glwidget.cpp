#include "glwidget.h"

int n_vertices = 0;
int n_indices = 0;

float* cubeVertices = NULL;
unsigned int* cubeIndices = NULL;

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

    float min_x = FLT_MAX, min_y = FLT_MAX, min_z = FLT_MAX;
    float max_x = FLT_MIN, max_y = FLT_MIN, max_z = FLT_MIN;

    while (getline(&line, &len, file) != -1) {
        if (line[0] == 'v' && line[1] == ' ') {
            n_vertices++;
            float x, y, z;
            sscanf(line, "v %f %f %f", &x, &y, &z);
            min_x = fmin(min_x, x);
            min_y = fmin(min_y, y);
            min_z = fmin(min_z, z);
            max_x = fmax(max_x, x);
            max_y = fmax(max_y, y);
            max_z = fmax(max_z, z);
        } else if (line[0] == 'l' && line[1] == ' ') {
            n_indices += 2;
        } else if (line[0] == 'f' && line[1] == ' ') {
            n_indices += 6;
        }
    }

    rewind(file);

    float max_range = fmax(fmax(max_x - min_x, max_y - min_y), max_z - min_z);

    cubeVertices = (float*)malloc(n_vertices * 3 * sizeof(float));
    cubeIndices = (unsigned int*)malloc(n_indices * sizeof(unsigned int));

    while (getline(&line, &len, file) != -1) {
        if (line[0] == 'v' && line[1] == ' ') {
            float x, y, z;
            sscanf(line, "v %f %f %f", &x, &y, &z);
            cubeVertices[vertexIndex++] = (x - min_x) / max_range;
            cubeVertices[vertexIndex++] = (y - min_y) / max_range;
            cubeVertices[vertexIndex++] = (z - min_z) / max_range;
        }
        // Parse the line-style obj file
          else if (line[0] == 'l' && line[1] == ' ') {
            int indices[2];
            sscanf(line, "l %d %d", &indices[0], &indices[1]);
            cubeIndices[faceIndex++] = indices[0] - 1;
            cubeIndices[faceIndex++] = indices[1] - 1;
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
            cubeIndices[faceIndex++] = indices[0];
            cubeIndices[faceIndex++] = indices[1];
            cubeIndices[faceIndex++] = indices[1];
            cubeIndices[faceIndex++] = indices[2];
            cubeIndices[faceIndex++] = indices[2];
            cubeIndices[faceIndex++] = indices[0];
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
    parseObjFile("/home/finchren/school/s21_3DViewer/src/3D_Viewer/models/apple.obj");
    // The initial color
    backgroundColor = QColor(0, 0, 0);
}

void GLWidget::initializeGL()
{
    initializeOpenGLFunctions();
    // Enable the use of vertex arrays for drawing
    glEnableClientState(GL_VERTEX_ARRAY);
    // Specify the format and the location of the vertex data in the array
    glVertexPointer(3, GL_FLOAT, 0, cubeVertices);
    qDebug() << "OpenGL initialized";
}

void GLWidget::paintGL()
{
    glEnable(GL_DEPTH_TEST); // Enable depth testing

    // Set background color: RGB and opacity
//    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClearColor(backgroundColor.redF(), backgroundColor.greenF(), backgroundColor.blueF(), backgroundColor.alphaF());


    // Clear the color buffer (color values of the pixels displayed on the screen)
    // and depth buffer (distance of each pixel)
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Set up the projection matrix
    // QMatrix4x4 is a data type that represents a 4x4 matrix, used for transformations in 3D graphics
    QMatrix4x4 projection;
    // First value - field of view angle in degrees. Determines how much of the scene is visible
    // Second value - aspect ratio of the screen. Ensures that the scene is displayed properly on screens of different sizes and aspect ratios
    // Third value - distance from the viewer to the near clipping plane, which determines how close objects can be to the viewer before they are clipped (not rendered)
    // Forth value - distance from the viewer to the far clipping plane, which determines how far objects can be from the viewer before they are clipped
    // Clipping is necessary because the graphics pipeline can only render objects that are within a certain range of distances from the viewer, and any objects that fall outside of this range are clipped or removed from the scene before rendering.
    projection.perspective(50.0, (double)width() / height(), 0.1, 100.0);

    // Set up the model-view matrix
    QMatrix4x4 modelView;
    // First set of values - position of the camera
    // Second set of values - position of the center
    // Third set of values - determines the orientation of the camera properly (in relation to the ground and other objects in the scene)
    modelView.lookAt(QVector3D(2, 2, 4), QVector3D(0, 0, 0), QVector3D(0, 1, 0));

    // Load the projection and model-view matrices
    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf(projection.constData());
    glMatrixMode(GL_MODELVIEW);
    glLoadMatrixf(modelView.constData());

    // Change point size and line width
    glPointSize(3.0f);
    glLineWidth(1.0f);

    // Update the vertex and index pointers every time paintGL is called
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, cubeVertices);

    // Draw the points
    glDrawArrays(GL_POINTS, 0, n_vertices);

    // Draw the lines
    glDrawElements(GL_LINES, n_indices, GL_UNSIGNED_INT, cubeIndices);

    qDebug() << "PaintGL finished";
}

void GLWidget::resizeGL(int width, int height)
{
    glViewport(0, 0, width, height);
}

// Destructor class
GLWidget::~GLWidget()
{
    if (cubeVertices) {
        free(cubeVertices);
    }
    if (cubeIndices) {
        free(cubeIndices);
    }
}

void GLWidget::loadModel(const QString& fileName)
{
    QByteArray byteArray = fileName.toLocal8Bit();
    const char* filePath = byteArray.constData();

    if (cubeVertices) {
        free(cubeVertices);
        cubeVertices = NULL;
    }
    if (cubeIndices) {
        free(cubeIndices);
        cubeIndices = NULL;
    }

    // Reset n_vertices and n_indices before parsing the new file
    n_vertices = 0;
    n_indices = 0;

    parseObjFile(filePath);

    qDebug() << "Finished parsing the OBJ file";

    update();
}


