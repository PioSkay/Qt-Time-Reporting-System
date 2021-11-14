#ifndef PROJECT_REPORTS_H
#define PROJECT_REPORTS_H

#include <QDialog>
#include "base.h"
#include "project_pending_request.h"

namespace Ui {
class project_reports;
}

class project_reports : public QDialog
{
    Q_OBJECT
    Base* m_base;
    std::shared_ptr<TOOLS::activities> m_activity;
    std::list<project_pending_request*> pending_data;
    int pending_time;
    int accepted_time;
    std::function<void()> notifyParent;
public:
    explicit project_reports(std::shared_ptr<TOOLS::activities> activity, Base* base, std::function<void()> fun, QWidget *parent = nullptr);
    void updateTime();
    ~project_reports();
public slots:
    void removeItem(QWidget* item);
private slots:
    void on_pushButton_2_released();
    void on_close_project_released();

private:
    Ui::project_reports *ui;
};

#endif // PROJECT_REPORTS_H
