#include "personnel.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>
#include<QSqlQueryModel>

Personnel::Personnel()
{
 CIN_per=0; num_tel=0; age_per=0;
nom_per=""; prenom_per=""; mail_per="";
}


Personnel::Personnel(int CIN_per,int num_tel,int age_per,QString nom_per,QString prenom_per,QString mail_per)

{

this->CIN_per=CIN_per;
this->num_tel=num_tel;
this->age_per=age_per;
this->nom_per=nom_per;
this->prenom_per=prenom_per;
this->mail_per=mail_per;

}

bool Personnel::Ajouter()
{

    QSqlQuery query;
    QString CIN_per_string=QString::number(CIN_per);
    QString num_tel_string=QString::number(num_tel);
    QString age_per_string=QString::number(age_per);

          query.prepare("INSERT INTO Personnel (CIN_per,prenom_per,age_per,mail_per,num_tel,nom_per) "
                        "VALUES (:CIN_per, :prenom_per ,:age_per,:mail_per,:num_tel ,:nom_per )");
          query.bindValue(":CIN_per", CIN_per_string );
          query.bindValue(":num_tel", num_tel_string);
          query.bindValue(":age_per", age_per_string);
          query.bindValue(":nom_per", nom_per);
          query.bindValue("prenom_per", prenom_per);
          query.bindValue("mail_per",mail_per);
          return query.exec();

}


QSqlQueryModel* Personnel::afficher()
{

    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT* FROM Personnel");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN_per"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("num_tel"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("age_per"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("nom_per"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("prenom_per"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("mail_per"));

    return model;
}


bool Personnel:: supprimer(int CIN_per)
  {
    QSqlQuery query;
    query.prepare("delete from personnel where CIN_per=:CIN_per");
    query.bindValue(":CIN_per",CIN_per);

    return  query.exec();
  }

bool Personnel::modifier()
{
           QSqlQuery query;
           QString CIN_per_string=QString ::number (CIN_per);
           QString num_tel_string=QString::number(num_tel);
           QString age_per_string=QString::number(age_per);

    query.prepare("UPDATE personnel SET CIN_per=:CIN_per,num_tel=:num_tel,age_per=:age_per,nom_per=:nom_per,prenom_per=:prenom_per,mail_per=:mail_per WHERE CIN_per=:CIN_per ");
                                          query.bindValue(":CIN_per",CIN_per_string);
                                          query.bindValue(":num_tel", num_tel_string);
                                          query.bindValue(":age_per", age_per_string);
                                          query.bindValue(":nom_per", nom_per);
                                          query.bindValue(":prenom_per", prenom_per);
                                          query.bindValue(":mail_per", mail_per);

                     return query.exec();
}


