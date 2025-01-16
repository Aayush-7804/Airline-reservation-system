#include "registertionform.h"
#include "ui_registertionform.h"
#include "loginform.h"

RegistertionForm::RegistertionForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RegistertionForm)
{
    ui->setupUi(this);
    AutoID();
    ui->PasswordEnter->setEchoMode(QLineEdit::Password);
    ui->PasswordReEnter->setEchoMode(QLineEdit::Password);
}

RegistertionForm::AutoID()
{

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

    QSqlQuery qrt;
    qrt.prepare("SELECT AdminID FROM admin ORDER BY AdminID DESC LIMIT 1");

    if(!qrt.exec())
    {
        qDebug() << "Failed to execute : " << qrt.lastError().text();
    }


    if (qrt.next())
    {
        QString lastValue = qrt.value(0).toString();
        int lastNumber = lastValue.mid(2).toInt();
        newValue = QString("AD%1").arg(lastNumber + 1, 3, 10, QChar('0'));
    }
    else
    {
        newValue = "AD001";
    }

    qrt.clear();
    db.close();
    if(!db.isOpen())
    {
        qDebug() << "Database is closed.";
    }
    return 0;

}

RegistertionForm::~RegistertionForm()
{
    delete ui;
}

bool RegistertionForm::isUsernameValid(const QString &username)
{
    QRegularExpression regex("^(?=[A-Za-z][A-Za-z0-9_.-@#]{6,10}[0-9]$){8,12}");
    QRegularExpressionMatch match = regex.match(username);
    return match.hasMatch();
}

bool RegistertionForm::isPasswordValid(const QString &password)
{
    QRegularExpression regex("^(?=.*[a-z])(?=.*[A-Z])(?=.*\\d)(?=.*[@$!%*?&])[A-Za-z\\d@$!%*?&]{8,20}$");
    QRegularExpressionMatch match = regex.match(password);
    return match.hasMatch();
}

bool RegistertionForm::isUsernameUnique(const QString &username)
{
    QSqlQuery query(db);
    query.prepare("SELECT COUNT(*) FROM admin WHERE Username = :username");
    query.bindValue(":username", username);

    if (!query.exec())
    {
        qDebug() << "Error executing query:" << query.lastError().text();
        return false;
    }

    query.next();
    int count = query.value(0).toInt();
    return count == 0;
}

void RegistertionForm::on_Sigup_clicked()
{
    QString Username = ui->UsernameEnter->text();
    QString Password = ui->PasswordEnter->text();
    QString PassRe = ui->PasswordReEnter->text();

    if (!isUsernameValid(Username))
    {
        QMessageBox::warning(NULL, "Registration Error", "Username must be 8-12 characters long; give validable Username.");
        return;
    }

    if (!isPasswordValid(Password))
    {
        QMessageBox::warning(NULL, "Registration Error", "Password must be 8-20 characters long and include at least one uppercase letter, one lowercase letter, one number, and one special character.");
        return;
    }

    if (Password != PassRe)
    {
        ui->WrongPass->setText("Passwords do not match.");
        return;
    }

    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1");
    db.setPort(3306);
    db.setUserName("root");
    db.setPassword("mysql");
    db.setDatabaseName("Airline_database");

    if (db.open())
    {
        qDebug() << "Database connected.";
    }
    else
    {
        qDebug() << "Database not connected.";
        return;
    }

    if (!isUsernameUnique(Username))
    {
        QMessageBox::information(NULL, "Registration Error", "Username is already in use. Please choose a different one.");
        db.close();
        return;
    }

    QSqlQuery qrt(db);
    qrt.prepare("INSERT INTO admin(AdminID, FirstName, LastName, Username, Password) values(?, ?, ?, ?, ?)");
    qrt.bindValue(0, newValue);
    qrt.bindValue(1, "");
    qrt.bindValue(2, "");
    qrt.bindValue(3, Username);
    qrt.bindValue(4, Password);

    if (qrt.exec())
    {
        QMessageBox::information(NULL, "Registration Successful", "You have been successfully registered.");
        emit backtoLogin();
    }
    else
    {
        qDebug() << "Error : " << qrt.lastError().text();
        QMessageBox::information(NULL, "Registration Error", "An error occurred during registration. Please try again.");
    }

    qrt.clear();
    db.close();
}


void RegistertionForm::on_GoLogin_clicked()
{
    emit backtoLogin();
}


void RegistertionForm::on_toolButton_clicked()
{
    if(ui->PasswordEnter->echoMode() == (QLineEdit::Password))
    {
        ui->PasswordEnter->setEchoMode(QLineEdit::Normal);
        ui->PasswordReEnter->setEchoMode(QLineEdit::Normal);
        ui->toolButton->setIcon(QIcon(":/ing/pngwing.com-1.png"));
    }
    else
    {
        ui->PasswordEnter->setEchoMode(QLineEdit::Password);
        ui->PasswordReEnter->setEchoMode(QLineEdit::Password);
        ui->toolButton->setIcon(QIcon(":/ing/pngwing.com.png"));
    }
}

