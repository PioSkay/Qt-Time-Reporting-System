#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "login.h"
#include "login.h"
#include "login.h"
#include "login.h"
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
    void log_time_Button();
    void addActivityToMainScreen(std::shared_ptr<activities> in) override;
    void update_temp(int year, int month, int day) override;
    void update_temp() override;
    void clearLayout(QLayout* layout, bool deleteWidgets = true);
    QDate getTime() const override;
    ~MainWindow();
private slots:
    void on_calendarWidget_clicked(const QDate &date);
    void on_calendarWidget_currentPageChanged(int year, int month);

private:
    Ui::MainWindow *ui;
    void init();
};

#endif // MAINWINDOW_H
