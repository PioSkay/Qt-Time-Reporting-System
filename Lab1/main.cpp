#include "mainwindow.h"
#include "Log.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    MEP::LOG_SETUP::Verbose::add("login.h", 1);

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
