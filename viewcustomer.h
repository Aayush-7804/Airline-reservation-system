#ifndef VIEWCUSTOMER_H
#define VIEWCUSTOMER_H

#include <QWidget>
#include<QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <Qline>

namespace Ui {
class ViewCustomer;
}

class ViewCustomer : public QWidget
{
    Q_OBJECT

public:
    explicit ViewCustomer(QWidget *parent = nullptr);
    ~ViewCustomer();

    void AutoTable();

signals:
    void toaddCust();

    void backtoform();

private slots:
    void on_Search_clicked();

    void on_Delete_Customer_clicked();

    void on_tableWidget_cellClicked(int row, int column);

    void on_Add_Customer_clicked();

    void on_pushButton_clicked();

private:
    Ui::ViewCustomer *ui;
    QSqlDatabase db;
    QString selectID;
};

#endif // VIEWCUSTOMER_H
