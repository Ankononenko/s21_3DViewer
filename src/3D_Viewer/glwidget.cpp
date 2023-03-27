#include "glwidget.h"

// Vertex shader source code
const char *vertexShaderSource = R"(
    #version 330 core
    layout (location = 0) in vec3 aPos;

    uniform mat4 model;
    uniform mat4 view;
    uniform mat4 projection;

    void main()
    {
        gl_Position = projection * view * model * vec4(aPos, 1.0);
    }
)";

// Fragment shader source code
const char *fragmentShaderSource = R"(
    #version 330 core
    out vec4 FragColor;

    void main()
    {
        FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
    }
)";

QOpenGLShaderProgram *shaderProgram;
GLuint VAO, VBO;

GLWidget::GLWidget(QWidget *parent)
    : QOpenGLWidget(parent)
{
}

void GLWidget::initializeGL()
{
    initializeOpenGLFunctions();

    // Compile and link shaders
    shaderProgram = new QOpenGLShaderProgram(this);
    shaderProgram->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSource);
    shaderProgram->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSource);
    shaderProgram->link();

    // Triangle vertices
    GLfloat vertices[] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
    };

    // Generate VAO and VBO
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    // Bind VAO
    glBindVertexArray(VAO);

    // Bind VBO and buffer the data
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Configure vertex attribute pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    // Unbind VAO
    glBindVertexArray(0);

    // Set clear color
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void GLWidget::paintGL()
{
    // Clear the color buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Enable depth testing
    glEnable(GL_DEPTH_TEST);

    // Enable wireframe mode
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // Use the shader program
    shaderProgram->bind();

    // Create model, view, and projection matrices
    QMatrix4x4 model;
    QMatrix4x4 view;
    QMatrix4x4 projection;

    // Rotate the model around the y-axis
    model.rotate(45.0f, QVector3D(0.0f, 1.0f, 0.0f));

    // Move the camera back along the z-axis
    view.translate(0.0f, 0.0f, -3.0f);

    // Set the projection matrix
    projection.perspective(45.0f, (float)width() / height(), 0.1f, 100.0f);

    // Set the uniform values for the matrices
    shaderProgram->setUniformValue("model", model);
    shaderProgram->setUniformValue("view", view);
    shaderProgram->setUniformValue("projection", projection);

    // Bind the VAO
    glBindVertexArray(VAO);

    // Draw the triangle
    glDrawArrays(GL_TRIANGLES, 0, 3);

    // Unbind the VAO
    glBindVertexArray(0);

    // Release the shader program
    shaderProgram->release();

    // Disable wireframe mode
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    // Disable depth testing
    glDisable(GL_DEPTH_TEST);

    // Request an update for continuous rendering
    update();
}

void GLWidget::resizeGL(int width, int height)
{
    glViewport(0, 0, width, height);
}
