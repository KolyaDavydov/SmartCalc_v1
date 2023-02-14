#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    graph_window = new Graph();
    credit_window = new Credit();

    ui->setupUi(this);
    ui->label->setText("0"); // начальное значение в строке вывода колькулятора
    ui->label->setAlignment(Qt::AlignRight); // для вывода цифр с права

    connect(ui->pushButton_0,SIGNAL(clicked()),this,SLOT(print_num()));
    connect(ui->pushButton_1,SIGNAL(clicked()),this,SLOT(print_num()));
    connect(ui->pushButton_2,SIGNAL(clicked()),this,SLOT(print_num()));
    connect(ui->pushButton_3,SIGNAL(clicked()),this,SLOT(print_num()));
    connect(ui->pushButton_4,SIGNAL(clicked()),this,SLOT(print_num()));
    connect(ui->pushButton_5,SIGNAL(clicked()),this,SLOT(print_num()));
    connect(ui->pushButton_6,SIGNAL(clicked()),this,SLOT(print_num()));
    connect(ui->pushButton_7,SIGNAL(clicked()),this,SLOT(print_num()));
    connect(ui->pushButton_8,SIGNAL(clicked()),this,SLOT(print_num()));
    connect(ui->pushButton_9,SIGNAL(clicked()),this,SLOT(print_num()));
    connect(ui->pushButton_x,SIGNAL(clicked()),this,SLOT(print_num()));

    connect(ui->pushButton_sin,SIGNAL(clicked()),this,SLOT(print_funct()));
    connect(ui->pushButton_asin,SIGNAL(clicked()),this,SLOT(print_funct()));
    connect(ui->pushButton_cos,SIGNAL(clicked()),this,SLOT(print_funct()));
    connect(ui->pushButton_acos,SIGNAL(clicked()),this,SLOT(print_funct()));
    connect(ui->pushButton_tan,SIGNAL(clicked()),this,SLOT(print_funct()));
    connect(ui->pushButton_atan,SIGNAL(clicked()),this,SLOT(print_funct()));
    connect(ui->pushButton_sqrt,SIGNAL(clicked()),this,SLOT(print_funct()));
    connect(ui->pushButton_ln,SIGNAL(clicked()),this,SLOT(print_funct()));
    connect(ui->pushButton_log,SIGNAL(clicked()),this,SLOT(print_funct()));

    connect(ui->pushButton_openBr,SIGNAL(clicked()),this,SLOT(print_num()));
    connect(ui->pushButton_closeBr,SIGNAL(clicked()),this,SLOT(print_num()));
    connect(ui->pushButton_plus,SIGNAL(clicked()),this,SLOT(print_num()));
    connect(ui->pushButton_minus,SIGNAL(clicked()),this,SLOT(print_num()));

    connect(ui->pushButton_div,SIGNAL(clicked()),this,SLOT(print_oper()));
    connect(ui->pushButton_mult,SIGNAL(clicked()),this,SLOT(print_oper()));
    connect(ui->pushButton_pow,SIGNAL(clicked()),this,SLOT(print_oper()));
    connect(ui->pushButton_mod,SIGNAL(clicked()),this,SLOT(print_oper()));

    connect(ui->pushButton_dot,SIGNAL(clicked()),this,SLOT(print_dot()));

    connect(ui->pushButton_AC,SIGNAL(clicked()),this,SLOT(print_AC()));

    connect(ui->pushButton_del,SIGNAL(clicked()),this,SLOT(print_del()));

    connect(ui->pushButton_equal,SIGNAL(clicked()),this,SLOT(print_equal()));

    connect(ui->pushButton_Graphics, SIGNAL(clicked()), graph_window, SLOT(show()));
    connect(ui->pushButton_Graphics, SIGNAL(clicked()), this, SLOT(print_graph()));

    connect(ui->pushButton_Credit, SIGNAL(clicked()), credit_window, SLOT(show()));
//    // для открытия нового виджета графика и передачи данных из окна калькулятора
//    connect(ui->pushButtonGraph, SIGNAL(clicked()), graph_window, SLOT(show()));
//    connect(ui->pushButtonGraph, SIGNAL(clicked()), this, SLOT(onButtonGraphSend()));
//    connect(this, SIGNAL(sendData(QString,QString,QString,QString,QString)),
//            graph_window, SLOT(recieveData(QString,QString,QString,QString,QString)));

