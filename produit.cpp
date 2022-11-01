#include "produit.h"
#include <QSqlQuery>
#include<QSqlQueryModel>
#include<QDebug>
#include<QObject>
produit::produit()
{   NomMagasin="";
    NumArticle=0 ;
    NomArticle="";
    PrixArticle=0 ;
    Nombre_Article =0;
}
produit::produit(QString NomMagasin ,QString NomArticle,int NumArticle,int PrixArticle,int NombreArticle)
{
           this ->NomMagasin=NomMagasin;
            this ->NomArticle=NomArticle;
           this -> NumArticle=NumArticle;
           this -> PrixArticle=PrixArticle;
          this ->  Nombre_Article=NombreArticle;
}

void produit::setNombreArticle(int n){Nombre_Article=n;}
void produit::setNomMagasin(QString n){NomMagasin=n;}
void produit::setNomArticle(QString n){NomArticle=n;}
void produit::setPrixArticle(int n){PrixArticle=n;};
void produit::setNumArticle(int n){NumArticle=n;}


int produit:: get_NumArticle(){return NumArticle;}
QString produit::get_NomMagasin(){return NomMagasin;}
QString produit::get_NomArticle(){return NomArticle;}
int produit::get_NombreArticle(){return Nombre_Article;}
int produit::get_PrixArticle(){return PrixArticle;}



//ajout d'un client
bool produit :: ajouter_produit( )
{
   QString NombreArticle_string=QString::number(Nombre_Article);
    QString NumArticle_string=QString::number(NumArticle);
    QString PrixArticle_string=QString::number(PrixArticle);

    QSqlQuery query;
  query.prepare("INSERT INTO PRODUIT (NomMagasin ,NomArticle,Prix_Article, NumArticle,Nombre_Article) "
               " VALUES (:Nom_Magasin ,:Nom_Article,:Prix_Article,:Num_Article,:Nombre_Article)");
      query.bindValue(":NomMagasin",NomMagasin);
    query.bindValue(":NombreArticle",NomArticle);
       query.bindValue(":Prix_Article",PrixArticle_string);
    query.bindValue(":NumArticle",NumArticle_string);
    query.bindValue(":NombreArticle",NombreArticle_string);
return query.exec();


}
void modifier_produit(produit p)
{
 QSqlQuery qry;
         qry.prepare ("UPDATE PRODUIT set  NOMMAGASIN = NomMagasin ,NOMARTICLE = NomArticle, NUMARTICLE = NumArticle ,PRIXARTICLE = Prix_Article,NOMBREARTICLE = NombreArticle" );
         qry.bindValue(":NombreArticle",p.get_NombreArticle());
         qry.bindValue(":NomMagasin",p.get_NomMagasin());
         qry.bindValue(":NumArticle",p.get_NumArticle());
         qry.bindValue(":Prix_Article",p.get_PrixArticle());
         qry.bindValue(":NombreArticle",p.get_NombreArticle());
        if(qry.exec())
    {
        QMessageBox::critical(nullptr, QObject::tr("sql query successful"),
                           QObject::tr("row updated and saved.\n"
                                       "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else{
        QMessageBox::critical(nullptr, QObject::tr("sql query unsuccessful"),
                           QObject::tr("row not updated and not saved.\n"
                                       "Click Cancel to exit."), QMessageBox::Cancel);
    }
}

bool supprimer_produit(int NombreArticle)
{

    QSqlQuery query ;
    query.prepare("Delete from vols where NombreArticle=:NombreArticle");
    query.bindValue(":NombreArticle",NombreArticle);
    return query.exec();
}

QSqlQueryModel* afficher_produit()
{
     QSqlQueryModel* model=new QSqlQueryModel();

     model->setQuery("SELECT *  FROM produit ");
     model->setHeaderData(0, Qt::Horizontal, QObject::tr("NomMagasin"));
     model->setHeaderData(1, Qt::Horizontal, QObject::tr("NomArticle"));
     model->setHeaderData(2, Qt::Horizontal, QObject::tr("NumArticle"));
     model->setHeaderData(3, Qt::Horizontal, QObject::tr("Prix_Article"));
     model->setHeaderData(3, Qt::Horizontal, QObject::tr("NombreArticle"));


     return model;
}
