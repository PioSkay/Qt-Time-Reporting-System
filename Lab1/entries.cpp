#include "entries.h"
entries::entries(QDate d, QString c, QString sub, int t, QString desc):
    date(d),
    code(c),
    subcode(sub),
    time(t),
    description(desc)
{}

entries::entries(const QJsonObject& obj)
{
    Log(3) << "entries";
    THROW_DEFAULT(!obj.contains("date"), "Entries does not contain date");
    date = QDate::fromString(obj["date"].toString(), "yyyy-MM-dd");
    THROW_DEFAULT(!obj.contains("code"), "Entries does not contain code");
    code = obj["code"].toString();
    THROW_DEFAULT(!obj.contains("subcode"), "Entries does not contain subcode");
    subcode = obj["subcode"].toString();
    THROW_DEFAULT(!obj.contains("time") || obj["time"].toInt() < 0, "Entries does not contain time or time is negative");
    time = obj["time"].toInt();
    THROW_DEFAULT(!obj.contains("description"), "Entries does not contain description");
    description = obj["description"].toString();
}
entries::entries(const entries& obj):
    date(obj.date),
    code(obj.code),
    subcode(obj.subcode),
    time(obj.time),
    description(obj.description)
{}

entries::entries(entries&& obj):
    date(std::move(obj.date)),
    code(std::move(obj.code)),
    subcode(std::move(obj.subcode)),
    time(obj.time),
    description(std::move(obj.description))
{}

QJsonObject entries::toJSONObject() const
{
    QJsonObject x;
    x["date"] = date.toString("yyyy-MM-dd");
    x["code"] = code;
    x["subcode"] = subcode;
    x["time"] = time;
    x["description"] = description;
    return x;
}

bool entries::operator==(const QString& x) const
{
    return code == x;
}

bool entries::operator==(const entries& x) const
{
    return code == x.code;
}

std::ostream& operator<<(std::ostream& in, const entries& x)
{
    in << "------Info regarding activity in project: " << x.code.toStdString() << std::endl;
    in << "------Date: " << x.date.toString("yyyy-MM-dd").toStdString() << std::endl;
    in << "------Subcode: " << x.subcode.toStdString() << std::endl;
    in << "------Time int minutes: " << x.time << std::endl;
    in << "------Description: " << x.description.toStdString() << std::endl;
    return in;
}
