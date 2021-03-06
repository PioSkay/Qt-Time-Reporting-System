#ifndef ADD_ACTIVITY_H
#define ADD_ACTIVITY_H

#include <QDialog>

#include "base.h"

namespace Ui {
class add_activity;
}

class add_activity : public QDialog
{
    Q_OBJECT
    Base* m_base;
    void init();
    std::shared_ptr<TOOLS::activities> m_created;
public:
    explicit add_activity(Base* base, QWidget *parent = nullptr);
    void create_button();
    void add_button();
    void errorMsg(const QString& in);
    std::shared_ptr<TOOLS::activities> getActivity();
    ~add_activity();
public slots:
    void removeItem(QWidget* in);
private:
    Ui::add_activity *ui;
};

#endif // ADD_ACTIVITY_H
