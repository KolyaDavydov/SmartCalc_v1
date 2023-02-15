#include "graph.h"

#include "ui_graph.h"

Graph::Graph(QWidget *parent) : QWidget(parent), ui(new Ui::Graph) {
  ui->setupUi(this);
  connect(ui->pushButton_draw_graph, SIGNAL(clicked()), this,
          SLOT(push_draw()));
}

Graph::~Graph() { delete ui; }

void Graph::push_draw() {
  QString function = ui->label_function->text();
  function.replace(".", ",");
  QByteArray qba = function.toLocal8Bit();
  char *function_on_c = qba.data();

  double result = 0.0;
  int error = calc(function_on_c, &result, 0);
  if (error == 0) {
    print_graph(function);
  } else {
    QMessageBox::critical(this, "WARNING", "проверте формулу");
  }
}
void Graph::print_graph(QString function) {
  ui->label_function->setText(function);

  ui->custom_plot->clearGraphs();

  function.replace(".", ",");
  QByteArray qba = function.toLocal8Bit();
  char *function_on_c = qba.data();

  // задаем границы для графика
  double x_begin = ui->spinBox_min_x->value();
  double x_end = ui->spinBox_max_x->value();
  double y_begin = ui->spinBox_min_y->value();
  double y_end = ui->spinBox_max_y->value();

  double h = 0.01;
  double X;
  double res = 0.0;
  QVector<double> x, y;

  // устанавливаем границы для графика
  ui->custom_plot->xAxis->setRange(x_begin, x_end);
  ui->custom_plot->yAxis->setRange(y_begin, y_end);

  int error = 0;
  for (X = x_begin; X < x_end && !error; X += h) {
    x.push_back(X);
    error = calc(function_on_c, &res, X);
    y.push_back(res);
  }
  ui->custom_plot->addGraph();
  ui->custom_plot->graph(0)->addData(x, y);
  ui->custom_plot->graph(0)->setPen(QColor(0, 0, 255, 255));
  ui->custom_plot->graph(0)->setLineStyle((QCPGraph::lsNone));
  ui->custom_plot->graph(0)->setScatterStyle(
      QCPScatterStyle(QCPScatterStyle::ssCircle, 1));
  ui->custom_plot->replot();

  x.clear();
  y.clear();
}
