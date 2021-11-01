#ifndef FILE_PIPELINE_H
#define FILE_PIPELINE_H

#include"json_base.h"
#include"jsonreader.h"
#include"entries.h"
#include"accepted.h"

enum class fileError
{
    CouldNotFindFrozen,
    CouldNotFindEntries,
    CouldNotFindAccepted,
    IncorrectFileName
};

class file: public json_base
{
    bool isModified;
    JSONReader m_json;
    bool isFrozen;
    QDate m_date;
    QString m_name;
    std::list<std::shared_ptr<entries>> formated_entries;
    std::list<std::shared_ptr<accepted>> formated_accepted;
    void initExisting();
    template<typename What, typename Where>
    bool add(Where& where, const QJsonObject& in);
public:
    file(const QString& path, bool create = false);
    QJsonObject toJSONObject() const override;
    bool addEntries(const QJsonObject& in);
    bool addAccepted(const QJsonObject& in);
    bool operator==(const file& in) const
    {
        return in.m_date == m_date && in.m_name == m_name;
    }
    const QString& owner() const
    {
        return m_name;
    }
    bool status() const
    {
        return isFrozen;
    }
    ~file();
};

template<typename What, typename Where>
bool file::add(Where& where, const QJsonObject& in)
{
    try {
        What obj(in);
        where.emplace_back(std::make_shared<What>(std::move(obj)));
    }  catch (DEFAULT_CATCH x) {
        Log(Error) << x.what();
        return false;
    }
    isModified = true;
    return true;
}

#endif // FILE_PIPELINE_H
