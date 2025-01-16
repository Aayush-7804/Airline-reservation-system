#ifndef ADDFLIGHT_H
#define ADDFLIGHT_H

#include <QWidget>
#include<QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <Qline>
#include <QTimer>
#include <QTime>
#include <QDate>

namespace Ui {
class AddFlight;
}

class AddFlight : public QWidget
{
    Q_OBJECT

public:
    explicit AddFlight(QWidget *parent = nullptr);
    ~AddFlight();
    int AutoID();

signals:
    void backtoform();

    void Relode();

private slots:

    void on_Cancel_clicked();

    void on_FA_Add_clicked();

    void on_FA_DateOfFlight_editingFinished();

    void on_calendarWidget_clicked(const QDate &date);

private:
    Ui::AddFlight *ui;
    QSqlDatabase db;

    QTimer *timer;
};

#endif // ADDFLIGHT_H
