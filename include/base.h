#ifndef BASE_H
#define BASE_H

#include "jsonreader.h"
#include "activities_pipeline.h"
#include "user.h"
#include "files_pipeline.h"

class Base
{
    activities_pipeline m_activities;
    std::list<QString> m_usernames;
    std::shared_ptr<files_pipeline> m_files;
protected:
    User current_user;
    void debug() const;
public:
    Base() = default;
    void initJSON(const std::list<QString>& username);
    activities_pipeline& getActivities();
    std::shared_ptr<files_pipeline> getFiles();
    bool isFrozen(const QString& name, int year, int month);
    const User& getUser() const;
    virtual void addActivityToMainScreen(std::shared_ptr<TOOLS::activities> in) = 0;
    virtual void update_temp(int year, int month, int day) = 0;
    virtual void update_temp() = 0;
    virtual void updateTotalTime() = 0;
    virtual QDate getTime() const = 0;
};

#endif // BASE_H
