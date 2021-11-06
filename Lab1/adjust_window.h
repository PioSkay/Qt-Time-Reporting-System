#ifndef ADJUST_WINDOW_H
#define ADJUST_WINDOW_H

#include <QDialog>

namespace Ui {
class adjust_window;
}

class adjust_window : public QDialog
{
    Q_OBJECT
    int &m_to_adjust;
    bool isAdjusted;
public:
    explicit adjust_window(int &to_adjust, QWidget *parent = nullptr);
    bool adjusted();
    ~adjust_window();
    int before;
    int after;
private slots:
    void on_pushButton_released();
    void on_pushButton_2_released();

private:
    Ui::adjust_window *ui;
};

#endif // ADJUST_WINDOW_H
