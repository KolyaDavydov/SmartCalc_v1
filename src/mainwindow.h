#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

extern "C" {
#include "s21_smartcalc.h"
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QLabel *actWindow;

// хедеры для наших функций
private slots:

    void print_num();
    void print_funct();
    void print_oper();
    void print_dot();
    void print_AC();
    void print_del();
    void print_equal();
};
#endif // MAINWINDOW_H