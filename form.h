#ifndef FORM_H
#define FORM_H

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlError>

namespace Ui {
class Form;
}

class Form : public QWidget
{
    Q_OBJECT

public:
    explicit Form(QWidget *parent = nullptr,  const QString &username = "");
    ~Form();
    void AutoTable();

public slots:
    void receiveCredentials(const QString &username);

private slots:
    void on_calendarWidget_clicked(const QDate &date);

    void on_tableWidget_cellClicked(int row, int column);

private:
    Ui::Form *ui;
    QSqlDatabase db;
    QString storedUsername;
};

#endif // FORM_H
