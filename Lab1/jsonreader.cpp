#include "jsonreader.h"
void JSONReader::open()
{
    using namespace TOOLS;
    Log(3) << "open()";
    QFile file(m_path);
    Log(1) << "Opening file: " << m_name.toStdString();
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        Log(Error) << "Could not open a file!";
        throw Exceptions<JSONReaderErrors>(JSONReaderErrors::CouldNotOpen);
    }
    QByteArray jsonData = file.readAll();
    file.close();
    QJsonDocument document = QJsonDocument::fromJson(jsonData);
    if(document.isNull())
    {
        Log(Error) << "Could not create a document!";
        throw Exceptions<JSONReaderErrors>(JSONReaderErrors::CouldNotCreateDocument);
    }
    if(!document.isObject())
    {
        Log(Error) << "Document is not an object!";
        throw Exceptions<JSONReaderErrors>(JSONReaderErrors::DocumentInNotAnObject);
    }
    QJsonObject object = document.object();
    QJsonValue value = object.value(m_name);
    if(value.isUndefined())
    {
        Log(Error) << "Could not find an class name in the JSON file";
        throw Exceptions<JSONReaderErrors>(JSONReaderErrors::CouldNotFindName);
    }
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
    if(!file.open(QIODevice::ReadWrite | QIODevice::Text))
    {
        Log(Error) << "Could not open a file!";
        throw Exceptions<JSONReaderErrors>(JSONReaderErrors::CouldNotOpen);
    }
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
}
