#include "activities_pipeline.h"
activities_pipeline::activities_pipeline():
    m_activities("activity.json", "activities", {"code", "manager", "name", "budget", "active", "subactivities"}, false),
    m_modified(false)
{}
void activities_pipeline::init()
{
    Log(3) << __FUNCTION__ << ", " << __LINE__;
    m_activities.init();
    if(m_activities.getStatus() == JSONReaderErrors::None)
    {
        TOOLS::setup<TOOLS::activities>(m_activities.getArray(), formated_activities);
    }
    else
    {
        Log(Info) << "Could not read any activities!";
    }
}

void activities_pipeline::modify()
{
    m_modified = true;
}

const std::list<std::shared_ptr<TOOLS::activities>>& activities_pipeline::getArray() const
{
    Log(3) << __FUNCTION__ << ", " << __LINE__;
    return formated_activities;
}
const JSONReader& activities_pipeline::getJSONReader() const
{
    Log(3) << __FUNCTION__ << ", " << __LINE__;
    return m_activities;
}

std::shared_ptr<TOOLS::activities> activities_pipeline::addActivities(const TOOLS::activities& obj)
{
    Log(3) << __FUNCTION__ << ", " << __LINE__;
    for(const auto& x : formated_activities)
    {
        THROW_DEFAULT(*x.get() == obj, "Project with that code already exists");
    }
    m_modified = true;
    formated_activities.emplace_back(std::make_shared<TOOLS::activities>(obj));
    return formated_activities.back();
}
activities_pipeline::~activities_pipeline()
{
    Log(3) << __FUNCTION__ << ", " << __LINE__;
    if(m_modified)
    {
        Log(Info) << "Saving activities!";
        m_activities.setArray(TOOLS::toArray<TOOLS::activities>(formated_activities));
        m_activities.save();
    }
}
