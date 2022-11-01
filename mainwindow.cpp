#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "produit.h"
#include <QSqlQueryModel>

#include <QMessageBox>
#include <QIntValidator>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
     //ui->tableView->setModel(p.afficher_produit());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{

}

void MainWindow::on_ajouter_clicked()
{
    /*QString NomMagasin ,NomArticle;
    int ,PrixArticle,NombreArticle;*/

    int  NumArticle = ui->lineEdit_numarticle ->text().toInt() ;
        QString NomMagasin=ui->lineEdit_nommagazin->text();
        QString NomArticle=ui->lineEdit_nomarticle->text();
        int  NombreArticle=ui->spinBox->text().toInt() ;
        int  PrixArticle=ui->lineEdit_prixarticle->text().toInt() ;
            //option
        produit p(NomMagasin ,NomArticle, NumArticle,PrixArticle,NombreArticle);
        bool test=p.ajouter_produit();
        if(test)
        {
            //ui->tableView->setModel(p.afficher_produit());
            //ui->Affichage->setIndexWidget(ui->Affichage->model()->index(1, 7),ui->delete_2);
            QMessageBox::information(nullptr, QObject::tr("ok"),
                        QObject::tr("ajout effectue.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
        }
        else
            QMessageBox::critical(nullptr, QObject::tr("not ok"),
                        QObject::tr("ajout non effectue.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
}
