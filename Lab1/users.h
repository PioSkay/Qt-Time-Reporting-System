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
public:
    Users();
    User loginUser(const QString& username, const QString& password);
    User registerUser(const QString& username, const QString& password, const QString& r_password);
};

#endif // USERS_H
