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
