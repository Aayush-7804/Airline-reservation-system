#include "viewcustomer.h"
#include "ui_viewcustomer.h"

#include "addcostomer.h"


ViewCustomer::ViewCustomer(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ViewCustomer)
{
    ui->setupUi(this);
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
    AutoTable();
    db.close();
}

void ViewCustomer::AutoTable()
{
    QSqlQuery qrt;
    qrt.prepare("SELECT * FROM customer");

    if(qrt.exec())
    {
        ui->tableWidget->verticalHeader()->setVisible(false);
        ui->tableWidget->setRowCount(0);
        int row = 0;
        while(qrt.next())
        {
            ui->tableWidget->insertRow(row);
            ui->tableWidget->setItem(row,0,new QTableWidgetItem(qrt.value("CustomerID").toString()));
            ui->tableWidget->setItem(row,1,new QTableWidgetItem(qrt.value("FirstName").toString()));
            ui->tableWidget->setItem(row,2,new QTableWidgetItem(qrt.value("LastName").toString()));
            ui->tableWidget->setItem(row,3,new QTableWidgetItem(qrt.value("Contact").toString()));
            ui->tableWidget->setItem(row,4,new QTableWidgetItem(qrt.value("PassportNo").toString()));
            ui->tableWidget->setItem(row,5,new QTableWidgetItem(qrt.value("NationalID").toString()));
            ui->tableWidget->setItem(row,6,new QTableWidgetItem(qrt.value("Address").toString()));
            ui->tableWidget->setItem(row,7,new QTableWidgetItem(qrt.value("Gender").toString()));
            ui->tableWidget->setItem(row,8,new QTableWidgetItem(qrt.value("DOB").toString()));
            row++;
        }
    }
    else
    {
        qDebug() << "Query Error : " << qrt.lastError().text();
    }
    qrt.clear();
}

ViewCustomer::~ViewCustomer()
{
    delete ui;
}

void ViewCustomer::on_Search_clicked()
{
    QString CustID = ui->En_CustID->text();
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1");
    db.setPort(3306);
    db.setUserName("root");
    db.setPassword("mysql");
    db.setDatabaseName("Airline_database");

    db.open();
    QSqlQuery qrt1;

    qrt1.prepare("SELECT * FROM customer WHERE CustomerID = ?");
    qrt1.bindValue(0,CustID);

    if(qrt1.exec())
    {
        if(qrt1.next())
        {
            ui->tableWidget->clearContents();
            ui->tableWidget->setRowCount(0);
            ui->tableWidget->insertRow(0);
            ui->tableWidget->setItem(0,0,new QTableWidgetItem(qrt1.value("CustomerID").toString()));
            ui->tableWidget->setItem(0,1,new QTableWidgetItem(qrt1.value("FirstName").toString()));
            ui->tableWidget->setItem(0,2,new QTableWidgetItem(qrt1.value("LastName").toString()));
            ui->tableWidget->setItem(0,3,new QTableWidgetItem(qrt1.value("Contact").toString()));
            ui->tableWidget->setItem(0,4,new QTableWidgetItem(qrt1.value("PassportNo").toString()));
            ui->tableWidget->setItem(0,5,new QTableWidgetItem(qrt1.value("NationalID").toString()));
            ui->tableWidget->setItem(0,6,new QTableWidgetItem(qrt1.value("Address").toString()));
            ui->tableWidget->setItem(0,7,new QTableWidgetItem(qrt1.value("Gender").toString()));
            ui->tableWidget->setItem(0,8,new QTableWidgetItem(qrt1.value("DOB").toString()));
        }
        else
        {
            QMessageBox::information(NULL,NULL,"Customer didn't exist.");
        }
    }
    qrt1.clear();
    db.close();
}

void ViewCustomer::on_Delete_Customer_clicked()
{
    QString DelID = ui->En_CustID->text();
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1");
    db.setPort(3306);
    db.setUserName("root");
    db.setPassword("mysql");
    db.setDatabaseName("Airline_database");

    if(DelID == "")
    {
        return;
    }

    db.open();
    QSqlQuery qrt2;

    qrt2.prepare("DELETE FROM customer WHERE CustomerID = ?");
    qrt2.bindValue(0,DelID);

    if(qrt2.exec())
    {
        QMessageBox::information(NULL,NULL,"Delete sucessful.");
        AutoTable();
        ui->En_CustID->setText("");
    }
    else
    {
        qDebug() << "Error DELETE : " << qrt2.lastError().text();
    }

    qrt2.clear();
    db.close();
}

void ViewCustomer::on_tableWidget_cellClicked(int row, int column)
{
    Q_UNUSED(column);

    ui->tableWidget->setCurrentCell(row,0);
    ui->tableWidget->selectRow(row);
    selectID = ui->tableWidget->item(row,0)->text();
    ui->En_CustID->setText(selectID);
}

void ViewCustomer::on_Add_Customer_clicked()
{
    /*AddCostomer* addCust = new AddCostomer();
    addCust->setVisible(true);*/
    emit toaddCust();
}

void ViewCustomer::on_pushButton_clicked()
{
    emit backtoform();
}

