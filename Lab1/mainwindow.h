#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "login.h"
#include "base.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow, public Base
{
    Q_OBJECT
    Login login_window;
    User current_user;
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    void init();
};

#endif // MAINWINDOW_H
