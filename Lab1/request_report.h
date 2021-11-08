#ifndef REQUEST_REPORT_H
#define REQUEST_REPORT_H

#include <QDialog>

#include "file_pipeline.h"

namespace Ui {
class request_report;
}

class request_report : public QDialog
{
    Q_OBJECT
    std::shared_ptr<file> m_entr;
public:
    explicit request_report(std::shared_ptr<file> entr, QWidget *parent = nullptr);
    ~request_report();

private slots:
    void on_pushButton_released();

private:
    Ui::request_report *ui;
};

#endif // REQUEST_REPORT_H
