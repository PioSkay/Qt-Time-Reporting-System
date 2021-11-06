#ifndef PROJECT_REPORTS_H
#define PROJECT_REPORTS_H

#include <QDialog>
#include "base.h"

namespace Ui {
class project_reports;
}

class project_reports : public QDialog
{
    Q_OBJECT
    Base* m_base;
    std::shared_ptr<TOOLS::activities> m_activity;
    int pending_time;
    int accepted_time;
public:
    explicit project_reports(std::shared_ptr<TOOLS::activities> activity, Base* base, QWidget *parent = nullptr);
    void updateTime();
    ~project_reports();
public slots:
    void removeItem(QWidget* item);
private slots:
    void on_pushButton_2_released();

private:
    Ui::project_reports *ui;
};

#endif // PROJECT_REPORTS_H
