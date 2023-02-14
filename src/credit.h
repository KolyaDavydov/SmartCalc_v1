#ifndef CREDIT_H
#define CREDIT_H

#include <QWidget>
#include "result_credit.h"

extern "C" {
#include "s21_smartcalc.h"
}

namespace Ui {
class Credit;
}

class Credit : public QWidget
{
    Q_OBJECT

public:
    explicit Credit(QWidget *parent = nullptr);
    ~Credit();

private slots:
    void show_result();

private:
    Ui::Credit *ui;
    Result_credit *result_credit_window;
};

#endif // CREDIT_H
