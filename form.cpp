#include "form.h"
#include "ui_form.h"

Form::Form(QWidget *parent, const QString &username)
    : QWidget(parent)
    , ui(new Ui::Form)
{
    ui->setupUi(this);
    receiveCredentials(username);
    ui->TF->setAlignment(Qt::AlignCenter);
    ui->TR->setAlignment(Qt::AlignCenter);
    ui->TTS->setAlignment(Qt::AlignCenter);

    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1");
    db.setPort(3306);
    db.setUserName("root");
    db.setPassword("mysql");
    db.setDatabaseName("Airline_database");

    if(db.open())
    {
        qDebug() << "Database connect.";
    }
    else
    {
        qDebug() << "not connect";
    }

    QSqlQuery qrt;

    int Total;
    qrt.prepare("SELECT SUM(TOT) FROM ticket");

    if(qrt.exec())
    {
        qrt.next();
        Total = qrt.value(0).toInt();
        ui->TTS->setText(QString::number(Total));
        qrt.clear();
    }
    else
    {
        ui->TTS->setText("0");
    }

    qrt.prepare("SELECT SUM(TOF) FROM ticket");

    if(qrt.exec())
    {
        qrt.next();
        Total = qrt.value(0).toInt();
        ui->TR->setText(QString::number(Total));
        qrt.clear();
    }
    else{
        ui->TR->setText("0");
    }

    qrt.prepare("SELECT COUNT(*) FROM flight");

    if(qrt.exec())
    {
        qrt.next();
        Total = qrt.value(0).toInt();
        ui->TF->setText(QString::number(Total));
        qrt.clear();
    }
    else{
        ui->TF->setText("0");
    }

    AutoTable();
    db.close();
}

void Form::receiveCredentials(const QString &username)
{
    storedUsername = username;
}

void Form::AutoTable()
{
    QSqlQuery qrt1;
    qrt1.prepare("SELECT * FROM flight");

    if(qrt1.exec())
    {
        ui->tableWidget->verticalHeader()->setVisible(false);
        ui->tableWidget->setRowCount(0);
        int row = 0;
        while(qrt1.next())
        {
            ui->tableWidget->insertRow(row);
            ui->tableWidget->setItem(row,0,new QTableWidgetItem(qrt1.value("FlightID").toString()));
            ui->tableWidget->setItem(row,1,new QTableWidgetItem(qrt1.value("FlightName").toString()));
            ui->tableWidget->setItem(row,2,new QTableWidgetItem(qrt1.value("Arrival").toString()));
            ui->tableWidget->setItem(row,3,new QTableWidgetItem(qrt1.value("Departure").toString()));
            ui->tableWidget->setItem(row,4,new QTableWidgetItem(qrt1.value("Duration").toString()));
            ui->tableWidget->setItem(row,5,new QTableWidgetItem(qrt1.value("Class").toString()));
            ui->tableWidget->setItem(row,6,new QTableWidgetItem(qrt1.value("Seats").toString()));
            ui->tableWidget->setItem(row,7,new QTableWidgetItem(qrt1.value("DOF").toString()));
            ui->tableWidget->setItem(row,8,new QTableWidgetItem(qrt1.value("Booked").toString()));
            row++;
        }
        qrt1.clear();
    }
    else
    {
        qDebug() << "Query Error : " << qrt1.lastError().text();
    }
}

void Form::on_calendarWidget_clicked(const QDate &date)
{
    QString Date = date.toString("MM-dd-yyyy");
    db.open();
    QSqlQuery qrt2;
    qrt2.prepare("SELECT * FROM flight WHERE DOF = ?");
    qrt2.bindValue(0,Date);

    if(qrt2.exec())
    {
        ui->tableWidget->setRowCount(0);
        int row = 0;
        while(qrt2.next())
        {
            ui->tableWidget->insertRow(row);
            ui->tableWidget->setItem(row,0,new QTableWidgetItem(qrt2.value("FlightID").toString()));
            ui->tableWidget->setItem(row,1,new QTableWidgetItem(qrt2.value("FlightName").toString()));
            ui->tableWidget->setItem(row,2,new QTableWidgetItem(qrt2.value("Arrival").toString()));
            ui->tableWidget->setItem(row,3,new QTableWidgetItem(qrt2.value("Departure").toString()));
            ui->tableWidget->setItem(row,4,new QTableWidgetItem(qrt2.value("Duration").toString()));
            ui->tableWidget->setItem(row,5,new QTableWidgetItem(qrt2.value("Class").toString()));
            ui->tableWidget->setItem(row,6,new QTableWidgetItem(qrt2.value("Seats").toString()));
            ui->tableWidget->setItem(row,7,new QTableWidgetItem(qrt2.value("DOF").toString()));
            ui->tableWidget->setItem(row,8,new QTableWidgetItem(qrt2.value("Booked").toString()));
            row++;
        }
        qrt2.clear();
    }
    else
    {
        qDebug() << "Query Error : " << qrt2.lastError().text();
    }
    db.close();
}

Form::~Form()
{
    delete ui;
}





void Form::on_tableWidget_cellClicked(int row, int column)
{
    Q_UNUSED(column);

    ui->tableWidget->setCurrentCell(row,0);
    ui->tableWidget->selectRow(row);
}

