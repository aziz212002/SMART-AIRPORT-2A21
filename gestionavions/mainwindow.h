#ifndef MAINWINDOW_H
#define MAINWINDOW_H
// second commit nn
#include <QMainWindow>
#include <QApplication>
#include <QMessageBox>
#include <avion.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public://mm
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_pushButton_ajouter_avion_clicked();
    void on_pushButton_supprimer_avion_clicked();
 //   void on_pushButton_modifier_avion_clicked();
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    Avion a ;

};
#endif // MAINWINDOW_H
