#ifndef INTEGRATION_H
#define INTEGRATION_H
#include <QMainWindow>
#include "passagers.h"
#include "dialog.h"
#include "mapping.h"
#include "arduino.h"


void on_pb_ajouter_clicked();

void on_pb_supp_clicked();

void on_pb_modif_clicked();

void on_tablePassager_clicked(const QModelIndex &index);

void on_lineEdit_recherche_textChanged(const QString &arg1);

void on_pushButton_PDF_clicked();

void on_pushButton_mail_clicked();

void on_checkBox_alphabet_clicked();

void on_checkBox_age_clicked();

void on_checkBox_3_clicked();

void on_pushButton_map_clicked();
void ChercherFromArduino();

private:
    Ui::MainWindow *ui;
    passager P;
    Dialog * Ui;
    mapping * m;
    Arduino a;
    QByteArray d;

#endif // INTEGRATION_H
