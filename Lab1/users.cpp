#include "users.h"

Users::Users():
    JSONReader(USERS_FILE_PATH, USERS_CLASS_NAME)
{
    if(!TOOLS::check(getArray(), {"username", "password"}))
    {
        Log(Error) << "Json file is corrupted!";
        clear();
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
