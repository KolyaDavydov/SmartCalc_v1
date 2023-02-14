#include "result_credit.h"
#include "ui_result_credit.h"

Result_credit::Result_credit(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Result_credit)
{
    ui->setupUi(this);
}

Result_credit::~Result_credit()
{
    delete ui;
}

void Result_credit::add_to_table(double **result, int period) {
  double total_sum = 0.0;
  double all_percent = 0.0;
  QDate date = QDate::currentDate();
  for (int i = 0; i < period; i++) {
    ui->tableWidget->insertRow(i);
    ui->tableWidget->setItem(
        i, 0, new QTableWidgetItem(date.toString("MMM yyyy")));
    ui->tableWidget->setItem(
        i, 1, new QTableWidgetItem(QString::number(result[i][1], 'g', 11)));
    ui->tableWidget->setItem(
        i, 2, new QTableWidgetItem(QString::number(result[i][2], 'g', 11)));
    ui->tableWidget->setItem(
        i, 3, new QTableWidgetItem(QString::number(result[i][3], 'g', 11)));
    ui->tableWidget->setItem(
        i, 4, new QTableWidgetItem(QString::number(result[i][4], 'g', 11)));
    total_sum  += result[i][1];
    date = date.addMonths(1);
    ui->label->setText(QString::number(total_sum , 'g', 11));
    all_percent += result[i][3];
    ui->label_2->setText(QString::number(all_percent, 'g', 11));
  }
  ui->tableWidget->resizeColumnsToContents();

  for (int i = 0; i < period; i++) {
    free(result[i]);
  }
  free(result);
  result = NULL;
}
