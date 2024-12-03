#include "shop.h"
#include "ui_shop.h"
#include "tovar.h"
#include <QFile>

shop::shop(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::shop)
{
    ui->setupUi(this);
}

shop::~shop()
{
    delete ui;
}

void shop::SET_TOVAR(int i){


    if(spisok[i].getPRICE()!=0){
        OUTPUT.ADD_TOVAR(i);
        QTableWidgetItem *item  = new QTableWidgetItem(QString::number(this->OUTPUT.GETTOVAR(i)));
        ui->TABLE->setItem(3,i,item);
        spisok[i].setPRICE(spisok[i].getPRICE()-1);
        QTableWidgetItem *item2  = new QTableWidgetItem(QString::number(spisok[i].getPRICE()));
        ui->TABLE->setItem(2,i,item2);
    }
}

void shop::on_B1_clicked()
{
    SET_TOVAR(0);
}


void shop::on_B2_clicked()
{
SET_TOVAR(1);
}


void shop::on_B3_clicked()
{
SET_TOVAR(2);
}


void shop::on_B4_clicked()
{
SET_TOVAR(3);
}


void shop::on_B5_clicked()
{
SET_TOVAR(4);
}


void shop::on_B6_clicked()
{
SET_TOVAR(5);
}


void shop::on_CHEK_clicked()
{
    OUTPUT_FILE();
    this->close();
}

void shop::setLOGIN(QString login){
    this->LOGIN = login;
}

void shop::setPASS(QString t){
    this->PASSWORD = t;
}

void shop::INPUT(){

    TOVAR tovar;
    QFile FILE("C:/Users/Abuna/Documents/i_dont_like_QT/product.txt");
    if(FILE.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QString LINE;
        QString D = "";
        while (!FILE.atEnd())
        {
            LINE = FILE.readLine();
            int j = 0;
            while(LINE[j]!='?'){
                D+=LINE[j];
                j++;
            }
            j++;
            tovar.setNAME(D);
            D = "";
            while(LINE[j]!='*'){
                D+=LINE[j];
                j++;
            }
            j++;
            tovar.setPRICE(D.toInt());
            D = "";
            while(j<LINE.size()){
                D+=LINE[j];
                j++;
            }
            tovar.setCOUNT(D.toInt());
            PUSH(tovar);
            D = "";
        }
    }
FILE.close();
}

void shop::OUTPUT_FILE(){

    QFile OUT("C:/Users/Abuna/Documents/i_dont_like_QT/check.txt");


    if(OUT.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream stream(&OUT);
        stream << "              YOUR CHECK          \n";
        stream<<"NAME - "<<LOGIN<<"\n";
        stream<<"PASSWORD - "<<PASSWORD<<"\n";
        for(int k = 0; k < 6;k ++)
             stream<<k<<") - "<<spisok[k].getNAME()<<" , count = "<<OUTPUT.GETTOVAR(k)<<",  price = "<<OUTPUT.GETTOVAR(k)*spisok[k].getCOUNT()<<"\n";
        stream << "YOUR PRICE - "<< QString::number(OUTPUT.CHECK_OUT_PRICE(spisok[0].getCOUNT(),spisok[1].getCOUNT(),spisok[2].getCOUNT(),spisok[3].getCOUNT(),spisok[4].getCOUNT(),spisok[5].getCOUNT())) << "\n";
        stream << "     THANKS FOR BUYING!    \n";
    }
    OUT.close();
}

void shop::LoadWindow(){
    INPUT();
    ui->TABLE->setEditTriggers(QAbstractItemView::NoEditTriggers);
    this->setWindowTitle("SHOP");
    for(int i = 0; i < 6 ; i++ ){
    ui->TABLE->setColumnWidth(i,100);
    }
    for(int i = 0; i < 4 ; i++ ){
        ui->TABLE->setRowHeight(i,83);
    }

    for(int g = 0;g < 4;g++){
        for(int k = 0; k < 6;k++){

            if(g == 0){
                auto h = this->spisok[k].getNAME();
                QTableWidgetItem *item  = new QTableWidgetItem(h);
                ui->TABLE->setItem(g,k,item);
            }
            if(g == 1){
                auto t = this->spisok[k].getCOUNT();
                QTableWidgetItem *item  = new QTableWidgetItem(QString::number(t));
                ui->TABLE->setItem(g,k,item);
            }
            if(g == 2){
                auto m = this->spisok[k].getPRICE();
                QTableWidgetItem *item  = new QTableWidgetItem(QString::number(m));
                ui->TABLE->setItem(g,k,item);
            }
            if(g == 3){
                QTableWidgetItem *item  = new QTableWidgetItem(QString::number(0));
                ui->TABLE->setItem(g,k,item);
            }

        }
    }



}

void shop::PUSH(TOVAR t){
    spisok.push_back(t);
}



