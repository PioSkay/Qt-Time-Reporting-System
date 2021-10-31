#ifndef LOGIN_H
#define LOGIN_H

#include <QDebug>
#include <QDialog>
#include <QFile>
#include <QCryptographicHash>

#include <iostream>
#include "Log.h"
#include "exceptions.h"
#include "users.h"
namespace Ui {
class Login;
}

class Login : public QDialog
{
    Q_OBJECT
    bool auth;
    Users m_users;
    User final_user;
public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();
    bool isLoggedIn() const;
    const User& loggedUser() const;
    const Users& getUsers() const
    {
        return m_users;
    }
private:
    Ui::Login *ui;
    void loginButton();
    void registerButton();
};

#endif // LOGIN_H
