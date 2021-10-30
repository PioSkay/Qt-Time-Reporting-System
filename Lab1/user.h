#ifndef USER_H
#define USER_H

#include <QString>
#include <unordered_map>
#include <list>

#include"base.h"

struct activities
{
    QString code;
    QString manager;
    QString name;
    int budget;
    bool active;
    std::list<std::pair<QString, QString>> subactivities;
    activities(const QJsonObject& obj)
    {
        Log(3) << "activities";
        THROW_DEFAULT(!obj.contains("code"), "Activity does not contain code");
        code = obj["code"].toString();
        manager = obj["manager"].toString();
        THROW_DEFAULT(!obj.contains("name"), "Activity does not contain name");
        name = obj["name"].toString();
        THROW_DEFAULT(!obj.contains("budget"), "Activity does not contain budget");
        budget = obj["budget"].toInt();
        THROW_DEFAULT(!obj.contains("active"), "Activity does not contain active");
        active = obj["active"].toBool();
        THROW_DEFAULT(!obj.contains("subactivities"), "Activity does not contain subactivities");
        if(obj["subactivities"].isArray()) {
            const auto& sub = obj["subactivities"].toArray();
            for(int i = 0; i < sub.size(); i++)
            {
                const auto& keys = sub[i].toObject().keys();
                for(const auto& key : keys)
                {
                    subactivities.push_back({key, sub[i][key].toString()});
                }
            }

        }
    }
    bool operator==(const QString& x) const
    {
        return code == x;
    }
    bool operator==(const activities& x) const
    {
        return code == x.code;
    }
    friend std::ostream& operator<<(std::ostream& in, const activities& x)
    {
        in << "------Info regarding project " << x.code.toStdString() << std::endl;
        in << "------Manager: " << x.manager.toStdString() << std::endl;
        in << "------Project name: " << x.name.toStdString() << std::endl;
        in << "------Time budget: " << x.budget << std::endl;
        in << "------Is project active: " << (x.active == true? "Yes" : "No") << std::endl;
        in << "------Project subactivities: " << x.subactivities.size() << std::endl;
        std::for_each(x.subactivities.begin(),
                        x.subactivities.end(),
                        [&in](const std::pair<QString, QString> &p) {
                            in << "{" << p.first.toStdString() << ": " << p.second.toStdString() << "}\n";
                        });
        return in;
    }
};


class User
{
    bool init;
    QString m_username;
    std::list<activities> manager_of;
public:
    User();
    User(const QString& username);
    User(const User& x);
    User(User&& x);

    void setup_activities(Base* base)
    {
        Log(3) << "setup_activities()";
        if(base != nullptr)
        {
            auto& act = base->getActivities();
            if(act.getStatus() == JSONReaderErrors::None)
            {
                auto& array = act.getArray();
                for(const auto& element : array)
                {
                    const auto& obj = element.toObject();
                    try {
                        THROW_DEFAULT(!obj.contains("manager"), "Activity does not contain manager");
                        THROW_DEFAULT(obj["manager"].toString() != m_username, "You are not the manager of that activity");
                        activities activity(obj);
                        Log(10) << activity;
                    } catch(DEFAULT_CATCH x) {
                        Log(Error) << "There was a problem during activity creation: " << x.what();
                        continue;
                    }
                    manager_of.emplace_back(obj);
                }
            }
            else
            {
                Log(Info) << "Could not read any activities!";
            }
        }
    }
    bool isManager(const QString& code)
    {
        for(const auto& x : manager_of)
        {
            if(x == code)
            {
                return true;
            }
        }
        return false;
    }
    User& operator=(const User& x);
    const QString& username() const;
    bool isInit() const;
};

#endif // USER_H
