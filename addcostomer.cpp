#include "addcostomer.h"
#include "ui_addcostomer.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include<QMessageBox>

AddCostomer::AddCostomer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddCostomer)
{
    ui->setupUi(this);
    AutoID();
}

AddCostomer::AutoID()
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
    qrt.prepare("SELECT CustomerID FROM customer ORDER BY CustomerID DESC LIMIT 1");

    if(!qrt.exec())
    {
            qDebug() << "Failed to execute : " << qrt.lastError().text();
    }

    QString newValue;
    if (qrt.next())
    {
            QString lastValue = qrt.value(0).toString();
            int lastNumber = lastValue.mid(2).toInt();
            newValue = QString("CS%1").arg(lastNumber + 1, 3, 10, QChar('0'));
            ui->AC_CustomerID->setText(newValue);
    }
     else
    {
            newValue = "CS001";
            ui->AC_CustomerID->setText(newValue);
    }

    qrt.clear();
    db.close();
    if(!db.isOpen())
    {
        qDebug() << "Database is closed.";
    }
    return 0;

}

AddCostomer::~AddCostomer()
{
    delete ui;
}

void AddCostomer::on_Cancel_clicked()
{
    //this->setVisible(false);
    emit backtoviewCust();
}

void AddCostomer::on_AC_Add_clicked()
{

    QString custID = ui->AC_CustomerID->text();
    QString FirstN = ui->AC_FirstName->text();
    QString LastN = ui->AC_LastName->text();
    QString Address = ui->AC_Address->toPlainText();
    QString Gender = "";
    if(ui->AC_Male->isChecked())
    {
        Gender = "Male";
    }
    else if (ui->AC_Female->isChecked())
    {
        Gender = "Female";
    }
    else
    {
        QMessageBox::information(NULL,NULL,"Fill the Respective information.");
        return;
    }
    QString Contact = ui->AC_ContentNo->text();
    QString PassPo = ui->AC_PassportNo->text();
    QString NIC = ui->AC_NID->text();

    QString CONT = "";
    QString PASSNO = "";
    QString NIC2 = "";


    QRegularExpression digitRegex("^\\d+$");

    if (!Contact.isEmpty() && !PassPo.isEmpty() && !NIC.isEmpty())
    {
        // Check if Contact has exactly 10 digits
        if (Contact.length() == 10 && digitRegex.match(Contact).hasMatch())
        {
            CONT = Contact;
        }
        else
        {
            QMessageBox::information(this, "Invalid Input", "Contact No must be exactly 10 digits.");
            return;
        }

        // Check if PassPo has exactly 8 digits
        if (PassPo.length() == 8 && digitRegex.match(PassPo).hasMatch())
        {
            PASSNO = PassPo;
        }
        else
        {
            QMessageBox::information(this, "Invalid Input", "Passport No must be exactly 8 digits.");
            return;
        }

        // Check if NIC has exactly 12 digits
        if (NIC.length() == 12 && digitRegex.match(NIC).hasMatch())
        {
            NIC2 = NIC;
        }
        else
        {
            QMessageBox::information(this, "Invalid Input", "NIC must be exactly 12 digits.");
            return;
        }

        // If all checks pass, proceed with the rest of your code
        // For example, save the information or perform further processing
    }
    /*if(Contact != "" && PassPo != "" && NIC != "")
    {
        if (Contact.length() == 10)
        {
            CONT = Contact;
        }
        else
        {
            QMessageBox::information(this, "Invalid Input", "Contact No must be exactly 10 characters.(give valid digit Number)");
            return;
        }

        if (PassPo.length() == 8)
        {
            PASSNO = PassPo;
        }
        else
        {
            QMessageBox::information(this, "Invalid Input", "Passport No must be exactly 8 characters.(give valid digit Number)");
            return;
        }

        if (NIC.length() == 12)
        {
            NIC2 = NIC;
        }
        else
        {
            QMessageBox::information(this, "Invalid Input", "NIC must be exactly 12 characters.(give valid digit Number)");
            return;
        }
    }*/

    else
    {
        QMessageBox::information(this, "Invalid Input", "Please provide valid Contact No, Passport No, and NIC.");
        return;
    }

    QString DOB = ui->AC_DateOfBirth->date().toString("MM-dd-yyyy");

    db.open();
    QSqlQuery qrt1;
    qrt1.prepare("INSERT INTO Customer(CustomerID,FirstName,LastName,PassportNo,NationalID,Address,Contact,Gender,DOB) values(?,?,?,?,?,?,?,?,?)");

    if(custID != "" && FirstN != "" && LastN != "" && PASSNO != "" && NIC2 != "" && Address != "" && CONT != "" && Gender != "")
    {
        qrt1.bindValue(0,custID);
        qrt1.bindValue(1,FirstN);
        qrt1.bindValue(2,LastN);
        qrt1.bindValue(3,PassPo);
        qrt1.bindValue(4,NIC);
        qrt1.bindValue(5,Address);
        qrt1.bindValue(6,Contact);
        qrt1.bindValue(7,Gender);
        qrt1.bindValue(8,DOB);

        if(!qrt1.exec())
        {
            qDebug() << "Faild : " << qrt1.lastError().text();
            QMessageBox::information(NULL,NULL,"Not Successful.");
        }
        else
        {
            QMessageBox::information(NULL,NULL,"Successful.");
            emit Relode();
        }
    }
    else
    {
        QMessageBox::information(NULL,NULL,"Fill the Respective information.");
    }

    db.close();
    AutoID();
}
