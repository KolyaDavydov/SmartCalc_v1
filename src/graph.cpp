#include "graph.h"
#include "ui_graph.h"

#include "mainwindow.h"

Graph::Graph(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Graph)
{
    ui->setupUi(this);
}

Graph::~Graph()
{
    delete ui;
}

void Graph::recieveData(QString str_xmin, QString str_xmax, QString str_ymin, QString str_ymax, QString str)
{
    ui->widget->clearGraphs();
    char *string = new char(str.length());
    QByteArray barr = str.toLatin1();
    strncpy(string, barr, str.length() + 1);

    double res = 0;
    int status = 0;
    // берем краевые значения графика из калькулятора
    x_begin = str_xmin.toDouble();
    x_end = str_xmax.toDouble();
    y_begin = str_ymin.toDouble();
    y_end = str_ymax.toDouble();
    if (x_begin < -1000) {
        x_begin = -1000;
    }
    if (y_begin < -1000) {
        y_begin = -1000;
    }
    if (x_end > 1000) {
        x_end = 1000;
    }
    if (y_end > 1000) {
        y_end = 1000;
    }
    h = 0.01; // шаг точек
    // настройка видимой областисистемы координат
    ui->widget->xAxis->setRange(x_begin, x_end);
    ui->widget->yAxis->setRange(y_begin, y_end);

    for (X = x_begin;  X <= x_end && !status; X +=h) {
        status = calc(string, &res, X);
        x.push_back(X); // в вектор Х записать Х
        y.push_back(res); // в вектор Y записать результат функции при данном Х
    }
    ui->widget->addGraph(); // добавляем график на виджет
    // обращаемся к графику и устанавливаем ему значения и передаем векторы Х и Y
    ui->widget->graph(0)->addData(x,y);
    ui->widget->replot(); // рисует график
    x.clear();
    y.clear();
    delete(string);
}
