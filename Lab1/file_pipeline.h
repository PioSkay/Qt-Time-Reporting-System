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

struct file_name
{
    QString m_name;
    int year;
    int month;
    bool isInit;
    file_name():
        isInit(false)
    {}
    file_name(const QString& m_path):
        isInit(false)
    {
        QString date;
        bool b = false;
        for(int i = 0; i < m_path.size(); i++)
        {
            if(!b)
            {
                if(m_path[i] == '-')
                {
                    b = true;
                    continue;
                }
                m_name += m_path[i];
            }
            else
            {
                date += m_path[i];
            }
        }
        LOG_THROW_ERROR_IF("Incorrect file name", m_name.size() == 0, fileError, fileError::IncorrectFileName);
        LOG_THROW_ERROR_IF("Incorrect file name", date.size() == 0, fileError, fileError::IncorrectFileName);
        date.remove(".json");
        QDate m_date = QDate::fromString(date, "yyyy-MM");
        LOG_THROW_ERROR_IF("Could not create date", !m_date.isValid(), fileError, fileError::IncorrectFileName);
        year = m_date.year();
        month = m_date.month();
        isInit = true;
    }
    file_name(const file_name& x):
        m_name(x.m_name),
        year(x.year),
        month(x.month),
        isInit(x.isInit)
    {}
    file_name(const QString& in, int y, int m)
    {
        m_name = in;
        year = y;
        month = m;
    }
    bool operator==(const file_name& in) const
    {
        return m_name == in.m_name && year == in.year && month == in.month;
    }
};

class file: public json_base
{
    bool isModified;
    JSONReader m_json;
    bool isFrozen;
    file_name m_data;
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
        return m_data == in.m_data;
    }
    bool operator==(const file_name& in) const
    {
        return m_data == in;
    }
    const QString& owner() const
    {
        return m_data.m_name;
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
