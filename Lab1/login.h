#ifndef LOGIN_H
#define LOGIN_H

#include <QDebug>
#include <QDialog>
#include <QFile>
#include <QCryptographicHash>

#include <iostream>
#include "Log.h"
#include "exceptions.h"
#include "jsonreader.h"
#include "user.h"


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
        if(!TOOLS::check(getArray(), {"username", "password"}))
        {
            Log(Error) << "Json file is corrupted!";
            clear();
        }
    }
    User loginUser(const QString& username, const QString& password)
    {
        const auto& array = getArray();
        for(const auto& ele : array)
        {
            if(ele.toObject()["username"].toString() == username)
            {
                QCryptographicHash passwardHash(QCryptographicHash::Sha256);
                passwardHash.addData(password.toUtf8());
                if(ele.toObject()["password"] != static_cast<QString>(passwardHash.result().toBase64()))
                {
                    throw TOOLS::Exceptions<LoginErrors>(LoginErrors::IncorrectPassward);
                }
                return User(username);
            }
        }
        throw TOOLS::Exceptions<LoginErrors>(LoginErrors::UserNotFound);
    }
    User registerUser(const QString& username, const QString& password, const QString& r_password)
    {
        if(password.size() < 6)
        {
            throw TOOLS::Exceptions<LoginErrors>(LoginErrors::ToSmallPassward);
        }
        else if(password != r_password)
        {
            throw TOOLS::Exceptions<LoginErrors>(LoginErrors::PasswardsDoesNotMath);
        }
        else
        {
            auto& table = getArray();
            for(const auto& x : table)
            {
                if(x.toObject().value("username") == username)
                {
                    throw TOOLS::Exceptions<LoginErrors>(LoginErrors::UsernameFound);
                }
            }
            QJsonObject obj;
            obj.insert("username", username);
            QCryptographicHash passwardHash(QCryptographicHash::Sha256);
            passwardHash.addData(password.toUtf8());
            obj.insert("password", static_cast<QString>(passwardHash.result().toBase64()));
            getArray().push_back(obj);
            save();
            return User(username);
        }
    }
};

class Login : public QDialog
{
    Q_OBJECT
    bool auth;
    Users m_users;
    User final_user;
public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();

    bool isLoggedIn() const
    {
        return auth;
    }
    const User& loggedUser() const
    {
        return final_user;
    }
private:
    Ui::Login *ui;
    void loginButton();
    void registerButton();
};

#endif // LOGIN_H
