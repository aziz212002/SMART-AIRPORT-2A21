#include "dialog.h"
#include "ui_dialog.h"
#include "smtp.h"
#include <QDialog>
#include <QFileDialog>
#include "passagers.h"
Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    ui->comboBox->setModel(P.afficher2());

}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushButton_clicked()
{
    QString from = ui ->lineEdit_from ->text();
    QString to = ui->lineEdit_to->text();
    QString subject = ui->lineEdit_subject->text();
    QString password = ui ->lineEdit_password ->text();
    QString email_text = ui->textEdit_mail->toPlainText();

   Smtp* smtp = new Smtp(from, password, "smtp.gmail.com",465);
    connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));


       smtp->sendMail(from, to, subject, email_text);
}

void Dialog::mailenvoye(QString nettoyer)
{
    if(nettoyer == "Mail envoyé")
            QMessageBox::warning( nullptr, tr( "email" ), tr( "Mail sent.\n\n" ) );
        ui->lineEdit_to->clear();
        ui->lineEdit_subject->clear();
        ui->textEdit_mail->clear();
        ui->lineEdit_password->clear();
}

void Dialog::on_comboBox_activated(const QString &arg1)
{

    int ID_PASS=ui->comboBox->currentText().toInt();
    QString id_string=QString::number(ID_PASS);
    QSqlQuery query;
    query.prepare("select * from passager where passeport_passager='"+id_string+"'");
    if (query.exec())

        while(query.next())
        { ui->lineEdit_to->setText(query.value(9).toString());}
            else

        QMessageBox::critical(nullptr, QObject::tr("not OK"),
                    QObject::tr("failed.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

}


