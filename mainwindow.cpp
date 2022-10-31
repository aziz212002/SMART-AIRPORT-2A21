#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <passagers.h>
#include <QIntValidator>
#include <QMessageBox>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEdit_pass->setValidator (new QIntValidator(0, 999999999, this));
    ui->tablePassager->setModel(P.afficher());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pb_ajouter_clicked()
{
    QString nom_passager=ui->lineEdit_nom->text();
    QString prenom_passager=ui->lineEdit_prenom->text();
    int age_passager=ui->lineEdit_age->text().toInt();
    int cin_passager=ui->lineEdit_cin->text().toInt();
    int passeport_passager=ui->lineEdit_pass->text().toInt();
    int num_portail=ui->lineEdit_porte->text().toInt();
    QString num_vol=ui->lineEdit_vol->text();
    QString num_siege=ui->lineEdit_siege->text();
    int nb_valises=ui->lineEdit_valise->text().toInt();
    QString mail=ui->lineEdit_mail->text();

    passager P (nom_passager,prenom_passager,age_passager,cin_passager,passeport_passager,num_portail,num_vol,num_siege,nb_valises,mail);
bool test=P.ajouter();
 if(test)
 {    ui->tablePassager->setModel(P.afficher());
     QMessageBox::information(nullptr, QObject::tr("ok"),
                                    QObject::tr("ajout effectue.\n"
                                                "Click Cancel to exit."), QMessageBox::Cancel);

}
 else
     QMessageBox::critical(nullptr, QObject::tr("not ok"),
                 QObject::tr("ajout non effectue.\n"
                             "Click Cancel to exit."), QMessageBox::Cancel);

}


void MainWindow::on_pb_supp_clicked()
{
    int passeport_passager=ui->lineEdit_pass->text().toInt();
     bool test=P.supprimer(passeport_passager);

     if (test)
     {
         ui->tablePassager->setModel(P.afficher());
     QMessageBox::information(nullptr, QObject::tr("OK"),
                                 QObject::tr("suppression effectué.\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);
     }
     else
     QMessageBox::critical(nullptr, QObject::tr("not OK"),
                         QObject::tr("suppression failed.\n"
                                     "Click Cancel to exit."), QMessageBox::Cancel);

}



void MainWindow::on_pb_modif_clicked()
{
    QString nom_passager=ui->lineEdit_nom->text();
    QString prenom_passager=ui->lineEdit_prenom->text();
    int age_passager=ui->lineEdit_age->text().toInt();
    int cin_passager=ui->lineEdit_cin->text().toInt();
    int passeport_passager=ui->lineEdit_pass->text().toInt();
    int num_portail=ui->lineEdit_porte->text().toInt();
    QString num_vol=ui->lineEdit_vol->text();
    QString num_siege=ui->lineEdit_siege->text();
    int nb_valises=ui->lineEdit_valise->text().toInt();
    QString mail=ui->lineEdit_mail->text();

    passager P (nom_passager,prenom_passager,age_passager,cin_passager,passeport_passager,num_portail,num_vol,num_siege,nb_valises,mail);
bool test=P.modifier();
        if(test){
            ui->tablePassager->setModel(P.afficher());
                    QMessageBox::information(nullptr, QObject::tr("OK"),
                                QObject::tr("modification effectué.\n"
                                            "Click Cancel to exit."), QMessageBox::Cancel);

        }
        else
            QMessageBox::critical(nullptr, QObject::tr("not OK"),
                        QObject::tr("modification failed.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
}
