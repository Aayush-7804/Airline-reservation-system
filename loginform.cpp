#include "loginform.h"
#include "ui_loginform.h"
#include "mainwindow.h"
#include "registertionform.h"

LoginForm::LoginForm(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LoginForm)
{
    ui->setupUi(this);
    ui->Password->setEchoMode(QLineEdit::Password);
}

LoginForm::~LoginForm()
{
    delete ui;
}


void LoginForm::on_Login_clicked()
{
    UserName = ui->Username->text();
    PassWord = ui->Password->text();

    if(UserName == "" && PassWord == "")
    {
        QMessageBox::information(NULL,NULL,"Enter Username and Password.");
    }
    else{
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
        qrt.prepare("SELECT * FROM admin WHERE username = ? AND Password = ?");
        qrt.bindValue(0,UserName);
        qrt.bindValue(1,PassWord);

        if(qrt.exec())
        {
            if(qrt.next())
            {
                qrt.clear();
                db.close();
                if(!db.isOpen())
                {
                    qDebug() << "Database Disconnect";
                }
                this->setVisible(false);
                MainWindow *mainWindow = new MainWindow(nullptr, UserName, PassWord);
                mainWindow->setVisible(true); 
            }
            else
            {
                QMessageBox::information(NULL,NULL,"User didn't identify(Entered Username or password are incorrect)");
            }
        }
        else
        {
            qDebug() <<"Error";
        }
    }

}


void LoginForm::on_Register_clicked()
{
    RegistertionForm *registertion = new RegistertionForm();
    setCentralWidget(registertion);
    connect(registertion, &RegistertionForm::backtoLogin, this, &LoginForm::showLog);
}

void LoginForm::showLog()
{
    ui->setupUi(this);
    ui->Password->setEchoMode(QLineEdit::Password);
}
