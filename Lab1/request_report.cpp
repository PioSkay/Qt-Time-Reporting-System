#include "request_report.h"
#include "ui_request_report.h"

request_report::request_report(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::request_report)
{
    ui->setupUi(this);
}

request_report::~request_report()
{
    delete ui;
}
