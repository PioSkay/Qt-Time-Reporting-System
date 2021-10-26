#include "mainwindow.h"
#include "Log.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    MEP::LOG_SETUP::Verbose::add("login.h", 1);
    MEP::LOG_SETUP::Verbose::add("login.cpp", 10);
    MEP::LOG_SETUP::Verbose::add("jsonreader.h", 10);
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
