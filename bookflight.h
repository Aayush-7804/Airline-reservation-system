#ifndef BOOKFLIGHT_H
#define BOOKFLIGHT_H

#include <QWidget>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlError>
#include <Qline>

namespace Ui {
class BookFlight;
}

class BookFlight : public QWidget
{
    Q_OBJECT

public:
    explicit BookFlight(QWidget *parent = nullptr);
    ~BookFlight();
    int AutoID();

signals:
    void backtoform();

    void Relode();

private slots:
    void on_comboBox_activated(const QString &arg1);

    void on_Cancel_clicked();

    void on_BF_Search_clicked();

    void on_BF_Search_2_clicked();

    void on_tableWidget_clicked(const QModelIndex &index);

    void on_tableWidget_cellClicked(int row, int column);

    void on_BF_Calcu_clicked();

    void on_BF_Book_clicked();

private:
    Ui::BookFlight *ui;
    QSqlDatabase db;
    QString FlightID;
    QString FLightName;
    QString Date;
    QString Time;
    QString Class;
};

#endif // BOOKFLIGHT_H
