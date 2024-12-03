#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    windshop = new shop();
    QWidget::setFixedSize(window()->width() , window()->height());
    this->setWindowTitle("АВТОРИЗАЦИЯ");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_AVTO_clicked()
{
    if(ui->lineEdit->text().isEmpty()){
        QMessageBox::information(this,"Error", "Введите логин");
        return;
    } else if(ui->lineEdit_2->text().isEmpty()){
        QMessageBox::information(this,"Error", "Введите пароль");
        return;
    }

    QString LOGIN = ui->lineEdit->text();
    QString Password = ui->lineEdit_2->text();
    windshop->setLOGIN(LOGIN);
    windshop->setPASS(Password);
    windshop->show();
    this->close();
    windshop->LoadWindow();
}

