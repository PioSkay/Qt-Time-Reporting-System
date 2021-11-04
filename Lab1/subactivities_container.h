#ifndef SUBACTIVITIES_CONTAINER_H
#define SUBACTIVITIES_CONTAINER_H

#include <QWidget>

namespace Ui {
class subactivities_container;
}

class subactivities_container : public QWidget
{
    Q_OBJECT
    QString m_master;
    QString m_second;
public:
    explicit subactivities_container(const QString& master, const QString& second, QWidget *parent = nullptr);
    const QString& getMaster() const;
    const QString& getSecond() const;
    bool operator==(const subactivities_container& in) const;
    void on_toolButton_clicked();
    ~subactivities_container();
signals:
    void sendRemoveItem(QWidget* in);
private:
    Ui::subactivities_container *ui;
};

#endif // SUBACTIVITIES_CONTAINER_H
