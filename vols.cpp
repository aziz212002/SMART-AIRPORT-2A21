#include "vols.h"
#include <QPdfWriter>
#include <QPainter>
#include <QDesktopServices>
#include <QPrinter>
#include <QFileDialog>
#include <QTextDocument>
vols::vols()
{

}
vols::vols(int num_vols,QDate d_vols,int cap_vols,QString dest,int nb)
{
    this->num_vols = num_vols ;
    this->d_vols = d_vols ;
    this->cap_vols = cap_vols ;
    this->dest = dest ;
    this->nb = nb ;
}


int vols::getnum_vols(){return num_vols;}
QDate vols::getd_vols(){return d_vols;}
int vols::getcap_vols(){return cap_vols;}
QString vols::getdest(){return dest;}
int vols::getnb(){return nb;}


void vols::setnum_vols(int num_vols){this->num_vols=num_vols;}
void vols::setd_vols(QDate d_vols){this->d_vols=d_vols;}
void vols::setcap_vols(int cap_vols){this->cap_vols=cap_vols;}
void vols::setdest(QString dest){this->dest=dest;}
void vols::setnb(int nb){this->nb=nb;}




bool vols::ajoutervols()
{

     QSqlQuery query;
     query.prepare("INSERT INTO VOLS (num_vols, d_vols, cap_vols ,dest,nb) "
                   "VALUES (:num_vols, :d_vols, :cap_vols, :dest, :nb)");// prparation de requette
     query.bindValue(":num_vols", num_vols); //remplir CIN2 dans CIN1
     query.bindValue(":d_vols", d_vols);
     query.bindValue(":cap_vols",cap_vols);
     query.bindValue(":dest",dest);
     query.bindValue(":nb",nb);

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
     model->setHeaderData(4, Qt::Horizontal, QObject::tr("NB"));

     return model;
}
QSqlQueryModel* vols::afficherlghayb()
{
     QSqlQueryModel* model=new QSqlQueryModel();

     model->setQuery("SELECT *  FROM LGHAYB ");
     model->setHeaderData(0, Qt::Horizontal, QObject::tr("NOMBRE_DE_VOLS "));//nom entite
     model->setHeaderData(1, Qt::Horizontal, QObject::tr("NB_DE_VOYAGEURS"));


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
double vols::ESTIMATION(  QString s){
    int i=0,n=0;
    QSqlQuery q1,q2,q3;
    QString s1="SELECT * FROM "+s;
    q1.prepare(s1);
if( q1.exec())
   {
    float a,b,x[100],y[100];

    while (q1.next()){n++;
        x[i]=(q1.value(0).toInt());
        y[i]=(q1.value(1).toInt());
        qDebug()<<y[i];
        i++;


    }



       double xsum=0,ysum=0,x2sum=0,xysum=0;
       for (i=0;i<n;i++)
       {
           xsum=xsum+x[i];                        //calculate sigma(xi)
           ysum=ysum+y[i];                        //calculate sigma(yi)
           x2sum=x2sum+pow(x[i],2);                //calculate sigma(x^2i)
           xysum=xysum+x[i]*y[i];
       }
       a=(n*xysum-xsum*ysum)/(n*x2sum-xsum*xsum);            //calculate slope
       b=(x2sum*ysum-xsum*xysum)/(x2sum*n-xsum*xsum);
qDebug()<<a;
return b+(a*(n+1));}
else
    return -1;

}

