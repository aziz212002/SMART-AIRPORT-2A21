#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "stat_produit.h"
#include "produit.h"
#include <QSqlQuery>
#include <QMessageBox>
#include <QIntValidator>
#include <connection.h>
#include <iostream>
#include <QRegExp>
#include <QRegExpValidator>
#define NOM_RX "^([a-z]+[ ]?|[A-Z]+['-]?)+$"
#define TYPE_RX "^([a-z]+[ ]?|[A-Z]+['-]?)+$"
#define PRIX_RX "^([0-9]?|[.]?)+$"
#include <QPainter>
//#include <QMediaPlayer>
#include <QSound>
#include <QDesktopServices>
#include <QUrl>
#include "piechartwidget.h"
#include <QSoundEffect>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QPixmap pix("C:/Users/21651/Documents/2A22/projet C++/photo_produit2.png");
    ui->image->setPixmap(pix);
    QPixmap pix2("C:/Users/21651/Documents/2A22/projet C++/photo_produit2.png");
    ui->image_2->setPixmap(pix2);
    QPixmap pix3("C:/Users/21651/Documents/2A22/projet C++/photo_produit2.png");
    ui->image_3->setPixmap(pix3);
    QPixmap pix4("C:/Users/21651/Documents/2A22/projet C++/photo_produit2.png");
    ui->image_4->setPixmap(pix4);

    ui->le_ID->setValidator(new QIntValidator(100, 99999999, this));
    ui->le_ID_mod->setValidator(new QIntValidator(100, 99999999, this));
    ui->le_ID_supp->setValidator(new QIntValidator(100, 99999999, this));
    ui->le_Nombre->setValidator(new QIntValidator(100, 99999999, this));
    ui->le_Nombre_mod->setValidator(new QIntValidator(100, 99999999, this));


    QRegExp rxNom(NOM_RX);
    QRegExp rxType(TYPE_RX);
    QRegExp rxPrix(PRIX_RX);
    QRegExpValidator*valiNom= new QRegExpValidator(rxNom,this);
    QRegExpValidator*valiType= new QRegExpValidator(rxType,this);
    QRegExpValidator*valiPrix= new QRegExpValidator(rxPrix,this);
    ui->le_Nom->setValidator(valiNom);
    ui->le_Type->setValidator(valiType);
    ui->le_Nom_mod->setValidator(valiNom);
    ui->le_Type_mod->setValidator(valiType);
    ui->le_Prix->setValidator(valiPrix);
    ui->le_Prix_mod->setValidator(valiPrix);

    int ret=A.connect_arduino(); // lancer la connexion à arduino
    switch(ret){
    case(0):qDebug()<< "arduino is available and connected to : "<< A.getarduino_port_name();
        break;
    case(1):qDebug() << "arduino is available but not connected to :" <<A.getarduino_port_name();
       break;
    case(-1):qDebug() << "arduino is not available";
    }
     QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(update_label())); // permet de lancer
     //le slot update_label suite à la reception du signal readyRead (reception des données).


    //ui->tab_afficher->setModel(P.afficher());
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_ajouter_clicked()
{


    int ID=ui->le_ID->text().toInt();
    QString Nom=ui->le_Nom->text();
    QString Type=ui->le_Type->text();
    int Quantite=ui->le_Nombre->text().toInt();
    QString Delai=ui->le_Delai->text();
    QString Prix=ui->le_Prix->text();

    Produit P(ID,Nom,Type,Quantite,Delai,Prix);
    bool test=P.ajouter();

    QMessageBox msgBox;

    if(test)
        msgBox.setText("ajout avec succes.");
    else
        msgBox.setText("Echec d'ajout");
        msgBox.exec();

}

void MainWindow::on_supprimer_clicked()
{
    Produit P1, P2;
    int val=ui->le_ID_supp->text().toInt();
    QSqlQuery qry;
      qry.prepare("SELECT * FROM Produit where ID_PRODUIT= :newid");
      qry.bindValue(":newid",val);

      if(!qry.exec())
      {
          QMessageBox::critical(nullptr, QObject::tr("ERROR"),
                  QObject::tr("Echec de suppression.\n"
                  "Click Cancel to exit."), QMessageBox::Cancel);
      }
      else
      {
      bool alreadyExist = false;
       alreadyExist = qry.next();

       if(alreadyExist)
       {

           P2.setID(ui->le_ID_supp->text().toInt()) ;
           bool test=P1.supprimer(P2.getID()) ;
           QMessageBox msgBox;

           if(!test)
           {
               msgBox.setText("Echec de suppression");
               //ui->tab_afficher->setModel(P.afficher());
           }
           else
               msgBox.setText("suppression avec succes.");
               msgBox.exec();
       }
       else
       {
           QMessageBox::critical(nullptr, QObject::tr("ERROR"),
                               QObject::tr("ID doesn't exist.\n"
                               "Click Cancel to exit."), QMessageBox::Cancel);
       }
        }

}



void MainWindow::on_afficher_clicked()
{
    Produit P;
    ui->tab_afficher->setModel(P.afficher());
}

