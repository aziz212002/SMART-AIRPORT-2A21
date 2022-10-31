#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"personnel.h"
#include<QIntValidator>
#include<QObject>
#include<QMainWindow>
#include <QSqlQueryModel>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEdit_1->setValidator( new QIntValidator(0, 999999, this));
    ui->tableView->setModel(p.afficher());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()   //Ajout
{

    int CIN_per=ui->lineEdit_1->text().toInt();
    int num_tel=ui->lineEdit_2->text().toInt();
    int age_per=ui->lineEdit_3->text().toInt();
    QString nom_per=ui->lineEdit_4->text();
    QString prenom_per=ui->lineEdit_5->text();
    QString mail_per=ui->lineEdit_7->text();

    Personnel p (CIN_per,num_tel,age_per,nom_per,prenom_per,mail_per);
     bool test =p.Ajouter();
      if (test)
      {

          ui->tableView->setModel(p.afficher());
          QMessageBox::information(nullptr , QObject::tr("OK"),
                                   QObject::tr("Ajout effectué \n"
                                               "Click Cancel to exit.") , QMessageBox::Cancel );
      }

 else //si requete non executée
      QMessageBox::critical(nullptr,QObject::tr("Not OK"),
                            QObject::tr("Ajout non effectué. \n"
                                        "Click Cancel to exit.") , QMessageBox::Cancel);

}


void MainWindow::on_pushButton_3_clicked() //Supprimer
{
    int CIN_per=ui->lineEdit_1->text().toInt();
    bool test=p.supprimer(CIN_per);
    if (test)
    {
        //Refresh
        ui->tableView->setModel(p.afficher());
     QMessageBox::information(nullptr, QObject::tr("OK"),
                              QObject::tr("Suppression effectueé. \n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                              QObject::tr("Suppression non effectuée. \n"
                                          "Click Cancel to exit."),QMessageBox::Cancel);
}


void MainWindow::on_pushButton_2_clicked() //modifier
{
    int CIN_per=ui->lineEdit_1->text().toInt();
        int num_tel=ui->lineEdit_2->text().toInt();
        int age_per=ui->lineEdit_3->text().toInt();
        QString nom_per=ui->lineEdit_4->text();
       QString prenom_per=ui->lineEdit_5->text();
       QString mail_per=ui->lineEdit_7->text();
         Personnel p(CIN_per,num_tel,age_per,nom_per,prenom_per,mail_per);
        bool test=p.modifier();

            if(test){
                ui->tableView->setModel(p.afficher());
                        QMessageBox::information(nullptr, QObject::tr("OK"),
                                    QObject::tr("modification effectué.\n"
                                                "Click Cancel to exit."), QMessageBox::Cancel);

            }
            else
                QMessageBox::critical(nullptr, QObject::tr("not OK"),
                            QObject::tr("modification failed.\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);
}
;


