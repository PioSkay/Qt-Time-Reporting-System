#ifndef YOUR_PROJECT_H
#define YOUR_PROJECT_H

#include <QWidget>

#include "activities.h"

namespace Ui {
class your_project;
}

class your_project : public QWidget
{
    Q_OBJECT
    std::shared_ptr<activities> m_activity;
    QString m_name;
public:
    explicit your_project(std::shared_ptr<activities> activity, const QString& name, QWidget *parent = nullptr);
    ~your_project();

private:
    Ui::your_project *ui;
};

#endif // YOUR_PROJECT_H
