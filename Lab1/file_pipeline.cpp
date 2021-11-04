#include "file_pipeline.h"
void file::initExisting()
{
    m_data = file_name(m_json.getPath());
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

file::file(const QString& path, bool create):
    isModified(false),
    m_json(path, false)
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
    obj["frozen"] = isFrozen == true ? "True" : "False";
    obj["entries"] = TOOLS::toArray<entries>(formated_entries);
    obj["accepted"] = TOOLS::toArray<accepted>(formated_accepted);
    return obj;
}
bool file::addEntries(const QJsonObject& in)
{
    if(!isFrozen)
    {
        return add<entries>(formated_entries, in);
    }
    else
    {
        Log(Error) << "File: " << m_json.getPath().toStdString() << ", is frozen";
        return false;
    }
}
bool file::addAccepted(const QJsonObject& in)
{
    return add<accepted>(formated_accepted, in);
}
file::~file()
{
    if(isModified)
    {
        m_json.setObject(file::toJSONObject());
        m_json.save();
    }
}
