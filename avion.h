#ifndef AVION_H
#define AVION_H
#include <QString>
#include <QDate>
#include <QSqlQuery>
#include <QSqlQueryModel>

class Avion
{
private :
    int Id_avion ;
    QString marque;
    QString type_moteur;
    QDate date_vol;
    float conso;
    float kilometrage;
    float prix_achat;
    QString etat_avion;

public:
    Avion();
    Avion(int , QString , QString ,QDate ,float ,float,float,QString);
    QSqlQueryModel * afficher();
        bool ajouter();
        bool supprimer(int);
        bool modifier(int);
};
#endif // AVION_H
