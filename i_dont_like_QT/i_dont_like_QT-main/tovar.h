#ifndef TOVAR_H
#define TOVAR_H
#include <QDialog>
#include <QString>

class TOVAR
{
public:
    TOVAR();

    void setNAME(QString name);
    void setCOUNT(int count);
    void setPRICE(int price);

    QString getNAME();
    int getCOUNT();
    int getPRICE();


private:
    QString NAME;
    int COUNT;
    int PRICE;
};

#endif // TOVAR_H
