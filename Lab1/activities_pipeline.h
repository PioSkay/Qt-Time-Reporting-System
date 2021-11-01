#ifndef ACTIVITIES_PIPELINE_H
#define ACTIVITIES_PIPELINE_H

#include"jsonreader.h"
#include"activities.h"

class activities_pipeline
{
    JSONReader m_activities;
    std::list<std::shared_ptr<activities>> formated_activities;
public:
    activities_pipeline():
        m_activities("activity.json", "activities", {"code", "manager", "name", "budget", "active", "subactivities"}, false)
    {}
    void init()
    {
        m_activities.init();
        if(m_activities.getStatus() == JSONReaderErrors::None)
        {
            TOOLS::setup<activities>(m_activities.getArray(), formated_activities);
        }
        else
        {
            Log(Info) << "Could not read any activities!";
        }
    }
    const std::list<std::shared_ptr<activities>>& getArray() const
    {
        return formated_activities;
    }
    const JSONReader& getJSONReader() const
    {
        return m_activities;
    }
    void addActivities(const QJsonObject& in)
    {
        activities obj(in);
        for(const auto& x : formated_activities)
        {
            THROW_DEFAULT(*x.get() == obj, "Activity does not contain code");
        }
        formated_activities.emplace_back(std::make_shared<activities>(std::move(obj)));
    }
};

#endif // ACTIVITIES_PIPELINE_H
