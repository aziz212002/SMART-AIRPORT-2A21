#include "passagers.h"
#include<QSqlQuery>
#include <QtDebug>
#include<QObject>
#include <QPdfWriter>
#include <QPainter>
#include <QDate>
#include <QDesktopServices>
#include <QUrl>

passager::passager()
{
passeport_passager=0;
nom_passager=" ";prenom_passager=" ";age_passager=0,cin_passager=0,type_passager=" ";num_portail=0;num_vol=" ";num_siege=" ";nb_valises=0;poids_totale=0;mail=" ";
}

passager::passager(QString nom_passager, QString prenom_passager , int age_passager,int cin_passager,int passeport_passager ,int num_portail , QString num_vol , QString num_siege , int nb_valises , QString mail , QString type_passager ,int poids_totale)
{this->nom_passager=nom_passager;this->prenom_passager=prenom_passager,this->age_passager=age_passager;this->cin_passager=cin_passager;this->passeport_passager=passeport_passager;this->num_portail=num_portail;this->num_vol=num_vol;this->num_siege=num_siege;this->nb_valises=nb_valises;this->mail=mail;this->type_passager=type_passager;this->poids_totale=poids_totale;}

QString passager::getnom_passager(){return nom_passager ;}
QString passager::getprenom_passager(){return prenom_passager ;}
int passager::getage_passager(){return age_passager ;}
int passager::getcin_passager(){return cin_passager;}
int passager::getpasseport_passager(){return passeport_passager;}
int passager::getnum_portail(){return num_portail;}
QString passager::getnum_vol(){return num_vol;}
QString passager::getnum_siege(){return num_siege;}
int passager::getnb_valises(){return nb_valises;}
QString passager::getmail(){return mail;}
QString passager::gettype_passager(){return type_passager ;}
int passager::getpoids_totale(){return poids_totale;}

void passager::setnom_passager(QString nom_passager){this->nom_passager=nom_passager;}
void passager::setprenom_passager(QString prenom_passager){this->prenom_passager=prenom_passager;}
void passager::setage_passager(int age_passager){this->age_passager=age_passager;}
void passager::setcin_passager(int cin_passager){this->cin_passager=cin_passager;}
void passager::setpasseport_passager(int passeport_passager){this->passeport_passager=passeport_passager;}
void passager::setnum_portail(int num_portail){this->num_portail=num_portail;}
void passager::setnum_vol(QString num_vol){this->num_vol=num_vol;}
void passager::setnum_siege(QString num_siege){this->num_siege=num_siege;}
void passager::setnb_valises(int nb_valises){this->nb_valises=nb_valises;}
void passager::setmail(QString mail){this->mail=mail;}
void passager::settype_passager(QString type_passager){this->type_passager=type_passager;}
void passager::setpoids_totale(int poids_totale){this->poids_totale=poids_totale;}

int passager::verifieremail(QString email)
{
 int temail=email.length(),iAT=0;

 for (int i=0;i<(temail-3);i++)
  {
      if (email[i]=='@' and iAT==0)
        iAT=1;//vrai
  }
 if ((email[temail-4]=='.' or email[temail-3]=='.') and iAT==1 )
     return 1;//vrai

return 0;//faux
}

bool passager::ajouter()
{
            QSqlQuery query;
                 query.prepare("INSERT INTO passager (nom_passager,prenom_passager,age_passager,cin_passager,passeport_passager,num_portail,num_vol,num_siege,nb_valises,mail,type_passager,poids_totale ) "
                               "VALUES (:nom_passager, :prenom_passager, :age_passager,:cin_passager,:passeport_passager,:num_portail,:num_vol,:num_siege,:nb_valises,:mail,:type_passager,:poids_totale)");
                 query.bindValue(":nom_passager", nom_passager);
                 query.bindValue(":prenom_passager", prenom_passager);
                 query.bindValue(":age_passager", age_passager);
                 query.bindValue(":cin_passager", cin_passager);
                 query.bindValue(":passeport_passager", passeport_passager);
                 query.bindValue(":num_portail", num_portail);
                 query.bindValue(":num_vol", num_vol);
                 query.bindValue(":num_siege", num_siege);
                 query.bindValue(":nb_valises", nb_valises);
                 query.bindValue(":mail", mail);
                 query.bindValue(":type_passager", type_passager);
                 query.bindValue(":poids_totale", poids_totale);


    return   query.exec();
}

