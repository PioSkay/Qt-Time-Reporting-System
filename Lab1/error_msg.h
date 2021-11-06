#ifndef ERROR_MSG_H
#define ERROR_MSG_H

#include <QDialog>

namespace Ui {
class error_msg;
}

class error_msg : public QDialog
{
    Q_OBJECT

public:
    explicit error_msg(const QString& msg, QWidget *parent = nullptr);
    ~error_msg();

private slots:
    void on_pushButton_released();

private:
    Ui::error_msg *ui;
};

#endif // ERROR_MSG_H
