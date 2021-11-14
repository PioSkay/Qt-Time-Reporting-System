#ifndef YOUR_PROJECT_H
#define YOUR_PROJECT_H

#include <QWidget>

#include "activities.h"
#include "base.h"

namespace Ui {
class your_project;
}

class your_project : public QWidget
{
    Q_OBJECT
    std::shared_ptr<TOOLS::activities> m_activity;
    QString m_name;
    Base* m_base;
public:
    explicit your_project(std::shared_ptr<TOOLS::activities> activity, Base* base, QWidget *parent = nullptr);
    void update();
    ~your_project();

private slots:
    void on_reports_released();

private:
    Ui::your_project *ui;
};

#endif // YOUR_PROJECT_H
