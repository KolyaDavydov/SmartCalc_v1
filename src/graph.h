#ifndef GRAPH_H
#define GRAPH_H

#include <QWidget>
#include <QVector>

namespace Ui {
class Graph;
}

class Graph : public QWidget
{
    Q_OBJECT

public slots:
    void recieveData(QString str_xmin, QString str_xmax, QString str_ymin, QString str_ymax, QString str);

public:
    explicit Graph(QWidget *parent = nullptr);
    ~Graph();

private:
    Ui::Graph *ui;
    double x_begin, x_end, y_begin, y_end, X, h;
    int N;
    QVector <double> x,y;
};

#endif // GRAPH_H
