#ifndef MAINWINDOW_H
#define MAINWINDOW_H
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
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QSortFilterProxyModel *proxy;

private slots:

    void on_pushButton_ajouter_avion_clicked();
    void on_pushButton_supprimer_avion_clicked();
 //   void on_pushButton_modifier_avion_clicked();
    void on_pushButton_clicked();
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

         void on_pushButton_supprimer_avion_2_clicked();

         void on_pushButton_del_clicked();

         void on_calendarWidget_clicked(const QDate &date);

         void on_tab_customContextMenuRequested(const QPoint &pos);

         void on_Excel_clicked();

         void on_tabWidget_currentChanged(int index);

         void on_tabWidget_tabBarClicked(int index);

         void on_lineEdit_textChanged(const QString &arg1);

         void on_search_avion_textChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
    Avion a ;
    Avion ptmp;


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
#endif // MAINWINDOW_H
