#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "glwidget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    glWidget = this->findChild<GLWidget *>("openGLWidget");
    Q_ASSERT(glWidget); // Assert that the glWidget is not null
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_QuitButton_clicked()
{
    close();
}

void MainWindow::on_loadModelFileButton_clicked()
{
    QString fileFilter = "OBJ Files (*.obj);;All Files (*)";
    QString fileName = QFileDialog::getOpenFileName(this, tr("Load Model File"), "", fileFilter);

    if (!fileName.isEmpty()) {
        qDebug() << "Selected file:" << fileName;
        QFileInfo fileInfo(fileName);
        QString absoluteFilePath = fileInfo.absoluteFilePath();
        qDebug() << "Absolute file path:" << absoluteFilePath;
        glWidget->loadModel(absoluteFilePath);
    }
}

void MainWindow::on_changeBGColorButton_clicked()
{
    QColor initialColor = glWidget->getBackgroundColor();
    QColor newColor = QColorDialog::getColor(initialColor, this, tr("Select Background Color"));

    if (newColor.isValid()) {
        glWidget->setBackgroundColor(newColor);
        glWidget->update();
    }
}

void MainWindow::on_moveUpButton_clicked()
{
    glWidget->moveModel(0, 0.1f, 0);
}

void MainWindow::on_moveDownButton_clicked()
{
    glWidget->moveModel(0, -0.1f, 0);
}

void MainWindow::on_moveLeftButton_clicked()
{
    glWidget->moveModel(-0.1f, 0, 0);
}

void MainWindow::on_moveRightButton_clicked()
{
    glWidget->moveModel(0.1f, 0, 0);
}

void MainWindow::on_moveForwardButton_clicked()
{
    glWidget->moveModel(0, 0, 0.1f);
}

void MainWindow::on_moveBackwardButton_clicked()
{
    glWidget->moveModel(0, 0, -0.1f);
}

void MainWindow::on_smallerButton_clicked()
{
    glWidget->scaleModel(0.9f);
}

void MainWindow::on_biggerButton_clicked()
{
    glWidget->scaleModel(1.1f);
}

void MainWindow::on_rotateUpButton_clicked()
{
    glWidget->rotateModel(-10.0f, 0.0f, 0.0f);
}

void MainWindow::on_rotateDownButton_clicked()
{
    glWidget->rotateModel(10.0f, 0.0f, 0.0f);
}

void MainWindow::on_rotateLeftButton_clicked()
{
    glWidget->rotateModel(0.0f, -10.0f, 0.0f);
}

void MainWindow::on_rotateRightButton_clicked()
{
    glWidget->rotateModel(0.0f, 10.0f, 0.0f);
}

void MainWindow::on_rotateClockwiseButton_clicked()
{
    glWidget->rotateModel(0.0f, 0.0f, -10.0f);
}

void MainWindow::on_rotateCounterclockwiseButton_clicked()
{
    glWidget->rotateModel(0.0f, 0.0f, 10.0f);
}

void MainWindow::on_parallelButton_clicked()
{
    glWidget->setParallelProjection();
}

void MainWindow::on_centralButton_clicked()
{
    glWidget->setCentralProjection();
}

void MainWindow::on_solidButton_clicked()
{
    // 0x00FF is a hexadecimal representation of a 16-bit binary number.
    // In this case, it represents the pattern 0000 0000 1111 1111 in binary,
    // which is used for line stippling. When you use 0x00FF as the pattern,
    // it alternates between one visible pixel and one hidden pixel, creating a dashed line effect.
    glWidget->setEdgeStyle(0xFFFF, 1.0f);
}

void MainWindow::on_dashedButton_clicked()
{
    glWidget->setEdgeStyle(0x00FF, 1.0f);
}

void MainWindow::on_thinnerButton_clicked()
{
    glWidget->setEdgeStyle(0xFFFF, 0.5f);
}

void MainWindow::on_thickerButton_clicked()
{
    glWidget->setEdgeStyle(0xFFFF, 2.0f);
}

void MainWindow::on_edgesColorButton_clicked()
{
    QColor initialColor = Qt::white;
    QColor newColor = QColorDialog::getColor(initialColor, this, tr("Select Edge Color"));

    if (newColor.isValid()) {
        glWidget->setEdgeColor(newColor);
    }
}
