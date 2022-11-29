 #include "mainwindow.h"
#include "ui_mainwindow.h"
#include "personnel.h"
#include <QApplication>
#include <QMessageBox>
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
#include<QPieSlice >
#include<QPieSeries>
#include<QChart>
#include<QPieSeries>
#include<QPrinter>
#include <QFileDialog>
#include<QPrintDialog>
#include<QtCharts>
#include<statistique.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{statistique *s;
    ui->setupUi(this);
    ui->lineEdit_1->setValidator( new QIntValidator(0, 999999, this));
    ui->tableView->setModel(p.afficher());
    ui->lineEdit_2->setValidator( new QIntValidator(0, 99999999, this));
    ui->lineEdit_3->setValidator( new QIntValidator(0, 999999, this));
    ui->lineEdit_3->setValidator( new QIntValidator(0, 999, this));
    s = new statistique();
                  s->setWindowTitle("statistique des employes");
                  s->Statistique();
                   s->setMinimumSize(800,800);
                 s->show();
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


void MainWindow::on_pushButton_3_clicked() //Supprimer
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


void MainWindow::on_lineEdit_recherche_textChanged()
{
    QString rech=ui->lineEdit_recherche->text();
    ui->tableView->setModel(p.Recherchepersonnel(rech));
}



void MainWindow::on_pushButton_5_clicked()//bouton tri
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


void MainWindow::on_pushButton_7_clicked()
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
void MainWindow::on_pb_mail_clicked()
    {
     Smtp* smtp = new Smtp("benromdhane.mohamedaziz@esprit.tn", "211JMT7323", "smtp.gmail.com", 465);
     connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));
     QString a=ui->Linemail->text();
     QString b=ui->Lineobjet->text();
     QString c=ui->msg ->toPlainText();

     smtp->sendMail("benromdhane.mohamedaziz@esprit.tn", a , b,c);
    }


void MainWindow::on_pushButton_8_clicked()
{


    QTabWidget tqb3;
        connect(ui->tqb3, SIGNAL(clicked()), this, SLOT(viewData));
        QString username=ui->lineEdit->text();
                QString password = ui->lineEdit_6->text();
                if(username == "Mohamed" && password == "143567")
                { QMessageBox::information(this, "Login", "Username and password is correct");
               //connect(ui->MainWindow->page_3, SIGNAL(on_connecter_clicked()), this, SLOT(viewData));

                }
                   // hide(); mainwindow = new MainWindow(this); mainwindow->show(); }
                    else if(username == "oussema" && password == "153567")
                { QMessageBox::information(this, "Login", "Username and password is correct");

                }
                        //hide(); mainwindow = new MainWindow(this); mainwindow->show(); }
                        else if(username == "khalil" && password == "73567")
                        { QMessageBox::information(this, "Login", "Username and password is correct");

                }
                            //hide(); mainwindow = new MainWindow(this); mainwindow->show(); }
                            else if(username == "Amine" && password == "133567")
                            { QMessageBox::information(this, "Login", "Username and password is correct");

                }
                                //hide(); mainwindow = new MainWindow(this); mainwindow->show(); }
                                else if(username == "Yassmine" && password == "123456")
                                { QMessageBox::information(this, "Login", "Username and password is correct");

                }
                                    //hide(); mainwindow = new MainWindow(this); mainwindow->show(); }
                                        else { QMessageBox::warning(this,"Login", "Username and password is not correct"); }
}

