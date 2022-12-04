#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "arduino.h"
#include <QPdfWriter>
#include <QPainter>
#include <QSqlQuery>
#include<QtCharts>

#include<QPieSlice>
#include<QPieSeries>
#include<QPrinter>
#include <QFileDialog>
#include<QPrintDialog>
#include <QPdfWriter>
#include <QPainter>
#include <QDesktopServices>
#include <QPrinter>
#include <QFileDialog>
#include <QTextDocument>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEdit_n_de_vol->setValidator( new QIntValidator(0, 999999, this));
    ui->lineEdit_nb->setValidator( new QIntValidator(0, 999999, this));
    ui->lineEdit_capacitevol->setValidator( new QIntValidator(0, 300, this));
    ui->lineEdit_numvolsupprimer->setValidator( new QIntValidator(0, 999999, this));
    ui->lineEdit_recherche->setValidator( new QIntValidator(0, 999999, this));
    int ret=a.connect_arduino(); // lancer la connexion Ã  arduino
        switch(ret){
        case(0):qDebug()<< "arduino is available and connected to : "<< a.getarduino_port_name();
            break;
        case(1):qDebug() << "arduino is available but not connected to :" <<a.getarduino_port_name();
           break;
        case(-1):qDebug() << "arduino is not available";
        }
         QObject::connect(a.getserial(),SIGNAL(readyRead()),this,SLOT(update_label())); // permet de lancer
         //le slot update_label suite Ã  la reception du signal readyRead (reception des donnÃ©es).



}
void MainWindow::update_label()
{
 data="";

while((a.getdata().size()<5))
{
    QString key;
data=a.read_from_arduino();

break;

}
if(data!=""){
if(data.toInt()!=0)
{int D=data.toInt();
    qDebug() << D ;
 a.fire();
 ui->tableView_vols->setModel(V.affichervols());

a.write_to_arduino("0");
}};
data="";
}
MainWindow::~MainWindow()
{
    delete ui;

}



void MainWindow::on_pushButton_Ajoutervols_clicked()
{
        int num_vols=ui->lineEdit_n_de_vol->text().toInt(); //convertir en entier
        QDate d_vols=ui->lineeditdateTimeEdit->date();
        int cap_vols=ui->lineEdit_capacitevol->text().toInt();
        QString dest=ui->lineEdit_Destination->text();
        int nb=ui->lineEdit_nb->text().toInt();
        vols E(num_vols,d_vols,cap_vols,dest,nb);
            bool test=E.ajoutervols();
            if(test)
                  {    QMessageBox::information(nullptr, QObject::tr("ajout avec succes"),
                                                QObject::tr("ajout successful.\n"
                                                            "Click Cancel to exit."), QMessageBox::Cancel);
                        ui->tableView_vols->setModel(V.affichervols());//mise a jour ecran
                  }
                                else
                                    QMessageBox::critical(nullptr, QObject::tr("Ajout errer"),
                                                QObject::tr("ajout failed.\n"
                                                            "Click Cancel to exit."), QMessageBox::Cancel);

                 ui->lineEdit_n_de_vol->clear();
                 ui->lineEdit_capacitevol->clear();
                 ui->lineEdit_Destination->clear();
                 ui->lineEdit_nb->clear();
    }




void MainWindow::on_pushButton_afichervols_clicked()
{
    ui->tableView_vols->setModel(V.affichervols());
}

void MainWindow::on_pushButton_supprimer_clicked()
{

        vols V1;
        V1.setnum_vols(ui->lineEdit_numvolsupprimer->text().toInt());
        bool test=V1.supprimervols(V1.getnum_vols());
        QMessageBox msgBox;
        if (ui->lineEdit_numvolsupprimer->text()=="")
        {
            QMessageBox::critical(this, QObject::tr("Suppression Errer"),
                               QObject::tr("Echec de Suppression!!!\n""Veuillez remplir la label de CIN"), QMessageBox::Cancel);
        }
        else if (test)
        {
            QMessageBox::information(this, QObject::tr("Suppression avec Succes"),
                               QObject::tr("Suppression avec succes"), QMessageBox::Cancel);
            ui->tableView_vols->setModel(V.affichervols());
        }
        ui->lineEdit_numvolsupprimer->clear();
    }


