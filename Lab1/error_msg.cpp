#include "error_msg.h"
#include "ui_error_msg.h"

error_msg::error_msg(const QString& msg, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::error_msg)
{
    ui->setupUi(this);
    ui->label->setText(msg);
}

error_msg::~error_msg()
{
    delete ui;
}

void error_msg::on_pushButton_released()
{
    close();
}

