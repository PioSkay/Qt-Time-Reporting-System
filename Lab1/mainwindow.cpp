#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "file_pipeline.h"

#include <QTimer>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    /*
    login_window.exec();
    if(!login_window.isLoggedIn())
    {
        //Passing the close event because the user is not auth.
        QTimer::singleShot(0, this, SLOT(close()));
    }
    else
    */
    {
        current_user = User("11");// login_window.loggedUser();
        initJSON(login_window.getUsers().getUsers());
        init();
        debug();
    }
}

void MainWindow::init()
{
    connect(ui->new_project, &QPushButton::released, this, &MainWindow::add_project_Button);
    //Setting style
    ui->your_projects->setFrameStyle(QFrame::Box);
    ui->your_projects->setLineWidth(2);
    ui->activities->setFrameStyle(QFrame::Box);
    ui->activities->setLineWidth(2);
    //ui->your_projects->setFrameShape(QFrame::StyledPanel);

    Log(Info) << "init()";
    ui->user->setText("Welcome " + current_user.username());
    file x("11-2021-11.json");
    file y("11-2021-10.json", true);
    x.addEntries(entries(QDate::fromString("2021-11-09", "yyyy-MM-dd"), "ARGUS-123", "kappa", 180, "nothing").toJSONObject());
    //current_user.setup_activities(this);
}

void MainWindow::add_project_Button()
{
    Log(Info) << __FUNCTION__ << " " << __LINE__;
    add_activity activity(this);
    activity.exec();
}

MainWindow::~MainWindow()
{
    delete ui;
}
