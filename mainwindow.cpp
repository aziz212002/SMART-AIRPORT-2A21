#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <passagers.h>
#include<dialog.h>
#include <QDialog>
#include <QIntValidator>
#include<QSqlQuery>
#include<passagers.h>
#include<QPainter>
#include<QtSvg/QGraphicsSvgItem>
#include<qrcode.h>
#include <QMessageBox>
#include <QDebug>
#include "arduino.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEdit_pass->setValidator (new QIntValidator(0, 999999999, this));
    ui->tablePassager->setModel(P.afficher());
    QPixmap pixPDF("C:/Users/toufa/OneDrive/Bureau/Projet QT/Icons/pdf1.ico");
         ui->label_pdf->setPixmap(pixPDF);
    QPixmap pixmap("C:/Users/toufa/OneDrive/Bureau/Projet QT/Icons/map1.ico");
         ui->label_map->setPixmap(pixmap);
    QPixmap pixmail("C:/Users/toufa/OneDrive/Bureau/Projet QT/Icons/mail1.ico");
         ui->label_mail->setPixmap(pixmail);
         int ret=a.connect_arduino();
                      switch(ret){
                      case (0): qDebug() << "arduino is available and connected to : " << a.getarduino_port_name();
                      break;
                      case (1) :qDebug () << "arduino is available but not connected to :" << a.getarduino_port_name ();
                      break;
                      case (-1): qDebug() << "arduino is not available";

                      }

                     // QObject:: connect (a.getserial(),SIGNAL (readyRead()), this, SLOT (update_label ())); // permet de lancer //le slot update label suite à la reception du signal readyRead (reception des données).
                      QObject:: connect (a.getserial(),SIGNAL (readyRead()), this, SLOT ( ChercherFromArduino()));

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
    int num_portail=ui->comboBox_portail->currentText().toInt();
    QString num_vol=ui->lineEdit_vol->text();
    QString num_siege=ui->lineEdit_siege->text();
    int nb_valises=ui->lineEdit_valise->text().toInt();
    QString mail=ui->lineEdit_mail->text();
    QString type_passager=ui->comboBox_type->currentText();
    int poids_totale=ui->lineEdit_poids->text().toInt();

    passager P (nom_passager,prenom_passager,age_passager,cin_passager,passeport_passager,num_portail,num_vol,num_siege,nb_valises,mail,type_passager,poids_totale);
bool test=P.ajouter();

if(P.verifieremail(mail)==0 )
{test=false;
    QMessageBox::critical(nullptr, QObject::tr("not ok"),
                       QObject::tr("ad.email incorrecte.\n"

                                   "Click Cancel to exit."), QMessageBox::Cancel);}
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
    int num_portail=ui->comboBox_portail->currentText().toInt();
    QString num_vol=ui->lineEdit_vol->text();
    QString num_siege=ui->lineEdit_siege->text();
    int nb_valises=ui->lineEdit_valise->text().toInt();
    QString mail=ui->lineEdit_mail->text();
    QString type_passager=ui->comboBox_type->currentText();
    int poids_totale=ui->lineEdit_poids->text().toInt();

    passager P (nom_passager,prenom_passager,age_passager,cin_passager,passeport_passager,num_portail,num_vol,num_siege,nb_valises,mail,type_passager,poids_totale);
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

void MainWindow::on_checkBox_age_clicked()
{
 ui->tablePassager->setModel(P.trieage());
}

void MainWindow::on_checkBox_alphabet_clicked()
{
  ui->tablePassager->setModel(P.triealphabet());
}

void MainWindow::on_checkBox_3_clicked()
{
  ui->tablePassager->setModel(P.trievalise());
}

