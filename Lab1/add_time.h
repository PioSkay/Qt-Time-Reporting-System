#ifndef ADD_TIME_H
#define ADD_TIME_H

#include <QDialog>

#include"base.h"

namespace Ui {
class add_time;
}

class add_time : public QDialog
{
    Q_OBJECT
    Base* m_base;
    std::shared_ptr<activities> current;
public:
    explicit add_time(Base* base, QWidget *parent = nullptr);
    void setSubactivity(const QString& project);
    void setSubactivity2(const QString& project);
    ~add_time();

private slots:
    void on_project_currentIndexChanged(const QString &arg1);
    void on_log_released();

private:
    Ui::add_time *ui;
};

#endif // ADD_TIME_H
