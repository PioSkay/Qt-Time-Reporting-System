#ifndef ACCEPTED_H
#define ACCEPTED_H

#include<QString>

#include"exceptions.h"
#include"json_base.h"

class accepted: public json_base
{
    QString code;
    int time;
public:
    accepted(const QJsonObject& obj)
    {
        Log(3) << "activities";
        THROW_DEFAULT(!obj.contains("code"), "Accepted does not contain code");
        code = obj["code"].toString();
        THROW_DEFAULT(!obj.contains("time") || obj["time"].toInt() < 0, "Accepted does not contain time");
        time = obj["time"].toInt();
    }
    QJsonObject toJSONObject() const override
    {
        QJsonObject x;
        x["code"] = code;
        x["time"] = time;
        return x;
    }
    friend std::ostream& operator<<(std::ostream& in, const accepted& x)
    {
        in << "------Accepted activity in project: " << x.code.toStdString() << std::endl;
        in << "------Logged time: " << x.time;
        return in;
    }
};

#endif // ACCEPTED_H
