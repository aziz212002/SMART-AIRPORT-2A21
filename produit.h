#ifndef PRODUIT_H
#define PRODUIT_H
#include <QString>
#include <QApplication>
#include"connection.h"
#include<QMessageBox>
#include<QString>
#include<qsqlquerymodel.h>

class produit
{
public:
    void setNomMagasin (QString n);
    void setNumArticle (int n);
    void setNomArticle(QString n);
    void setPrixArticle(int n);
    void setNombreArticle(int n);
    QString get_NomMagasin();
    int get_NumArticle();
    QString get_NomArticle();
    QString get_rech();
    int get_PrixArticle();
    int get_NombreArticle();
    bool ajouter_produit();
    void supprimer_produit(produit p);
    void modifier_produit(produit p);
    QSqlQueryModel* chercher_produit(QString rech);
    QSqlQueryModel* afficher_produit();


    produit();
    produit(QString ,QString,int ,int ,int );
    //constructer

private:
    QString NomMagasin ,NomArticle;
    int NumArticle,PrixArticle,Nombre_Article;
};


#endif // PRODUIT_H
