#ifndef JSONREADER_H
#define JSONREADER_H

#include <QFile>
#include <QByteArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include <string>
#include "Log.h"
#include "exceptions.h"

enum class JSONReaderErrors
{
    None,
    CouldNotOpen,
    CouldNotCreateDocument,
    DocumentInNotAnObject,
    CouldNotFindName
};

class JSONReader
{
    QJsonArray m_array;
    const QString& m_name;
    const QString& m_path;
    JSONReaderErrors m_status;
    void open()
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
    void save()
    {
        Log(3) << "save()";
    }
public:
    JSONReader(const QString& path = "", const QString& class_name = ""):
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
    QJsonArray& getArray()
    {
        return m_array;
    }
    ~JSONReader()
    {
        save();
    }
};

#endif // JSONREADER_H
