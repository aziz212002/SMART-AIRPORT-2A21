#ifndef DIALOG_H
#define DIALOG_H
#include <QMainWindow>
#include "produit.h"
#include <QListView>
#include <QTableView>
#include <QTreeView>
#include <QItemDelegate>
#include <QDialog>
#include "passagers.h"
#include "arduino.h"
#include "mapping.h"
#include <QDialog>
#include <QMessageBox>
#include <QDebug>
#include "personnel.h"
#include<QAbstractSocket>
#include<QtNetwork>
#include <QTcpSocket>
#include <QDateTime>
#include <QMessageBox>
#include "QIntValidator"
#include <QDateEdit>
#include <QPlainTextEdit>
#include <QPrinter>
//#include <QPrinterInfo>
//#include <QPrintDialog>
#include <QTextStream>
#include <QPainter>
#include <QTextStream>
#include <QFileDialog>
#include <QTextDocument>
#include <QtPrintSupport/QPrinter>
#include <QFileDialog>
#include <QTextDocument>
#include <strstream>
#include <QSystemTrayIcon>
#include <QRegExpValidator>
#include <QDesktopServices>
#include <QUrl>
#include <QGuiApplication>
//#include <QQmlApplicationEngine>
#include <QTcpSocket>
//#include <QQuickItem>
#include <QSystemTrayIcon>
#include <QIntValidator>
//*********AVION MEHDI********
#include "exportexcelobject.h"
#include <QMainWindow>
#include <QApplication>
#include <QMessageBox>
#include <avion.h>
#include <QFileDialog>
#include <QtPrintSupport/QPrinter>
#include <QTextDocument>
#include <QtDebug>
#include <QMessageBox>
#include <QTableView>
#include <QAbstractItemView>
#include <QIntValidator>
#include <QVector>
#include <qjsondocument.h>
#include <QSortFilterProxyModel>
#include <QFile>
#include <QInputDialog>
#include <QJsonArray>
#include <QJsonObject>
#include <QLineEdit>
#include <QMainWindow>
#include <QMessageBox>
#include <QNetworkAccessManager>
#include <QNetworkCookie>
#include <QNetworkCookieJar>
#include <QNetworkReply>
#include <QNetworkSession>
//*********VOLS*ILYESS********
#include <QMainWindow>
#include <QMessageBox>
#include "vols.h"


namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:

    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();

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

    void on_pushButton_clicked();
    void mailenvoye(QString);
    void on_comboBox_activated(const QString &arg1);
    void on_pushButton_55_clicked();

    void on_pushButton_333_clicked();

    void on_pushButton_222_clicked();

    void on_pushButton_444_clicked();

    void on_pushButton_555_clicked();

    void on_pushButton_777_clicked();

    void on_pb_mail_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_9_clicked();
//******AVION MEHDI****************************
    void on_pushButton_ajouter_avion_clicked();
    void on_pushButton_supprimer_avion_clicked();
 //   void on_pushButton_modifier_avion_clicked();
    void on_pushButton_modify_clicked();
    void on_pushButton_tri_clicked();
    void on_pushButton_chercher_avion_clicked();
   // void on_tabWidget_currentChanged(int index);
    void on_pushButton_tri_conso_clicked();
    void on_pushButton_triprix_clicked();
    void on_pushButton_exportPDF_clicked();
    QVector<double> statistiques();
         void makePlot();

         void on_pushButton_statistic_event_clicked();
    //void on_pushButton_stat_clicked();

         void on_pushButton_supptous_clicked();

         void on_pushButton_alerte_clicked();

         void on_pushButton_alerte_2_clicked();

         void on_pushButton_add_clicked();





         void on_calendarWidget_clicked(const QDate &date);


         void on_Excel_clicked();



         void on_search_avion_textChanged(const QString &arg1);

         void on_pb_ajouter_clicked();

         void on_pb_supp_clicked();

         void on_pb_modif_clicked();

         void on_checkBox_age_clicked();

         void on_checkBox_alphabet_clicked();

         void on_checkBox_3_clicked();

         void on_tablePassager_clicked(const QModelIndex &index);

         void on_lineEdit_recherche_2_textChanged(const QString &arg1);

         void on_pushButton_PDF_clicked();

         void on_pushButton_map_clicked();

         void ChercherFromArduino();

/***********************VOLS*ILYESS*************************/

 void on_pushButton_Ajoutervols_clicked();

    void on_pushButton_afichervols_clicked();

    void on_pushButton_supprimer_clicked();

    void on_pushButton_modifiervol_clicked();

    void on_tableView_vols_clicked(const QModelIndex &index);

    void on_lineEdit_recherche_textChanged();

    void on_pushButton_Reset_clicked();

    //void on_comboBox_tri_activated();

    void on_SSS_activated();


    void on_pushButton_pdf_clicked();

    void on_pushButton_AI_clicked();

   // void update_label();
    void on_pushButton_statestique_clicked();

    void on_pushButton_4_clicked();




    void on_lineEdit_recherche_3_textChanged(const QString &arg1);

    void on_lineEdit_recherche_3_cursorPositionChanged(int arg1, int arg2);

private:
    passager P;
    mapping * m;
    Arduino ar;
    Ui::Dialog *ui;
    Personnel p;
    QStringList files;
    QTcpSocket*mSocket;
    Produit P1;
    QByteArray data;
    //*******MAHDI AVION**********
    Avion a ;
    Avion ptmp;
    QByteArray d;
    vols V;
    vols vs;


    QNetworkAccessManager *manager;

    QByteArray token = "";
    QByteArray user = "";
    QByteArray name = "";

    QJsonObject json;
    QJsonArray selected_day_json;
    QString select_date;

    QByteArray post(QString url, QByteArray data, const char *type);
    QByteArray get(QString url);
    QJsonObject format(QByteArray data);
    void updatetoken(QNetworkReply *reply);
};

#endif // DIALOG_H
