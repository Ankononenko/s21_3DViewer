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

void MainWindow::on_SmallerButton_clicked()
{
    float currentScale = glWidget->getScaleFactor();
    glWidget->setScaleFactor(currentScale * 0.9f); // 10% smaller
}

void MainWindow::on_BiggerButton_clicked()
{
    float currentScale = glWidget->getScaleFactor();
    glWidget->setScaleFactor(currentScale * 1.1f); // 10% bigger
}

