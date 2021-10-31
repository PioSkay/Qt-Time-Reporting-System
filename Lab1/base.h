#ifndef BASE_H
#define BASE_H

#include "jsonreader.h"
#include "activities.h"

class Base
{
    JSONReader m_activities;
    std::list<std::shared_ptr<activities>> formated_activities;
    std::list<QString> m_usernames;
protected:
    void debug() const
    {
        Log(Debug) << "[formated_activities]:";
        for(auto& x : formated_activities)
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
    Base():
        m_activities("activity.json", "activities", {"code", "manager", "name", "budget", "active", "subactivities"}, false)
    {}
    void initJSON(const std::list<QString>& username)
    {
        Log(3) << "initJSON()";
        m_usernames = username;
        Log(Info) << username.size();
        m_activities.init();
        if(m_activities.getStatus() == JSONReaderErrors::None)
        {
            TOOLS::setup<activities>(m_activities.getArray(), formated_activities);
        }
        else
        {
            Log(Info) << "Could not read any activities!";
        }
        debug();
    }
    JSONReader& getActivities()
    {
        return m_activities;
    }
    std::list<std::shared_ptr<activities>>& getActivitiesList()
    {
        return formated_activities;
    }
};

#endif // BASE_H
