#include "check_in.h"

CHECK_IN::CHECK_IN() {
    T1 = 0;
    T2 = 0;
    T3 = 0;
    T4 = 0;
    T5 = 0;
    T6 = 0;
}

void CHECK_IN::DELETE_TOVAR(){
    T1 = 0;
    T2 = 0;
    T3 = 0;
    T4 = 0;
    T5 = 0;
    T6 = 0;

}

void CHECK_IN::ADD_TOVAR(int number){
    if(number == 0)
        T1++;
    if(number == 1)
           T2++;
    if(number == 2)
        T3++;
    if(number == 3)
        T4++;
    if(number == 4)
       T5++;
    if(number == 5)
        T6++;

}

int CHECK_IN::CHECK_OUT_PRICE(int p1,int p2,int p3,int p4, int p5,int p6){
    return T1*p1 + T2*p2 + T3*p3 + T4*p4 + T5*p5 + T6*p6;
}

int CHECK_IN::GETTOVAR(int num){
    if(num == 0)
        return  T1;;
    if(num == 1)
        return T2;;
    if(num == 2)
        return T3;
    if(num == 3)
        return T4;
    if(num == 4)
        return  T5;
    if(num == 5)
        return T6;
    return 0;
}
