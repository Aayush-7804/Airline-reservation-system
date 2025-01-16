#ifndef ADDADMIN_H
#define ADDADMIN_H

#include <QWidget>
#include <QSqlDatabase>
#include<QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include <Qline>
#include <QRegularExpression>

namespace Ui {
class AddAdmin;
}

class AddAdmin : public QWidget
{
    Q_OBJECT

public:
    explicit AddAdmin(QWidget *parent = nullptr, const QString &username = "", const QString &password = "");
    ~AddAdmin();
    int AutoID();

signals:
    void backtoform();

public slots:
    void receiveCredentials(const QString &username, const QString &password);

private slots:
    void on_Cencel_clicked();

    void on_AI_Update_clicked();


    void on_toolButton_clicked();

private:
    Ui::AddAdmin *ui;
    QSqlDatabase db;
    QString storedUsername;
    QString storedPassword;

    bool isUsernameValid(const QString &username);
    bool isPasswordValid(const QString &password);
    //bool isUsernameUnique(const QString &username);
};

#endif // ADDADMIN_H
