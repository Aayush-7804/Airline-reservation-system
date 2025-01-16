#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>

#include "viewcustomer.h"
#include "addflight.h"
#include "ui_addflight.h"
#include "bookflight.h"
#include "ui_bookflight.h"
#include "viewticket.h"
#include "ui_viewticket.h"
#include "addadmin.h"
#include "ui_addadmin.h"
#include "form.h"
#include "ui_form.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr, const QString &username = "", const QString &password = "");
    ~MainWindow();

private slots:
    void on_actionAdd_Coustomer_triggered();

    void on_actionAdd_Flight_triggered();

    void on_actionBook_Flight_triggered();

    void on_actionView_Ticket_triggered();

    void on_actionAdd_Admin_triggered();

    void addCustPage();

    void backtoform();

private:
    Ui::MainWindow *ui;
    QString storedUsername;
    QString storedPassword;
    /*QWidget *mainWidget;
    QStackedWidget *stackedWidget;
    QWidget *addCostomerWidget;*/
};

#endif // MAINWINDOW_H
