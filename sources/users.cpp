#include "users.h"

Users::Users():
    JSONReader(USERS_FILE_PATH, USERS_CLASS_NAME, {"username", "password"})
{
    if(getStatus() == JSONReaderErrors::None)
    {
        const auto& x = getArray();
        for(const auto& y : x)
        {
            users.push_back(y[0].toString());
        }
    }
}
User Users::loginUser(const QString& username, const QString& password)
{
    const auto& array = getArray();
    for(const auto& ele : array)
    {
        if(ele.toObject()["username"].toString() == username)
        {
            QCryptographicHash passwardHash(QCryptographicHash::Sha256);
            passwardHash.addData(password.toUtf8());
            THROW_ERROR_IF(ele.toObject()["password"] != static_cast<QString>(passwardHash.result().toBase64()), LoginErrors, LoginErrors::IncorrectPassward);
            return User(username);
        }
    }
    THROW_ERROR(LoginErrors, LoginErrors::UserNotFound);
}
User Users::registerUser(const QString& username, const QString& password, const QString& r_password)
{
    THROW_ERROR_IF(password.size() < 6, LoginErrors, LoginErrors::ToSmallPassward);
    THROW_ERROR_IF(password != r_password, LoginErrors, LoginErrors::PasswardsDoesNotMath);
    auto& table = getArray();
    for(const auto& x : table)
    {
        THROW_ERROR_IF(x.toObject().value("username") == username, LoginErrors, LoginErrors::UsernameFound);
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

const std::list<QString>& Users::getUsers() const
{
    return users;
}

void Users::debug() const
{
    Log(Debug) << "Current users:";
    for(auto& x : users)
    {
        Log(Debug) << x.toStdString();
    }
}
