#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include"passagers.h"

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
    void on_pushButton_clicked();
    void mailenvoye(QString);
    void on_comboBox_activated(const QString &arg1);


private:
    passager P;
    Ui::Dialog *ui;
};

#endif // DIALOG_H
