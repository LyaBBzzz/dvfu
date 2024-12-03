#ifndef SHOP_H
#define SHOP_H

#include <QDialog>
#include "tovar.h"
#include "check_in.h"

namespace Ui {
class shop;
}

class shop : public QDialog
{
    Q_OBJECT

public:
    explicit shop(QWidget *parent = nullptr);
    ~shop();

    void setLOGIN(QString login);
    void LoadWindow();
    void INPUT();
    void PUSH(TOVAR t);
    void SET_TOVAR(int i);
    void OUTPUT_FILE();
    void setPASS(QString t);

private slots:
    void on_B1_clicked();

    void on_B2_clicked();

    void on_B3_clicked();

    void on_B4_clicked();

    void on_B5_clicked();

    void on_B6_clicked();

    void on_CHEK_clicked();

private:
    Ui::shop *ui;
    QString LOGIN;
    QString PASSWORD;
    QList<TOVAR> spisok;
    CHECK_IN OUTPUT;
};

#endif // SHOP_H
