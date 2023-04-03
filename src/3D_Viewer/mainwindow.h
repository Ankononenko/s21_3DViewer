#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "glwidget.h"

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

//    void on_smallerButton_clicked();

//    void on_biggerButton_clicked();

private:
    Ui::MainWindow *ui;
    GLWidget *glWidget;
};
#endif // MAINWINDOW_H
