#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPdfWriter>
#include <QPainter>
#include <QSqlQuery>
#include<QtCharts>

#include<QPieSlice >
#include<QPieSeries>
#include<QPrinter>
#include <QFileDialog>
#include<QPrintDialog>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEdit_n_de_vol->setValidator( new QIntValidator(0, 999999, this));
    ui->lineEdit_capacitevol->setValidator( new QIntValidator(0, 300, this));
    ui->lineEdit_numvolsupprimer->setValidator( new QIntValidator(0, 999999, this));
    ui->lineEdit_recherche->setValidator( new QIntValidator(0, 999999, this));



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
        vols E(num_vols,d_vols,cap_vols,dest);
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
        vols V(num_vols,d_vols,cap_vols,dest);

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

void MainWindow::on_pushButton_statestique_clicked()
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
