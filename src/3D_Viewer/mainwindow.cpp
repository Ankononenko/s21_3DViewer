#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "glwidget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    GLWidget *glWidget = new GLWidget(this);
    setCentralWidget(glWidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}
