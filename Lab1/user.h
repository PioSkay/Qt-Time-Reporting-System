#ifndef USER_H
#define USER_H

#include <QString>

class User
{
    bool init;
    QString m_username;
public:
    User();
    User(const QString& username);
    User(const User& x);
    User(User&& x);
    User& operator=(const User& x)
    {
        if(this != &x)
        {
            init = x.init;
            m_username = x.m_username;
        }
        return *this;
    }
    const QString& username() const
    {
        return m_username;
    }
    bool isInit() const
    {
        return init;
    }
};

#endif // USER_H
