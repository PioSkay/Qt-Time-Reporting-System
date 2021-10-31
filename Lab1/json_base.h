#ifndef JSON_BASE_H
#define JSON_BASE_H

#include<QJsonObject>

struct json_base
{
    json_base() = default;
    virtual QJsonObject toJSONObject() const = 0;
    ~json_base() = default;
};

#endif // JSON_BASE_H
