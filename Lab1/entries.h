#ifndef ENTRIES_H
#define ENTRIES_H

#include<QJsonObject>
#include<QJsonArray>
#include<QString>

#include"exceptions.h"
#include"Log.h"
#include"json_base.h"

struct entries: public json_base
{
    QDate date;
    QString code;
    QString subcode;
    int time;
    QString description;
    entries(QDate d, QString c, QString sub, int t, QString desc);
    entries(const QJsonObject& obj);
    entries(const entries& obj);
    entries(entries&& obj);
    QJsonObject toJSONObject() const override;
    bool operator==(const QString& x) const;
    bool operator==(const entries& x) const;
    friend std::ostream& operator<<(std::ostream& in, const entries& x);
};


#endif // ENTRIES_H
