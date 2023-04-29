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

void GLWidget::scaleModel(float scaleFactor)
{
    for (int i = 0; i < n_vertices * 3; i++) {
        cubeVertices[i] *= scaleFactor;
    }
    update();
}

void GLWidget::moveModel(float x, float y, float z)
{
    for (int i = 0; i < n_vertices * 3; i += 3) {
        cubeVertices[i] += x;
        cubeVertices[i + 1] += y;
        cubeVertices[i + 2] += z;
    }
    update();
}

void GLWidget::rotateModel(float xAngle, float yAngle, float zAngle)
{
    QMatrix4x4 rotationMatrix;
    rotationMatrix.rotate(xAngle, QVector3D(1.0f, 0.0f, 0.0f));
    rotationMatrix.rotate(yAngle, QVector3D(0.0f, 1.0f, 0.0f));
    rotationMatrix.rotate(zAngle, QVector3D(0.0f, 0.0f, 1.0f));

    for (int i = 0; i < n_vertices * 3; i += 3) {
        QVector3D vertex(cubeVertices[i], cubeVertices[i + 1], cubeVertices[i + 2]);
        vertex = rotationMatrix * vertex;
        cubeVertices[i] = vertex.x();
        cubeVertices[i + 1] = vertex.y();
        cubeVertices[i + 2] = vertex.z();
    }
    update();
}

GLWidget::GLWidget(QWidget *parent)
    : QOpenGLWidget(parent)
{
    // Make sure the widget has a valid OpenGL context
    setFormat(QSurfaceFormat::defaultFormat());
    parseObjFile("/home/finchren/school/s21_3DViewer/s21_3DViewer/src/3D_Viewer/models/cube_first.obj");
    //    parseObjFile("/home/finchren/school/s21_3DViewer/s21_3DViewer/src/3D_Viewer/models/apple.obj");
    emit modelLoaded(n_vertices, n_indices / 2);
    // The initial color
    backgroundColor = QColor(0, 0, 0);
    // The initial point size
    vertexSize = 3.0f;
    // Set the initial vertex color to white
    vertexColor = QColor(255, 255, 255);
    // Set the initial edge color to white
    edgeColor = QColor(255, 255, 255);
    loadSettings();
    connect(this, &GLWidget::initializeGL, this, &GLWidget::postInitialization, Qt::QueuedConnection);
}

void GLWidget::initializeGL()
{
    initializeOpenGLFunctions();
    // Enable the use of vertex arrays for drawing
    glEnableClientState(GL_VERTEX_ARRAY);
    // Specify the format and the location of the vertex data in the array
    glVertexPointer(3, GL_FLOAT, 0, cubeVertices);
    // Enable line stipple for dashed lines
    if (!isDashedEdges) {
        glLineStipple(1, 0xFFFF);
    } else {
        glLineStipple(1, 0x00FF);
    }
    glLineWidth(edgeThickness);
    // Set the default edge color to white
    glColor3f(1.0f, 1.0f, 1.0f);
    // Set the vertex display method
    vertexDisplayMethod = Circle;
    qDebug() << "OpenGL initialized";
}

