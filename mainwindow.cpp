#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableView_avions->setModel(a.afficher());
    QValidator *validator_id = new QIntValidator(1, 99999, this);
        QValidator *validator_prix = new QIntValidator(0, 900,this);
    // the edit lineedit will only accept integers between 100 and 999

        ui->lineEdit_prix->setValidator(validator_prix);

        ui->lineEdit_id_avion->setValidator(validator_id);



        QRegularExpression rx("^[0-9]+.+[0-9]");



        QValidator *validator = new QRegularExpressionValidator(rx, this);

        ui->lineEdit_prix->setValidator(validator);

        ui->lineEdit_kilometrage->setValidator(validator);

        ui->lineEdit_cosomation->setValidator(validator);



}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_ajouter_avion_clicked()
{

    int Id_avion = ui->lineEdit_id_avion->text().toInt();
    QString marque = ui->lineEdit_Marque->text();
    QString type_moteur = ui->lineEdit_type->text();
    QDate Date = ui->dateEdit_vol->date();
    float consomation = ui->lineEdit_cosomation->text().toFloat();
    float kilometrage = ui->lineEdit_kilometrage->text().toFloat();
    float prix_achat = ui ->lineEdit_prix->text().toFloat();
    QString etat_avion = ui->lineEdit_etat->text();
    Avion atmp (Id_avion,marque,type_moteur,Date,consomation,kilometrage,prix_achat,etat_avion);
    bool test =  atmp.ajouter();
    if(test)
         {
                QMessageBox::information(nullptr, QObject::tr("database is open"),
                            QObject::tr("ajout successful.\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);
                ui->tableView_avions->setModel(a.afficher());

        }
            else
               { QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                            QObject::tr("ajout failed.\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel); }
}
void MainWindow::on_pushButton_supprimer_avion_clicked()
{
    int Id_avion =ui->lineEdit_id2->text().toInt();
    bool test=a.supprimer(Id_avion);
    if(test)
    {
         QMessageBox::information(nullptr, QObject::tr("ok"),
                                  QObject::tr("supp successful.\n"
                                               "Click Cancel to exit."), QMessageBox::Cancel);
         ui->tableView_avions->setModel(a.afficher());

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("not ok"),
                              QObject::tr("suppression non efectuee.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);

    }





void MainWindow::on_pushButton_clicked()
{
    int Id_avion =ui->lineEdit_id_avion->text().toInt();
    QString marque = ui->lineEdit_Marque->text();
    QString type_moteur = ui->lineEdit_type->text();
    float consomation = ui->lineEdit_cosomation->text().toFloat();
    QDate Date = ui->dateEdit_vol->date();
    float kilometrage = ui->lineEdit_kilometrage->text().toFloat();
    float prix_achat = ui ->lineEdit_prix->text().toFloat();
    QString etat_avion = ui->lineEdit_etat->text();
    Avion a (Id_avion, marque,type_moteur,Date,consomation,kilometrage,prix_achat,etat_avion);
    bool test =  a.modifier(Id_avion);

    if(test)

           {

        ui->tableView_avions->setModel(a.afficher());
               QMessageBox :: information (nullptr, QObject ::tr("OK"),

                            QObject ::tr("modifier effectué\n"

                                         "click cancel to exit"),

                       QMessageBox:: Cancel);


       }

           else

           {

               QMessageBox::critical(nullptr,QObject::tr("not ok"),

                                    QObject::tr("try again.\n"

                                                "click cancel to exit."),QMessageBox::Cancel);

           }
}
