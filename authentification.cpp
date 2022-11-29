#include "authentification.h"
#include<QMessageBox>
#include<QPainter>
#include<QPdfWriter>
#include<QSystemTrayIcon>
#include<QDateTime>



authentification::authentification(QString NOM_UTILI ,QString MOT_DE_PASSE)
{
    this->NOM_UTILI=NOM_UTILI;
    this->MOT_DE_PASSE=MOT_DE_PASSE;



}
 bool authentification::ajouter()
 {

     QSqlQuery query;
     query.prepare("INSERT INTO PERSONNEL (NOM_UTILI ,MOT_DE_PASSE) " "values(:NOM_UTILI, :MOT_DE_PASSE)");

    query.bindValue(":NOM_UTILI",NOM_UTILI);
    query.bindValue(":MOT_DE_PASSE",MOT_DE_PASSE);

     return query.exec();
 }


 QSqlQueryModel *authentification:: afficher()
 {
     QSqlQueryModel * model= new QSqlQueryModel();
     model->setQuery("select NOM_UTILI,MOT_DE_PASSE from PERSONNEL");

     model->setHeaderData(0, Qt::Horizontal, QObject::tr("NOM_UTILI"));
     model->setHeaderData(1, Qt::Horizontal, QObject::tr("CIN_per"));
      return  model;

 }


  bool authentification::supprimer(QString NOM_UTILI)
 {
    QSqlQuery query;

    query.prepare("Delete from PERSONNEL where NOM_UTILI=:NOM_UTILI ");
   query.bindValue(":NOM_UTILI", NOM_UTILI);
   return    query.exec();
  }


 bool authentification:: modifier(QString NOM_UTILI , QString MOT_DE_PASSE)
  {
      QSqlQuery query;
      query.prepare("Update PERSONNEL set MOT_DE_PASSE=:MOT_DE_PASSE where NOM_UTILI=:NOM_UTILI");

       query.bindValue(":NOM_UTILI",NOM_UTILI);
       query.bindValue(":MOT_DE_PASSE",MOT_DE_PASSE);
           return       query.exec()  ;
 }

