#ifndef BASE_H
#define BASE_H

#include "jsonreader.h"

class Base
{
    JSONReader m_activities;
public:
    Base():
        m_activities("activity.json", "activities", {"code", "manager", "name", "budget", "active", "subactivities"}, false)
    {}
    void initJSON()
    {
        Log(3) << "initJSON()";
        m_activities.init();
    }
    JSONReader& getActivities()
    {
        return m_activities;
    }
};

#endif // BASE_H
