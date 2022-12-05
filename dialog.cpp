#include "dialog.h"
#include "ui_dialog.h"
#include "smtp.h"
#include <QDialog>
#include <QFileDialog>
#include "passagers.h"
#include "qrcodegen.hpp"
#include "personnel.h"
#include <QApplication>
#include <QMessageBox>
#include <QDebug>
#include<QIntValidator>
#include <QPdfWriter>
#include <QPainter>
#include <QDesktopServices>
#include <QPrinter>
#include <QFileDialog>
#include <QTextDocument>
#include<QDateTime>
#include <QTextStream>
#include <smtp.h>
#include<QString>
#include <QtNetwork>
#include <QAbstractSocket>

#include<QPrinter>
#include <QFileDialog>
#include<QPrintDialog>

#include <QMessageBox>
#include "QIntValidator"
#include <QDateEdit>
#include <QPlainTextEdit>
#include <QPrinter>
//#include <QPrinterInfo>
//#include <QPrintDialog>
#include <QTextStream>
#include <QPainter>
#include <QTextStream>
#include <QFileDialog>
#include <QTextDocument>
#include <QtPrintSupport/QPrinter>
#include <QFileDialog>
#include <QTextDocument>
#include <strstream>
#include <QSystemTrayIcon>
#include <QRegExpValidator>
#include <QDesktopServices>
#include <QUrl>
#include <QGuiApplication>
//#include <QQmlApplicationEngine>
#include <QTcpSocket>
//#include <QQuickItem>
#include <QSystemTrayIcon>
#include <QIntValidator>
//********MAHDI AVION*********
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "avion.h"
#include "calendrier.h"
#include "exportexcelobject.h"
//********ilyess*vols***************************************
#include "mainwindow.h"
#include "ui_mainwindow.h"
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
#include "vols.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    ui->comboBox->setModel(P.afficher2());
    ui->lineEdit_1->setValidator( new QIntValidator(0, 999999, this));
    ui->tableView->setModel(p.afficher());
    ui->lineEdit_2->setValidator( new QIntValidator(0, 99999999, this));
    ui->lineEdit_3->setValidator( new QIntValidator(0, 999999, this));
    ui->lineEdit_3->setValidator( new QIntValidator(0, 999, this));

    //****************************MAHDI AVION************************

    ui->tableView_avions->setModel(a.afficher());
    QValidator *validator_id = new QIntValidator(1, 99999, this);
    QValidator *validator_kilom = new QIntValidator(0, 900,this);
    // the edit lineedit will only accept integers between 100 and 999
        ui->lineEdit_kilometrage->setValidator(validator_kilom);
        ui->lineEdit_id_avion->setValidator(validator_id);
        QRegularExpression rx("^[0-9]+.+[0-9]");
        QValidator *validator = new QRegularExpressionValidator(rx, this);
        ui->lineEdit_prix->setValidator(validator);
        ui->lineEdit_kilometrage->setValidator(validator);
        ui->lineEdit_consomation->setValidator(validator);

        //ilyess

            ui->lineEdit_n_de_vol->setValidator( new QIntValidator(0, 999999, this));
            ui->lineEdit_nb->setValidator( new QIntValidator(0, 999999, this));
            ui->lineEdit_capacitevol->setValidator( new QIntValidator(0, 300, this));
            ui->lineEdit_numvolsupprimer->setValidator( new QIntValidator(0, 999999, this));
            ui->lineEdit_recherche->setValidator( new QIntValidator(0, 999999, this));

}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushButton_clicked()
{
    QString from = ui ->lineEdit_from ->text();
    QString to = ui->lineEdit_to->text();
    QString subject = ui->lineEdit_subject->text();
    QString password = ui ->lineEdit_password ->text();
    QString email_text = ui->textEdit_mail->toPlainText();

   Smtp* smtp = new Smtp(from, password, "smtp.gmail.com",465);
    connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));


       smtp->sendMail(from, to, subject, email_text);
       QMessageBox::information(nullptr, QObject::tr("mail sent"),
                   QObject::tr(""
                               "Click Cancel to exit."), QMessageBox::Cancel);
}

