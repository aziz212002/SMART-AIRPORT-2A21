#ifndef PASSAGERS_H
#define PASSAGERS_H
#include <QString>
#include<QSqlQueryModel>

class passager
{
public:
    passager();
    passager(QString,QString,int,int,int,int,QString,QString,int,QString);
    QString getnom_passager();
    QString getprenom_passager();
    int getage_passager();
    int getcin_passager();
    int getpasseport_passager();
    int getnum_portail();
    QString getnum_vol();
    QString getnum_siege();
    int getnb_valises();
    QString getmail();
    void setnom_passager(QString);
    void setprenom_passager(QString);
    void setage_passager(int);
    void setcin_passager(int);
    void setpasseport_passager(int);
    void setnum_portail(int);
    void setnum_vol(QString);
    void setnum_siege(QString);
    void setnb_valises(int);
    void setmail(QString);
    bool ajouter();
    QSqlQueryModel* afficher();
    bool supprimer(int passeport_passager);
    bool modifier();




private:
    int age_passager,cin_passager,passeport_passager,num_portail,nb_valises;
    QString nom_passager,prenom_passager,num_vol,num_siege,mail;
};
#endif // PASSAGERS_H
