#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLExtraFunctions>
#include <QMatrix4x4>
#include <QOpenGLShaderProgram>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

class GLWidget : public QOpenGLWidget, protected QOpenGLExtraFunctions
{
    Q_OBJECT
public:
    explicit GLWidget(QWidget *parent = nullptr);
    // Destructor declaration for the frees of the arrays
    ~GLWidget();
    float getScaleFactor() const;
    void setScaleFactor(float newScaleFactor);

protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int width, int height) override;

private:
    float scaleFactor;
};

#endif // GLWIDGET_H
