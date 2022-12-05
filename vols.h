#ifndef VOLS_H
#define VOLS_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QtDebug>
#include <QDate>

class vols

{
public:
    vols();
    vols(int,QDate,int,QString,int);
    int getnum_vols();
    QDate getd_vols();
    int getcap_vols();
    QString getdest();
    int getnb();



    void setnum_vols(int);
    void setd_vols(QDate);
    void setcap_vols(int);
    void setdest(QString);
    void setnb(int);


    bool ajoutervols();
    QSqlQueryModel* affichervols();
    bool supprimervols(int);
    bool modifiervols(int,QDate,int,QString,int);
    QSqlQueryModel* Recherchevols(QString);
    bool supprimerTout();
    QSqlQueryModel * triervolsParnvols();
    QSqlQueryModel * triervolsParnbplace();
    QSqlQueryModel * triervolspardate();
    void telechargerPDF();
    QSqlQueryModel * Historique(QString);
    double ESTIMATION(  QString s);
    QSqlQueryModel* afficherlghayb();

private:
    int num_vols,cap_vols,nb;
    QString dest;
    QDate d_vols;
};


#endif // VOLS_H
