#ifndef ADDCOSTOMER_H
#define ADDCOSTOMER_H

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <Qline>

namespace Ui {
class AddCostomer;
}

class AddCostomer : public QWidget
{
    Q_OBJECT

public:
    explicit AddCostomer(QWidget *parent = nullptr);
    ~AddCostomer();
    int AutoID();

signals:
    void backtoviewCust();
    void Relode();

private slots:
    void on_Cancel_clicked();
    void on_AC_Add_clicked();

private:
    Ui::AddCostomer *ui;
    QSqlDatabase db;
};

#endif // ADDCOSTOMER_H
