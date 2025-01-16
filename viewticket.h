#ifndef VIEWTICKET_H
#define VIEWTICKET_H

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
class ViewTicket;
}

class ViewTicket : public QWidget
{
    Q_OBJECT

public:
    explicit ViewTicket(QWidget *parent = nullptr);
    ~ViewTicket();

signals:
    void backtoform();

    void Relode();

private slots:
    void on_Cancel_clicked();

    void on_VT_GetTicket_clicked();

private:
    Ui::ViewTicket *ui;
    QSqlDatabase db;
};

#endif // VIEWTICKET_H