void Dialog::mailenvoye(QString nettoyer)
{
    if(nettoyer == "Mail envoyé")
            QMessageBox::warning( nullptr, tr( "email" ), tr( "Mail sent.\n\n" ) );
        ui->lineEdit_to->clear();
        ui->lineEdit_subject->clear();
        ui->textEdit_mail->clear();
        ui->lineEdit_password->clear();
}

void Dialog::on_comboBox_activated(const QString &arg1)
{

    int ID_PASS=ui->comboBox->currentText().toInt();
    QString id_string=QString::number(ID_PASS);
    QSqlQuery query;
    query.prepare("select * from passager where passeport_passager='"+id_string+"'");
    if (query.exec())

        while(query.next())
        { ui->lineEdit_to->setText(query.value(9).toString());}
            else

        QMessageBox::critical(nullptr, QObject::tr("not OK"),
                    QObject::tr("failed.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

}
void Dialog::on_pushButton_55_clicked()//ajouter
{
    int CIN_per=ui->lineEdit_1->text().toInt();
    int num_tel=ui->lineEdit_2->text().toInt();
    int age_per=ui->lineEdit_3->text().toInt();
    QString nom_per=ui->lineEdit_4->text();
    QString prenom_per=ui->lineEdit_5->text();
    QString mail_per=ui->lineEdit_7->text();

    Personnel pTMP (CIN_per,num_tel,age_per,nom_per,prenom_per,mail_per);
     bool test =pTMP.Ajouter();
      if (test)
      {

          ui->tableView->setModel(p.afficher());
          QMessageBox::information(nullptr , QObject::tr("OK"),
                                   QObject::tr("Ajout effectué \n"
                                               "Click Cancel to exit.") , QMessageBox::Cancel );
      }

 else
      QMessageBox::critical(nullptr,QObject::tr("Not OK"),
                            QObject::tr("Ajout non effectué. \n"
                                        "Click Cancel to exit.") , QMessageBox::Cancel);
}

void Dialog::on_pushButton_222_clicked()//SUPP
{
    int CIN_per=ui->lineEdit_8->text().toInt();
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

void Dialog::on_pushButton_333_clicked()//sup
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

void Dialog::on_pushButton_444_clicked()//RECHERCHE
{
    QString rech=ui->lineEdit_recherche->text();
    ui->tableView->setModel(p.Recherchepersonnel(rech));
}

void Dialog::on_pushButton_555_clicked()
{
    if(ui->comboBox_tri->currentText()=="trier personnel par Cin")
    {
        ui->tableView->setModel(p.trierpersonnelparCin());

    }
    else if(ui->comboBox_tri->currentText()=="trier personnel par Age")
    {
        ui->tableView->setModel(p.trierpersonnelparAge());

    }
    else
    {
        ui->tableView->setModel(p.trierpersonnelparordrealphabetiquedunom());
    }
}

void Dialog::on_pushButton_777_clicked()
{
    QSqlQuery query;

query.prepare("select * from personnel");
 p.telechargerPDF();
    if(query.exec()){

       while(query.next())
        {


       ui->lineEdit_1->setText(query.value(0).toString());
       ui->lineEdit_2->setText(query.value(1).toString());
       ui->lineEdit_3->setText(query.value(2).toString());
       ui->lineEdit_4->setText(query.value(3).toString());
       ui->lineEdit_5->setText(query.value(4).toString());
       ui->lineEdit_7->setText(query.value(5).toString());


   }
    }
    else
        QMessageBox::information(nullptr,QObject::tr("OK"),
                   QObject::tr("Téléchargement terminé"), QMessageBox::Cancel);

}


void Dialog::on_pb_mail_clicked()
{
    Smtp* smtp = new Smtp("benromdhane.mohamedaziz@esprit.tn", "211JMT7323", "smtp.gmail.com", 465);
    connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));
    QString a=ui->Linemail->text();
    QString b=ui->Lineobjet->text();
    QString c=ui->msg ->toPlainText();

    smtp->sendMail("benromdhane.mohamedaziz@esprit.tn", a , b,c);
}

void Dialog::on_pushButton_6_clicked()
{
    mSocket->write(ui->lineEdit->text().toLatin1().data(),ui->lineEdit->text().size());

        ui->plainTextEdit_2->appendPlainText(ui->lineEdit->text());

        ui->lineEdit->clear();

}

void Dialog::on_pushButton_9_clicked()
{
    mSocket->write(ui->lineEdit_2->text().toLatin1().data(),ui->lineEdit_2->text().size());

        ui->plainTextEdit->appendPlainText(ui->lineEdit_2->text());

        ui->lineEdit_2->clear();
}
void Dialog::on_ajouter_clicked()
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

void Dialog::on_supprimer_clicked()
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



void Dialog::on_afficher_clicked()
{
    Produit P;
    ui->tab_afficher->setModel(P.afficher());
}

void Dialog::on_modifier_clicked()
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



void Dialog::on_Annuler_1_clicked()
{
    ui->le_ID->setText("");
    ui->le_Nom->setText("");
    ui->le_Type->setText("");
    ui->le_Nombre->setText("");
    ui->le_Delai->setText("");
    ui->le_Prix->setText("");
}


void Dialog::on_Annuler_2_clicked()
{
    ui->le_ID_mod->setText("");
    ui->le_Nom_mod->setText("");
    ui->le_Type_mod->setText("");
    ui->le_Nombre_mod->setText("");
    ui->le_Delai_mod->setText("");
    ui->le_Prix_mod->setText("");
}

void Dialog::on_Annuler_3_clicked()
{
    ui->le_ID_supp->setText("");
}

void Dialog::on_afficher_pour_modifier_clicked()
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

void Dialog::on_Rechercher_clicked()
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

void Dialog::on_trier_clicked()
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


void Dialog::on_Quitter_clicked()
{//QSound::play("C:/Users/21651/Documents/2A22/projet C++/QT/projet_produit/button-49.wav");
    Dialog::close();
}

void Dialog::on_alerte_clicked()
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

void Dialog::on_mailing_clicked()
{
    QString link="https://mail.google.com/mail/u/0/#inbox?compose=new";
    QDesktopServices::openUrl(link);
}

//******************************MAHDI AVION******************************

//...........................AJOUT.........................

void Dialog::on_pushButton_ajouter_avion_clicked()
{

    int Id_avion = ui->lineEdit_id_avion->text().toInt();
    QString marque = ui->comboBox_marque->currentText();
    QString type_moteur = ui->comboBox_type->currentText();
    float consomation = ui->lineEdit_consomation->text().toFloat();
    float kilometrage = ui->lineEdit_kilometrage->text().toFloat();
    float prix_achat = ui ->lineEdit_prix->text().toFloat();
    QString etat_avion=ui->comboBox_etat->currentText();

    Avion atmp (Id_avion,marque,type_moteur,consomation,kilometrage,prix_achat,etat_avion);
    bool test =  atmp.ajouter();
    if(test)
         {
                QMessageBox::information(nullptr, QObject::tr("database is open"),
                            QObject::tr("ajout successful.\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);
                ui->tableView_avions->setModel(a.afficher());

        }
            else
               { QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                            QObject::tr("ajout failed.\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel); }
}
//...........................SUPPRIMER............................
void Dialog::on_pushButton_supprimer_avion_clicked()
{
    int Id_avion =ui->lineEdit_id2->text().toInt();
    bool test=a.supprimer(Id_avion);
    if(test)
    {
         QMessageBox::information(nullptr, QObject::tr("ok"),
                                  QObject::tr("supp successful.\n"
                                               "Click Cancel to exit."), QMessageBox::Cancel);
         ui->tableView_avions->setModel(a.afficher());

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("not ok"),
                              QObject::tr("suppression non efectuee.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);

    }



//..........................MODIFICATION........................

void Dialog::on_pushButton_modify_clicked()
{
    int Id_avion =ui->lineEdit_id_avion->text().toInt();
    QString marque = ui->comboBox_marque->currentText();
    QString type_moteur = ui->comboBox_type->currentText();
    float consomation = ui->lineEdit_consomation->text().toFloat();
    float kilometrage = ui->lineEdit_kilometrage->text().toFloat();
    float prix_achat = ui ->lineEdit_prix->text().toFloat();
    QString etat_avion=ui->comboBox_etat->currentText();
    Avion a (Id_avion, marque,type_moteur,consomation,kilometrage,prix_achat,etat_avion);
    bool test =  a.modifier(Id_avion);

    if(test)

           {

        ui->tableView_avions->setModel(a.afficher());
               QMessageBox :: information (nullptr, QObject ::tr("OK"),

                            QObject ::tr("modifier effectué\n"

                                         "click cancel to exit"),

                       QMessageBox:: Cancel);


       }

           else

           {

               QMessageBox::critical(nullptr,QObject::tr("not ok"),

                                    QObject::tr("try again.\n"

                                                "click cancel to exit."),QMessageBox::Cancel);

           }
}



//......................................TRI.......................................
void Dialog::on_pushButton_tri_clicked()
{
   ui->tableView_avions->setModel(ptmp.tri());
}
void Dialog::on_pushButton_tri_conso_clicked()
{
   ui->tableView_avions->setModel(ptmp.triconso());
}
void Dialog::on_pushButton_triprix_clicked()
{
    ui->tableView_avions->setModel(ptmp.triprix());

}

//..........................RECHERCHE........................

void Dialog::on_pushButton_chercher_avion_clicked()
{
    int Id_avion=ui->lineEdit_id3->text().toInt() ;
          if (Id_avion == NULL) {
              QMessageBox::information(this, tr("Empty Field"),
                  tr("Please enter a Name."));
              return;
          } else {
          ui->tableView_avions->setModel(ptmp.cherche_id(Id_avion));
}
}

void Dialog::on_search_avion_textChanged(const QString &arg1)
{
    ui->tableView_avions->setModel(ptmp.recherche(arg1));

}




//////................PDF......................
void Dialog::on_pushButton_exportPDF_clicked()
{
    QString strStream;
            strStream = QFileDialog::getSaveFileName((QWidget* )0, "Export PDF", QString(), "*.pdf");
                if (QFileInfo(strStream).suffix().isEmpty())
                    { strStream.append(".pdf"); }

                QPrinter printer(QPrinter::PrinterResolution);
                printer.setOutputFormat(QPrinter::PdfFormat);
                printer.setPaperSize(QPrinter::A4);
                printer.setOutputFileName(strStream);

                      QTextStream out(&strStream);

                      const int rowCount = ui->tableView_avions->model()->rowCount();
                      const int columnCount = ui->tableView_avions->model()->columnCount();
                      QString TT = QDateTime::currentDateTime().toString();
                      out <<"<html>\n"
                            "<head>\n"
                             "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                          << "<title>ERP - COMmANDE LIST<title>\n "
                          << "</head>\n"
                          "<body bgcolor=#ffffff link=#5000A0>\n"
                             "<h1 style=\"text-align: center;\"><strong> "+TT+"</strong></h1>"
                            +"<img src=C:\\Users\\asus\\Desktop\\pdf\\logo_projet />" //path
                          "<h1 style=\"text-align: center;\"><strong> ****LISTE DES AVIONS **** </strong></h1>"

                          "<table style=\"text-align: center; font-size: 10px;\" border=1>\n "
                            "</br> </br>";
                      // headers
                      out << "<thead><tr bgcolor=#d6e5ff>";
                      for (int column = 0; column < columnCount; column++)
                          if (!ui->tableView_avions->isColumnHidden(column))
                              out << QString("<th>%1</th>").arg(ui->tableView_avions->model()->headerData(column, Qt::Horizontal).toString());
                      out << "</tr></thead>\n";

                      // data table
                      for (int row = 0; row < rowCount; row++) {
                          out << "<tr>";
                          for (int column = 0; column < columnCount; column++)
                        {
                              if (!ui->tableView_avions->isColumnHidden(column)) {
                                  QString data =ui->tableView_avions->model()->data(ui->tableView_avions->model()->index(row, column)).toString().simplified();
                                  out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;")); //pas compriis
                              }
                          }
                          out << "</tr>\n";
                      }
                      out <<  "</table>\n"
                          "</body>\n"
                          "</html>\n";

                      QTextDocument document;
                      document.setHtml(strStream);
                      document.print(&printer);


}

///////.................statistique..............................
QVector<double> Dialog::statistiques()
{
    QSqlQuery q;
    QVector<double> stat(5);
    stat[0]=0;
    stat[1]=0;
    stat[2]=0;
    stat[3]=0;
    stat[4]=0;
    q.prepare("SELECT PRIX_AV FROM AVION WHERE PRIX_AV<=1000");
    q.exec();
    while (q.next())
    {
        stat[0]++;

    }
    q.prepare("SELECT PRIX_AV FROM AVION WHERE PRIX_AV>1000 and PRIX_AV<=5000");
    q.exec();
    while (q.next())
    {
        stat[1]++;

    }
    q.prepare("SELECT PRIX_AV FROM AVION WHERE PRIX_AV>5000 and PRIX_AV<=100000");
    q.exec();
    while (q.next())
    {
        stat[2]++;

    }
    q.prepare("SELECT PRIX_AV FROM AVION WHERE PRIX_AV>100000 and PRIX_AV<=150000");
    q.exec();
    while (q.next())
    {
        stat[3]++;

    }
    q.prepare("SELECT PRIX_AV FROM AVION WHERE PRIX_AV>150000 and PRIX_AV<=1000000 ");
    q.exec();
    while (q.next())
    {
        stat[4]++;

    }
    return stat;
}
///............................CUSTOMPLOT..........................
void Dialog::makePlot()
{
    // prepare data:
    QVector<double> x3(5), y3(20);
    for (int i=0; i<x3.size(); ++i)
    {
      x3[i] = i+1;

    }
    for (int i=0; i<y3.size(); ++i)
    {
      y3[i] = i+1;

    }

    QCPBars *bars1 = new QCPBars(ui->customplot->xAxis, ui->customplot->yAxis);
    bars1->setWidth(2/(double)x3.size());
    bars1->setData(x3, Dialog::statistiques());////fonction statistiques
    bars1->setPen(Qt::NoPen);
    bars1->setBrush(QColor(200, 40, 60, 170));
    ui->customplot->replot();

    // move bars above graphs and grid below bars:
    ui->customplot->addLayer("abovemain", ui->customplot->layer("main"), QCustomPlot::limAbove);
    ui->customplot->addLayer("belowmain", ui->customplot->layer("main"), QCustomPlot::limBelow);
    ui->customplot->xAxis->grid()->setLayer("belowmain");
    ui->customplot->yAxis->grid()->setLayer("belowmain");

    // set some pens, brushes and backgrounds:
    QVector<double> Ticks;
    Ticks<<1<<2<<3<<4<<5<<6<<7;//////
    QVector<QString> labels;
    labels<<"0-1000"<<"1000-5000"<<"5000-10000"<<"10000-150000"<<"150000-1000000";////////
    QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
    textTicker->addTicks(Ticks,labels);
    ui->customplot->xAxis->setTicker(textTicker);
    ui->customplot->xAxis->setSubTicks(false);
    ui->customplot->xAxis->setTickLength(0,4);
    ui->customplot->xAxis->setBasePen(QPen(Qt::white, 1));
    ui->customplot->yAxis->setBasePen(QPen(Qt::white, 1));
    ui->customplot->xAxis->setTickPen(QPen(Qt::transparent, 1));
    ui->customplot->yAxis->setTickPen(QPen(Qt::white, 1));
    ui->customplot->xAxis->setSubTickPen(QPen(Qt::transparent, 1));
    ui->customplot->yAxis->setSubTickPen(QPen(Qt::transparent, 1));
    ui->customplot->xAxis->setTickLabelColor(Qt::white);
    ui->customplot->yAxis->setTickLabelColor(Qt::white);
    ui->customplot->xAxis->grid()->setPen(QPen(QColor(140, 140, 140), 1, Qt::DotLine));
    ui->customplot->yAxis->grid()->setPen(QPen(QColor(140, 140, 140), 1, Qt::DotLine));
    ui->customplot->xAxis->grid()->setSubGridPen(QPen(QColor(80, 80, 80), 1, Qt::DotLine));
    ui->customplot->yAxis->grid()->setSubGridPen(QPen(QColor(80, 80, 80), 1, Qt::DotLine));
    ui->customplot->xAxis->grid()->setSubGridVisible(true);
    ui->customplot->yAxis->grid()->setSubGridVisible(true);
    ui->customplot->xAxis->grid()->setZeroLinePen(Qt::NoPen);
    ui->customplot->yAxis->grid()->setZeroLinePen(Qt::NoPen);
    ui->customplot->xAxis->setUpperEnding(QCPLineEnding::esSpikeArrow);
    ui->customplot->yAxis->setUpperEnding(QCPLineEnding::esSpikeArrow);
    QLinearGradient plotGradient;
    plotGradient.setStart(0, 0);
    plotGradient.setFinalStop(0, 350);
    plotGradient.setColorAt(0, QColor(00, 50, 80));
    plotGradient.setColorAt(1, QColor(10, 20, 50));
    ui->customplot->setBackground(plotGradient);
    QLinearGradient axisRectGradient;
    axisRectGradient.setStart(0, 0);
    axisRectGradient.setFinalStop(0, 350);
    axisRectGradient.setColorAt(0, QColor(10, 50, 80));//
    axisRectGradient.setColorAt(1, QColor(0, 0, 30));
    ui->customplot->axisRect()->setBackground(axisRectGradient);

    ui->customplot->rescaleAxes();
    ui->customplot->xAxis->setRange(0, 7);
    ui->customplot->yAxis->setRange(0, 10);


}
//................STATSTIQUE..................
void Dialog::on_pushButton_statistic_event_clicked()
{
    ui->customplot->clearPlottables();
    Dialog::makePlot();
    Dialog::makePlot();
}




//.............supprimer tous..............
void Dialog::on_pushButton_supptous_clicked()
{
    {
         bool test = a.supprimerTout();
        QMessageBox msgBox;

        if(test)
        {
            msgBox.setText("Suppression avec succes.");
        ui->tableView_avions->setModel(a.afficher());

        }
        else
            msgBox.setText("Echec de suppression");
        msgBox.exec();

}

}
//...............ALERTE..................
void Dialog::on_pushButton_alerte_clicked()
{
    if (a.alerte()>0)
                {
                    QString notif=QString::number(a.alerte())+" etat En panne .\n""Click Ok to exit.";
                    QMessageBox::warning(nullptr, QObject::tr("Alerte"),notif, QMessageBox::Ok);
                }
        else QMessageBox::information(nullptr, QObject::tr("OK"), QObject::tr("etat non panne  \n""Click Ok to exit."), QMessageBox::Ok);
}



void Dialog::on_pushButton_alerte_2_clicked()
{
    Calendrier *cal = new Calendrier();
    cal->resize(600,600);
    cal->show();


}

void Dialog::on_pushButton_add_clicked()
{
    bool ok;
    QString text = QInputDialog::getText(
        this, tr("Evenement d'entré"), tr("Veuillez entrer le nom de l'événement"), QLineEdit::Normal, 0, &ok);
    if (!ok || text.isEmpty()) return;

    auto date = ui->calendarWidget->selectedDate();

    QString event_title = text;
    QString event_start = "";
    QString event_end = "";
    QString event_local = "";
    QString _method = "POST";
    date = date.addDays(-1);
    event_start = event_end = date.toString("yyyy-MM-ddT16%3A00%3A00Z");

    QByteArray byte;
    byte.append("calendar_event%5Btitle%5D=" + event_title.toUtf8());
    byte.append("&calendar_event%5Bstart_at%5D=" + event_start.toUtf8());
    byte.append("&calendar_event%5Bend_at%5D=" + event_end.toUtf8());
    byte.append("&calendar_event%5Blocation_name%5D=" + event_local.toUtf8());
 //   byte.append("&calendar_event%5Bcontext_code%5D=user_" + user);
    byte.append("&_method=POST");
   // byte.append("&authenticity_token=" + token);
    QString url = "http://canvas.tongji.edu.cn/api/v1/calendar_events";
    //auto re = post(url, byte, "application/x-www-form-urlencoded");

   /* auto document = QJsonDocument::fromJson(re);
    auto object = document.object();
    auto value = object.value("id");
    auto plid = value.toInt();*/

    QJsonObject temp;
    temp.insert("context_name", QString(name));
    temp.insert("context_type", "User");
    QString d = date.toString("yyyy-MM-dd");
    d = d + "T16:00:00Z";
    temp.insert("plannable_date", d);
    QJsonObject pl;
    pl.insert("title", text);
    temp.insert("plannable", QJsonValue(pl));
   // temp.insert("plannable_id", plid);
   /* QJsonValueRef ref = this->json.find(this->select_date).value();
    QJsonArray arr = ref.toArray();
    arr.append(temp);
    ref = arr;*/

    auto format =
        ui->calendarWidget->dateTextFormat(ui->calendarWidget->selectedDate());
    format.setBackground(QColor("#00FFFF"));
    ui->calendarWidget->setDateTextFormat(ui->calendarWidget->selectedDate(),
                                          format);

  //  on_calendarWidget_clicked(ui->calendarWidget->selectedDate());
}






void Dialog::on_calendarWidget_clicked(const QDate &date)
{
    this->select_date = date.toString("yyyy-MM-dd");
    this->selected_day_json = this->json[date.toString("yyyy-MM-dd")].toArray();
    if (selected_day_json.size()) {
       // ui->comboBox->clear();
        for (int i = 0; i < selected_day_json.size(); i++) {
            auto context_name =
                selected_day_json[i].toObject()["context_name"].toString();
          //  ui->comboBox->addItem(context_name);
        }
    } else {
      //  ui->comboBox->clear();
       // ui->lineEdit_id_avion_2->clear();
      //  ui->lineEdit_id_avion_3->clear();
        ui->lineEdit_id_avion_3->setText("En panne");
        auto format = ui->calendarWidget->dateTextFormat(
            ui->calendarWidget->selectedDate());
        format.setBackground(QColor("#FFFFFF"));
        ui->calendarWidget->setDateTextFormat(
            ui->calendarWidget->selectedDate(), format);
    }
}




void Dialog::on_Excel_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Excel file"), qApp->applicationDirPath (),
                                                       tr("Excel Files (*.xls)"));
            QString sheetName="test";
    ExportExcelObject obj(fileName, sheetName, ui->tableView_avions);
    obj.addField(0, tr("Id_avion"), "int");
    obj.addField(1, tr("marque"), "char(20)");
    obj.addField(2, tr("type_moteur"), "char(20)");
    obj.addField(3, tr("conso"), "float");
    obj.addField(4, tr("kilometrage"), "float");
    obj.addField(5, tr("prix_achat"), "float");
    obj.addField(6, tr("etat_avion"), "char(20)");



    obj.export2Excel();
}

// ////////////////////////////////////////////////PASSAGERS///////////////////////////////////////////////////////////////////////////////////


void Dialog::on_pb_ajouter_clicked()
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

void Dialog::on_pb_supp_clicked()
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

void Dialog::on_pb_modif_clicked()
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




void Dialog::on_checkBox_age_clicked()
{
   ui->tablePassager->setModel(P.trieage());
}


void Dialog::on_checkBox_alphabet_clicked()
{
   ui->tablePassager->setModel(P.triealphabet());
}

void Dialog::on_checkBox_3_clicked()
{
     ui->tablePassager->setModel(P.trievalise());
}


void Dialog::on_tablePassager_clicked(const QModelIndex &index)
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

void Dialog::on_lineEdit_recherche_2_textChanged(const QString &arg1)
{
    QString rech = ui->lineEdit_recherche->text();
        P.recherche(ui->tablePassager,rech);
        if (ui->lineEdit_recherche->text().isEmpty())
        {
            ui->tablePassager->setModel(P.afficher());
        }
}

void Dialog::on_pushButton_PDF_clicked()
{
    P.telechargerPDF();


           QMessageBox::information(nullptr,QObject::tr("OK"),
                      QObject::tr("Téléchargement terminé"), QMessageBox::Cancel);
}

void Dialog::on_pushButton_map_clicked()
{
    m = new mapping(this);

     m->show();
}
void Dialog::ChercherFromArduino(){
    d = ar.read_from_arduino();
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

/************************************* VOLS/ILYESS ***********************************************/


void Dialog::on_pushButton_Ajoutervols_clicked()
{
        int num_vols=ui->lineEdit_n_de_vol->text().toInt(); //convertir en entier
        QDate d_vols=ui->lineeditdateTimeEdit->date();
        int cap_vols=ui->lineEdit_capacitevol->text().toInt();
        QString dest=ui->lineEdit_Destination->text();
        int nb=ui->lineEdit_nb->text().toInt();
        vols V(num_vols,d_vols,cap_vols,dest,nb);
            bool test=V.ajoutervols();
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




void Dialog::on_pushButton_afichervols_clicked()
{
    ui->tableView_vols->setModel(V.affichervols());
}

void Dialog::on_pushButton_supprimer_clicked()
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


void Dialog::on_pushButton_modifiervol_clicked()
{

        int num_vols=ui->lineEdit_n_de_vol->text().toInt();
        QDate d_vols=ui->lineeditdateTimeEdit->date();
        int cap_vols=ui->lineEdit_capacitevol->text().toInt();
        QString dest=ui->lineEdit_Destination->text();
        int nb=ui->lineEdit_nb->text().toInt();
        vols V(num_vols,d_vols,cap_vols,dest,nb);

        bool test=V.modifiervols(V.getnum_vols(),V.getd_vols(),V.getcap_vols(),V.getdest(),V.getnb());
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



void Dialog::on_tableView_vols_clicked(const QModelIndex &index)
{
    ui->lineEdit_n_de_vol->setText(ui->tableView_vols->model()->data(ui->tableView_vols->model()->index(index.row(),0)).toString());
    ui->lineEdit_capacitevol->setText(ui->tableView_vols->model()->data(ui->tableView_vols->model()->index(index.row(),1)).toString());
    ui->lineEdit_Destination->setText(ui->tableView_vols->model()->data(ui->tableView_vols->model()->index(index.row(),2)).toString());
    ui->lineEdit_nb->setText(ui->tableView_vols->model()->data(ui->tableView_vols->model()->index(index.row(),3)).toString());

}
/*void Dialog::on_lineEdit_recherche_textChanged()
{

}*/
void Dialog::on_pushButton_Reset_clicked()
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


void Dialog::on_SSS_activated()
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


void Dialog::on_pushButton_pdf_clicked()
{
    QPdfWriter pdf("C:\\Users\\USER\\Desktop\\QTT\\LAYYSSYY\\PDF_Avions.pdf");

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
             QMessageBox::information(this, QObject::tr("PDF EnregistrÃ©!"),
             QObject::tr("PDF EnregistrÃ©!.\n" "Click Cancel to exit."), QMessageBox::Cancel);
}
void Dialog::on_pushButton_AI_clicked()
{   QString test=ui->test->text();
    if(V.ESTIMATION(test)!=-1)
  {

     QString pred=QString::number(int(V.ESTIMATION(test)));
     ui->Estimation->setText(pred);
     ui->estimation->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
     ui->estimation->setModel(V.afficherlghayb());

  }
    else QMessageBox::critical(nullptr, QObject::tr(" NOT OK"),
                               QObject::tr("Nom Du Base Est Incorrecte RÃ©essayer.\n"
                                           "Click Cancel to exit."), QMessageBox::Cancel);

}

void Dialog::on_pushButton_statestique_clicked()
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

void Dialog::on_pushButton_4_clicked()
{
    QString nomFile="fichier excel ";
            QMessageBox msg;
            if(!nomFile.length()){

                msg.setText("entrer le nom du fichier");
                msg.exec();
            }
            else{
            QFile file("C:\\Users\\USER\\Desktop\\QTT\\LAYYSSYY\\"+nomFile+".csv");
            QString finalmsg="fichier modifie avec succes";
             if(!file.exists()){
             finalmsg="fichier cree avec succes";
             }
            file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text);

            QTextStream txt(&file);
            txt<<"num_vols             \t\t  d_vols    \t\t                                   cap_vols   \t\t                         dest \n";

            for(int i=0;i<5;i++){

            QString num_vols= ui->tableView_vols->model()->index(i,0).data().toString();
            QString d_vols= ui->tableView_vols->model()->index(i,1).data().toString();
            QString cap_vols= ui->tableView_vols->model()->index(i,2).data().toString();
            QString dest= ui->tableView_vols->model()->index(i,3).data().toString();

            if(num_vols.length()){

            txt<< "'"+ num_vols +"' \t";
            txt<< "                 '"+ d_vols +"' \t";
            txt<< "                     '"+ cap_vols +"' \t";
            txt<< "                    '"+ dest +"' \t\n\n";
            }
            }
            msg.setText(finalmsg);
            msg.exec();
            file.close();
            }

}


void Dialog::on_lineEdit_recherche_3_textChanged(const QString &arg1)
{
    ui->tableView_vols->setModel(vs.Recherchevols(arg1));

}
