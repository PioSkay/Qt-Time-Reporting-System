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
    JSONReader m_json;
    QString m_path;
    bool isFrozen;
    QDate m_date;
    QString m_name;
    std::list<std::shared_ptr<entries>> formated_entries;
    std::list<std::shared_ptr<accepted>> formated_accepted;
public:
    file(const QString& path):
        m_json(path),
        m_path(path)
    {
        QString name;
        QString date;
        bool b = false;
        for(int i = 0; i < path.size(); i++)
        {
            if(!b)
            {
                if(path[i] == '-')
                {
                    b = true;
                    continue;
                }
                name += path[i];
            }
            else
            {
                date += path[i];
            }
        }
        LOG_THROW_ERROR_IF("Incorrect file name", name.size() == 0, fileError, fileError::IncorrectFileName);
        LOG_THROW_ERROR_IF("Incorrect file name", date.size() == 0, fileError, fileError::IncorrectFileName);
        date.remove(".json");
        Log(Info) << name.toStdString() << " " << date.toStdString();
        QDate x = QDate::fromString(date, "yyyy-MM");
        LOG_THROW_ERROR_IF("Could not create date", !x.isValid(), fileError, fileError::IncorrectFileName);
        const auto& obj = m_json.getObject();
        const auto& frozen = obj.value("frozen");
        const auto& ent = obj.value("entries");
        const auto& acc = obj.value("accepted");
        LOG_THROW_ERROR_IF("Could not find frozen", !frozen.isString(), fileError, fileError::CouldNotFindFrozen);
        LOG_THROW_ERROR_IF("Could not find entries", !ent.isArray(), fileError, fileError::CouldNotFindEntries);
        LOG_THROW_ERROR_IF("Could not find accepted", !acc.isArray(), fileError, fileError::CouldNotFindAccepted);
        Log(1) << "Entry check ok: " << __FUNCTION__ << ", " << __LINE__;
        isFrozen = frozen.toString() == "True" || "true" ? true : false;
        auto array = ent.toArray();
        TOOLS::setup<entries>(array, formated_entries);
        auto array2 = acc.toArray();
        TOOLS::setup<accepted>(array2, formated_accepted);
    }
    QJsonObject toJSONObject() const override
    {
        QJsonObject obj;
        return obj;
    }
};

#endif // FILE_PIPELINE_H
