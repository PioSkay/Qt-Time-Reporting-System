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
    activities(const QJsonObject& obj);
    activities(QString co, QString ma, QString n, int b, bool a, std::list<std::pair<QString, QString>> sub);
    activities(const activities& obj);
    activities(activities&& obj);
    QJsonObject toJSONObject() const override;
    bool operator==(const QString& x) const;
    bool operator==(const activities& x) const;
    friend std::ostream& operator<<(std::ostream& in, const activities& x);
};


#endif // ACTIVITIES_H
