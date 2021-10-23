#ifndef LOGIN_H
#define LOGIN_H

#include <QDebug>
#include <QDialog>
#include <QFile>
#include <iostream>
#include "Log.h"
#include "exceptions.h"

namespace Ui {
class Login;
}

enum class LoginErrors
{
    CouldNotOpenFIle
};

class Users
{
    bool createNewFile()
    {

    }
    bool initExistingFile()
    {
        QFile file("users.json");
        if(!file.open(QIODevice::ReadWrite | QIODevice::Text))
        {
            throw TOOLS::Exceptions<LoginErrors>(LoginErrors::CouldNotOpenFIle);
        }
    }
public:
    Users()
    {
        Log(1) << "Creating users class.";
        try {
            initExistingFile();
        }  catch (const TOOLS::Exceptions<LoginErrors>& x) {
            Log(Error) << "Could not open a file!";
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
};

#endif // LOGIN_H
