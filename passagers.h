#ifndef PASSAGERS_H
#define PASSAGERS_H
#include <QString>
#include<QSqlQueryModel>
#include<QSqlQuery>
#include <QTableView>

class passager
{
public:
    passager();
    passager(QString,QString,int,int,int,int,QString,QString,int,QString,QString,int);
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
    QString gettype_passager();
    int getpoids_totale();

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
    void settype_passager(QString);
    void setpoids_totale(int);

    bool ajouter();
    QSqlQueryModel* afficher();
    QSqlQueryModel* afficher2();

    bool supprimer(int passeport_passager);
    bool modifier();

    int verifieremail(QString);

    QSqlQueryModel * trieage();
    QSqlQueryModel * trievalise();
    QSqlQueryModel * triealphabet();
    void recherche(QTableView * table, QString);
    void telechargerPDF();


private:
    int age_passager,cin_passager,passeport_passager,num_portail,nb_valises,poids_totale;
    QString nom_passager,prenom_passager,type_passager,num_vol,num_siege,mail;
};
#endif // PASSAGERS_H
