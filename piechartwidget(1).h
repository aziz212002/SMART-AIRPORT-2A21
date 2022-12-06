#ifndef PIECHARTWIDGET_H
#define PIECHARTWIDGET_H

#include <QWidget>

class piechartWidget : public QWidget
{
    Q_OBJECT
public:
    explicit piechartWidget(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *);

signals:

};

#endif // PIECHARTWIDGET_H
