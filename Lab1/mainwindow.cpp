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
    current_year(0),
    current_month(0),
    submit_button(nullptr),
    ui(new Ui::MainWindow)
{
    Log(3) << __FUNCTION__ << ", " << __LINE__;
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
    Log(3) << __FUNCTION__ << ", " << __LINE__;
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
    submitButton(date.year(), date.month());
    updateTotalTime();
}

void MainWindow::addActivityToMainScreen(std::shared_ptr<TOOLS::activities> in)
{
    Log(3) << __FUNCTION__ << " " << __LINE__;
    your_project* element = new your_project(in, this);
    ui->projects->widget()->layout()->addWidget(element);
}

void MainWindow::add_project_Button()
{
    Log(3) << __FUNCTION__ << " " << __LINE__;
    add_activity activity(this, this);
    activity.exec();
}

void MainWindow::log_time_Button()
{
    Log(3) << __FUNCTION__ << " " << __LINE__;
    add_time time(this, this);
    time.exec();
}

QDate MainWindow::getTime() const
{
    Log(3) << __FUNCTION__ << ", " << __LINE__;
    return ui->calendarWidget->selectedDate();
}

MainWindow::~MainWindow()
{
    Log(3) << __FUNCTION__ << ", " << __LINE__;
    delete ui;
}

void MainWindow::on_calendarWidget_clicked(const QDate &date)
{
    Log(3) << date.toString().toStdString();
    update_temp(date.year(), date.month(), date.day());
}

void MainWindow::update_temp(int year, int month, int day)
{
    Log(3) << __FUNCTION__ << ", " << __LINE__;
    ui->day->setText(QString::number(year) + "/" + QString::number(month) + "/" + QString::number(day));
    clearLayout(ui->activities->widget()->layout());
    auto* array = getFiles().get();
    if(array)
    {
        getFiles().get()->foreachEntries([this, day, month](auto ele, auto fi){
            if(ele.get()->date.day() == day && ele.get()->date.month() == month)
            {
                Log(Info) << day;
                your_tempo* widget = new your_tempo(this, ele, fi, fi->isSubmited());
                ui->activities->widget()->layout()->addWidget(widget);
            }
        });
    }
}

void MainWindow::updateTotalTime()
{
    int totalTime = 0;
    getFiles().get()->foreachAccepted([&totalTime](auto in, auto fi){
       totalTime += in.get()->time;
    });
    getFiles().get()->foreachEntries([&totalTime](auto in, auto fi){
       totalTime += in.get()->time;
    });
    ui->totaltime->setText("Total work time: " + QString::number(totalTime) + " min");
}

void MainWindow::update_temp()
{
    update_temp(ui->calendarWidget->selectedDate().year(),
                ui->calendarWidget->selectedDate().month(),
                ui->calendarWidget->selectedDate().day());
}

void MainWindow::clearLayout(QLayout* layout, bool deleteWidgets)
{
    Log(3) << __FUNCTION__ << ", " << __LINE__;
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

void MainWindow::submitButton(int year, int month)
{
    Log(3) << __FUNCTION__ << ", " << __LINE__ << ", year: " << year << ", month:" << month;
    current_year = year;
    current_month = month;
    if(submit_button == nullptr)
    {
        std::shared_ptr<file> m_file = getFiles()->find(getUser().username(), year, month);
        if(m_file.get() != nullptr)
        {
            if(!m_file.get()->isSubmited())
            {
                submit_button = new QPushButton;
                submit_button->setText("Submit");
                ui->frame->layout()->addWidget(submit_button);
                connect(submit_button, &QPushButton::released, this, &MainWindow::submit_button_released);
            }
        }
        else
        {
            submit_button = new QPushButton;
            submit_button->setText("Submit");
            ui->frame->layout()->addWidget(submit_button);
            connect(submit_button, &QPushButton::released, this, &MainWindow::submit_button_released);
        }
    }
    else
    {
        std::shared_ptr<file> m_file = getFiles()->find(getUser().username(), year, month);
        if(m_file.get() != nullptr)
        {
            if(m_file.get()->isSubmited())
            {
                ui->frame->layout()->removeWidget(submit_button);
                delete submit_button;
                submit_button = nullptr;
            }
        }
    }
}

void MainWindow::submit_button_released()
{
    Log(3) << __FUNCTION__ << ", " << __LINE__;
    std::shared_ptr<file> m_file = getFiles()->add_or_find(getUser().username(), current_year, current_month);
    if(m_file.get())
    {
        m_file.get()->submitFile();
        submitButton(current_year, current_month);
        update_temp();
    }
    else
    {
        Log(Error) << "Could not create a file!";
    }
}

void MainWindow::on_calendarWidget_currentPageChanged(int year, int month)
{
    Log(3) << __FUNCTION__ << ", " << __LINE__ << ", year: " << year << ", month:" << month;
    submitButton(year, month);
}


