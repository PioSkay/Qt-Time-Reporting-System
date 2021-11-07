#ifndef REQUEST_DATA_H
#define REQUEST_DATA_H

#include <QWidget>

namespace Ui {
class request_data;
}

class request_data : public QWidget
{
    Q_OBJECT

public:
    explicit request_data(QWidget *parent = nullptr);
    ~request_data();

private:
    Ui::request_data *ui;
};

#endif // REQUEST_DATA_H
