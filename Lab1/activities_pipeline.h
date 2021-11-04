#ifndef ACTIVITIES_PIPELINE_H
#define ACTIVITIES_PIPELINE_H

#include"jsonreader.h"
#include"activities.h"

class activities_pipeline
{
    JSONReader m_activities;
    bool m_modified;
    std::list<std::shared_ptr<activities>> formated_activities;
public:
    activities_pipeline();
    void init();
    const std::list<std::shared_ptr<activities>>& getArray() const;
    const JSONReader& getJSONReader() const;
    std::shared_ptr<activities> addActivities(const activities& obj);
    ~activities_pipeline();
};

#endif // ACTIVITIES_PIPELINE_H
