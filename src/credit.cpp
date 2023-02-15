#include "credit.h"

#include "ui_credit.h"

Credit::Credit(QWidget *parent) : QWidget(parent), ui(new Ui::Credit) {
  ui->setupUi(this);

  connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(show_result()));
}

Credit::~Credit() { delete ui; }

void Credit::show_result() {
  result_credit_window = new Result_credit();
  double sum = ui->spinBox_Sum->value();
  double percent = ui->doubleSpinBox_Percent->value();
  int months = ui->spinBox_Month->value();

  double **result = NULL;
  if (ui->radioButton_Ann->isChecked()) {
    result = annuity_credit_calc(sum, months, percent);
    result_credit_window->show();
  } else {
    result = dif_credit_calc(sum, months, percent);
    result_credit_window->show();
  }
  result_credit_window->add_to_table(result, months, sum, percent);
}
