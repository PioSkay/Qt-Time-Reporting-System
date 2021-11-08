#include "mainwindow.h"
#include "Log.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    //MEP::LOG_SETUP::Verbose::add("mainwindow.cpp", 10);
    MEP::LOG_SETUP::Verbose::add("project_reports.cpp", 10);
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
