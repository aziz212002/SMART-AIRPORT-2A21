#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "calendrier.h"
#include "exportexcelobject.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableView_avions->setModel(a.afficher());
    QValidator *validator_id = new QIntValidator(1, 99999, this);
    QValidator *validator_kilom = new QIntValidator(0, 900,this);
    // the edit lineedit will only accept integers between 100 and 999

        ui->lineEdit_kilometrage->setValidator(validator_kilom);

        ui->lineEdit_id_avion->setValidator(validator_id);



        QRegularExpression rx("^[0-9]+.+[0-9]");



        QValidator *validator = new QRegularExpressionValidator(rx, this);

        ui->lineEdit_prix->setValidator(validator);

        ui->lineEdit_kilometrage->setValidator(validator);

        ui->lineEdit_consomation->setValidator(validator);



}

MainWindow::~MainWindow()
{
    delete ui;
}
//...........................AJOUT.........................

void MainWindow::on_pushButton_ajouter_avion_clicked()
{

    int Id_avion = ui->lineEdit_id_avion->text().toInt();
    QString marque = ui->comboBox_marque->currentText();
    QString type_moteur = ui->comboBox_type->currentText();
    float consomation = ui->lineEdit_consomation->text().toFloat();
    float kilometrage = ui->lineEdit_kilometrage->text().toFloat();
    float prix_achat = ui ->lineEdit_prix->text().toFloat();
    QString etat_avion=ui->comboBox_etat->currentText();

    Avion atmp (Id_avion,marque,type_moteur,consomation,kilometrage,prix_achat,etat_avion);
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
//...........................SUPPRIMER............................
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



//..........................MODIFICATION........................

void MainWindow::on_pushButton_clicked()
{
    int Id_avion =ui->lineEdit_id_avion->text().toInt();
    QString marque = ui->comboBox_marque->currentText();
    QString type_moteur = ui->comboBox_type->currentText();
    float consomation = ui->lineEdit_consomation->text().toFloat();
    float kilometrage = ui->lineEdit_kilometrage->text().toFloat();
    float prix_achat = ui ->lineEdit_prix->text().toFloat();
    QString etat_avion=ui->comboBox_etat->currentText();
    Avion a (Id_avion, marque,type_moteur,consomation,kilometrage,prix_achat,etat_avion);
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



//......................................TRI.......................................
void MainWindow::on_pushButton_tri_clicked()
{
   ui->tableView_avions->setModel(ptmp.tri());
}
void MainWindow::on_pushButton_tri_conso_clicked()
{
   ui->tableView_avions->setModel(ptmp.triconso());
}
void MainWindow::on_pushButton_triprix_clicked()
{
    ui->tableView_avions->setModel(ptmp.triprix());

}

//..........................RECHERCHE........................

void MainWindow::on_pushButton_chercher_avion_clicked()
{
    int Id_avion=ui->lineEdit_id3->text().toInt() ;
          if (Id_avion == NULL) {
              QMessageBox::information(this, tr("Empty Field"),
                  tr("Please enter a Name."));
              return;
          } else {
          ui->tableView_avions->setModel(ptmp.cherche_id(Id_avion));
}
}

void MainWindow::on_search_avion_textChanged(const QString &arg1)
{
    ui->tableView_avions->setModel(ptmp.recherche(arg1));

}




//////................PDF......................
void MainWindow::on_pushButton_exportPDF_clicked()
{
    QString strStream;
            strStream = QFileDialog::getSaveFileName((QWidget* )0, "Export PDF", QString(), "*.pdf");
                if (QFileInfo(strStream).suffix().isEmpty())
                    { strStream.append(".pdf"); }

                QPrinter printer(QPrinter::PrinterResolution);
                printer.setOutputFormat(QPrinter::PdfFormat);
                printer.setPaperSize(QPrinter::A4);
                printer.setOutputFileName(strStream);

                      QTextStream out(&strStream);

                      const int rowCount = ui->tableView_avions->model()->rowCount();
                      const int columnCount = ui->tableView_avions->model()->columnCount();
                      QString TT = QDateTime::currentDateTime().toString();
                      out <<"<html>\n"
                            "<head>\n"
                             "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                          << "<title>ERP - COMmANDE LIST<title>\n "
                          << "</head>\n"
                          "<body bgcolor=#ffffff link=#5000A0>\n"
                             "<h1 style=\"text-align: center;\"><strong> "+TT+"</strong></h1>"
                            +"<img src=C:\\Users\\asus\\Desktop\\pdf\\logo_projet />" //path
                          "<h1 style=\"text-align: center;\"><strong> ****LISTE DES AVIONS **** </strong></h1>"

                          "<table style=\"text-align: center; font-size: 10px;\" border=1>\n "
                            "</br> </br>";
                      // headers
                      out << "<thead><tr bgcolor=#d6e5ff>";
                      for (int column = 0; column < columnCount; column++)
                          if (!ui->tableView_avions->isColumnHidden(column))
                              out << QString("<th>%1</th>").arg(ui->tableView_avions->model()->headerData(column, Qt::Horizontal).toString());
                      out << "</tr></thead>\n";

                      // data table
                      for (int row = 0; row < rowCount; row++) {
                          out << "<tr>";
                          for (int column = 0; column < columnCount; column++)
                        {
                              if (!ui->tableView_avions->isColumnHidden(column)) {
                                  QString data =ui->tableView_avions->model()->data(ui->tableView_avions->model()->index(row, column)).toString().simplified();
                                  out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;")); //pas compriis
                              }
                          }
                          out << "</tr>\n";
                      }
                      out <<  "</table>\n"
                          "</body>\n"
                          "</html>\n";

                      QTextDocument document;
                      document.setHtml(strStream);
                      document.print(&printer);


}

///////.................statistique..............................
QVector<double> MainWindow::statistiques()
{
    QSqlQuery q;
    QVector<double> stat(5);
    stat[0]=0;
    stat[1]=0;
    stat[2]=0;
    stat[3]=0;
    stat[4]=0;
    q.prepare("SELECT PRIX FROM AVION WHERE PRIX<=1000");
    q.exec();
    while (q.next())
    {
        stat[0]++;

    }
    q.prepare("SELECT CONSO FROM AVION WHERE PRIX>1000 and PRIX<=5000");
    q.exec();
    while (q.next())
    {
        stat[1]++;

    }
    q.prepare("SELECT PRIX FROM AVION WHERE PRIX>5000 and PRIX<=100000");
    q.exec();
    while (q.next())
    {
        stat[2]++;

    }
    q.prepare("SELECT PRIX FROM AVION WHERE PRIX>100000 and PRIX<=150000");
    q.exec();
    while (q.next())
    {
        stat[3]++;

    }
    q.prepare("SELECT PRIX FROM AVION WHERE PRIX>150000 and PRIX<=1000000 ");
    q.exec();
    while (q.next())
    {
        stat[4]++;

    }
    return stat;
}
///............................CUSTOMPLOT..........................
void MainWindow::makePlot()
{
    // prepare data:
    QVector<double> x3(5), y3(20);
    for (int i=0; i<x3.size(); ++i)
    {
      x3[i] = i+1;

    }
    for (int i=0; i<y3.size(); ++i)
    {
      y3[i] = i+1;

    }

    QCPBars *bars1 = new QCPBars(ui->customplot->xAxis, ui->customplot->yAxis);
    bars1->setWidth(2/(double)x3.size());
    bars1->setData(x3, MainWindow::statistiques());////fonction statistiques
    bars1->setPen(Qt::NoPen);
    bars1->setBrush(QColor(200, 40, 60, 170));
    ui->customplot->replot();

    // move bars above graphs and grid below bars:
    ui->customplot->addLayer("abovemain", ui->customplot->layer("main"), QCustomPlot::limAbove);
    ui->customplot->addLayer("belowmain", ui->customplot->layer("main"), QCustomPlot::limBelow);
    ui->customplot->xAxis->grid()->setLayer("belowmain");
    ui->customplot->yAxis->grid()->setLayer("belowmain");

    // set some pens, brushes and backgrounds:
    QVector<double> Ticks;
    Ticks<<1<<2<<3<<4<<5<<6<<7;//////
    QVector<QString> labels;
    labels<<"0-1000"<<"1000-5000"<<"5000-10000"<<"10000-150000"<<"150000-1000000";////////
    QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
    textTicker->addTicks(Ticks,labels);
    ui->customplot->xAxis->setTicker(textTicker);
    ui->customplot->xAxis->setSubTicks(false);
    ui->customplot->xAxis->setTickLength(0,4);
    ui->customplot->xAxis->setBasePen(QPen(Qt::white, 1));
    ui->customplot->yAxis->setBasePen(QPen(Qt::white, 1));
    ui->customplot->xAxis->setTickPen(QPen(Qt::transparent, 1));
    ui->customplot->yAxis->setTickPen(QPen(Qt::white, 1));
    ui->customplot->xAxis->setSubTickPen(QPen(Qt::transparent, 1));
    ui->customplot->yAxis->setSubTickPen(QPen(Qt::transparent, 1));
    ui->customplot->xAxis->setTickLabelColor(Qt::white);
    ui->customplot->yAxis->setTickLabelColor(Qt::white);
    ui->customplot->xAxis->grid()->setPen(QPen(QColor(140, 140, 140), 1, Qt::DotLine));
    ui->customplot->yAxis->grid()->setPen(QPen(QColor(140, 140, 140), 1, Qt::DotLine));
    ui->customplot->xAxis->grid()->setSubGridPen(QPen(QColor(80, 80, 80), 1, Qt::DotLine));
    ui->customplot->yAxis->grid()->setSubGridPen(QPen(QColor(80, 80, 80), 1, Qt::DotLine));
    ui->customplot->xAxis->grid()->setSubGridVisible(true);
    ui->customplot->yAxis->grid()->setSubGridVisible(true);
    ui->customplot->xAxis->grid()->setZeroLinePen(Qt::NoPen);
    ui->customplot->yAxis->grid()->setZeroLinePen(Qt::NoPen);
    ui->customplot->xAxis->setUpperEnding(QCPLineEnding::esSpikeArrow);
    ui->customplot->yAxis->setUpperEnding(QCPLineEnding::esSpikeArrow);
    QLinearGradient plotGradient;
    plotGradient.setStart(0, 0);
    plotGradient.setFinalStop(0, 350);
    plotGradient.setColorAt(0, QColor(00, 50, 80));
    plotGradient.setColorAt(1, QColor(10, 20, 50));
    ui->customplot->setBackground(plotGradient);
    QLinearGradient axisRectGradient;
    axisRectGradient.setStart(0, 0);
    axisRectGradient.setFinalStop(0, 350);
    axisRectGradient.setColorAt(0, QColor(10, 50, 80));//
    axisRectGradient.setColorAt(1, QColor(0, 0, 30));
    ui->customplot->axisRect()->setBackground(axisRectGradient);

    ui->customplot->rescaleAxes();
    ui->customplot->xAxis->setRange(0, 7);
    ui->customplot->yAxis->setRange(0, 10);


}
//................STATSTIQUE..................
void MainWindow::on_pushButton_statistic_event_clicked()
{
    ui->customplot->clearPlottables();
    MainWindow::makePlot();
    MainWindow::makePlot();
}




//.............supprimer tous..............
void MainWindow::on_pushButton_supptous_clicked()
{
    {
         bool test = a.supprimerTout();
        QMessageBox msgBox;

        if(test)
        {
            msgBox.setText("Suppression avec succes.");
        ui->tableView_avions->setModel(a.afficher());

        }
        else
            msgBox.setText("Echec de suppression");
        msgBox.exec();

}

}
//...............ALERTE..................
void MainWindow::on_pushButton_alerte_clicked()
{
    if (a.alerte()>0)
                {
                    QString notif=QString::number(a.alerte())+" etat En panne .\n""Click Ok to exit.";
                    QMessageBox::warning(nullptr, QObject::tr("Alerte"),notif, QMessageBox::Ok);
                }
        else QMessageBox::information(nullptr, QObject::tr("OK"), QObject::tr("etat non panne  \n""Click Ok to exit."), QMessageBox::Ok);
}



void MainWindow::on_pushButton_alerte_2_clicked()
{
    Calendrier *cal = new Calendrier();
    cal->resize(600,600);
    cal->show();


}

void MainWindow::on_pushButton_add_clicked()
{
    bool ok;
    QString text = QInputDialog::getText(
        this, tr("Evenement d'entré"), tr("Veuillez entrer le nom de l'événement"), QLineEdit::Normal, 0, &ok);
    if (!ok || text.isEmpty()) return;

    auto date = ui->calendarWidget->selectedDate();

    QString event_title = text;
    QString event_start = "";
    QString event_end = "";
    QString event_local = "";
    QString _method = "POST";
    date = date.addDays(-1);
    event_start = event_end = date.toString("yyyy-MM-ddT16%3A00%3A00Z");

    QByteArray byte;
    byte.append("calendar_event%5Btitle%5D=" + event_title.toUtf8());
    byte.append("&calendar_event%5Bstart_at%5D=" + event_start.toUtf8());
    byte.append("&calendar_event%5Bend_at%5D=" + event_end.toUtf8());
    byte.append("&calendar_event%5Blocation_name%5D=" + event_local.toUtf8());
 //   byte.append("&calendar_event%5Bcontext_code%5D=user_" + user);
    byte.append("&_method=POST");
   // byte.append("&authenticity_token=" + token);
    QString url = "http://canvas.tongji.edu.cn/api/v1/calendar_events";
    //auto re = post(url, byte, "application/x-www-form-urlencoded");

   /* auto document = QJsonDocument::fromJson(re);
    auto object = document.object();
    auto value = object.value("id");
    auto plid = value.toInt();*/

    QJsonObject temp;
    temp.insert("context_name", QString(name));
    temp.insert("context_type", "User");
    QString d = date.toString("yyyy-MM-dd");
    d = d + "T16:00:00Z";
    temp.insert("plannable_date", d);
    QJsonObject pl;
    pl.insert("title", text);
    temp.insert("plannable", QJsonValue(pl));
   // temp.insert("plannable_id", plid);
   /* QJsonValueRef ref = this->json.find(this->select_date).value();
    QJsonArray arr = ref.toArray();
    arr.append(temp);
    ref = arr;*/

    auto format =
        ui->calendarWidget->dateTextFormat(ui->calendarWidget->selectedDate());
    format.setBackground(QColor("#00FFFF"));
    ui->calendarWidget->setDateTextFormat(ui->calendarWidget->selectedDate(),
                                          format);

  //  on_calendarWidget_clicked(ui->calendarWidget->selectedDate());
}






void MainWindow::on_calendarWidget_clicked(const QDate &date)
{
    this->select_date = date.toString("yyyy-MM-dd");
    this->selected_day_json = this->json[date.toString("yyyy-MM-dd")].toArray();
    if (selected_day_json.size()) {
       // ui->comboBox->clear();
        for (int i = 0; i < selected_day_json.size(); i++) {
            auto context_name =
                selected_day_json[i].toObject()["context_name"].toString();
          //  ui->comboBox->addItem(context_name);
        }
    } else {
      //  ui->comboBox->clear();
       // ui->lineEdit_id_avion_2->clear();
      //  ui->lineEdit_id_avion_3->clear();
        ui->lineEdit_id_avion_3->setText("En panne");
        auto format = ui->calendarWidget->dateTextFormat(
            ui->calendarWidget->selectedDate());
        format.setBackground(QColor("#FFFFFF"));
        ui->calendarWidget->setDateTextFormat(
            ui->calendarWidget->selectedDate(), format);
    }
}




void MainWindow::on_Excel_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Excel file"), qApp->applicationDirPath (),
                                                       tr("Excel Files (*.xls)"));
            QString sheetName="test";
    ExportExcelObject obj(fileName, sheetName, ui->tableView_avions);
    obj.addField(0, tr("Id_avion"), "int");
    obj.addField(1, tr("marque"), "char(20)");
    obj.addField(2, tr("type_moteur"), "char(20)");
    obj.addField(3, tr("conso"), "float");
    obj.addField(4, tr("kilometrage"), "float");
    obj.addField(5, tr("prix_achat"), "float");
    obj.addField(6, tr("etat_avion"), "char(20)");



    obj.export2Excel();
}







