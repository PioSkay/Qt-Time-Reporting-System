#include "jsonreader.h"
void JSONReader::open()
{
    using namespace TOOLS;
    Log(3) << "open()";
    QFile file(m_path);
    Log(1) << "Opening file: " << m_name.toStdString();
    LOG_THROW_ERROR_IF("Could not open a file!", !file.open(QIODevice::ReadOnly | QIODevice::Text), JSONReaderErrors, JSONReaderErrors::CouldNotOpen);
    QByteArray jsonData = file.readAll();
    file.close();
    QJsonDocument document = QJsonDocument::fromJson(jsonData);
    LOG_THROW_ERROR_IF("Could not create a document!", document.isNull(), JSONReaderErrors, JSONReaderErrors::CouldNotCreateDocument);
    LOG_THROW_ERROR_IF("Document is not an object!", !document.isObject(), JSONReaderErrors, JSONReaderErrors::DocumentInNotAnObject);
    QJsonObject object = document.object();
    QJsonValue value = object.value(m_name);
    LOG_THROW_ERROR_IF("Could not find an class name in the JSON file", value.isUndefined(), JSONReaderErrors, JSONReaderErrors::CouldNotFindName);
    m_array = value.toArray();
    qDebug() << "Reading array: " << m_array;
}

JSONReader::JSONReader(const QString& path, const QString& class_name):
    m_name(class_name),
    m_path(path),
    m_status(JSONReaderErrors::None)
{
    try {
        open();
    }
    catch(const TOOLS::Exceptions<JSONReaderErrors>& er)
    {
       m_status = er.what();
    }
}
QJsonArray& JSONReader::getArray()
{
    Log(3) << "getArray()";
    return m_array;
}

const QJsonArray& JSONReader::getArray() const
{
    Log(3) << "getArray()";
    return m_array;
}

const QString& JSONReader::getPath() const
{
    Log(3) << "getPath()";
    return m_path;
}

const QString& JSONReader::getName() const
{
    Log(3) << "getName()";
    return m_name;
}

void JSONReader::clear()
{
    Log(3) << "clear()";
    while(m_array.size() >= 1)
    {
        m_array.pop_front();
    }
}

void JSONReader::save()
{
    using namespace TOOLS;
    Log(3) << "save()";
    QFile file(m_path);
    Log(1) << "Opening file: " << m_name.toStdString();
    LOG_THROW_ERROR_IF("Could not open a file!", !file.open(QIODevice::ReadWrite | QIODevice::Text), JSONReaderErrors, JSONReaderErrors::CouldNotOpen);
    QJsonObject obj;
    obj[m_name] = getArray();
    file.write(QJsonDocument(obj).toJson());
    file.close();
}

namespace TOOLS
{
    bool check(const QJsonArray& json, std::vector<QString> array)
    {
        for(const auto& ele: json)
        {
            for(const auto& string : array)
            {
                if(!ele.toObject().contains(string))
                {
                    return false;
                }
            }
        }
        return true;
    }
    QJsonObject* SaveJSON::m_obj = nullptr;
    QString SaveJSON::m_path = "";
    bool SaveJSON::info = false;

}
