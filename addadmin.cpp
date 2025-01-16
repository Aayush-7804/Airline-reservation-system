#include "addadmin.h"
#include "ui_addadmin.h"
#include<QMessageBox>

AddAdmin::AddAdmin(QWidget *parent, const QString &username, const QString &password) :
    QWidget(parent),
    ui(new Ui::AddAdmin)
{
    ui->setupUi(this);
    receiveCredentials(username, password);
    this->setStyleSheet("background-image: url(:/ing/flight-hero-1.jpg);");

    connect(ui->Cencel, &QPushButton::clicked, this, &AddAdmin::on_Cencel_clicked);
}

void AddAdmin::receiveCredentials(const QString &username, const QString &password)
{
    storedUsername = username;
    storedPassword = password;

    qDebug() << "StoredUsername :" << storedUsername;
    AutoID();
}

AddAdmin::AutoID()
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

    qrt.prepare("SELECT * FROM admin WHERE Username = ? AND Password = ?");
    qrt.bindValue(0,storedUsername);
    qrt.bindValue(1,storedPassword);

    if(qrt.exec())
    {
        if(qrt.next())
        {
            ui->AI_AdminID->setText(qrt.value("AdminID").toString());
            ui->AI_FirstName->setText(qrt.value("FirstName").toString());
            ui->AI_LastName->setText(qrt.value("lastName").toString());
            ui->AI_Username->setText(qrt.value("Username").toString());
            ui->AI_Password->setText(qrt.value("Password").toString());
            ui->AI_Password->setEchoMode(QLineEdit::Password);
        }
    }
    else
    {
        qDebug() << "Error : " << qrt.lastError().text();
    }
    return 0;

}

AddAdmin::~AddAdmin()
{
    delete ui;
}

bool AddAdmin::isUsernameValid(const QString &username)
{
    QRegularExpression regex("^(?=[A-Za-z][A-Za-z0-9_.-@#]{6,10}[0-9]$){8,12}");
    QRegularExpressionMatch match = regex.match(username);
    return match.hasMatch();
}

bool AddAdmin::isPasswordValid(const QString &password)
{
    QRegularExpression regex("^(?=.*[a-z])(?=.*[A-Z])(?=.*\\d)(?=.*[@$!%*?&])[A-Za-z\\d@$!%*?&]{8,20}$");
    QRegularExpressionMatch match = regex.match(password);
    return match.hasMatch();
}

void AddAdmin::on_Cencel_clicked()
{
    emit backtoform();
}

void AddAdmin::on_AI_Update_clicked()
{
    QString AdminID = ui->AI_AdminID->text();
    QString FirstN = ui->AI_FirstName->text();
    QString LastN = ui->AI_LastName->text();
    QString Username = ui->AI_Username->text();
    QString Password = ui->AI_Password->text();

    if (!isUsernameValid(Username))
    {
        QMessageBox::warning(NULL, "Registration Error", "Username must be 6-20 characters long and can only contain letters, numbers, periods, underscores, or hyphens.");
        return;
    }

    if (!isPasswordValid(Password))
    {
        QMessageBox::warning(NULL, "Registration Error", "Password must be 8-20 characters long and include at least one uppercase letter, one lowercase letter, one number, and one special character.");
        return;
    }

    db.open();

    QSqlQuery qrt1;

    qrt1.prepare("SELECT FirstName,Lastname FROM admin WHERE AdminID = ?");
    qrt1.bindValue(0,AdminID);

    qrt1.exec();
    qrt1.next();
    QString FName = qrt1.value("FirstName").toString();
    QString LName = qrt1.value("LastName").toString();

    if(FName == FirstN && LName == LastN)
    {
        qrt1.clear();
        return;
    }
    qrt1.prepare("UPDATE admin SET FirstName = ?, LastName = ?, Username = ?, Password = ? WHERE AdminID = ?");
    if(FirstN != "" && LastN != "" && Username != "" && Password != "")
    {
        qrt1.bindValue(0,FirstN);
        qrt1.bindValue(1,LastN);
        qrt1.bindValue(2,Username);
        qrt1.bindValue(3,Password);
        qrt1.bindValue(4,AdminID);

        if(qrt1.exec())
        {
            QMessageBox::information(NULL,NULL,"Updated Sucessfuly.");
        }
        else
        {
            qDebug() << "Error : " << qrt1.lastError().text();
        }
    }
    else
    {
        QMessageBox::information(NULL,NULL,"Fill the Respective information.");
    }
    qrt1.clear();
    db.close();
}


void AddAdmin::on_toolButton_clicked()
{
    if(ui->AI_Password->echoMode() == (QLineEdit::Password))
    {
        ui->AI_Password->setEchoMode(QLineEdit::Normal);
        ui->toolButton->setIcon(QIcon(":/ing/pngwing.com-1.png"));
    }
    else
    {
        ui->AI_Password->setEchoMode(QLineEdit::Password);
        ui->toolButton->setIcon(QIcon(":/ing/pngwing.com.png"));
    }
}

