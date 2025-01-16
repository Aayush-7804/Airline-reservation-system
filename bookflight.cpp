#include "bookflight.h"
#include "ui_bookflight.h"

BookFlight::BookFlight(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BookFlight)
{
    ui->setupUi(this);
    AutoID();
}

BookFlight::AutoID()
{

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
    qrt.prepare("SELECT TicketID FROM ticket ORDER BY TicketID DESC LIMIT 1");

    if(!qrt.exec())
    {
        qDebug() << "Failed to execute : " << qrt.lastError().text();
    }

    QString newValue;
    if (qrt.next())
    {
        QString lastValue = qrt.value(0).toString();
        int lastNumber = lastValue.mid(2).toInt();
        newValue = QString("TK%1").arg(lastNumber + 1, 3, 10, QChar('0'));
        ui->ID->setText(newValue);
    }
    else
    {
        newValue = "TK001";
        ui->ID->setText(newValue);
    }

    qrt.clear();
    db.close();
    if(!db.isOpen())
    {
        qDebug() << "Database is closed.";
    }
    return 0;

}

BookFlight::~BookFlight()
{
    delete ui;
}

void BookFlight::on_Cancel_clicked()
{
    emit backtoform();
}

void BookFlight::on_BF_Search_clicked()
{
    QString Arrival = ui->BF_ArrivalSelecte->currentText();
    QString Dep = ui->BF_DipartureSelecte->currentText();

    db.open();
    QSqlQuery qrt;

    qrt.prepare("SELECT FlightID, FlightName, Class, Duration, DOF AS Date, TOF AS Time FROM flight WHERE Arrival= ? AND Departure= ?");
    qrt.bindValue(0,Arrival);
    qrt.bindValue(1,Dep);

    if(qrt.exec())
    {
        ui->tableWidget->verticalHeader()->setVisible(false);
        ui->tableWidget->setRowCount(0);
        int row = 0;

        while(qrt.next())
        {
            ui->tableWidget->insertRow(row);
            ui->tableWidget->setItem(row,0,new QTableWidgetItem(qrt.value("date").toString()));
            ui->tableWidget->setItem(row,1,new QTableWidgetItem(qrt.value("Time").toString()));
            ui->tableWidget->setItem(row,2,new QTableWidgetItem(qrt.value("FlightID").toString()));
            ui->tableWidget->setItem(row,3,new QTableWidgetItem(qrt.value("FlightName").toString()));
            ui->tableWidget->setItem(row,4,new QTableWidgetItem(qrt.value("Class").toString()));
            ui->tableWidget->setItem(row,5,new QTableWidgetItem(qrt.value("Duration").toString()));
            row++;
        }
    }
    else
    {
        qDebug() << "Error : " << qrt.lastError().text();
    }

    qrt.clear();
    db.close();

}

void BookFlight::on_BF_Search_2_clicked()
{
    QString CustID = ui->BF_CustomerID->text();

    if(db.open())
    {
        qDebug() << "Database connect.";
    }
    else
    {
        qDebug() << "not connect";
    }
    QSqlQuery qrt1;
    qrt1.prepare("SELECT FirstName,LastName, Contact, Gender FROM customer WHERE CustomerID = ?");
    qrt1.bindValue(0,CustID);

    if(qrt1.exec())
    {
        if(qrt1.next())
        {
            ui->BF_FirstName->setText(qrt1.value("FirstName").toString());
            ui->BF_LastName->setText(qrt1.value("LastName").toString());
            ui->BF_Contact->setText(qrt1.value("Contact").toString());
            ui->BF_Gender->setText(qrt1.value("Gender").toString());
        }

    }
    else
    {
        QMessageBox::information(NULL,NULL,"Customer didn't exist.");
        qDebug() << "error : " << qrt1.lastError().text();
    }

    qrt1.clear();
    db.close();
    if(!db.isOpen())
    {
        qDebug() << "Database is closed.";
    }
}

void BookFlight::on_tableWidget_cellClicked(int row, int column)
{
    Q_UNUSED(column);

    ui->tableWidget->setCurrentCell(row,2);
    ui->tableWidget->selectRow(row);
    this->Date = ui->tableWidget->item(row,0)->text();
    this->Time = ui->tableWidget->item(row,1)->text();
    this->FlightID = ui->tableWidget->item(row,2)->text();
    this->FLightName = ui->tableWidget->item(row,3)->text();
    this->Class = ui->tableWidget->item(row,4)->text();

    db.open();
    QSqlQuery qrt2;
    qrt2.prepare("SELECT Fare FROM flight WHERE FlightID = ?");
    qrt2.bindValue(0,FlightID);

    if(qrt2.exec() && qrt2.next())
    {
        QString fare = qrt2.value("Fare").toString();
        ui->BF_Fare->setText(fare);
    }
    else
    {
        qDebug() << "error : " << qrt2.lastError().text();
    }

    qrt2.clear();
    db.close();
}

