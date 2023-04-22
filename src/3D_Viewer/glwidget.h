#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLExtraFunctions>
#include <QMatrix4x4>
#include <QOpenGLShaderProgram>

// For max and min
#include <cfloat>
#include <cmath>

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
    void loadModel(const QString& fileName);
    QColor getBackgroundColor() const { return backgroundColor; }
    void setBackgroundColor(const QColor &color) { backgroundColor = color; }
    void scaleModel(float scaleFactor);
    void moveModel(float x, float y, float z);
    void rotateModel(float xAngle, float yAngle, float zAngle);
    void setParallelProjection();
    void setCentralProjection();
    void setEdgeStyle(unsigned int style, float width);
    void setEdgeColor(const QColor& color);
    void changeVertexSize(float increment);
    void setVertexColor(const QColor& color);

protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int width, int height) override;

private:
    float scaleFactor;
    float vertexSize;
    QColor backgroundColor;
    // Set up the projection matrix
    // QMatrix4x4 is a data type that represents a 4x4 matrix, used for transformations in 3D graphics
    QMatrix4x4 projectionMatrix;
    QColor vertexColor;
    QColor edgeColor;
};

#endif // GLWIDGET_H
