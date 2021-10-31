#ifndef ACTIVITIES_H
#define ACTIVITIES_H

#include<QString>
#include<QJsonObject>
#include<QJsonArray>
#include<list>

#include"Log.h"
#include"exceptions.h"
#include"json_base.h"

struct activities: public json_base
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
        THROW_DEFAULT(!obj.contains("manager"), "Activity does not contain manager");
        manager = obj["manager"].toString();
        THROW_DEFAULT(!obj.contains("name"), "Activity does not contain name");
        name = obj["name"].toString();
        THROW_DEFAULT(!obj.contains("budget"), "Activity does not contain budget");
        budget = obj["budget"].toInt();
        THROW_DEFAULT(!obj.contains("active"), "Activity does not contain active");
        active = obj["active"] == "True" || "true" ? true : false;
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

    activities(activities&& obj):
        code(std::move(obj.code)),
        manager(std::move(obj.manager)),
        name(std::move(obj.name)),
        budget(obj.budget),
        active(obj.active),
        subactivities(std::move(obj.subactivities))
    {}

    QJsonObject toJSONObject() const override
    {
        QJsonObject x;
        x["code"] = code;
        x["manager"] = manager;
        x["name"] = name;
        x["budget"] = budget;
        x["active"] = (active == true ? "True" : "False");
        QJsonArray sub;
        for(auto& x : subactivities)
        {
            QJsonObject y;
            y.insert(x.first, x.second);
            sub.push_back(y);
        }
        x["subactivities"] = sub;
        return x;
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

#endif // ACTIVITIES_H
