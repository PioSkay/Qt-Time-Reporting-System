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
    QString m_name;
    QString m_path;
    JSONReaderErrors m_status;
    void open();
public:
    JSONReader(const QString& path = "", const QString& class_name = "");
    QJsonArray& getArray();
    void clear();
    void save();
    ~JSONReader() = default;
};
namespace TOOLS
{
    bool check(const QJsonArray& json, std::vector<QString> array);
}
#endif // JSONREADER_H
