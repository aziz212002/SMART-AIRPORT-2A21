#include "avion.h"
#include <QPdfWriter>
#include <QPainter>
#include <QDesktopServices>
#include <QPrinter>
#include <QFileDialog>
#include <QTextDocument>
#include <iostream>
using namespace std;
#define STR_EQUAL 0
Avion::Avion()
{

}
Avion::Avion(int a , QString b , QString  c, float e, float f, float k, QString g)
{
    this->Id_avion = a ;
    this->marque= b ;
    this->type_moteur = c ;
    this->conso = e ;
    this->kilometrage = f ;
    this->prix_achat = k ;
    this->etat_avion = g ;
}
QSqlQueryModel * Avion::afficher()
{
    QSqlQueryModel *model=new QSqlQueryModel();
    model->setQuery("SELECT * FROM AVION ");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("Id_avion"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("marque"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("type_moteur"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("conso"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("kilometrage"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("prix_achat"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("etat_avion"));

    return model;
}
    bool Avion::ajouter()

    {
           QSqlQuery query;
           QString res  = QString::number(Id_avion);
           QString res1 = QString::number(conso);
           QString res2 = QString::number(kilometrage);
           QString res3 = QString::number(prix_achat);

           query.prepare("INSERT INTO AVION(ID,MARQUE,TYPE_AV,CONSO,KILOM,PRIX_AV,ETAT)""VALUES (:id,:marque,:type,:conso,:kilom,:prix,:etat_avion)");

            query.bindValue(":id",res);
            query.bindValue(":marque",marque);
            query.bindValue(":type",type_moteur);
            query.bindValue(":conso",res1);
            query.bindValue(":kilom",res2);
            query.bindValue(":prix",res3);
            query.bindValue(":etat_avion",etat_avion);

            return query.exec();
    }
    bool Avion:: supprimer(int Id_avion)
    {
    QSqlQuery query;
    int res3=Id_avion;
      query.prepare ("Delete from avion where ID= :id");
      query.addBindValue (res3);
      return query.exec () ;
     }
    bool Avion::supprimerTout()
    {
        QSqlQuery query;
              query.prepare("TRUNCATE TABLE AVION");
              return query.exec();

    }
    bool Avion::modifier(int Id_avion)
    {
        QSqlQuery query;
        QString res = QString::number(Id_avion);
        QString res1 = QString::number(conso);
        QString res2 = QString::number(kilometrage);
        QString res3 = QString::number(prix_achat);
              query.prepare("UPDATE AVION SET MARQUE=:marque,TYPE_AV=:type,CONSO=:conso,KILOM=:kilom,PRIX_AV=:prix,ETAT=:etat WHERE ID=:id  ");


              query.bindValue(":id",res);
              query.bindValue(":marque",marque);
              query.bindValue(":type",type_moteur);
              query.bindValue(":conso",res1);
              query.bindValue(":kilom",res2);
              query.bindValue(":prix",res3);
              query.bindValue(":etat",etat_avion);

              return query.exec();

    }

    QSqlQueryModel* Avion::tri()
    {
        QSqlQueryModel *model=new QSqlQueryModel();
                model->setQuery("select * from AVION order by ID");
                model->setHeaderData(0,Qt::Horizontal,QObject::tr("Id_avion"));
                model->setHeaderData(1,Qt::Horizontal,QObject::tr("marque"));
                model->setHeaderData(2,Qt::Horizontal,QObject::tr("type_moteur"));
                model->setHeaderData(3,Qt::Horizontal,QObject::tr("conso"));
                model->setHeaderData(4,Qt::Horizontal,QObject::tr("kilometrage"));
                model->setHeaderData(5,Qt::Horizontal,QObject::tr("prix_achat"));
                model->setHeaderData(6,Qt::Horizontal,QObject::tr("etat_avion"));



       return model;
    }
    QSqlQueryModel* Avion ::triconso()
    {
        QSqlQueryModel *model=new QSqlQueryModel();
        model->setQuery("select * from AVION order by CONSO");

              model->setHeaderData(0,Qt::Horizontal,QObject::tr("Id_avion"));
              model->setHeaderData(1,Qt::Horizontal,QObject::tr("marque"));
              model->setHeaderData(2,Qt::Horizontal,QObject::tr("type_moteur"));
              model->setHeaderData(3,Qt::Horizontal,QObject::tr("conso"));
              model->setHeaderData(4,Qt::Horizontal,QObject::tr("kilometrage"));
              model->setHeaderData(5,Qt::Horizontal,QObject::tr("prix_achat"));
              model->setHeaderData(6,Qt::Horizontal,QObject::tr("etat_avion"));

       return model;

    }
    QSqlQueryModel* Avion ::triprix()
    {
        QSqlQueryModel *model=new QSqlQueryModel();
        model->setQuery("select * from AVION order by PRIX_AV");

        model->setHeaderData(0,Qt::Horizontal,QObject::tr("Id_avion"));
        model->setHeaderData(1,Qt::Horizontal,QObject::tr("marque"));
        model->setHeaderData(2,Qt::Horizontal,QObject::tr("type_moteur"));
        model->setHeaderData(3,Qt::Horizontal,QObject::tr("conso"));
        model->setHeaderData(4,Qt::Horizontal,QObject::tr("kilometrage"));
        model->setHeaderData(5,Qt::Horizontal,QObject::tr("prix_achat"));
        model->setHeaderData(6,Qt::Horizontal,QObject::tr("etat_avion"));

       return model;
   }
       QSqlQueryModel* Avion ::cherche_id(int Id_avion)
    {
        QString res=QString ::number(Id_avion);
        QSqlQueryModel *model=new QSqlQueryModel();
                model->setQuery("select * from AVION where ID ='"+res+"'");
                model->setHeaderData(0,Qt::Horizontal,QObject::tr("Id_avion"));
                model->setHeaderData(1,Qt::Horizontal,QObject::tr("marque"));
                model->setHeaderData(2,Qt::Horizontal,QObject::tr("type_moteur"));
                model->setHeaderData(3,Qt::Horizontal,QObject::tr("conso"));
                model->setHeaderData(4,Qt::Horizontal,QObject::tr("kilometrage"));
                model->setHeaderData(5,Qt::Horizontal,QObject::tr("prix_achat"));
                model->setHeaderData(6,Qt::Horizontal,QObject::tr("etat_avion"));

       return model;

    }
       QSqlQueryModel * Avion::recherche(QString res)
            {


                QSqlQueryModel *model=new QSqlQueryModel();
                model->setQuery("SELECT * FROM AVION WHERE ( ID LIKE '%"+res+"%' OR CONSO LIKE '%"+res+"%' OR KILOM LIKE '%"+res+"%' OR PRIX_AV LIKE '%"+res+"%' ) ");
                model->setHeaderData(0,Qt::Horizontal,QObject::tr("Id_avion"));
                model->setHeaderData(1,Qt::Horizontal,QObject::tr("marque"));
                model->setHeaderData(2,Qt::Horizontal,QObject::tr("type_moteur"));
                model->setHeaderData(3,Qt::Horizontal,QObject::tr("conso"));
                model->setHeaderData(4,Qt::Horizontal,QObject::tr("kilometrage"));
                model->setHeaderData(5,Qt::Horizontal,QObject::tr("prix_achat"));
                model->setHeaderData(6,Qt::Horizontal,QObject::tr("etat_avion"));

                return model;
            }
       int Avion::alerte()
       {
           QSqlQuery query;
           int i=0;
           QString testing;

           query.prepare(QString("SELECT ETAT FROM AVION"));
           query.exec();
           QString panne="En panne";
           while(query.next()){

               cout<<"etat de la ligne "<<query.value(0).toString().toStdString()<<"  ";
               cout<<(QString::compare(query.value(0).toString(), panne, Qt::CaseInsensitive)== STR_EQUAL)<<endl;

               if(QString::compare(query.value(0).toString(), panne, Qt::CaseInsensitive)== STR_EQUAL)
               {
                   i++;
               }
           }

           cout<<"valeur de i "<<i<<endl;

           return i;
       }


    void Avion::CREATION_PDF()
    {
        QString fileName = QFileDialog::getSaveFileName((QWidget* )0, "Export PDF", QString(), "*.pdf");
        if (QFileInfo(fileName).suffix().isEmpty())
            { fileName.append(".pdf"); }

        QPrinter printer(QPrinter::PrinterResolution);
        printer.setOutputFormat(QPrinter::PdfFormat);
        printer.setPaperSize(QPrinter::A4);
        printer.setOutputFileName(fileName);

        QTextDocument doc;
        QSqlQuery q;
        q.prepare("SELECT * FROM AVION ");
        q.exec();
        QString pdf="<br> <h1  style='color:blue'>LISTE DES AVIONS  <br></h1>\n <br> <table>  <tr>  <th>CIN </th> <th>NOM </th> <th>PRENOM  </th> <th>AGE  </th><th>TEL  </th><th>ADRESS   </th> </tr>" ;
    //br traja ll star oel tr tzidlek colonne th tzidlek ligne h1 asghrr size o akbr size h6 //

        while ( q.next())
            {

            pdf= pdf+ " <br> <tr> <td>"+ q.value(0).toString()+" " + q.value(1).toString() +"</td>   <td>" +q.value(2).toString() +" <td>" +q.value(3).toString() +" <td>" +q.value(4).toString() +" <td>" +q.value(5).toString() +" "" " "</td> </td>" ;
        }
        doc.setHtml(pdf);
        doc.setPageSize(printer.pageRect().size()); // This is necessary if you want to hide the page number
        doc.print(&printer);


    }
    void Avion::statistique(QVector<double>* ticks,QVector<QString> *labels)
          {
              QSqlQuery q;
              int i=0;
              q.exec("select CONSO from AVION");
              while (q.next())
              {
                  QString id_event = q.value(0).toString();
                  i++;
                  *ticks<<i;
                  *labels <<id_event;
              }
          }








































    /*  QChart * Equipement::Statistique(){


        QSqlQuery q,q1,q2;
        q.exec("Select * from equipement");
        int tot=0;
        while (q.next())
            tot++;
        q1.prepare("Select * from Equipement where etat = :nom ");
        q1.bindValue(":nom","En panne");
        q1.exec();

        int tot_panne=0;
        while (q1.next())
            tot_panne++;

        qreal pour_panne=(tot_panne*100)/tot;

        q2.prepare("Select * from Equipement where etat = :nom ");
        q2.bindValue(":nom","Actif");
        q2.exec();
        int tot_act=0;
        while (q2.next())
            tot_act++;

        qreal pour_act=(tot_act*100)/tot;



        QPieSeries *series = new QPieSeries();
         series->append("En panne",pour_panne);
         series->append("Actif",pour_act);
         QPieSlice *slice0= series->slices().at(0);
         slice0->setLabelVisible();
         QPieSlice *slice1 = series->slices().at(1);
         slice1->setLabelVisible();
         slice1->setBrush(Qt::green);

         QChart *chart = new QChart();
         chart->addSeries(series);
         chart->setTitle("Etat de les equipements");
         chart->legend()->hide();


        return chart;

    }*/





