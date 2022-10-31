#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QMessageBox>
#include "personnel.h"

namespace Ui { class MainWindow; }

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

private:
    Ui::MainWindow *ui;
    Personnel p;
};
#endif // MAINWINDOW_H