void MainWindow::on_modifier_clicked()
{
    int ID=ui->le_ID_mod->text().toInt();
    QString Nom=ui->le_Nom_mod->text();
    QString Type=ui->le_Type_mod->text();
    int Quantite=ui->le_Nombre_mod->text().toInt();
    QString Delai=ui->le_Delai_mod->text();
    QString Prix=ui->le_Prix_mod->text();

    Produit P(ID,Nom,Type,Quantite,Delai,Prix);


    P.setID(ui->le_ID_mod->text().toInt()) ;
    bool test=P.modifier(P.getID()) ;

    QMessageBox msgBox;

    if(test)
    {msgBox.setText("modification avec succes.");
        ui->tab_afficher->setModel(P.afficher());
    }
    else
        msgBox.setText("Echec de modification");
        msgBox.exec();

}



void MainWindow::on_Annuler_1_clicked()
{
    ui->le_ID->setText("");
    ui->le_Nom->setText("");
    ui->le_Type->setText("");
    ui->le_Nombre->setText("");
    ui->le_Delai->setText("");
    ui->le_Prix->setText("");
}


void MainWindow::on_Annuler_2_clicked()
{
    ui->le_ID_mod->setText("");
    ui->le_Nom_mod->setText("");
    ui->le_Type_mod->setText("");
    ui->le_Nombre_mod->setText("");
    ui->le_Delai_mod->setText("");
    ui->le_Prix_mod->setText("");
}

void MainWindow::on_Annuler_3_clicked()
{
    ui->le_ID_supp->setText("");
}

void MainWindow::on_afficher_pour_modifier_clicked()
{
    int val=ui->le_ID_mod->text().toInt();
        QSqlQuery qry;
        qry.prepare("SELECT * FROM Produit where ID_produit=:newid");
        qry.bindValue(":newid",val);

        if(qry.exec())
        {
            bool alreadyExist = false;
            alreadyExist = qry.next();
            if(alreadyExist)
            {
                ui->tabWidget->setCurrentIndex(3);


                    ui->le_ID_mod->setText(qry.value(0).toString());
                    ui->le_Nom_mod->setText(qry.value(1).toString());
                    ui->le_Type_mod->setText(qry.value(2).toString());
                    ui->le_Nombre_mod->setText(qry.value(3).toString());
                    ui->le_Delai_mod->setText(qry.value(4).toString());
                    ui->le_Prix_mod->setText(qry.value(5).toString());

            }
            else
            {
                QMessageBox::critical(nullptr, QObject::tr("ERROR"),
                QObject::tr("ID doesn't exist.\n"
                "Click Cancel to exit."), QMessageBox::Cancel);
            }

        }
        else{
            QMessageBox::critical(nullptr, QObject::tr("ERROR"),
            QObject::tr("Error.\n"
            "Click Cancel to exit."), QMessageBox::Cancel);
            }
}

void MainWindow::on_Rechercher_clicked()
{
    Produit P;

    QString crit=ui->comboBox_rechercher->currentText();
    if(crit=="ID")
    {
        QString id=ui->le_Rchercher->text() ;
        ui->tab_rechercher->setModel(P.rechercheID(id));
    }
    else if(crit=="Nom")
    {
        QString Nom=ui->le_Rchercher->text() ;
        ui->tab_rechercher->setModel(P.rechercheNom(Nom));
    }
    else if(crit=="Quantité")
    {
        QString Quant=ui->le_Rchercher->text() ;
        ui->tab_rechercher->setModel(P.rechercheQuantite(Quant));
    }
    else
    {
        QString Prix=ui->le_Rchercher->text() ;
        ui->tab_rechercher->setModel(P.recherchePrix(Prix));
    }

    //QString cin=ui->lineEdit->text();
    //ui->tabvoyageur->setModel(tmpvoy.chercher(cin));
}

void MainWindow::on_trier_clicked()
{
    Produit P;
    QString crit=ui->comboBox_trier->currentText();
    if(crit=="Delai")
    {
        ui->tab_trier->setModel(P.trierDelai());
    }
    else if(crit=="Quantité")
    {
        ui->tab_trier->setModel(P.trierQuant());
    }
    else
    {
        ui->tab_trier->setModel(P.trierNom());
    }
}


void MainWindow::on_Quitter_clicked()
{//QSound::play("C:/Users/21651/Documents/2A22/projet C++/QT/projet_produit/button-49.wav");
    MainWindow::close();
}

void MainWindow::on_alerte_clicked()
{
    QSqlQuery qry;
 if (qry.exec("select * from Produit WHERE Quantite <= 5 "))
 {
    int n=0;

     while (qry.next())
     {
         qDebug () <<n;
         n= qry.value(2).toInt();
        if(n<5)
           {  Produit P;
                 P.alerte_fin_stock();

           }
     }
 }
}

void MainWindow::on_mailing_clicked()
{
    QString link="https://mail.google.com/mail/u/0/#inbox?compose=new";
    QDesktopServices::openUrl(link);
}

//**arduino**

void MainWindow::update_label()
{
    data=A.read_from_arduino();

    if(data=="1")

        ui->label_3->setText("Produit acceptée"); // si les données reçues de arduino via la liaison série sont égales à 1
    // alors afficher ON

    else if (data=="0")

        ui->label_3->setText("Produit refusé");   // si les données reçues de arduino via la liaison série sont égales à 0
     //alors afficher ON
}

void MainWindow::on_pushButton_clicked()   // implémentation du slot bouton on
{
     A.write_to_arduino("1"); //envoyer 1 à arduino
}

void MainWindow::on_pushButton_2_clicked()  // implémentation du slot bouton off
{

     A.write_to_arduino("0");  //envoyer 0 à arduino
}

