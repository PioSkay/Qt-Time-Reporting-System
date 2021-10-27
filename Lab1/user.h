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

    User& operator=(const User& x);
    const QString& username() const;
    bool isInit() const;
};

#endif // USER_H
