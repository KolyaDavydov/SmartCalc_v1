#ifndef RESULT_CREDIT_H
#define RESULT_CREDIT_H

#include <QWidget>
#include <QDate>

namespace Ui {
class Result_credit;
}

class Result_credit : public QWidget
{
    Q_OBJECT

public:
    explicit Result_credit(QWidget *parent = nullptr);
    ~Result_credit();
      void add_to_table(double **result, int months, double sum, double percent);

private:
    Ui::Result_credit *ui;
};

#endif // RESULT_CREDIT_H
