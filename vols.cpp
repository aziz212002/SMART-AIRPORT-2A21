#include "vols.h"

vols::vols()
{

}
vols::vols(int num_vols,QDate d_vols,int cap_vols,QString dest)
{
    this->num_vols = num_vols ;
    this->d_vols = d_vols ;
    this->cap_vols = cap_vols ;
    this->dest = dest ;
}


int vols::getnum_vols(){return num_vols;}
QDate vols::getd_vols(){return d_vols;}
int vols::getcap_vols(){return cap_vols;}
QString vols::getdest(){return dest;}


void vols::setnum_vols(int num_vols){this->num_vols=num_vols;}
void vols::setd_vols(QDate d_vols){this->d_vols=d_vols;}
void vols::setcap_vols(int cap_vols){this->cap_vols=cap_vols;}
void vols::setdest(QString dest){this->dest=dest;}





bool vols::ajoutervols()
{

     QSqlQuery query;
     query.prepare("INSERT INTO VOLS (num_vols, d_vols, cap_vols ,dest) "
                   "VALUES (:num_vols, :d_vols, :cap_vols, :dest)");// prparation de requette
     query.bindValue(":num_vols", num_vols); //remplir CIN2 dans CIN1
     query.bindValue(":d_vols", d_vols);
     query.bindValue(":cap_vols",cap_vols);
     query.bindValue(":dest",dest);
     return query.exec();

}



QSqlQueryModel* vols::affichervols()
{
     QSqlQueryModel* model=new QSqlQueryModel();

     model->setQuery("SELECT *  FROM vols ");
     model->setHeaderData(0, Qt::Horizontal, QObject::tr("numero de vols"));//nom entite
     model->setHeaderData(1, Qt::Horizontal, QObject::tr("date de vols"));
     model->setHeaderData(2, Qt::Horizontal, QObject::tr("capacite"));
     model->setHeaderData(3, Qt::Horizontal, QObject::tr("destination"));

     return model;
}



bool vols::supprimervols(int num_vols)
{
    QSqlQuery query;
    query.prepare(" Delete from vols where num_vols=:num_vols ");
    query.bindValue(":num_vols",num_vols);

    return query.exec();
}




bool vols::modifiervols(int num_vols,QDate d_vols,int cap_vols,QString dest)
{

        QSqlQuery query;
        query.prepare("update vols set d_vols=:d_vols,cap_vols=:cap_vols,dest=:dest where num_vols=:num_vols");
        query.bindValue(":num_vols",num_vols);
        query.bindValue(":d_vols",d_vols);
        query.bindValue(":cap_vols",cap_vols);
        query.bindValue(":dest",dest);
        return query.exec();

    }
QSqlQueryModel* vols::Recherchevols(QString recherche)
 {
     QSqlQueryModel * model= new QSqlQueryModel();
     model->setQuery("SELECT * FROM vols WHERE num_vols LIKE '"+recherche+"%' OR d_vols LIKE '"+recherche+"%' OR dest LIKE '"+recherche+"%'");
     model->setHeaderData(0, Qt::Horizontal, QObject::tr("num_vols"));
     model->setHeaderData(1, Qt::Horizontal, QObject::tr("d_vols"));
     model->setHeaderData(2, Qt::Horizontal, QObject::tr("cap_vols"));
     model->setHeaderData(3, Qt::Horizontal, QObject::tr("dest"));


return model;
}
bool vols::supprimerTout()
{
    QSqlQuery query;
    query.prepare("delete from vols ");
    return query.exec();
}

QSqlQueryModel * vols::triervolsParnvols()
{

    QSqlQuery * q = new  QSqlQuery ();
           QSqlQueryModel * model = new  QSqlQueryModel ();
           q->prepare("SELECT * FROM VOLS order by num_vols ASC");
           q->exec();
           model->setQuery(*q);
           return model;
}

QSqlQueryModel * vols::triervolsParnbplace()
{

    QSqlQuery * q = new  QSqlQuery ();
           QSqlQueryModel * model = new  QSqlQueryModel ();
           q->prepare("SELECT * FROM VOLS order by cap_vols ASC");
           q->exec();
           model->setQuery(*q);
           return model;
}


QSqlQueryModel * vols::triervolspardate()
{

    QSqlQuery * q = new  QSqlQuery ();
           QSqlQueryModel * model = new  QSqlQueryModel ();
           q->prepare("SELECT * FROM VOLS order by d_vols ASC");
           q->exec();
           model->setQuery(*q);
           return model;
}



