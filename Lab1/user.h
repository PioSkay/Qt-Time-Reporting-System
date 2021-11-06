#ifndef USER_H
#define USER_H

#include <QString>
#include <unordered_map>
#include <list>

#include"activities.h"
#include"jsonreader.h"

class User
{
    bool init;
    QString m_username;
    QString m_password_hash;
    std::list<std::weak_ptr<TOOLS::activities>> manager_of;
public:
    User();
    User(const QString& username);
    User(const User& x);
    User(User&& x);

    void setup_activities(const std::list<std::shared_ptr<TOOLS::activities>>& base);
    bool isManager(const QString& code);
    User& operator=(const User& x);
    const QString& username() const;
    bool isInit() const;
    void debug();
};

#endif // USER_H
