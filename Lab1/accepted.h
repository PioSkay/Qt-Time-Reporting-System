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
    accepted(const QJsonObject& obj);
    QJsonObject toJSONObject() const override;
    friend std::ostream& operator<<(std::ostream& in, const accepted& x);
};

#endif // ACCEPTED_H
