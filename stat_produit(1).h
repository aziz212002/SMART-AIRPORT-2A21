#ifndef STAT_PRODUIT_H
#define STAT_PRODUIT_H

#include <QDialog>
#include <QtGui>
#include <QtCore>


namespace Ui {
class stat_Produit;
}

class stat_Produit : public QDialog
{
    Q_OBJECT

public:
    explicit stat_Produit(QWidget *parent = nullptr);
    ~stat_Produit();

    int Stat_1();
    int Stat_2();
    int Stat_3();


private:
    Ui::stat_Produit *ui;


};

#endif // STAT_PRODUIT_H