//    ui->lineEdit_OpMin->setText(ui->lineEdit_OpMin->text() + "-5");
//    ui->lineEdit_OpMax->setText(ui->lineEdit_OpMax->text() + "5");
//    ui->lineEdit_ZnMin->setText(ui->lineEdit_ZnMin->text() + "-5");
//    ui->lineEdit_ZnMax->setText(ui->lineEdit_ZnMax->text() + "5");
}

MainWindow::~MainWindow()
{
    delete ui;
}

/**
 * @brief print_num печатает в окно (label) соответствующую цифру
 */
void MainWindow::print_num() {
    QPushButton *button = (QPushButton *)sender();
    if (ui->label->text().endsWith("0") && ui->label->text().size() == 1) {
        ui->label->setText(button->text());
    } else {
        ui->label->setText(ui->label->text().append(button->text()));
    }
}

/**
 * @brief print_funct печатает в окно (label) функцию и открывающую скобку после неё
 */
void MainWindow::print_funct() {
    QPushButton *button = (QPushButton *)sender();
    if (ui->label->text().endsWith("0") && ui->label->text().size() == 1) {
        ui->label->setText(button->text() + "(");
    } else {
        ui->label->setText(ui->label->text().append(button->text() + "("));
    }
}

/**
 * @brief print_oper печатает в окно (label) знак арифметической операции
 */
void MainWindow::print_oper() {
    QPushButton *button = (QPushButton *)sender();
    if (ui->label->text() != "0") {
        if(button->text() == "pow") {
            ui->label->setText(ui->label->text().append("^"));
        } else if (button->text() == "mod") {
            ui->label->setText(ui->label->text().append("%"));
        } else {
            ui->label->setText(ui->label->text().append(button->text()));
        }
    }
}

/**
 * @brief print_num печатает в окно (label)  десятичную точку
 */
void MainWindow::print_dot() {
    QPushButton *button = (QPushButton *)sender();
    if (ui->label->text() == "0") {
        ui->label->setText("0" + button->text());
    } else {
        ui->label->setText(ui->label->text().append(button->text()));
    }
}

/**
 * @brief print_AC обнуляет значение экрана калькулятора в символ "0"
 */
void MainWindow::print_AC() {

    ui->label->setText("0");
//    ui->lineEdit_x->setText("");
}

/**
 * @brief print_del удаляет последний символ из экрана калькулятора
 */
void MainWindow::print_del() {
    QString text = ui->label->text();
    text.chop(1);
    ui->label->setText(text);
    if(text == "") ui->label->setText("0");

}

/**
 * @brief print_equal запускает механизм вычесления с Сишными файлами и выводит результат на экран
 */
void MainWindow::print_equal() {
    if (ui->label->text() != "0") {
            double result = 0.0;
            double x = ui->doubleSpinBox->value();
            // переводим из QString в string

            QString result_Qtext = ui->label->text();
            // почему то с ублюдской точкой не работает поэтому
            result_Qtext.replace(".", ",");
            qDebug() << result_Qtext;
            QByteArray qba = result_Qtext.toLocal8Bit();
            char *result_text = qba.data();

            int error = 0;
            error = calc(result_text, &result, x);

            if (error == 0) {
                    QString str_tmp = QString::number(result);
                    ui->label_2->setText(ui->label->text());
                    ui->label->setText(str_tmp);
            } else if (error == 2){
                QMessageBox::critical(this, "WARNING", "деление на ноль");
            } else {
                QMessageBox::critical(this, "WARNING", "проверьте выражение на корректность");
            }
        }
}



/**
 * @brief передает значение формулы в график (если формула правильная и есть Х)
 */
void MainWindow::print_graph() {
//    if (ui->label->text() != "0") {
        double result = 0;
        double x = ui->doubleSpinBox->value();
        QString result_Qtext = ui->label->text();
        // почему то с ублюдской точкой не работает поэтому
        result_Qtext.replace(".", ",");

        QByteArray qba = result_Qtext.toLocal8Bit();
        char *result_text = qba.data();
        int error = check_formula((result_text));
        if (error == 0) {
//            if (ui->lineEdit_x->text().isEmpty() != 1) {
//                x = ui->lineEdit_x->text().toDouble();
//            }
            error = calc(result_text, &result, x);
            if (error == 0) {
                QString str_tmp = QString::number(result);
                graph_window->print_graph(ui->label->text());
            } else {
                QMessageBox::critical(this, "WARNING", "вы ввели что то не так");
            }
        } else {
            QMessageBox::critical(this, "WARNING", "вы ввели что то не так");
        }
//    } else {
//        QMessageBox::critical(this, "WARNING", "проверте формулу");
//    }


}



