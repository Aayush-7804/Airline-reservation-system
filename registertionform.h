#ifndef REGISTERTIONFORM_H
#define REGISTERTIONFORM_H

#include <QWidget>
#include<QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <Qline>
#include <QRegularExpression>

namespace Ui {
class RegistertionForm;
}

class RegistertionForm : public QWidget
{
    Q_OBJECT

public:
    explicit RegistertionForm(QWidget *parent = nullptr);
    ~RegistertionForm();
    int AutoID();

signals:
    void backtoLogin();

private slots:
    void on_Sigup_clicked();

    void on_GoLogin_clicked();

    void on_toolButton_clicked();

private:
    Ui::RegistertionForm *ui;
    QSqlDatabase db;
    QString newValue;

    bool isUsernameValid(const QString &username);
    bool isPasswordValid(const QString &password);
    bool isUsernameUnique(const QString &username);
};

#endif // REGISTERTIONFORM_H
