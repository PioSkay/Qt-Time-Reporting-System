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
    static int ID;
public:
    explicit add_activity(Base* base, QWidget *parent = nullptr);
    void create_button();
    void add_button();
    ~add_activity();
public slots:
    void removeItem(int ID);
private:
    Ui::add_activity *ui;
};

#endif // ADD_ACTIVITY_H
