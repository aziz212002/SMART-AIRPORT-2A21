#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QMessageBox>
#include "vols.h"

namespace Ui { class MainWindow; }

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
     explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:

    void on_pushButton_Ajoutervols_clicked();

    void on_pushButton_afichervols_clicked();

    void on_pushButton_supprimer_clicked();

    void on_pushButton_modifiervol_clicked();

    void on_tableView_vols_clicked(const QModelIndex &index);

    void on_lineEdit_recherche_textChanged();

    void on_pushButton_Reset_clicked();

    //void on_comboBox_tri_activated();

    void on_SSS_activated();

    void on_pushButton_statestique_clicked();

private:
    Ui::MainWindow *ui;
    vols V;
};
#endif // MAINWINDOW_H