bool passager::supprimer(int passeport_passager)
{
     QSqlQuery query;
     query.prepare("Delete from passager where passeport_passager=:passeport_passager");
     query.bindValue(":passeport_passager", passeport_passager);

return   query.exec();


}
QSqlQueryModel* passager::afficher()
{
      QSqlQueryModel* model=new QSqlQueryModel();
    model->setQuery("SELECT* FROM passager");
    model->setHeaderData(0, Qt::Horizontal, QObject:: tr("Nom du passager"));
    model->setHeaderData(1, Qt::Horizontal, QObject:: tr("Prénom du passager"));
    model->setHeaderData(2, Qt::Horizontal, QObject:: tr("Age du passager"));
    model->setHeaderData(3, Qt::Horizontal, QObject:: tr("CIN du passager"));
    model->setHeaderData(4, Qt::Horizontal, QObject:: tr("Numéro de passeport"));
    model->setHeaderData(5, Qt::Horizontal, QObject:: tr("Numéro du portail"));
    model->setHeaderData(6, Qt::Horizontal, QObject:: tr("Numéro du vol"));
    model->setHeaderData(7, Qt::Horizontal, QObject:: tr("Numéro du siège"));
    model->setHeaderData(8, Qt::Horizontal, QObject:: tr("Nombre de valises"));
    model->setHeaderData(9, Qt::Horizontal, QObject:: tr("Email du passager"));
    model->setHeaderData(10, Qt::Horizontal, QObject:: tr("Type du passager"));
    model->setHeaderData(11, Qt::Horizontal, QObject:: tr("Poids total autorisé"));

    return  model;
}
QSqlQueryModel* passager::afficher2()
{
      QSqlQueryModel* model=new QSqlQueryModel();
    model->setQuery("SELECT passeport_passager FROM passager");
    model->setHeaderData(0, Qt::Horizontal, QObject:: tr("Numéro de passeport"));
    return  model;
}
bool passager ::modifier()
{
                       QSqlQuery query;
    query.prepare("UPDATE passager SET nom_passager=:nom_passager,prenom_passager=:prenom_passager,age_passager=:age_passager,cin_passager=:cin_passager,passeport_passager=:passeport_passager,num_portail=:num_portail,num_vol=:num_vol,num_siege=:num_siege,nb_valises=:nb_valises,mail=:mail,type_passager=:type_passager,poids_totale=:poids_totale WHERE passeport_passager=:passeport_passager ");
                         query.bindValue(":nom_passager",nom_passager);
                         query.bindValue(":prenom_passager",prenom_passager);
                         query.bindValue(":age_passager",age_passager);
                         query.bindValue(":cin_passager",cin_passager);
                         query.bindValue(":passeport_passager",passeport_passager);
                         query.bindValue(":num_portail",num_portail);
                         query.bindValue(":num_vol",num_vol);
                         query.bindValue(":num_siege",num_siege);
                         query.bindValue(":nb_valises",nb_valises);
                         query.bindValue(":mail",mail);
                         query.bindValue(":type_passager",type_passager);
                         query.bindValue(":poids_totale",poids_totale);

                     return query.exec();}



QSqlQueryModel * passager::trieage()
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("SELECT * FROM PASSAGER ORDER BY AGE_PASSAGER");
    model->setHeaderData(0, Qt::Horizontal, QObject:: tr("Nom du passager"));
    model->setHeaderData(1, Qt::Horizontal, QObject:: tr("Prénom du passager"));
    model->setHeaderData(2, Qt::Horizontal, QObject:: tr("Age du passager"));
    model->setHeaderData(3, Qt::Horizontal, QObject:: tr("CIN du passager"));
    model->setHeaderData(4, Qt::Horizontal, QObject:: tr("Numéro de passeport"));
    model->setHeaderData(5, Qt::Horizontal, QObject:: tr("Numéro du portail"));
    model->setHeaderData(6, Qt::Horizontal, QObject:: tr("Numéro du vol"));
    model->setHeaderData(7, Qt::Horizontal, QObject:: tr("Numéro du siège"));
    model->setHeaderData(8, Qt::Horizontal, QObject:: tr("Nombre de valises"));
    model->setHeaderData(9, Qt::Horizontal, QObject:: tr("Email du passager"));
    model->setHeaderData(10, Qt::Horizontal, QObject:: tr("Type du passager"));
    model->setHeaderData(11, Qt::Horizontal, QObject:: tr("Poids total autorisé"));
    return model;
}
QSqlQueryModel * passager::trievalise()
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("SELECT * FROM PASSAGER ORDER BY NB_VALISES");
    model->setHeaderData(0, Qt::Horizontal, QObject:: tr("Nom du passager"));
    model->setHeaderData(1, Qt::Horizontal, QObject:: tr("Prénom du passager"));
    model->setHeaderData(2, Qt::Horizontal, QObject:: tr("Age du passager"));
    model->setHeaderData(3, Qt::Horizontal, QObject:: tr("CIN du passager"));
    model->setHeaderData(4, Qt::Horizontal, QObject:: tr("Numéro de passeport"));
    model->setHeaderData(5, Qt::Horizontal, QObject:: tr("Numéro du portail"));
    model->setHeaderData(6, Qt::Horizontal, QObject:: tr("Numéro du vol"));
    model->setHeaderData(7, Qt::Horizontal, QObject:: tr("Numéro du siège"));
    model->setHeaderData(8, Qt::Horizontal, QObject:: tr("Nombre de valises"));
    model->setHeaderData(9, Qt::Horizontal, QObject:: tr("Email du passager"));
    model->setHeaderData(10, Qt::Horizontal, QObject:: tr("Type du passager"));
    model->setHeaderData(11, Qt::Horizontal, QObject:: tr("Poids total autorisé"));
    return model;
}

