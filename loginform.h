#ifndef LOGINFORM_H
#define LOGINFORM_H

#include <QMainWindow>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlError>
#include <Qline>

QT_BEGIN_NAMESPACE
namespace Ui { class LoginForm; }
QT_END_NAMESPACE

class LoginForm : public QMainWindow
{
    Q_OBJECT

public:
    LoginForm(QWidget *parent = nullptr);
    ~LoginForm();

signals:
    void sendCredentials(const QString &username, const QString &password);

private slots:
    void on_Login_clicked();

    void on_Register_clicked();

    void showLog();

private:
    Ui::LoginForm *ui;
    QSqlDatabase db;
    QString UserName;
    QString PassWord;
};
#endif // LOGINFORM_H
