#include "login.h"
#include "ui_login.h"

Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login),
    auth(false)
{
    ui->setupUi(this);
}

Login::~Login()
{
    delete ui;
}
