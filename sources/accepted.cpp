#include "accepted.h"
namespace TOOLS
{
    accepted::accepted(const QJsonObject& obj)
    {
        Log(3) << "activities";
        THROW_DEFAULT(!obj.contains("code"), "Accepted does not contain code");
        code = obj["code"].toString();
        THROW_DEFAULT(!obj.contains("time") || obj["time"].toInt() < 0, "Accepted does not contain time");
        time = obj["time"].toInt();
    }

    accepted::accepted(QString c, int t):
        code(c),
        time(t)
    {
    }

    QJsonObject accepted::toJSONObject() const
    {
        QJsonObject x;
        x["code"] = code;
        x["time"] = time;
        return x;
    }

    std::ostream& operator<<(std::ostream& in, const accepted& x)
    {
        in << "------Accepted activity in project: " << x.code.toStdString() << std::endl;
        in << "------Logged time: " << x.time;
        return in;
    }
}

