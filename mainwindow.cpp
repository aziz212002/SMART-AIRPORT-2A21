//.....MUSTAPHA.....
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

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_8_clicked()//auth
{


        QString nom=ui->lineEdit_6->text();
        int cin=ui->lineEdit->text().toInt();
        QString c=QString::number(cin);
        QSqlQuery qry;
               qry.prepare("select * from PERSONNEL where Nom_per='"+nom+"'and  cin_per='"+c+"'");

               if (qry.exec())
               {

        QMessageBox::information(nullptr,QObject::tr("login done"),
                                                QObject::tr("login succesfully \n"
                                                            "Click Cancel to exit."),QMessageBox::Cancel);
               Dialog d;
               d.setModal(true);
               d.exec();
}
               else

               QMessageBox::information(nullptr,QObject::tr("login done"),
                                                       QObject::tr("login unsuccesfully \n"
                                                                   "Click Cancel to exit."),QMessageBox::Cancel); }