void GLWidget::paintGL()
{

    qDebug() << "paintGL: isParallelProjection set to:" << isParallelProjection;
    qDebug() << "paintGL: isDashedEdges set to:" << isDashedEdges;
    qDebug() << "paintGL: edgeThickness set to:" << edgeThickness;

    // Enable depth testing
    glEnable(GL_DEPTH_TEST);

    // Set background color: RGB and opacity
    //    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClearColor(backgroundColor.redF(), backgroundColor.greenF(), backgroundColor.blueF(), backgroundColor.alphaF());

    // Enable line stipple for dashed lines
     if (isDashedEdges) {
         glEnable(GL_LINE_STIPPLE);
     } else {
         glDisable(GL_LINE_STIPPLE);
     }

    // Clear the color buffer (color values of the pixels displayed on the screen)
    // and depth buffer (distance of each pixel)
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadMatrixf(projectionMatrix.constData());

    // QMatrix4x4 is a data type that represents a 4x4 matrix, used for transformations in 3D graphics
    // Set up the model-view matrix
    QMatrix4x4 modelView;
    // First set of values - position of the camera
    // Second set of values - position of the center
    // Third set of values - determines the orientation of the camera properly (in relation to the ground and other objects in the scene)
    modelView.lookAt(QVector3D(2, 2, 4), QVector3D(0, 0, 0), QVector3D(0, 1, 0));

    // Load the projection and model-view matrices
    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf(projectionMatrix.constData());
    glMatrixMode(GL_MODELVIEW);
    glLoadMatrixf(modelView.constData());

    // Change point size
    glPointSize(vertexSize);

    // Update the vertex and index pointers every time paintGL is called
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, cubeVertices);

    // Draw the points
    glColor3f(vertexColor.redF(), vertexColor.greenF(), vertexColor.blueF());

    if (vertexDisplayMethod == Circle) {
            // Draw the vertices as circles
            for (int i = 0; i < n_vertices * 3; i += 3) {
                glBegin(GL_TRIANGLE_FAN);
                float x = cubeVertices[i];
                float y = cubeVertices[i + 1];
                float z = cubeVertices[i + 2];
                glVertex3f(x, y, z);
                for (int angle = 0; angle <= 360; angle += 10) {
                    float rad = M_PI * angle / 180.0f;
                    glVertex3f(x + vertexSize * cos(rad) / width(), y + vertexSize * sin(rad) / height(), z);
                }
                glEnd();
            }
        } else if (vertexDisplayMethod == Square) {
            // Draw the vertices as squares
            for (int i = 0; i < n_vertices * 3; i += 3) {
                glBegin(GL_QUADS);
                float x = cubeVertices[i];
                float y = cubeVertices[i + 1];
                float z = cubeVertices[i + 2];
                float halfSize = vertexSize / 2.0f;
                glVertex3f(x - halfSize / width(), y - halfSize / height(), z);
                glVertex3f(x + halfSize / width(), y - halfSize / height(), z);
                glVertex3f(x + halfSize / width(), y + halfSize / height(), z);
                glVertex3f(x - halfSize / width(), y + halfSize / height(), z);
                glEnd();
            }
        }

    // Draw the lines
    glColor3f(edgeColor.redF(), edgeColor.greenF(), edgeColor.blueF());
    glDrawElements(GL_LINES, n_indices, GL_UNSIGNED_INT, cubeIndices);

    qDebug() << "PaintGL finished";
}

void GLWidget::resizeGL(int width, int height)
{
    glViewport(0, 0, width, height);

    // setToIdentity resets the projection matrix
    projectionMatrix.setToIdentity();
    if (isParallelProjection) {
       projectionMatrix.ortho(-1.0, 1.0, -1.0, 1.0, 0.1, 100.0);
    } else {
        projectionMatrix.perspective(50.0, (double)width / height, 0.1, 100.0);
    }
    update();
}


// Destructor class
GLWidget::~GLWidget()
{
    saveSettings();
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

    // Display the filename in the QLabel
    if (filenameLabel) {
        QFileInfo fileInfo(fileName);
        filenameLabel->setText(fileInfo.fileName());
    }

    // Reset n_vertices and n_indices before parsing the new file
    n_vertices = 0;
    n_indices = 0;

    parseObjFile(filePath);

    qDebug() << "Finished parsing the OBJ file";
    emit modelLoaded(n_vertices, n_indices / 2);
    update();
}

void GLWidget::setParallelProjection(bool updateValue)
{
    projectionMatrix.setToIdentity();
    // Define the orthogonal (parallel) projection matrix's clipping planes:
    //    -1.0: left plane
    //    1.0: right plane
    //    -1.0: bottom plane
    //    1.0: top plane
    //    0.1: near plane (closest distance to the camera where objects are still visible)
    //    100.0: far plane (farthest distance from the camera where objects are still visible)
    projectionMatrix.ortho(-1.0, 1.0, -1.0, 1.0, 0.1, 100.0);
    if (updateValue) {
        isParallelProjection = true;
    }
    update();
}

void GLWidget::setCentralProjection(bool updateValue)
{
    projectionMatrix.setToIdentity();
    // First value - field of view angle in degrees. Determines how much of the scene is visible
    // Second value - aspect ratio of the screen. Ensures that the scene is displayed properly on screens of different sizes and aspect ratios
    // Third value - distance from the viewer to the near clipping plane, which determines how close objects can be to the viewer before they are clipped (not rendered)
    // Forth value - distance from the viewer to the far clipping plane, which determines how far objects can be from the viewer before they are clipped
    // Clipping is necessary because the graphics pipeline can only render objects that are within a certain range of distances from the viewer, and any objects that fall outside of this range are clipped or removed from the scene before rendering.
    projectionMatrix.perspective(50.0, (double)width() / height(), 0.1, 100.0);
    if (updateValue) {
        isParallelProjection = false;
    }
    update();
}

