#include "viewticket.h"
#include "ui_viewticket.h"

ViewTicket::ViewTicket(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ViewTicket)
{
    ui->setupUi(this);

    ui->worrning->setAlignment(Qt::AlignCenter);
}

ViewTicket::~ViewTicket()
{
    delete ui;
}

void ViewTicket::on_Cancel_clicked()
{
    emit backtoform();
}


void ViewTicket::on_VT_GetTicket_clicked()
{
    QString TicID = ui->VT_TicketID->text();

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
    qrt.prepare("SELECT * FROM ticket WHERE TicketID = ?");
    qrt.bindValue(0,TicID);

    if(qrt.exec())
    {
        if(qrt.next())
        {
            ui->VT_FlightID->setText(qrt.value("FlightID").toString());
            ui->VT_FlightName->setText(qrt.value("FlightName").toString());
            ui->VT_Arrival->setText(qrt.value("Arrival").toString());
            ui->VT_Departure->setText(qrt.value("Departure").toString());
            ui->VT_DOF->setText(qrt.value("Date").toString());
            ui->VT_TOF->setText(qrt.value("Time").toString());
            ui->VT_CustomerID->setText(qrt.value("CustomerID").toString());
            ui->VT_FirstName->setText(qrt.value("Firstname").toString());
            ui->VT_LastName->setText(qrt.value("Lastname").toString());
            ui->VT_Gender->setText(qrt.value("Gender").toString());
            ui->VT_ContactNo->setText(qrt.value("Contact").toString());

            QString dateString = qrt.value("Date").toString();
            QString timeString = qrt.value("time").toString();

            QDate selectedDate = QDate::fromString(dateString, "MM-dd-yyyy");
            QTime selectedTime = QTime::fromString(timeString, "HH:mm:ss");

            QDateTime selectedDateTime(selectedDate, selectedTime);

            QDateTime currentDateTime = QDateTime::currentDateTime();

            if (selectedDateTime < currentDateTime) {
                ui->worrning->setText("Ticket has been expired.");
                ui->worrning->setStyleSheet("color: rgb(255,0,0);");
            }
            else{
                ui->worrning->setText("Ticket is valid.");
                ui->worrning->setStyleSheet("color: rgb(0,255,0);");
            }

            ui->VT_Payment->setText(qrt.value("Payment").toString());
            ui->VT_TotalSeats->setText(qrt.value("TOT").toString());
        }
        else
        {
            QMessageBox::information(NULL,"","Ticket didn't exist; enter thw valid Ticket ID.");
            emit Relode();
        }
    }
    else
    {
        qDebug() << "Error to execut : " << qrt.lastError().text();
    }

    qrt.clear();
    db.close();
}

