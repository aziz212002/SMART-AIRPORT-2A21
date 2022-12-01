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
    float conso;
    float kilometrage;
    float prix_achat;
    QString etat_avion;

public:
    Avion();
    Avion(int , QString , QString  ,float ,float,float,QString);
    QSqlQueryModel * afficher();
        bool ajouter();
        bool supprimer(int);
        bool supprimerTout();
        bool modifier(int);
    QSqlQueryModel  * tri();
    QSqlQueryModel*triconso();
    QSqlQueryModel*triprix();
    QSqlQueryModel* cherche_id(int);
    QSqlQueryModel *recherche(QString res);

    void statistique(QVector<double>* ticks,QVector<QString> *labels);
    void CREATION_PDF();
    int alerte();
    //QChart * Statistique();

};
#endif // AVION_H
