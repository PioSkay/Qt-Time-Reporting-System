#ifndef ACCEPTED_H
#define ACCEPTED_H

#include<QString>

#include"exceptions.h"
#include"json_base.h"
namespace TOOLS
{
    struct accepted: public json_base
    {
        QString code;
        int time;
        accepted(const QJsonObject& obj);
        accepted(QString c, int t);
        QJsonObject toJSONObject() const override;
        friend std::ostream& operator<<(std::ostream& in, const accepted& x);
    };
}


#endif // ACCEPTED_H
