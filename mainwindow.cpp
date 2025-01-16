#include "mainwindow.h"
#include "ui_mainwindow.h"


#include "addcostomer.h"

MainWindow::MainWindow(QWidget *parent,const QString &username, const QString &password) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    storedUsername(username),
    storedPassword(password)
{
    ui->setupUi(this);
    this->showMaximized();
    setWindowTitle("Flight Resevation");

    Form* form = new Form();
    form->receiveCredentials(storedUsername);
    setCentralWidget(form);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionAdd_Coustomer_triggered()
{
    ViewCustomer *viewCust = new ViewCustomer();
    setCentralWidget(viewCust);
    connect(viewCust, &ViewCustomer::toaddCust, this, &MainWindow::addCustPage);
    connect(viewCust, &ViewCustomer::backtoform, this, &MainWindow::backtoform);
}

void MainWindow::addCustPage()
{
    AddCostomer *addCust = new AddCostomer();
    setCentralWidget(addCust);
    connect(addCust, &AddCostomer::Relode, this, &MainWindow::addCustPage);
    connect(addCust, &AddCostomer::backtoviewCust, this, &MainWindow::on_actionAdd_Coustomer_triggered);
}

void MainWindow::on_actionAdd_Flight_triggered()
{
    AddFlight *addFlg = new AddFlight();
    setCentralWidget(addFlg);
    connect(addFlg, &AddFlight::Relode, this, &MainWindow::on_actionAdd_Flight_triggered);
    connect(addFlg, &AddFlight::backtoform, this, &MainWindow::backtoform);
}

void MainWindow::on_actionBook_Flight_triggered()
{
    BookFlight *bookFlg = new BookFlight();
    setCentralWidget(bookFlg);
    connect(bookFlg, &BookFlight::Relode, this, &MainWindow::on_actionBook_Flight_triggered);
    connect(bookFlg, &BookFlight::backtoform, this, &MainWindow::backtoform);
}

void MainWindow::on_actionView_Ticket_triggered()
{
    ViewTicket *viwTic = new ViewTicket();
    setCentralWidget(viwTic);
    connect(viwTic, &ViewTicket::Relode, this, &MainWindow::on_actionView_Ticket_triggered);
    connect(viwTic, &ViewTicket::backtoform, this, &MainWindow::backtoform);
}

void MainWindow::on_actionAdd_Admin_triggered()
{
    AddAdmin *addAdm = new AddAdmin();
    addAdm->receiveCredentials(storedUsername, storedPassword);
    setCentralWidget(addAdm);
    connect(addAdm, &AddAdmin::backtoform, this, &MainWindow::backtoform);
}

void MainWindow::backtoform()
{
    Form* form = new Form();
    form->receiveCredentials(storedUsername);
    setCentralWidget(form);
}
