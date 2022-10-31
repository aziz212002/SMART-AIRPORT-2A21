#include "passagers.h"
#include<QSqlQuery>
#include <QtDebug>
#include<QObject>
passager::passager()
{
passeport_passager=0;
nom_passager=" ";prenom_passager=" ";age_passager=0,cin_passager=0,num_portail=0;num_vol=" ";num_siege=" ";nb_valises=0;mail=" ";
}

passager::passager(QString nom_passager, QString prenom_passager , int age_passager,int cin_passager,int passeport_passager,int num_portail, QString num_vol , QString num_siege, int nb_valises, QString mail)
{this->nom_passager=nom_passager;this->prenom_passager=prenom_passager,this->age_passager=age_passager;this->cin_passager=cin_passager;this->passeport_passager=passeport_passager;this->num_portail=num_portail;this->num_vol=num_vol;this->num_siege=num_siege;this->nb_valises=nb_valises;this->mail=mail;}

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



bool passager::ajouter()
{
            QSqlQuery query;
                 query.prepare("INSERT INTO passeport (nom_passager,prenom_passager,age_passager,cin_passager,passeport_passager,num_portail,num_vol,num_siege,nb_valises,mail ) "
                               "VALUES (:nom_passager, :prenom_passager, :age_passager,:cin_passager,:passeport_passager,:num_portail,:num_vol,:num_siege,:nb_valises,:mail)");
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

    return  model;
}
bool passager ::modifier()
{
                       QSqlQuery query;
    query.prepare("UPDATE passager SET nom_passager=:nom_passager,prenom_passager=:prenom_passager,age_passager=:age_passager,cin_passager=:cin_passager,passeport_passager=:passeport_passager,num_portail=:num_portail,num_vol=:num_vol,num_siege=:num_siege,nb_valises=:nb_valises,mail=:mail WHERE passeport_passager=:passeport_passager ");
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

                     return query.exec();}
