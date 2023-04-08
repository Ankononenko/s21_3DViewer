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

//void MainWindow::on_smallerButton_clicked()
//{
//    float currentScale = glWidget->getScaleFactor();
//    glWidget->setScaleFactor(currentScale * 0.9f); // 10% smaller
//}

//void MainWindow::on_biggerButton_clicked()
//{
//    float currentScale = glWidget->getScaleFactor();
//    glWidget->setScaleFactor(currentScale * 1.1f); // 10% bigger
//}

void MainWindow::on_loadModelFileButton_clicked()
{
    QString fileFilter = "OBJ Files (*.obj);;All Files (*)";
    QString fileName = QFileDialog::getOpenFileName(this, tr("Load Model File"), "", fileFilter);

    if (!fileName.isEmpty()) {
        qDebug() << "Selected file:" << fileName;
        GLWidget *glWidget = findChild<GLWidget*>("openGLWidget");
        glWidget->loadModel(fileName);
    }
}

