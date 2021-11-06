#include "jsonreader.h"
void JSONReader::open()
{
    using namespace TOOLS;
    Log(3) << "open()";
    QFile file(m_path);
    Log(1) << "Opening file: " << m_path.toStdString();
    LOG_THROW_ERROR_IF("Could not open a file!", !file.open(QIODevice::ReadOnly | QIODevice::Text), JSONReaderErrors, JSONReaderErrors::CouldNotOpen);
    QByteArray jsonData = file.readAll();
    file.close();
    QJsonDocument document = QJsonDocument::fromJson(jsonData);
    LOG_THROW_ERROR_IF("Could not create a document!", document.isNull(), JSONReaderErrors, JSONReaderErrors::CouldNotCreateDocument);
    LOG_THROW_ERROR_IF("Document is not an object!", !document.isObject(), JSONReaderErrors, JSONReaderErrors::DocumentInNotAnObject);
    m_object = document.object();
    if(m_name.size() != 0)
    {
        QJsonValue value = m_object.value(m_name);
        LOG_THROW_ERROR_IF("Could not find an class name in the JSON file", value.isUndefined(), JSONReaderErrors, JSONReaderErrors::CouldNotFindName);
        m_array = value.toArray();
    }
}

JSONReader::JSONReader(const QString& path, bool initNow):
    JSONReader(path, "", {}, initNow)
{}

JSONReader::JSONReader(const QString& path, const QString& class_name, std::initializer_list<QString> check, bool initNow):
    m_name(class_name),
    m_path(path),
    m_status(JSONReaderErrors::NotInit),
    m_check(check)
{
    Log(3) << __FUNCTION__ << ", " << __LINE__;
    if(initNow)
    {
        init();
    }
}
QJsonArray& JSONReader::getArray()
{
    Log(3) << __FUNCTION__ << ", " << __LINE__;
    return m_array;
}

const QJsonArray& JSONReader::getArray() const
{
    Log(3) << __FUNCTION__ << ", " << __LINE__;
    return m_array;
}

void JSONReader::update()
{
    Log(3) << __FUNCTION__ << ", " << __LINE__;
    m_object[m_name] = m_array;
}
void JSONReader::setArray(const QJsonArray& newArray)
{
    Log(3) << __FUNCTION__ << ", " << __LINE__;
    m_array = newArray;
}
void JSONReader::setObject(const QJsonObject& in)
{
    Log(3) << __FUNCTION__ << ", " << __LINE__;
    m_object = in;
}

const QJsonObject& JSONReader::getObject() const
{
    Log(3) << __FUNCTION__ << ", " << __LINE__;
    return m_object;
}

const QString& JSONReader::getPath() const
{
    Log(3) << __FUNCTION__ << ", " << __LINE__;
    return m_path;
}

const QString& JSONReader::getName() const
{
    Log(3) << __FUNCTION__ << ", " << __LINE__;
    return m_name;
}

JSONReaderErrors JSONReader::getStatus() const
{
    Log(3) << __FUNCTION__ << ", " << __LINE__;
    return m_status;
}

void JSONReader::clear()
{
    Log(3) << __FUNCTION__ << ", " << __LINE__;
    while(m_array.size() >= 1)
    {
        m_array.pop_front();
    }
}

JSONReaderErrors JSONReader::init()
{
    Log(3) << __FUNCTION__ << ", " << __LINE__ << ", " << m_path.toStdString();
    if(m_status != JSONReaderErrors::None)
    {
        m_status = JSONReaderErrors::NotInit;
        try {
            open();
            if(m_array.size() > 0)
            {
                const auto& ele = m_array.first().toObject();
                for(const auto& x : m_check)
                {
                    Log(3) << "Checking: " << x.toStdString();
                    LOG_THROW_ERROR_IF("First elements does not containt all check values!", !ele.contains(x),
                                       JSONReaderErrors, JSONReaderErrors::PostCheckArrayError);
                }
            }
            m_status = JSONReaderErrors::None;
        }
        catch(const TOOLS::Exceptions<JSONReaderErrors>& er)
        {
           m_status = er.what();
        }
    }
    return m_status;
}

void JSONReader::save()
{
    using namespace TOOLS;
    Log(3) << "save()";
    QFile file(m_path);
    Log(1) << "Opening file: " << m_name.toStdString();
    LOG_THROW_ERROR_IF("Could not open a file!", !file.open(QIODevice::ReadWrite | QIODevice::Text), JSONReaderErrors, JSONReaderErrors::CouldNotOpen);
    file.resize(0);
    if(m_name.size() > 0)
    {
        QJsonObject obj;
        obj[m_name] = getArray();
        file.write(QJsonDocument(obj).toJson());
    }
    else
    {
        file.write(QJsonDocument(m_object).toJson());
    }
    file.close();

}
