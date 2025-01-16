#include "addflight.h"
#include "ui_addflight.h"

AddFlight::AddFlight(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddFlight),
    timer(new QTimer(this))
{
    ui->setupUi(this);
    AutoID();

    ui->calendarWidget->setVisible(false);

    ui->FA_TimeOfFlight->setTime(QTime::currentTime());
    ui->FA_DateOfFlight->setDate(QDate::currentDate());

}

AddFlight::AutoID()
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
    qrt.prepare("SELECT FlightID FROM flight ORDER BY FlightID DESC LIMIT 1");

    if(!qrt.exec())
    {
        qDebug() << "Failed to execute : " << qrt.lastError().text();
    }

    QString newValue;
    if (qrt.next())
    {
        QString lastValue = qrt.value(0).toString();
        int lastNumber = lastValue.mid(2).toInt();
        newValue = QString("FL%1").arg(lastNumber + 1, 3, 10, QChar('0'));
        ui->FA_FlightID->setText(newValue);
    }
    else
    {
        newValue = "FL001";
        ui->FA_FlightID->setText(newValue);
    }

    qrt.clear();
    db.close();
    if(!db.isOpen())
    {
        qDebug() << "Database is closed.";
    }
    return 0;

}

void AddFlight::on_Cancel_clicked()
{
    emit backtoform();
}

void AddFlight::on_FA_Add_clicked()
{
    QDate selectedDate = ui->FA_DateOfFlight->date();
    QTime selectedTime = ui->FA_TimeOfFlight->time();
    QDateTime selectedDateTime(selectedDate, selectedTime);

    QDateTime currentDateTime = QDateTime::currentDateTime();

    if (selectedDateTime < currentDateTime) {
        QMessageBox::warning(NULL, "Time/Date", "Select valid Time/Date.");
        return;
    }

    QString FlightID = ui->FA_FlightID->text();
    QString FlightN = ui->FA_FlightName->text();
    QString Arrival = ui->FA_Arrival->currentText();
    QString Dep = ui->FA_Departure->currentText();
    int Dur = ui->FA_Duration->text().toInt();
    QString Class = ui->FA_Class->currentText();
    int Seats = ui->FA_Seat->text().toInt();
    int Fare = ui->FA_Fare->text().toInt();
    QString DOF = ui->FA_DateOfFlight->date().toString("MM-dd-yyyy");
    QString TOF = ui->FA_TimeOfFlight->time().toString("HH:mm:ss");
    int Booked = 0;

    QString FaRe = "" ;
    QString SeatS = "" ;
    QString DUR = "";
    if(Fare > 0 && Seats >0 && Dur >0)
    {
       FaRe = QString::number(Fare);
        SeatS = QString::number(Seats);
       DUR = QString::number(Dur);
    }
    else
    {
        QMessageBox::information(NULL,NULL,"Give valid Fare/Seats/Duration.");
        return;
    }
    db.open();
    QSqlQuery qrt1;
    qrt1.prepare("INSERT INTO flight(FlightID,FlightName,Arrival,Departure,Duration,Class,Seats,Fare,DOF,TOF,Booked) values(?,?,?,?,?,?,?,?,?,?,?)");

    if(Arrival != Dep)
    {
        if(FlightID != "" && FlightN != "" && DUR != "" && Class != "" && SeatS != "" && FaRe != "")
        {
            qrt1.bindValue(0,FlightID);
            qrt1.bindValue(1,FlightN);
            qrt1.bindValue(2,Arrival);
            qrt1.bindValue(3,Dep);
            qrt1.bindValue(4,DUR);
            qrt1.bindValue(5,Class);
            qrt1.bindValue(6,SeatS);
            qrt1.bindValue(7,FaRe);
            qrt1.bindValue(8,DOF);
            qrt1.bindValue(9,TOF);
            qrt1.bindValue(10,Booked);

            if(!qrt1.exec())
            {
                qDebug() << "Faild : " << qrt1.lastError().text();
                QMessageBox::information(NULL,NULL,"Flight is Not Added.");
                return;
            }
            else
            {
                QMessageBox::information(NULL,NULL,"Flight Added Successfuly.");
                qrt1.clear();
                emit Relode();
            }
        }
        else
        {
            QMessageBox::information(NULL,NULL,"Fill the Respactive information.");
            return;
        }
    }

    else
    {
        QMessageBox::information(NULL,NULL,"Cann't add flight for same location.");
        return;
    }

    db.close();
}

AddFlight::~AddFlight()
{
    delete ui;
}

void AddFlight::on_FA_DateOfFlight_editingFinished()
{
    ui->calendarWidget->setVisible(true);
}


void AddFlight::on_calendarWidget_clicked(const QDate &date)
{
    QDate currentDate = QDate::currentDate();

    if (date > currentDate) {
        QDateEdit *dateEdit = findChild<QDateEdit*>("FA_DateOfFlight");
        dateEdit->setDate(date);
    } else {
        QMessageBox::warning(this, "Invalid Date", "The selected date must be in the future.");
    }
    ui->calendarWidget->setVisible(false);
}
