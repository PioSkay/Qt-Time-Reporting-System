#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "login.h"
#include "base.h"
#include "add_activity.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow, public Base
{
    Q_OBJECT
    Login login_window;
public:
    explicit MainWindow(QWidget *parent = 0);
    void add_project_Button();
    void addActivityToMainScreen(std::shared_ptr<activities> in) override;
    ~MainWindow();
private:
    Ui::MainWindow *ui;
    void init();
};

#endif // MAINWINDOW_H
