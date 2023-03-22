#include "glwidget.h"

GLWidget::GLWidget(QWidget *parent)
    : QOpenGLFunctions {parent}
{

}

void GLWidget::initializeGL()
{
    glEnable(GL_DEPTH_TEST);
    initializeOpenGLFunctions();
}

void GLWidget::paintGL()
{

}

void GLWidget::resizeGL(int width, int height)
{
    glViewport(0, 0, 300, 200);
}

void GLWidget::qColorToRGB(const QColor &C, float &r, float &g, float &b) const
{
    C.red();
    C.green();
    C.blue();
}
