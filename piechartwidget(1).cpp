#include "piechartwidget.h"
#include "stat_produit.h"

piechartWidget::piechartWidget(QWidget *parent) : QWidget(parent)
{

}

void piechartWidget::paintEvent(QPaintEvent *)
{
    stat_Produit s;
    int b=s.Stat_1();
    int c=s.Stat_2();
    int d=s.Stat_3();

     float s1= b*100 ;
     float s2=c*100;
     float nb = b+c+d ;
     float q1 ;
        q1 = s1/nb ;
     float q2;
        q2=s2/nb;
     float y  ;
        y = (q1*360)/100 ;
     float m;
        m= (q2*360)/100;
     float z  ;
        z=360-(y+m) ;

    QPainter painter(this);
    QRectF size=QRectF(50,50,this->width()-200,this->width()-200);

    painter.setBrush(Qt::blue);
    painter.drawPie(size,0,16*y);
    //Entre 0 et 30
    painter.setBrush(Qt::green);
    painter.drawPie(size,16*y,16*m);
    //Entre 30 et 60
    painter.setBrush(Qt::red);
    painter.drawPie(size,16*(m+y),16*z);
    //Plus que 60
}
