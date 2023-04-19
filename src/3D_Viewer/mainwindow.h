#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "glwidget.h"
#include <QFileDialog>
#include <QDebug>
#include <QColorDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_QuitButton_clicked();
    void on_loadModelFileButton_clicked();
    void on_changeBGColorButton_clicked();
    void changeBackgroundColor(const QColor &color);

private:
    Ui::MainWindow *ui;
    GLWidget *glWidget;
};
#endif // MAINWINDOW_H