void MainWindow::on_pushButton_modifiervol_clicked()
{

        int num_vols=ui->lineEdit_n_de_vol->text().toInt();
        QDate d_vols=ui->lineeditdateTimeEdit->date();
        int cap_vols=ui->lineEdit_capacitevol->text().toInt();
        QString dest=ui->lineEdit_Destination->text();
        int nb=ui->lineEdit_nb->text().toInt();
        vols V(num_vols,d_vols,cap_vols,dest,nb);

        bool test=V.modifiervols(V.getnum_vols(),V.getd_vols(),V.getcap_vols(),V.getdest());

        QMessageBox msgBox;

        if(test)
        {
            QMessageBox::information(this, QObject::tr("Modification Succes"),
                               QObject::tr("Modifications mrigla"), QMessageBox::Cancel);
            ui->tableView_vols->setModel(V.affichervols());

        }
        else
        {

            QMessageBox::critical(this, QObject::tr("Modification Erreur"),
                               QObject::tr("Erreur de Modifications"), QMessageBox::Cancel);

        }

        ui->lineEdit_n_de_vol->clear();
        ui->lineEdit_capacitevol->clear();
        ui->lineEdit_Destination->clear();
        ui->lineEdit_nb->clear();

    }



void MainWindow::on_tableView_vols_clicked(const QModelIndex &index)
{
    ui->lineEdit_n_de_vol->setText(ui->tableView_vols->model()->data(ui->tableView_vols->model()->index(index.row(),0)).toString());
    ui->lineEdit_capacitevol->setText(ui->tableView_vols->model()->data(ui->tableView_vols->model()->index(index.row(),2)).toString());
    ui->lineEdit_Destination->setText(ui->tableView_vols->model()->data(ui->tableView_vols->model()->index(index.row(),3)).toString());

}
void MainWindow::on_lineEdit_recherche_textChanged()
{
    QString rech=ui->lineEdit_recherche->text();
    ui->tableView_vols->setModel(V.Recherchevols(rech));
}
void MainWindow::on_pushButton_Reset_clicked()
{
    vols V1;
    bool test=V1.supprimerTout();
    QMessageBox msgBox;
         if(test)
          {    QMessageBox::information(nullptr, QObject::tr("Reset avec succes"),
                                        QObject::tr("Reset jwwha beehy.\n"
                                                    "Click Cancel to exit."), QMessageBox::Cancel);
                         ui->tableView_vols->setModel(V.affichervols());
          }
                        else
                            QMessageBox::critical(nullptr, QObject::tr("Reset errer"),
                                        QObject::tr("Reset failed.\n"
                                                    "Click Cancel to exit."), QMessageBox::Cancel);
}


void MainWindow::on_SSS_activated()
{
    if(ui->SSS->currentText()=="Tri par NUM_VOLS")
    {
        ui->tableView_vols->setModel(V.triervolsParnvols());

    }
    else if(ui->SSS->currentText()=="Tri par CAP_VOLS")
    {
        ui->tableView_vols->setModel(V.triervolsParnbplace());

    }
    else
    {
        ui->tableView_vols->setModel(V.triervolspardate());
    }
}

