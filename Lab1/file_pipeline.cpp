#include "file_pipeline.h"

file_name::file_name():
    isInit(false)
{}
file_name::file_name(const QString& m_path):
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
file_name::file_name(const file_name& x):
    m_name(x.m_name),
    year(x.year),
    month(x.month),
    isInit(x.isInit)
{}
file_name::file_name(const QString& in, int y, int m)
{
    m_name = in;
    year = y;
    month = m;
}
bool file_name::operator==(const file_name& in) const
{
    return m_name == in.m_name && year == in.year && month == in.month;
}
QString file_name::toString() const
{
    return m_name + "-" + QString::number(year) + "-" + QString::number(month) + ".json";
}


void file::initExisting()
{
    const auto& obj = m_json.getObject();
    const auto& frozen = obj.value("frozen");
    const auto& ent = obj.value("entries");
    const auto& acc = obj.value("accepted");
    LOG_THROW_ERROR_IF("Could not find frozen", !frozen.isString(), fileError, fileError::CouldNotFindFrozen);
    LOG_THROW_ERROR_IF("Could not find entries", !ent.isArray(), fileError, fileError::CouldNotFindEntries);
    LOG_THROW_ERROR_IF("Could not find accepted", !acc.isArray(), fileError, fileError::CouldNotFindAccepted);
    Log(1) << "Entry check ok: " << __FUNCTION__ << ", " << __LINE__;
    isFrozen = (frozen.toString() == "True" || frozen.toString() == "true" ? true : false);
    auto array = ent.toArray();
    TOOLS::setup<TOOLS::entries>(array, formated_entries);
    auto array2 = acc.toArray();
    TOOLS::setup<TOOLS::accepted>(array2, formated_accepted);
}

file::file(const QString& path, const file_name& name, bool create):
    isModified(false),
    m_json(path, false),
    m_data(name)
{
    if(create == false)
    {
        m_json.init();
        initExisting();
    }
    else
    {
        isFrozen = false;
        isModified = true;
    }
}
QJsonObject file::toJSONObject() const
{
    QJsonObject obj;
    obj["frozen"] = (isFrozen == true ? "True" : "False");
    obj["entries"] = TOOLS::toArray<TOOLS::entries>(formated_entries);
    obj["accepted"] = TOOLS::toArray<TOOLS::accepted>(formated_accepted);
    return obj;
}
bool file::addEntries(const QJsonObject& in)
{
    if(!isFrozen)
    {
        return add<TOOLS::entries>(formated_entries, in);
    }
    else
    {
        Log(Error) << "File: " << m_json.getPath().toStdString() << ", is frozen";
        return false;
    }
}
bool file::addAccepted(const QJsonObject& in)
{
    return add<TOOLS::accepted>(formated_accepted, in);
}

bool file::addEntries(const TOOLS::entries& in)
{
    if(!isFrozen)
    {
        isModified = true;
        formated_entries.emplace_back(std::make_shared<TOOLS::entries>(std::move(in)));
        return true;
    }
    else
    {
        Log(Error) << "File: " << m_json.getPath().toStdString() << ", is frozen";
        return false;
    }
}

bool file::addAccepted(const TOOLS::accepted& in)
{
    if(!isFrozen)
    {
        isModified = true;
        formated_accepted.emplace_back(std::make_shared<TOOLS::accepted>(std::move(in)));
        return true;
    }
    else
    {
        Log(Error) << "File: " << m_json.getPath().toStdString() << ", is frozen";
        return false;
    }
}

bool file::removeEntrie(std::shared_ptr<TOOLS::entries> in)
{
    for(auto ele = formated_entries.begin();
        ele !=  formated_entries.end(); ++ele)
    {
        if(in.get() == ele->get())
        {
            formated_entries.erase(ele);
            return true;
        }
    }
    return false;
}

bool file::isFileFrozen() const
{
    return isFrozen;
}

void file::modifyFile()
{
    isModified = true;
}

std::list<std::shared_ptr<TOOLS::entries>> file::getEntries()
{
    return formated_entries;
}
std::list<std::shared_ptr<TOOLS::accepted>> file::getAccepted()
{
    return formated_accepted;
}
bool file::operator==(const file& in) const
{
    return m_data == in.m_data;
}
bool file::operator==(const file_name& in) const
{
    return m_data == in;
}
const QString& file::owner() const
{
    return m_data.m_name;
}
file::~file()
{
    if(isModified)
    {
        m_json.setObject(file::toJSONObject());
        m_json.save();
    }
}
