#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->label->setText("O");
    ui->lineEdit_x->setText("0");
    ui->label->setAlignment(Qt::AlignRight); // для вывода цифр с права
    this->actWindow = ui->label;

    graph_window = new Graph();

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

    // для открытия нового виджета графика и передачи данных из окна калькулятора
    connect(ui->pushButtonGraph, SIGNAL(clicked()), graph_window, SLOT(show()));
    connect(ui->pushButtonGraph, SIGNAL(clicked()), this, SLOT(onButtonGraphSend()));
    connect(this, SIGNAL(sendData(QString,QString,QString,QString,QString)),
            graph_window, SLOT(recieveData(QString,QString,QString,QString,QString)));

    ui->lineEdit_OpMin->setText(ui->lineEdit_OpMin->text() + "-5");
    ui->lineEdit_OpMax->setText(ui->lineEdit_OpMax->text() + "5");
    ui->lineEdit_ZnMin->setText(ui->lineEdit_ZnMin->text() + "-5");
    ui->lineEdit_ZnMax->setText(ui->lineEdit_ZnMax->text() + "5");
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
    if (this->actWindow->text() == "O") {
        this->actWindow->setText(button->text());
    } else {
        actWindow->setText(actWindow->text().append(button->text()));
    }
}

/**
 * @brief print_funct печатает в окно (label) функцию и открывающую скобку после неё
 */
void MainWindow::print_funct() {
    QPushButton *button = (QPushButton *)sender();
    if (this->actWindow->text() == "O") {
        this->actWindow->setText(button->text() + "(");
    } else {
        actWindow->setText(actWindow->text().append(button->text() + "("));
    }
}

/**
 * @brief print_oper печатает в окно (label) знак арифметической операции
 */
void MainWindow::print_oper() {
    QPushButton *button = (QPushButton *)sender();
    if (this->actWindow->text() != "O") {
        if(button->text() == "pow") {
            this->actWindow->setText(actWindow->text().append("^"));
        } else if (button->text() == "mod") {
            this->actWindow->setText(actWindow->text().append("%"));
        } else {
            this->actWindow->setText(actWindow->text().append(button->text()));
        }
    }
}

/**
 * @brief print_num печатает в окно (label)  десятичную точку
 */
void MainWindow::print_dot() {
    QPushButton *button = (QPushButton *)sender();
    if (this->actWindow->text() == "O") {
        this->actWindow->setText("0" + button->text());
    } else {
        this->actWindow->setText(actWindow->text().append(button->text()));
    }
}

/**
 * @brief print_AC обнуляет значение экрана калькулятора в символ "O"
 */
void MainWindow::print_AC() {

    this->actWindow->setText("O");
}

/**
 * @brief print_del удаляет последний символ из экрана калькулятора
 */
void MainWindow::print_del() {
    QString text = this->actWindow->text();
    text.chop(1);
    actWindow->setText(text);
    if(text == "") this->actWindow->setText("O");

}

/**
 * @brief print_equal запускает механизм вычесления с Сишными файлами и выводит результат на экран
 */
void MainWindow::print_equal() {
        if (this->actWindow->text() != "O") {
            double result = 0;;
            double x = 0;
            QString result_Qtext = ui->label->text();

            QByteArray qba = result_Qtext.toLocal8Bit();
            char *result_text = qba.data();
            int error = check_formula((result_text));
            if (error == 0) {
                if (ui->lineEdit_x->text().isEmpty() != 1) {
                    x = ui->lineEdit_x->text().toDouble();
                }
                error = calc(result_text, &result, x);
                if (error == 0) {
                    QString str_tmp = QString::number(result);
                    actWindow->setText(str_tmp);
                } else {
                    QMessageBox::critical(this, "WARNING", "вы ввели что то не так");
                }
            } else {
                QMessageBox::critical(this, "WARNING", "вы ввели что то не так");
            }
        }
}

/**
 * @brief onButtonGraphSend передает все необходимые данные в график
 */
void MainWindow::onButtonGraphSend() {
    if (this->actWindow->text().length() == 0) {
        this->actWindow->setText("0");
    }
    emit sendData(ui->lineEdit_OpMin->text(), ui->lineEdit_OpMax->text(), ui->lineEdit_ZnMin->text(),
                  ui->lineEdit_ZnMax->text(), this->actWindow->text());
}
