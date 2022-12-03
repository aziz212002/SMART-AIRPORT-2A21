#include "mapping.h"
#include "ui_mapping.h"
#include "passagers.h"
#include <QPrinter>
#include <QPrintDialog>
#include <QPagedPaintDevice>
#include<QPixmap>
#include<QString>
#include<QSqlQuery>
#include<QPainter>
#include<QLineEdit>
#include<QLabel>
#include<QMessageBox>
#include<QSqlDatabase>

mapping::mapping(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::mapping)
{
    ui->setupUi(this);
}

mapping::~mapping()
{
    delete ui;
}


void mapping::on_pushButton_generer_map_clicked()
{
    int passeport = ui->lineEdit_passeport->text().toInt();
    QString emplacement= ui->comboBox_emplacement->currentText();

             QString id_string= QString::number(passeport);
                    QSqlQuery query;
                    query.prepare("select * from passager where passeport_passager='"+id_string+"'");

                    if(query.exec()){

                        while(query.next())
                        { ui->textEdit->setText(query.value(5).toString());


                            if((ui->textEdit->toPlainText()== "1")and(ui->comboBox_emplacement->currentText()=="Check-In area"))
                              {
                                     ui->label_pic->clear();
                                     QPixmap pix("C:/Users/toufa/OneDrive/Bureau/Projet QT/Maps/Check-In_Gate1.png");
                                     int w = ui->label_pic->width();
                                     int h = ui->label_pic->height();
                                     ui->label_pic->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
                                         }
                             else if((ui->textEdit->toPlainText()=="2")and(ui->comboBox_emplacement->currentText()=="Check-In area"))
                              {
                                     ui->label_pic->clear();
                                     QPixmap pix("C:/Users/toufa/OneDrive/Bureau/Projet QT/Maps/Check-In_Gate2.png");
                                     int w = ui->label_pic->width();
                                     int h = ui->label_pic->height();
                                     ui->label_pic->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
                              }
                              else if((ui->textEdit->toPlainText()=="3")and(ui->comboBox_emplacement->currentText()=="Check-In area"))
                                 {
                                     ui->label_pic->clear();
                                     QPixmap pix("C:/Users/toufa/OneDrive/Bureau/Projet QT/Maps/Check-In_Gate3.png");
                                     int w = ui->label_pic->width();
                                     int h = ui->label_pic->height();
                                     ui->label_pic->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
                                 }
                              else if((ui->textEdit->toPlainText()=="4")and(ui->comboBox_emplacement->currentText()=="Check-In area"))
                                 {
                                     ui->label_pic->clear();
                                     QPixmap pix("C:/Users/toufa/OneDrive/Bureau/Projet QT/Maps/Check-In_Gate4.png");
                                     int w = ui->label_pic->width();
                                     int h = ui->label_pic->height();
                                     ui->label_pic->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
                                 }
                            else if((ui->textEdit->toPlainText()=="1")and(ui->comboBox_emplacement->currentText()=="Entrance hall"))
                             {
                                    ui->label_pic->clear();
                                    QPixmap pix("C:/Users/toufa/OneDrive/Bureau/Projet QT/Maps/Hall_Gate1.png");
                                    int w = ui->label_pic->width();
                                    int h = ui->label_pic->height();
                                    ui->label_pic->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
                             }
                             else if((ui->textEdit->toPlainText()=="2")and(ui->comboBox_emplacement->currentText()=="Entrance hall"))
                                {
                                    ui->label_pic->clear();
                                    QPixmap pix("C:/Users/toufa/OneDrive/Bureau/Projet QT/Maps/Hall_Gate2.png");
                                    int w = ui->label_pic->width();
                                    int h = ui->label_pic->height();
                                    ui->label_pic->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
                                }
                             else if((ui->textEdit->toPlainText()=="3")and(ui->comboBox_emplacement->currentText()=="Entrance hall"))
                                {
                                    ui->label_pic->clear();
                                    QPixmap pix("C:/Users/toufa/OneDrive/Bureau/Projet QT/Maps/Hall_Gate3.png");
                                    int w = ui->label_pic->width();
                                    int h = ui->label_pic->height();
                                    ui->label_pic->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
                                }
                              else if((ui->textEdit->toPlainText()=="4")and(ui->comboBox_emplacement->currentText()=="Entrance hall"))
                                {
                                    ui->label_pic->clear();
                                    QPixmap pix("C:/Users/toufa/OneDrive/Bureau/Projet QT/Maps/Hall_Gate4.png");
                                    int w = ui->label_pic->width();
                                    int h = ui->label_pic->height();
                                    ui->label_pic->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
                                }
                              else if((ui->textEdit->toPlainText()== "1")and(ui->comboBox_emplacement->currentText()=="Services"))
                              {
                                     ui->label_pic->clear();
                                     QPixmap pix("C:/Users/toufa/OneDrive/Bureau/Projet QT/Maps/Services_Gate1.png");
                                     int w = ui->label_pic->width();
                                     int h = ui->label_pic->height();
                                     ui->label_pic->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
                                         }
                             else if((ui->textEdit->toPlainText()=="2")and(ui->comboBox_emplacement->currentText()=="Services"))
                              {
                                     ui->label_pic->clear();
                                     QPixmap pix("C:/Users/toufa/OneDrive/Bureau/Projet QT/Maps/Services_Gate2.png");
                                     int w = ui->label_pic->width();
                                     int h = ui->label_pic->height();
                                     ui->label_pic->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
                              }
                              else if((ui->textEdit->toPlainText()=="3")and(ui->comboBox_emplacement->currentText()=="Services"))
                                 {
                                     ui->label_pic->clear();
                                     QPixmap pix("C:/Users/toufa/OneDrive/Bureau/Projet QT/Maps/Services_Gate3.png");
                                     int w = ui->label_pic->width();
                                     int h = ui->label_pic->height();
                                     ui->label_pic->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
                                 }
                              else if((ui->textEdit->toPlainText()=="4")and(ui->comboBox_emplacement->currentText()=="Services"))
                                 {
                                     ui->label_pic->clear();
                                     QPixmap pix("C:/Users/toufa/OneDrive/Bureau/Projet QT/Maps/Services_Gate4.png");
                                     int w = ui->label_pic->width();
                                     int h = ui->label_pic->height();
                                     ui->label_pic->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
                                 }
                            else if((ui->textEdit->toPlainText()=="1")and(ui->comboBox_emplacement->currentText()=="Administration"))
                             {
                                    ui->label_pic->clear();
                                    QPixmap pix("C:/Users/toufa/OneDrive/Bureau/Projet QT/Maps/Administration_Gate1.png");
                                    int w = ui->label_pic->width();
                                    int h = ui->label_pic->height();
                                    ui->label_pic->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
                             }
                             else if((ui->textEdit->toPlainText()=="2")and(ui->comboBox_emplacement->currentText()=="Administration"))
                                {
                                    ui->label_pic->clear();
                                    QPixmap pix("C:/Users/toufa/OneDrive/Bureau/Projet QT/Maps/Administration_Gate2.png");
                                    int w = ui->label_pic->width();
                                    int h = ui->label_pic->height();
                                    ui->label_pic->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
                                }
                             else if((ui->textEdit->toPlainText()=="3")and(ui->comboBox_emplacement->currentText()=="Administration"))
                                {
                                    ui->label_pic->clear();
                                    QPixmap pix("C:/Users/toufa/OneDrive/Bureau/Projet QT/Maps/Administration_Gate3.png");
                                    int w = ui->label_pic->width();
                                    int h = ui->label_pic->height();
                                    ui->label_pic->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
                                }
                              else if((ui->textEdit->toPlainText()=="4")and(ui->comboBox_emplacement->currentText()=="Administration"))
                                {
                                    ui->label_pic->clear();
                                    QPixmap pix("C:/Users/toufa/OneDrive/Bureau/Projet QT/Maps/Administration_Gate4.png");
                                    int w = ui->label_pic->width();
                                    int h = ui->label_pic->height();
                                    ui->label_pic->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
                                }
                            else if((ui->textEdit->toPlainText()=="1")and(ui->comboBox_emplacement->currentText()=="Control"))
                             {
                                    ui->label_pic->clear();
                                    QPixmap pix("C:/Users/toufa/OneDrive/Bureau/Projet QT/Maps/Control_Gate1.png");
                                    int w = ui->label_pic->width();
                                    int h = ui->label_pic->height();
                                    ui->label_pic->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
                             }
                             else if((ui->textEdit->toPlainText()=="2")and(ui->comboBox_emplacement->currentText()=="Control"))
                                {
                                    ui->label_pic->clear();
                                    QPixmap pix("C:/Users/toufa/OneDrive/Bureau/Projet QT/Maps/Control_Gate2.png");
                                    int w = ui->label_pic->width();
                                    int h = ui->label_pic->height();
                                    ui->label_pic->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
                                }
                             else if((ui->textEdit->toPlainText()=="3")and(ui->comboBox_emplacement->currentText()=="Control"))
                                {
                                    ui->label_pic->clear();
                                    QPixmap pix("C:/Users/toufa/OneDrive/Bureau/Projet QT/Maps/Control_Gate3.png");
                                    int w = ui->label_pic->width();
                                    int h = ui->label_pic->height();
                                    ui->label_pic->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
                                }
                              else if((ui->textEdit->toPlainText()=="4")and(ui->comboBox_emplacement->currentText()=="Control"))
                                {
                                    ui->label_pic->clear();
                                    QPixmap pix("C:/Users/toufa/OneDrive/Bureau/Projet QT/Maps/Control_Gate4.png");
                                    int w = ui->label_pic->width();
                                    int h = ui->label_pic->height();
                                    ui->label_pic->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
                                }
                            else if((ui->textEdit->toPlainText()=="1")and(ui->comboBox_emplacement->currentText()=="VIP Lounge"))
                             {
                                    ui->label_pic->clear();
                                    QPixmap pix("C:/Users/toufa/OneDrive/Bureau/Projet QT/Maps/VIP_Gate1.png");
                                    int w = ui->label_pic->width();
                                    int h = ui->label_pic->height();
                                    ui->label_pic->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
                             }
                             else if((ui->textEdit->toPlainText()=="2")and(ui->comboBox_emplacement->currentText()=="VIP Lounge"))
                                {
                                    ui->label_pic->clear();
                                    QPixmap pix("C:/Users/toufa/OneDrive/Bureau/Projet QT/Maps/VIP_Gate2.png");
                                    int w = ui->label_pic->width();
                                    int h = ui->label_pic->height();
                                    ui->label_pic->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
                                }
                             else if((ui->textEdit->toPlainText()=="3")and(ui->comboBox_emplacement->currentText()=="VIP Lounge"))
                                {
                                    ui->label_pic->clear();
                                    QPixmap pix("C:/Users/toufa/OneDrive/Bureau/Projet QT/Maps/VIP_Gate3.png");
                                    int w = ui->label_pic->width();
                                    int h = ui->label_pic->height();
                                    ui->label_pic->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
                                }
                              else if((ui->textEdit->toPlainText()=="4")and(ui->comboBox_emplacement->currentText()=="VIP Lounge"))
                                {
                                    ui->label_pic->clear();
                                    QPixmap pix("C:/Users/toufa/OneDrive/Bureau/Projet QT/Maps/VIP_Gate4.png");
                                    int w = ui->label_pic->width();
                                    int h = ui->label_pic->height();
                                    ui->label_pic->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
                                }
                            else if((ui->textEdit->toPlainText()=="1")and(ui->comboBox_emplacement->currentText()=="Duty-free shop"))
                             {
                                    ui->label_pic->clear();
                                    QPixmap pix("C:/Users/toufa/OneDrive/Bureau/Projet QT/Maps/DutyFree_Gate1.png");
                                    int w = ui->label_pic->width();
                                    int h = ui->label_pic->height();
                                    ui->label_pic->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
                             }
                             else if((ui->textEdit->toPlainText()=="2")and(ui->comboBox_emplacement->currentText()=="Duty-free shop"))
                                {
                                    ui->label_pic->clear();
                                    QPixmap pix("C:/Users/toufa/OneDrive/Bureau/Projet QT/Maps/DutyFree_Gate2.png");
                                    int w = ui->label_pic->width();
                                    int h = ui->label_pic->height();
                                    ui->label_pic->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
                                }
                             else if((ui->textEdit->toPlainText()=="3")and(ui->comboBox_emplacement->currentText()=="Duty-free shop"))
                                {
                                    ui->label_pic->clear();
                                    QPixmap pix("C:/Users/toufa/OneDrive/Bureau/Projet QT/Maps/DutyFree_Gate3.png");
                                    int w = ui->label_pic->width();
                                    int h = ui->label_pic->height();
                                    ui->label_pic->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
                                }
                              else if((ui->textEdit->toPlainText()=="4")and(ui->comboBox_emplacement->currentText()=="Duty-free shop"))
                                {
                                    ui->label_pic->clear();
                                    QPixmap pix("C:/Users/toufa/OneDrive/Bureau/Projet QT/Maps/DutyFree_Gate4.png");
                                    int w = ui->label_pic->width();
                                    int h = ui->label_pic->height();
                                    ui->label_pic->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
                                }

                          }
}}
