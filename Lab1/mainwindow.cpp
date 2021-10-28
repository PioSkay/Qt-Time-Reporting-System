#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTimer>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    login_window.exec();
    if(!login_window.isLoggedIn())
    {
        //Passing the close event because the user is not auth.
        QTimer::singleShot(0, this, SLOT(close()));
    }
    else
    {
        current_user = login_window.loggedUser();
        init();
    }
}

void MainWindow::init()
{
    Log(Info) << "init()";
    ui->user->setText("Welcome " + current_user.username());
    JSONReader A("a.json", "a");
    JSONReader B("b.json", "b");
    TOOLS::SaveJSON::save(A, B);
}


MainWindow::~MainWindow()
{
    delete ui;
}