void GLWidget::setEdgeStyle(unsigned int style, float widthIncrement, bool updateValue)
{
    makeCurrent();
    glLineStipple(1, style);
    float newWidth;
    glGetFloatv(GL_LINE_WIDTH, &newWidth);
    newWidth += widthIncrement;
    if (newWidth < 1.0f) {
        newWidth = 1.0f;
    }
    if (updateValue) {
        if (style == 0x00FF) {
            isDashedEdges = true;
        } else {
            isDashedEdges = false;
        }
        edgeThickness += widthIncrement;
    }
    glLineWidth(newWidth);
    update();
}

void GLWidget::setEdgeColor(const QColor& color)
{
    edgeColor = color;
    update();
}

void GLWidget::changeVertexSize(float increment) {
    vertexSize += increment;
    if (vertexSize < 1.0f) {
        vertexSize = 1.0f;
    }
    update();
}

void GLWidget::setVertexColor(const QColor &color) {
    vertexColor = color;
    update();
}

void GLWidget::setVertexDisplayMethod(VertexDisplayMethod method) {
    vertexDisplayMethod = method;
    update();
}

void GLWidget::saveSettings()
{
    QSettings settings("finchren", "3D_Viewer");
    settings.setValue("backgroundColor", backgroundColor);
    settings.setValue("scaleFactor", scaleFactor);
    settings.setValue("vertexSize", vertexSize);
    settings.setValue("vertexColor", vertexColor);
    settings.setValue("edgeColor", edgeColor);
    settings.setValue("vertexDisplayMethod", vertexDisplayMethod);
    settings.setValue("isParallelProjection", isParallelProjection);
    qDebug() << "saveSettings: isParallelProjection set to:" << isParallelProjection;
    settings.setValue("isDashedEdges", isDashedEdges);
    qDebug() << "saveSettings: isDashedEdges set to:" << isDashedEdges;
    settings.setValue("edgeThickness", edgeThickness);
    qDebug() << "saveSettings: edgeThickness set to:" << edgeThickness;
}

void GLWidget::loadSettings() {
    QSettings settings("finchren", "3D_Viewer");

    if (settings.contains("backgroundColor")) {
        backgroundColor = settings.value("backgroundColor").value<QColor>();
    } else {
        backgroundColor = QColor(0, 0, 0);
    }

    if (settings.contains("scaleFactor")) {
        scaleFactor = settings.value("scaleFactor").toFloat();
    } else {
        scaleFactor = 1.0f;
    }

    if (settings.contains("vertexSize")) {
        vertexSize = settings.value("vertexSize").toFloat();
    } else {
        vertexSize = 3.0f;
    }

    if (settings.contains("vertexColor")) {
        vertexColor = settings.value("vertexColor").value<QColor>();
    } else {
        vertexColor = QColor(255, 255, 255);
    }

    if (settings.contains("edgeColor")) {
        edgeColor = settings.value("edgeColor").value<QColor>();
    } else {
        edgeColor = QColor(255, 255, 255);
    }

    if (settings.contains("vertexDisplayMethod")) {
        vertexDisplayMethod = static_cast<VertexDisplayMethod>(settings.value("vertexDisplayMethod").toInt());
    } else {
        vertexDisplayMethod = Circle;
    }
    if (settings.contains("isParallelProjection")) {
        isParallelProjection = settings.value("isParallelProjection").toBool();
        qDebug() << "loadSettings: isParallelProjection set:" << isParallelProjection;
    } else {
        isParallelProjection = false;
        qDebug() << "loadSettings: isParallelProjection not found, defaulting to" << isParallelProjection;
    }

    if (settings.contains("isDashedEdges")) {
        isDashedEdges = settings.value("isDashedEdges").toBool();
        qDebug() << "loadSettings: isDashedEdges set to:" << isDashedEdges;
    } else {
        isDashedEdges = false;
        qDebug() << "loadSettings: isDashedEdges set to:" << isDashedEdges;
    }

    if (settings.contains("edgeThickness")) {
        edgeThickness = settings.value("edgeThickness").toFloat();
        qDebug() << "loadSettings: edgeThickness set to:" << edgeThickness;
    } else {
        edgeThickness = 1.0f;
        qDebug() << "loadSettings: edgeThickness set to:" << edgeThickness;
    }
}

void GLWidget::postInitialization()
{
    if (isParallelProjection) {
        setParallelProjection(false);
    } else {
        setCentralProjection(false);
    }

    // Set edge style based on the loaded settings
    unsigned int edgeStyle = isDashedEdges ? 0x00FF : 0xFFFF;
    setEdgeStyle(edgeStyle, edgeThickness - 1.0f, false);

    setVertexDisplayMethod(vertexDisplayMethod);
}

QImage GLWidget::takeScreenshot() {
    return grabFramebuffer();
}