void BookFlight::on_BF_Calcu_clicked()
{
    int fare = ui->BF_Fare->text().toInt();
    int No_Tic = ui->BF_TotalTik->text().toInt();

    int Ans = (fare * No_Tic);
    int Discount;

    if(Class == "Economy")
    {
        if(fare<=30000)
            Discount = 10;

        if(fare>30000)
            Discount = 12;
    }
    else if(Class == "Business")
    {
        if(fare<=50000)
            Discount = 14;

        if(fare>50000)
            Discount = 16;
    }
    else
    {
        if(fare<=70000)
            Discount = 18;

        if(fare>70000)
            Discount = 20;
    }

    Ans -= ((Ans*Discount)/100);
    ui->BF_TotalFare->setText(QString::number(Ans));
    ui->BF_Discount->setText(QString::number(Discount) +" %");
}

void BookFlight::on_BF_Book_clicked()
{
    QString TicketID = ui->ID->text();
    QString CustID = ui->BF_CustomerID->text();
    QString FirstN = ui->BF_FirstName->text();
    QString LastN = ui->BF_LastName->text();
    QString Gender = ui->BF_Gender->text();
    QString Contact = ui->BF_Contact->text();
    QString Arrival = ui->BF_ArrivalSelecte->currentText();
    QString Dep = ui->BF_DipartureSelecte->currentText();
    QString Fare = ui->BF_Fare->text();
    QString TOF = ui->BF_TotalFare->text();
    int TOS = ui->BF_TotalTik->text().toInt();
    int TOSF = ui->BF_TotalFare->text().toInt();
    QString Pay = "";

    if(ui->UPI->isChecked())
    {
        Pay = "UPI";
    }
    else if(ui->Cash->isChecked())
    {
        Pay = "Cash";
    }
    else if(ui->Cred_debCard->isChecked())
    {
        Pay = "Cradit/Debit Card";
    }
    else
    {
        QMessageBox::information(NULL,NULL,"Select The Payment option.");
        return;
    }
    db.open();
    QSqlQuery qrt3;

    qrt3.prepare("SELECT seats,Booked FROM flight WHERE FlightID = ?");
    qrt3.bindValue(0,FlightID);

    int SeatsAv;
    int BookedSE;
    if(qrt3.exec())
    {
        qrt3.next();
        SeatsAv = qrt3.value("Seats").toInt();
        BookedSE = qrt3.value("Booked").toInt();
        qrt3.clear();
    }

    if(Fare == "")
    {
        QMessageBox::warning(NULL,NULL,"Select Flight");
        return;
    }

    if(SeatsAv > 0)
    {
        BookedSE += TOS;
        SeatsAv -= TOS;

        qrt3.prepare("UPDATE flight SET Seats = ?, Booked = ? WHERE FlightID = ?");
        qrt3.bindValue(0,QString::number(SeatsAv));
        qrt3.bindValue(1,BookedSE);
        qrt3.bindValue(2,FlightID);

        qrt3.exec();

        qrt3.prepare("INSERT INTO ticket(TicketID,FlightID,FlightName,Arrival,Departure,Date,Time,CustomerID,FirstName,LastName,Gender,Contact,TOT,TOF,Payment) VALUES(?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)");

        if(CustID != "" && FirstN != "" && Fare != "" && TOF != "")
        {
            qrt3.bindValue(0,TicketID);
            qrt3.bindValue(1,FlightID);
            qrt3.bindValue(2,FLightName);
            qrt3.bindValue(3,Arrival);
            qrt3.bindValue(4,Dep);
            qrt3.bindValue(5,Date);
            qrt3.bindValue(6,Time);
            qrt3.bindValue(7,CustID);
            qrt3.bindValue(8,FirstN);
            qrt3.bindValue(9,LastN);
            qrt3.bindValue(10,Gender);
            qrt3.bindValue(11,Contact);
            qrt3.bindValue(12,TOS);
            qrt3.bindValue(13,TOSF);
            qrt3.bindValue(14,Pay);

            if(!qrt3.exec())
            {
                qDebug() << "Faild : " << qrt3.lastError().text();
                QMessageBox::information(NULL,NULL,"Flight is Not Added.");
            }
            else
            {
                QMessageBox::information(NULL,NULL,"Flight Added Successfuly.");
                qrt3.clear();
                emit Relode();
            }
        }
        else
        {
            QMessageBox::information(NULL,NULL,"Fill the Respective informatiom");
            qrt3.clear();
        }
    }
    else
    {
        QMessageBox::information(NULL,NULL,"All Seats are booked.");
        emit Relode();
        qrt3.clear();
    }
    db.close();
}

