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
    try{
        final_user = m_users.loginUser(ui->login_username->text(),
                             ui->login_password->text());
        auth = true;
        close();
    }
    catch(const TOOLS::Exceptions<LoginErrors>& er)
    {
        if(er.what() == LoginErrors::IncorrectPassward)
        {
            Log(1) << "Passwords is not correct!";
            ui->login_error->setText("Passwords is not correct!");
        }
        else if(er.what() == LoginErrors::UserNotFound)
        {
            Log(1) << "User is not registered!";
            ui->login_error->setText("User is not registered!");
        }
    }
}
void Login::registerButton()
{
    Log(Info) << "Register button released.";
    try{
        final_user = m_users.registerUser(ui->register_username->text(),
                             ui->register_password->text(),
                             ui->register_password_r->text());
        auth = true;
        close();
    }
    catch(const TOOLS::Exceptions<LoginErrors>& er)
    {
        if(er.what() == LoginErrors::PasswardsDoesNotMath)
        {
            Log(1) << "Passwords do not match!";
            ui->register_error->setText("Passwords do not match!");
        }
        else if(er.what() == LoginErrors::ToSmallPassward)
        {
            Log(1) << "Passwords needs to have atleast 6 characters!";
            ui->register_error->setText("Passwords needs to have atleast 6 characters!");
        }
        else if(er.what() == LoginErrors::UsernameFound)
        {
            Log(1) << "User already exists!";
            ui->register_error->setText("User already exists!");
        }
    }
}

bool Login::isLoggedIn() const
{
    return auth;
}

const User& Login::loggedUser() const
{
    return final_user;
}

const Users& Login::getUsers() const
{
    return m_users;
}

Login::~Login()
{
    delete ui;
}
