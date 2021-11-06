#include "base.h"

void Base::debug() const
{
    Log(Debug) << "[formated_activities]:";
    const auto& array = m_activities.getArray();
    for(auto& x : array)
    {
        Log(Debug) << *x.get();
    }
    Log(Debug) << "[m_usernames]:";
    for(auto& x : m_usernames)
    {
        Log(Debug) << x.toStdString();
    }
}
void Base::initJSON(const std::list<QString>& username)
{
    Log(3) << __FUNCTION__ << " " << __LINE__;
    m_usernames = username;
    m_activities.init();
    m_files = std::make_shared<files_pipeline>(username);
}
activities_pipeline& Base::getActivities()
{
    return m_activities;
}
std::shared_ptr<files_pipeline> Base::getFiles()
{
    return m_files;
}
bool Base::isFrozen(const QString& name, int year, int month)
{
    const auto& x = m_files.get()->find(name, year, month);
    return x.get() != nullptr && x.get()->isFileFrozen();
}
const User& Base::getUser() const
{
    return current_user;
}
