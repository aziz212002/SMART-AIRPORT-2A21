#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QMessageBox>
#include "personnel.h"
#include<QAbstractSocket>
#include<QtNetwork>
#include <QTcpSocket>
#include <QDateTime>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_MOC_NAMESPACE
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
     explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:

void on_pushButton_clicked(); //Ajout

void on_pushButton_2_clicked(); //Modif

void on_pushButton_3_clicked();//supp

void on_lineEdit_recherche_textChanged();

 void on_pushButton_5_clicked();

//void telechargerPDF();

 void on_pushButton_7_clicked();

/* void MainWindow::on_pushButton_8_clicked();*/

 void on_pb_mail_clicked();

 void on_pushButton_8_clicked();

private:
    Ui::MainWindow *ui;
    Personnel p;
    QStringList files;

};
#endif // MAINWINDOW_H
