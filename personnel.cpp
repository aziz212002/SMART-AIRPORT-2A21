#include "personnel.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>
#include<QSqlQueryModel>
#include<QPrintDialog>
#include<QPainter>
#include<QPrinter>
#include<QPagedPaintDevice>
#include<QPdfWriter>



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
          query.bindValue(":prenom_per", prenom_per);
          query.bindValue(":mail_per",mail_per);
          return query.exec();

}


QSqlQueryModel* Personnel::afficher()
{

    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT* FROM Personnel");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN_per"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("prenom_per"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("age_per"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("mail_per"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("num_tel"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("nom_per"));

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

QSqlQueryModel* Personnel::Recherchepersonnel(QString recherche)
 {
     QSqlQueryModel * model= new QSqlQueryModel();
     model->setQuery("SELECT * FROM Personnel WHERE CIN_per LIKE '"+recherche+"%' OR num_tel LIKE '"+recherche+"%' OR age_per LIKE '"+recherche+"%'");
     model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN_per"));
     model->setHeaderData(1, Qt::Horizontal, QObject::tr("num_tel"));
     model->setHeaderData(2, Qt::Horizontal, QObject::tr("age_per"));
     model->setHeaderData(3, Qt::Horizontal, QObject::tr("nom_per"));
     model->setHeaderData(3, Qt::Horizontal, QObject::tr("prenom_per"));
     model->setHeaderData(3, Qt::Horizontal, QObject::tr("mail_per"));



return model;
}
QSqlQueryModel * Personnel::trierpersonnelparCin()
{

    QSqlQuery * q = new  QSqlQuery ();
           QSqlQueryModel * model = new  QSqlQueryModel ();
           q->prepare("SELECT * FROM PERSONNEL ORDER BY CIN_PER ASC ");
           q->exec();
           model->setQuery(*q);
           return model;
}

QSqlQueryModel * Personnel::trierpersonnelparAge()
{

    QSqlQuery * q = new  QSqlQuery ();
           QSqlQueryModel * model = new  QSqlQueryModel ();
           q->prepare("SELECT * FROM PERSONNEL ORDER BY age_per ASC");
           q->exec();
           model->setQuery(*q);
           return model;
}


QSqlQueryModel * Personnel::trierpersonnelparordrealphabetiquedunom()
{

    QSqlQuery * q = new  QSqlQuery ();
           QSqlQueryModel * model = new  QSqlQueryModel ();
           q->prepare("SELECT * FROM PERSONNEL ORDER BY NOM_PER ASC");

           q->exec();
           model->setQuery(*q);
           return model;
}
void  Personnel::telechargerPDF(){


                     QPdfWriter pdf("C:/Users/zizo/Desktop/PDF.pdf");

                     QPainter painter(&pdf);
                    int i = 4000;
                         painter.setPen(Qt::blue);
                         painter.setFont(QFont("Arial", 30));
                         painter.drawText(1100,1200,"LISTES DES PERSONNEL");
                         painter.setPen(Qt::black);
                         painter.setFont(QFont("Arial",14));

                         painter.drawRect(0,3000,9600,500);
                         painter.setFont(QFont("Arial",11));
                         painter.drawText(200,3300,"CIN_per");
                         painter.drawText(1300,3300,"num_tel");
                         painter.drawText(2700,3300,"age_per");
                         painter.drawText(4000,3300,"nom_per");
                         painter.drawText(6500,3300,"prenom_per");
                         painter.drawText(7700,3300,"mail_per");


                         QSqlQuery query;
                         query.prepare("select * from personnel");
                         query.exec();
                         while (query.next())
                         {
                             painter.drawText(200,i,query.value(0).toString());
                             painter.drawText(1300,i,query.value(1).toString());
                             painter.drawText(2700,i,query.value(2).toString());
                             painter.drawText(4000,i,query.value(3).toString());
                             painter.drawText(6500,i,query.value(4).toString());
                             painter.drawText(7700,i,query.value(5).toString());



                            i = i + 500;
                         }}
/*bool Personnel::login()
 {     QSqlQuery query;
     QString id_string = QString::number(CIN_per);
     QString select ="select * from PERSONNEL where Cin=Cin ";
 qDebug()<<select;

         query.bindValue(":id",CIN_per);
    return query.exec();}
    */
