#ifndef SUBACTIVITIES_CONTAINER_H
#define SUBACTIVITIES_CONTAINER_H

#include <QWidget>

namespace Ui {
class subactivities_container;
}

class subactivities_container : public QWidget
{
    Q_OBJECT
    const int m_ID;
    QString m_master;
    QString m_second;
public:
    explicit subactivities_container(const int ID, const QString& master, const QString& second, QWidget *parent = nullptr);
    int getID() const
    {
        return m_ID;
    }
    bool operator==(const subactivities_container& in)
    {
        return m_master == in.m_master && m_second == in.m_second;
    }
    void on_toolButton_clicked();
    ~subactivities_container();
signals:
    void sendRemoveItem(int ID);
private:
    Ui::subactivities_container *ui;
};

#endif // SUBACTIVITIES_CONTAINER_H
