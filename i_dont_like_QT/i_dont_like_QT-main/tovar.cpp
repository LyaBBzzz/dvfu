#include "tovar.h"

TOVAR::TOVAR() {}


void TOVAR::setNAME(QString name){
    NAME = name;
}

void TOVAR::setCOUNT(int count){
    COUNT = count;
}

void TOVAR::setPRICE(int price){
    PRICE = price;
}

QString TOVAR::getNAME(){
    return NAME;
}

int TOVAR::getCOUNT(){
    return COUNT;
}

int TOVAR::getPRICE(){
    return PRICE;
}
