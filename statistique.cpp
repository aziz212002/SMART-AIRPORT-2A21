#include "statistique.h"
#include "ui_statistique.h"
#include<QSqlQueryModel>
#include<QSqlQuery>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QHorizontalStackedBarSeries>
#include <QtCharts/QLineSeries>
#include <QtCharts/QCategoryAxis>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>

statistique::statistique(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::statistique)
{
    ui->setupUi(this);
}

statistique::~statistique()
{
    delete ui;

}
void statistique::Statistique()
{
    QSqlQuery query0,query1,query2,query3,query4,query5,query6;

    qreal tot=0,p1=0,p2=0,p3=0,p4=0,p5=0,p6=0;


    query0.prepare("SELECT * FROM PERSONNEL");
    query0.exec();




    query1.prepare("SELECT * FROM PERSONNEL  WHERE  age_per='21' ");
    query1.exec();

    query2.prepare("SELECT * FROM PERSONNEL WHERE age_per='25' ");
    query2.exec();

    query3.prepare("SELECT * FROM PERSONNEL WHERE age_per='34' ");
    query3.exec();

    query4.prepare("SELECT * FROM PERSONNEL WHERE age_per='27' ");
    query4.exec();



    while (query0.next()){tot++;}

  while (query1.next()){p1++;}
    while (query2.next()){p2++;}
    while (query3.next()){p3++;}
      while (query4.next()){p4++;}

   tot=tot/2;



    // forme + pourcntage + chnia cercule
    QPieSeries *series = new QPieSeries();

    series->append("AGE 21",p3);
    series->append("AGE 25",p4);
    series->append("AGE 34",p3);
    series->append("AGE 27",p4);
    //

    // Create the chart widget
    QChart *chart = new QChart();

    // Add data to chart with title and show legend
           chart->addSeries(series);
        //  chart->setTitle("statistique des personnel
          chart->legend()->show();


 //display
   QChartView *chartView=new QChartView(chart,ui->label);
   chartView->setRenderHint(QPainter::Antialiasing);
        chartView->setMinimumSize(900,900);
   chartView->show();
}
