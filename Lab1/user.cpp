#include "user.h"

User::User():
    init(false),
    m_username("")
{

}

User::User(const QString& username):
    init(true),
    m_username(username)
{

}

User::User(const User& x):
    init(true),
    m_username(x.m_username)
{

}

User::User(User&& x):
    init(true),
    m_username(std::move(x.m_username))
{}

void User::setup_activities(const std::list<std::shared_ptr<activities>>& array)
{
    Log(3) << "setup_activities()";
    for(const auto& x : array)
    {
        if(x.get()->manager == m_username)
        {
            manager_of.push_back(x);
        }
    }
}
bool User::isManager(const QString& code)
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

User& User::operator=(const User& x)
{
    if(this != &x)
    {
        init = x.init;
        m_username = x.m_username;
    }
    return *this;
}

const QString& User::username() const
{
    return m_username;
}

bool User::isInit() const
{
    return init;
}

void User::debug()
{
    Log(Debug) << "Data for user: " << m_username.toStdString() << ", is init: " << (init == true ? "True" : "False") << ", is a manager of:";
    for(auto& ele : manager_of)
    {
        if(!ele.expired())
            Log(Debug) << *ele.lock();
    }
}
