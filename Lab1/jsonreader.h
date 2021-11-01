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
#include "nonInitializable.h"


enum class JSONReaderErrors
{
    None,
    NotInit,
    CouldNotOpen,
    CouldNotCreateDocument,
    DocumentInNotAnObject,
    PostCheckArrayError,
    CouldNotFindName
};
enum class JSONSaveErrors
{
    ObjectNotInitialized
};

class JSONReader
{
    QJsonArray m_array;
    QJsonObject m_object;
    QString m_name;
    QString m_path;
    JSONReaderErrors m_status;
    std::list<QString> m_check;
    void open();
public:
    JSONReader(const QString& path, bool initNow = true);
    JSONReader(const QString& path, const QString& class_name, std::initializer_list<QString> check = {}, bool initNow = true);
    QJsonArray& getArray();
    void update();
    void setArray(const QJsonArray& newArray);
    void setObject(const QJsonObject& in);
    const QJsonArray& getArray() const;
    const QJsonObject& getObject() const;
    const QString& getName() const;
    const QString& getPath() const;
    JSONReaderErrors getStatus() const;
    JSONReaderErrors init();
    void clear();
    void save();
    ~JSONReader() = default;
};
namespace TOOLS
{
    template<typename Type, typename What, typename Where>
    inline int setup(What& what, Where& where)
    {
        int problems = 0;
        for(const auto& element : what)
        {
            const auto& obj = element.toObject();
            try {
                Type activity(obj);
                Log(10) << activity;
                where.emplace_back(std::make_shared<Type>(std::move(activity)));
            } catch(DEFAULT_CATCH x) {
                Log(Error) << "There was a problem during activity creation: " << x.what();
                ++problems;
                continue;
            }
        }
        return problems;
    }
    template<typename What>
    inline QJsonArray toArray(const std::list<std::shared_ptr<What>>& in)
    {
        QJsonArray array;
        for(const auto& ele : in)
        {
            const What& x = *ele.get();
            array.push_back(x.toJSONObject());
        }
        return array;
    }
}
#endif // JSONREADER_H
