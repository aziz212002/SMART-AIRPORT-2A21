#ifndef PERSONNEL_H
#define PERSONNEL_H


#include<QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <iostream>
#include <string>
#include <QSqlQuery>
#include <QtDebug>

class Personnel
{
private:

   int CIN_per;
   int num_tel ;
   int age_per;
    QString nom_per;
    QString prenom_per;
    QString mail_per;

public:

Personnel();
Personnel(int CIN_per,int num_tel,int age_per,QString nom_per,QString prenom_per,QString mail_per);
int getCIN_per(){return CIN_per;}
int getnum_tel(){return num_tel;}
int getage_per(){return age_per;}
QString getnom_per(){return nom_per;}
QString getprenom_per(){return prenom_per;}
QString getmail_per(){return mail_per;}

void setCIN_per(int CIN_per){this->CIN_per=CIN_per;}
void setnum_tel(int num_tel){this->num_tel=num_tel;}
void setage_per(int age_per){this->age_per=age_per;}
void setnom_per(QString  nom_per){this-> nom_per= nom_per;}
void setprenom_per(QString prenom_per){this->prenom_per=prenom_per;}
void setmail_per(QString mail_per){this->mail_per=mail_per;}
bool Ajouter();
QSqlQueryModel* afficher();
bool modifier();
bool supprimer(int);
QSqlQueryModel* Recherchepersonnel(QString);
QSqlQueryModel* trierpersonnelparCin();
QSqlQueryModel* trierpersonnelparAge();
QSqlQueryModel* trierpersonnelparordrealphabetiquedunom();
void telechargerPDF();
/*bool login();*/

};



#endif // PERSONNEL_H
