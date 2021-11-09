#include <QDir>
#include "mainwindow.h"
#include "Log.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    /*
    MEP::LOG_SETUP::Verbose::add("mainwindow.cpp", 10);
    MEP::LOG_SETUP::Verbose::add("add_activity.cpp", 10);
    MEP::LOG_SETUP::Verbose::add("add_time.cpp", 10);
    MEP::LOG_SETUP::Verbose::add("adjust_window.cpp", 10);
    MEP::LOG_SETUP::Verbose::add("login.cpp", 10);
    MEP::LOG_SETUP::Verbose::add("request_data.cpp", 10);
    MEP::LOG_SETUP::Verbose::add("project_pending_request.cpp", 10);
    MEP::LOG_SETUP::Verbose::add("request_report.cpp", 10);
    MEP::LOG_SETUP::Verbose::add("subactivities_container.cpp", 10);
    MEP::LOG_SETUP::Verbose::add("view_tempo.cpp", 10);
    MEP::LOG_SETUP::Verbose::add("your_tempo.cpp", 10);
    MEP::LOG_SETUP::Verbose::add("project_reports.cpp", 10);
    MEP::LOG_SETUP::Verbose::add("project_reports.cpp", 10);
    MEP::LOG_SETUP::Verbose::add("add_time.cpp", 10);
    */
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
