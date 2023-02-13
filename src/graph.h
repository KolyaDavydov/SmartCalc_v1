#ifndef GRAPH_H
#define GRAPH_H

#include <QWidget>
#include <QVector>

extern "C" {
#include "s21_smartcalc.h"
}

namespace Ui {
class Graph;
}

class Graph : public QWidget
{
    Q_OBJECT

public:
    explicit Graph(QWidget *parent = nullptr);
    ~Graph();

    void print_graph(QString function);

private slots:
    void push_draw();

private:
    Ui::Graph *ui;
};

#endif // GRAPH_H
