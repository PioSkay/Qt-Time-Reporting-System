#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "file_pipeline.h"
#include "your_project.h"
#include "subactivities_container.h"

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
    else*/
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
    ui->projects->setFrameStyle(QFrame::Box);
    ui->projects->setLineWidth(2);
    ui->activities->setFrameStyle(QFrame::Box);
    ui->activities->setLineWidth(2);
    //ui->your_projects->setFrameShape(QFrame::StyledPanel);

    ui->user->setText("Welcome " + current_user.username());
    file x("11-2021-11.json");
    file y("11-2021-10.json", true);
    x.addEntries(entries(QDate::fromString("2021-11-09", "yyyy-MM-dd"), "ARGUS-123", "kappa", 180, "nothing").toJSONObject());

    auto& array = getActivities().getArray();
    QVBoxLayout* layout = new QVBoxLayout();
    ui->projects->widget()->setLayout(layout);
    for(auto& x: array)
    {
        if(x.get()->manager == getUser().username())
        {
            your_project* project = new your_project(x, this);
            ui->projects->widget()->layout()->addWidget(project);
        }
    }
}

void MainWindow::addActivityToMainScreen(std::shared_ptr<activities> in)
{
    Log(Info) << __FUNCTION__ << " " << __LINE__;
    your_project* element = new your_project(in, this);
    ui->projects->widget()->layout()->addWidget(element);
}

void MainWindow::add_project_Button()
{
    Log(Info) << __FUNCTION__ << " " << __LINE__;
    add_activity activity(this, this);
    activity.exec();
}

MainWindow::~MainWindow()
{
    delete ui;
}