QSqlQueryModel * passager::triealphabet()
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("SELECT * FROM PASSAGER ORDER BY NOM_PASSAGER");
    model->setHeaderData(0, Qt::Horizontal, QObject:: tr("Nom du passager"));
    model->setHeaderData(1, Qt::Horizontal, QObject:: tr("Prénom du passager"));
    model->setHeaderData(2, Qt::Horizontal, QObject:: tr("Age du passager"));
    model->setHeaderData(3, Qt::Horizontal, QObject:: tr("CIN du passager"));
    model->setHeaderData(4, Qt::Horizontal, QObject:: tr("Numéro de passeport"));
    model->setHeaderData(5, Qt::Horizontal, QObject:: tr("Numéro du portail"));
    model->setHeaderData(6, Qt::Horizontal, QObject:: tr("Numéro du vol"));
    model->setHeaderData(7, Qt::Horizontal, QObject:: tr("Numéro du siège"));
    model->setHeaderData(8, Qt::Horizontal, QObject:: tr("Nombre de valises"));
    model->setHeaderData(9, Qt::Horizontal, QObject:: tr("Email du passager"));
    model->setHeaderData(10, Qt::Horizontal, QObject:: tr("Type du passager"));
    model->setHeaderData(11, Qt::Horizontal, QObject:: tr("Poids total autorisé"));
    return model;
}
void passager :: recherche(QTableView * table ,QString rech )
{
    QSqlQueryModel *model= new QSqlQueryModel();
    QString cin_passager_string=QString::number(cin_passager);
    QString passeport_passager_string=QString::number(passeport_passager);

    QSqlQuery *query=new QSqlQuery;
    query->prepare("select * from passager where type_passager like '%"+rech+"%'  or passeport_passager like '%"+rech+"%'or nom_passager like '%"+rech+"%';");

    query->exec();
    model->setQuery(*query);
    table->setModel(model);
    table->show();

}
void  passager::telechargerPDF(){



                            QPdfWriter pdf("C:/Users/toufa/OneDrive/Bureau/Projet QT/Export PDF/PDF.pdf");


                              QPainter painter(&pdf);
                             int i = 3500;
                             QPixmap pixmapl("C:/Users/toufa/OneDrive/Bureau/Projet QT/Export PDF/Images PDF/logo.png");
                             QPixmap pixmapl2("C:/Users/toufa/OneDrive/Bureau/Projet QT/Export PDF/Images PDF/logoesprit.png");
                                  painter.setPen(Qt::red);
                                  painter.setFont(QFont("Century Gothic", 30,QFont::Bold));
                                  painter.drawText(2700,1400,"Liste des passagers");
                                  painter.setPen(Qt::black);
                                  painter.drawLine(100,2500,9550,2500);
                                  painter.drawLine(100,3000,9550,3000);
                                  painter.drawLine(100,11000,9550,11000);
                                  painter.drawLine(100,2500,100,11000);
                                  painter.drawLine(2375,2500,2375,11000);
                                  painter.drawLine(4750,2500,4750,11000);
                                  painter.drawLine(7150,2500,7150,11000);
                                  painter.drawLine(9550,2500,9550,11000);
                                  painter.setFont(QFont("Calibri",16,QFont::Bold));
                                  painter.drawText(1000,2800,"Nom");
                                  painter.drawText(3200,2800,"Prénom");
                                  painter.drawText(5400,2800,"Passeport");
                                  painter.drawText(7700,2800,"Numéro vol");


                                  QSqlQuery query;
                                  query.prepare("select * from passager");
                                  query.exec();
                                  while (query.next())
                                  {
                                      painter.setFont(QFont("Calibri",14));
                                      painter.drawText(700,i,query.value(0).toString());
                                      painter.drawText(3000,i,query.value(1).toString());
                                      painter.drawText(5300,i,query.value(4).toString());
                                      painter.drawText(7700,i,query.value(6).toString());


                                     i = i + 500;
                                  }
                                  painter.drawPixmap(100,100,2000,1200, pixmapl);
                                  painter.drawPixmap(7900,500,1500,500, pixmapl2);

                                  QString s ="Tunis le "+ QDate::currentDate().toString();

                                  painter.setFont(QFont("Arial",15));

                                  painter.drawText(6000,12000,s);
                                  QDesktopServices::openUrl(QUrl::fromLocalFile("C:/Users/toufa/OneDrive/Bureau/Projet QT/Export PDF/PDF.pdf"));
}
