#include "login.h"
#include "ui_login.h"

Login::Login(QWidget *parent) :
    QDialog(parent),
    auth(false),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    connect(ui->login_button, &QPushButton::released, this, &Login::loginButton);
    connect(ui->register_button, &QPushButton::released, this, &Login::registerButton);
}

void Login::loginButton()
{
    Log(Info) << "Login button released.";
}
void Login::registerButton()
{
    Log(Info) << "Register button released.";
    try{
        m_users.registerUser(ui->register_username->text(),
                             ui->register_password->text(),
                             ui->register_password_r->text());
    }
    catch(const TOOLS::Exceptions<LoginErrors>& er)
    {
        if(er.what() == LoginErrors::PasswardsDoesNotMath)
        {
            ui->register_error->setText("Passwords do not match!");
        }
        else if(er.what() == LoginErrors::ToSmallPassward)
        {
            ui->register_error->setText("Passwords needs to have atleast 6 characters!");
        }
    }
}




Login::~Login()
{
    delete ui;
}
