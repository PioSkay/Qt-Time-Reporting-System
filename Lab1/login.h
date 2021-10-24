#ifndef LOGIN_H
#define LOGIN_H

#include <QDebug>
#include <QDialog>
#include <QFile>

#include <iostream>
#include "Log.h"
#include "exceptions.h"
#include "jsonreader.h"

#define USERS_CLASS_NAME QString("users")
#define USERS_FILE_PATH QString("users.json")

namespace Ui {
class Login;
}

enum class LoginErrors
{
    CouldNotOpenFIle,
    UserNotFound,
    UsernameFound,
    IncorrectPassward,
    PasswardsDoesNotMath,
    ToSmallPassward
};

class Users: public JSONReader
{
public:
    Users():
        JSONReader(USERS_FILE_PATH, USERS_CLASS_NAME)
    {

    }
    void loginUser(const QString& username, const QString& passward)
    {

    }
    void registerUser(const QString& username, const QString& passward, const QString& r_passward)
    {
        if(passward.size() < 6)
        {
            throw TOOLS::Exceptions<LoginErrors>(LoginErrors::ToSmallPassward);
        }
        else if(passward != r_passward)
        {
            throw TOOLS::Exceptions<LoginErrors>(LoginErrors::PasswardsDoesNotMath);
        }
    }
};

class Login : public QDialog
{
    Q_OBJECT
    bool auth;
    Users m_users;
public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();

    bool isLoggedIn() const
    {
        return auth;
    }
private:
    Ui::Login *ui;
    void loginButton();
    void registerButton();
};

#endif // LOGIN_H
