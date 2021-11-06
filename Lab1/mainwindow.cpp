#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "file_pipeline.h"
#include "your_project.h"
#include "subactivities_container.h"
#include "add_time.h"
#include "your_tempo.h"

#include <QTimer>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    /*login_window.exec();
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
        //debug();
    }
}

void MainWindow::init()
{
    connect(ui->new_project, &QPushButton::released, this, &MainWindow::add_project_Button);
    connect(ui->log_time, &QPushButton::released, this, &MainWindow::log_time_Button);

    ui->projects->setFrameStyle(QFrame::Box);
    ui->projects->setLineWidth(2);
    ui->activities->setFrameStyle(QFrame::Box);
    ui->activities->setLineWidth(2);
    ui->user->setText("Welcome " + current_user.username());

    auto& array = getActivities().getArray();
    QVBoxLayout* layout = new QVBoxLayout();
    ui->projects->widget()->setLayout(layout);
    QVBoxLayout* layout2 = new QVBoxLayout();
    ui->activities->widget()->setLayout(layout2);
    for(auto& x: array)
    {
        if(x.get()->manager == getUser().username())
        {
            your_project* project = new your_project(x, this);
            ui->projects->widget()->layout()->addWidget(project);
        }
    }
    QDate date = ui->calendarWidget->selectedDate();
    update_temp(date.year(), date.month(), date.day());
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

void MainWindow::log_time_Button()
{
    Log(Info) << __FUNCTION__ << " " << __LINE__;
    add_time time(this, this);
    time.exec();
}

QDate MainWindow::getTime() const
{
    return ui->calendarWidget->selectedDate();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_calendarWidget_clicked(const QDate &date)
{
    Log(Info) << date.toString().toStdString();
    update_temp(date.year(), date.month(), date.day());
}

void MainWindow::update_temp(int year, int month, int day)
{
    ui->day->setText(QString::number(year) + "/" + QString::number(month) + "/" + QString::number(day));
    clearLayout(ui->activities->widget()->layout());
    auto* array = getFiles().get();
    if(array)
    {
        file* fi = array->find(getUser().username(), year, month).get();
        if(fi != nullptr)
        {
            std::list<std::shared_ptr<entries>> entr = fi->getEntries();
            for(auto& ele : entr)
            {
                if(ele.get()->date.day() == day)
                {
                    Log(Info) << day;
                    your_tempo* widget = new your_tempo(ele.get()->date, ele, fi->isFileFrozen());
                    ui->activities->widget()->layout()->addWidget(widget);
                }
            }
        }
    }
}

void MainWindow::update_temp()
{
    update_temp(ui->calendarWidget->selectedDate().year(),
                ui->calendarWidget->selectedDate().month(),
                ui->calendarWidget->selectedDate().day());
}

void MainWindow::clearLayout(QLayout* layout, bool deleteWidgets)
{
    while (QLayoutItem* item = layout->takeAt(0))
    {
        if (deleteWidgets)
        {
            if (QWidget* widget = item->widget())
                widget->deleteLater();
        }
        if (QLayout* childLayout = item->layout())
            clearLayout(childLayout, deleteWidgets);
        delete item;
    }
}

void MainWindow::on_calendarWidget_currentPageChanged(int year, int month)
{
    Log(Info) << year << " " << month;
}


