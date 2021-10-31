#ifndef USERS_H
#define USERS_H

#include<QJsonObject>
#include<QCryptographicHash>

#include "user.h"
#include "jsonreader.h"

#define USERS_CLASS_NAME QString("users")
#define USERS_FILE_PATH QString("users.json")

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
    std::list<QString> users;
public:
    Users();
    User loginUser(const QString& username, const QString& password);
    User registerUser(const QString& username, const QString& password, const QString& r_password);
    const std::list<QString>& getUsers() const
    {
        return users;
    }
    void debug() const
    {
        Log(Debug) << "Current users:";
        for(auto& x : users)
        {
            Log(Debug) << x.toStdString();
        }
    }
};

#endif // USERS_H
