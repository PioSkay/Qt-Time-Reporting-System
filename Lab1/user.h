#ifndef USER_H
#define USER_H

#include <QString>
#include <unordered_map>
#include <list>

#include"activities.h"
#include"jsonreader.h"
#include"base.h"

class User
{
    bool init;
    QString m_username;
    QString m_password_hash;
    std::list<std::weak_ptr<activities>> manager_of;
public:
    User();
    User(const QString& username);
    User(const User& x);
    User(User&& x);

    void setup_activities(Base* base)
    {
        Log(3) << "setup_activities()";
        if(base != nullptr)
        {
            auto& array = base->getActivitiesList();
            for(const auto& x : array)
            {
                if(*x.get() == m_username)
                {
                    manager_of.push_back(x);
                }
            }
        }
        else
        {
            Log(Error) << "Base in as nullptr! In: " << __FUNCTION__;
        }
    }
    bool isManager(const QString& code)
    {
        for(const auto& x : manager_of)
        {
            if(!x.expired())
            {
                const auto& ele = x.lock();
                if(*ele == code)
                {
                    return true;
                }
            }
        }
        return false;
    }
    User& operator=(const User& x);
    const QString& username() const;
    bool isInit() const;
    void debug()
    {
        Log(Debug) << "Data for user: " << m_username.toStdString() << ", is init: " << (init == true ? "True" : "False") << ", is a manager of:";
        for(auto& ele : manager_of)
        {
            if(!ele.expired())
                Log(Debug) << *ele.lock();
        }
    }
};

#endif // USER_H