void MainWindow::on_tablePassager_clicked(const QModelIndex &index)
{
    ui->lineEdit_nom->setText(ui->tablePassager->model()->data(ui->tablePassager->model()->index(index.row(),0)).toString());
    ui->lineEdit_prenom->setText(ui->tablePassager->model()->data(ui->tablePassager->model()->index(index.row(),1)).toString());
    ui->lineEdit_age->setText(ui->tablePassager->model()->data(ui->tablePassager->model()->index(index.row(),2)).toString());
    ui->lineEdit_cin->setText(ui->tablePassager->model()->data(ui->tablePassager->model()->index(index.row(),3)).toString());
    ui->lineEdit_pass->setText(ui->tablePassager->model()->data(ui->tablePassager->model()->index(index.row(),4)).toString());
    ui->comboBox_portail->setCurrentText(ui->tablePassager->model()->data(ui->tablePassager->model()->index(index.row(),5)).toString());
    ui->lineEdit_vol->setText(ui->tablePassager->model()->data(ui->tablePassager->model()->index(index.row(),6)).toString());
    ui->lineEdit_siege->setText(ui->tablePassager->model()->data(ui->tablePassager->model()->index(index.row(),7)).toString());
    ui->lineEdit_valise->setText(ui->tablePassager->model()->data(ui->tablePassager->model()->index(index.row(),8)).toString());
    ui->lineEdit_mail->setText(ui->tablePassager->model()->data(ui->tablePassager->model()->index(index.row(),9)).toString());
    ui->comboBox_type->setCurrentText(ui->tablePassager->model()->data(ui->tablePassager->model()->index(index.row(),10)).toString());
    ui->lineEdit_poids->setText(ui->tablePassager->model()->data(ui->tablePassager->model()->index(index.row(),11)).toString());
    QString text ="Details du passager : \nNom:  "+ui->tablePassager->model()->data(ui->tablePassager->model()->index(ui->tablePassager->currentIndex().row(),0)).toString()
                +"\nPrénom:  "+ui->tablePassager->model()->data(ui->tablePassager->model()->index(ui->tablePassager->currentIndex().row(),1)).toString()
                +"\nAge:  "+ui->tablePassager->model()->data(ui->tablePassager->model()->index(ui->tablePassager->currentIndex().row(),2)).toString()
                +"\nCIN:  "+ui->tablePassager->model()->data(ui->tablePassager->model()->index(ui->tablePassager->currentIndex().row(),3)).toString()
                +"\nPasseport:  "+ui->tablePassager->model()->data(ui->tablePassager->model()->index(ui->tablePassager->currentIndex().row(),4)).toString()
                +"\nNum portail"+ui->tablePassager->model()->data(ui->tablePassager->model()->index(ui->tablePassager->currentIndex().row(),5)).toString()
                +"\nNum vol"+ui->tablePassager->model()->data(ui->tablePassager->model()->index(ui->tablePassager->currentIndex().row(),6)).toString()
                +"\nNum siège"+ui->tablePassager->model()->data(ui->tablePassager->model()->index(ui->tablePassager->currentIndex().row(),7)).toString()
                +"\nNb valises"+ui->tablePassager->model()->data(ui->tablePassager->model()->index(ui->tablePassager->currentIndex().row(),8)).toString()
                +"\nBoite mail"+ui->tablePassager->model()->data(ui->tablePassager->model()->index(ui->tablePassager->currentIndex().row(),9)).toString()
                +"\nType passager"+ui->tablePassager->model()->data(ui->tablePassager->model()->index(ui->tablePassager->currentIndex().row(),10)).toString();
        using namespace qrcodegen;
          // Create the QR Code object
          QrCode qr = QrCode::encodeText( text.toUtf8().data(), QrCode::Ecc::MEDIUM );
          qint32 sz = qr.getSize();
          QImage im(sz,sz, QImage::Format_RGB32);
            QRgb black = qRgb(  0,  0,  0);
            QRgb white = qRgb(255,255,255);
          for (int y = 0; y < sz; y++)
            for (int x = 0; x < sz; x++)
              im.setPixel(x,y,qr.getModule(x, y) ? black : white );
          ui->qrcode_2->setPixmap( QPixmap::fromImage(im.scaled(110,110,Qt::KeepAspectRatio,Qt::FastTransformation),Qt::MonoOnly) );
}



void MainWindow::on_lineEdit_recherche_textChanged(const QString &arg1)
{

    QString rech = ui->lineEdit_recherche->text();
        P.recherche(ui->tablePassager,rech);
        if (ui->lineEdit_recherche->text().isEmpty())
        {
            ui->tablePassager->setModel(P.afficher());
        }
}



void MainWindow::on_pushButton_PDF_clicked()
{

 P.telechargerPDF();


        QMessageBox::information(nullptr,QObject::tr("OK"),
                   QObject::tr("Téléchargement terminé"), QMessageBox::Cancel);


}

void MainWindow::on_pushButton_mail_clicked()
{
    Ui=new Dialog(this);
    Ui->show();

}


void MainWindow::on_pushButton_map_clicked()
{
    m = new mapping(this);

     m->show();
}
void MainWindow::ChercherFromArduino(){
    d = a.read_from_arduino();
        qDebug() << d;
        if (d!=" ")
        {
            QSqlQuery *query=new QSqlQuery;
            query->prepare("select * from passager where passeport_passager like '%"+d+"%';");
            if(query->exec()){
              ui->lineEdit_recherche->setText(d);
              P.recherche(ui->tablePassager,d);
              if (ui->lineEdit_recherche->text().isEmpty())
              {
                  ui->tablePassager->setModel(P.afficher());
              }
            }else{
                qDebug()<<"query is wrong";
            }
}
}
