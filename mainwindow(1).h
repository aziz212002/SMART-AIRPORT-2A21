#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "produit.h"
#include <QListView>
#include <QTableView>
#include <QTreeView>
#include <QItemDelegate>
#include "arduino.h"

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
    void on_ajouter_clicked();

    void on_supprimer_clicked();

    void on_afficher_clicked();

    void on_modifier_clicked();

    void on_Annuler_1_clicked();

    void on_Annuler_2_clicked();

    void on_Annuler_3_clicked();

    void on_trier_clicked();

    void on_afficher_pour_modifier_clicked();

    void on_Rechercher_clicked();

    void on_Quitter_clicked();

    void on_alerte_clicked();

    void on_mailing_clicked();

    void update_label();   // slot permettant la mise à jour du label état de la lampe 1,
    // ce slot est lancé à chaque réception d'un message de Arduino

    void on_pushButton_clicked();   // bouton ON

    void on_pushButton_2_clicked(); // bouton OFF



private:
    Ui::MainWindow *ui;
    Produit P;
    QByteArray data; // variable contenant les données reçues

    Arduino A; // objet temporaire
};

#endif // MAINWINDOW_H
