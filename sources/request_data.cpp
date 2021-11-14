#include "request_data.h"
#include "ui_request_data.h"

request_data::request_data(const QString& code, int pending, int accepted, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::request_data)
{
    ui->setupUi(this);
    ui->code->setText(code);
    ui->pending->setText(QString::number(pending) + QString(" min"));
    ui->accepted->setText(QString::number(accepted) + QString(" min"));
}

request_data::~request_data()
{
    delete ui;
}
