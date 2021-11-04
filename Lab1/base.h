#ifndef BASE_H
#define BASE_H

#include "jsonreader.h"
#include "activities_pipeline.h"
#include "user.h"

class Base
{
    activities_pipeline m_activities;
    std::list<QString> m_usernames;
protected:
    User current_user;
    void debug() const
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
public:
    Base() = default;
    void initJSON(const std::list<QString>& username)
    {
        Log(3) << __FUNCTION__ << " " << __LINE__;
        m_usernames = username;
        m_activities.init();
        debug();
    }
    activities_pipeline& getActivities()
    {
        return m_activities;
    }
    const User& getUser() const
    {
        return current_user;
    }
    virtual void addActivityToMainScreen(std::shared_ptr<activities> in) = 0;
};

#endif // BASE_H
