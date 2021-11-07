#include "request_data.h"
#include "ui_request_data.h"

request_data::request_data(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::request_data)
{
    ui->setupUi(this);
}

request_data::~request_data()
{
    delete ui;
}
