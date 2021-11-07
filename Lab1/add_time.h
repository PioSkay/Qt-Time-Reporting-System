#ifndef ADD_TIME_H
#define ADD_TIME_H

#include <QDialog>

#include"entries.h"
#include"base.h"

namespace Ui {
class add_time;
}

class add_time : public QDialog
{
    Q_OBJECT
    Base* m_base;
    std::shared_ptr<TOOLS::activities> current;
    std::shared_ptr<TOOLS::entries> m_entr;
    std::shared_ptr<file> m_file;
public:
    explicit add_time(Base* base, QWidget *parent = nullptr, std::shared_ptr<TOOLS::entries> entr = nullptr, std::shared_ptr<file> file = nullptr);
    void setSubactivity(const QString& project, const QString& subactivity = "");
    ~add_time();

private slots:
    void on_project_currentIndexChanged(const QString &arg1);
    void on_log_released();

private:
    Ui::add_time *ui;
};

#endif // ADD_TIME_H
