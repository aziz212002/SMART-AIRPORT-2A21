#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "passagers.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pb_ajouter_clicked();

    void on_pb_supp_clicked();

    void on_pb_modif_clicked();

    void on_radioB_age_clicked();

    void on_radioB_alphabet_clicked();

    void on_tablePassager_clicked(const QModelIndex &index);

    void on_radioB_nbvalises_clicked();

    void on_lineEdit_recherche_textChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
    passager P;
};
#endif // MAINWINDOW_H