/*void MainWindow::on_pushButton_statestique_clicked()
{
        QSqlQueryModel * model= new QSqlQueryModel();
                         model->setQuery("select * from VOLS where CAP_VOLS < 100 ");
                         float cap=model->rowCount();
                         model->setQuery("select * from VOLS where CAP_VOLS  between 100 and 250 ");
                         float capp=model->rowCount();
                         model->setQuery("select * from VOLS where CAP_VOLS > 250 ");
                         float cappp=model->rowCount();
                         float total=cap+capp+cappp;
                         QString a=QString("moins de 100 places "+QString::number((cap*100)/total,'f',2)+"%" );
                         QString b=QString("entre 100 et 200 places"+QString::number((capp*100)/total,'f',2)+"%" );
                         QString c=QString("+250 places"+QString::number((cappp*100)/total,'f',2)+"%" );
                         QPieSeries *series = new QPieSeries();
                         series->append(a,cap);
                         series->append(b,capp);
                         series->append(c,cappp);
                 if (cap!=0)
                 {QPieSlice *slice = series->slices().at(0);
                  slice->setLabelVisible();
                  slice->setPen(QPen());}
                 if ( cap!=0)
                 {
                          // Add label, explode and define brush for 2nd slice
                          QPieSlice *slice1 = series->slices().at(1);
                          //slice1->setExploded();
                          slice1->setLabelVisible();
                 }
                 if(cap!=0)
                 {
                          // Add labels to rest of slices
                          QPieSlice *slice2 = series->slices().at(2);
                          //slice1->setExploded();
                          slice2->setLabelVisible();
                 }
                         // Create the chart widget
                         QChart *chart = new QChart();
                         // Add data to chart with title and hide legend
                         chart->addSeries(series);
                         chart->setTitle("Pourcentage Par Capacite d'avion :Nombre Des Avions "+ QString::number(total));
                         chart->legend()->hide();
                         // Used to display the chart
                         QChartView *chartView = new QChartView(chart);
                         chartView->setRenderHint(QPainter::Antialiasing);
                         chartView->resize(1000,500);
                         chartView->show();





}


*/


void MainWindow::on_pushButton_pdf_clicked()
{
    QPdfWriter pdf("C:\\Users\\USER\\Desktop\\QTT\\ilyessgestion\\PDF_Employe.pdf");

      QPainter painter(&pdf);
      int i = 4000;
             painter.setPen(Qt::red);
             painter.setFont(QFont("Time New Roman", 25));
             painter.drawText(3000,1400,"Liste Des vols");
             painter.setPen(Qt::black);
             painter.setFont(QFont("Time New Roman", 15));
             painter.drawRect(100,3000,9400,500);
             painter.setFont(QFont("Time New Roman", 9));
             painter.drawText(400,3300,"num_vols");
             painter.drawText(2350,3300,"d_vols");
             painter.drawText(4200,3300,"cap_vols");
             painter.drawText(5400,3300,"dest");
             painter.drawRect(100,3000,9400,9000);

             QSqlQuery query;
             query.prepare("select * from VOLS");
             query.exec();
             while (query.next())
             {
                 painter.drawText(400,i,query.value(0).toString());
                 painter.drawText(2100,i,query.value(1).toString());
                 painter.drawText(4300,i,query.value(2).toString());
                 painter.drawText(5400,i,query.value(3).toString());


                i = i + 350;
             }
             QMessageBox::information(this, QObject::tr("PDF Enregistré!"),
             QObject::tr("PDF Enregistré!.\n" "Click Cancel to exit."), QMessageBox::Cancel);
}
void MainWindow::on_pushButton_AI_clicked()
{   QString test=ui->test->text();
    if(V.ESTIMATION(test)!=-1)
  {

     QString pred=QString::number(int(V.ESTIMATION(test)));
     ui->Estimation->setText(pred);
     ui->estimation->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
     ui->estimation->setModel(V.afficherlghayb());

  }
    else QMessageBox::critical(nullptr, QObject::tr(" NOT OK"),
                               QObject::tr("Nom Du Base Est Incorrecte Réessayer.\n"
                                           "Click Cancel to exit."), QMessageBox::Cancel);

}
/*void MainWindow::on_pb_excel_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Excel file"), qApp->applicationDirPath (),tr("Excel Files (*.xls)"));
                if (fileName.isEmpty())
                    return;

                ExportExcelObject obj(fileName, "mydata", ui->tableView_vols);

                //colums to export
                obj.addField(1, "Nom", "char(20)");
                obj.addField(0, "Matricule", "char(20)");
                obj.addField(2,"Adresse", "char(20)");
                obj.addField(3, "Email", "char(20)");
                obj.addField(5, "Durée", "char(20)");
                obj.addField(4, "Montant", "char(20)");

                int retVal = obj.export2Excel();
                if( retVal > 0)
                {
                    QMessageBox::information(this, tr("Done"),
                                             QString(tr("%1 records exported!")).arg(retVal)
                                             );
                }

}*/



