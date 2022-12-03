#ifndef MAPPING_H
#define MAPPING_H

#include <QDialog>

namespace Ui {
class mapping;
}

class mapping : public QDialog
{
    Q_OBJECT

public:
    explicit mapping(QWidget *parent = nullptr);
    ~mapping();

private slots:
    void on_pushButton_generer_map_clicked();

private:
    Ui::mapping *ui;
};

#endif // MAPPING_H
