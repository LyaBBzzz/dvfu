#ifndef CHECK_IN_H
#define CHECK_IN_H
#include <QString>
#include <tuple>
#include <QVector>

class CHECK_IN
{
public:
    CHECK_IN();
    void DELETE_TOVAR();
    void ADD_TOVAR(int number);
    int GETTOVAR(int num);
    int CHECK_OUT_PRICE(int p1,int p2,int p3,int p4, int p5,int p6);

private:
    int T1;
    int T2;
    int T3;
    int T4;
    int T5;
    int T6;
};

#endif // CHECK_IN_H
