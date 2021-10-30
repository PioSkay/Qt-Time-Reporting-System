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
    QString m_name;
    QString m_path;
    JSONReaderErrors m_status;
    std::list<QString> m_check;
    void open();
public:
    JSONReader(const QString& path = "", const QString& class_name = "", std::initializer_list<QString> check = {}, bool initNow = true);
    QJsonArray& getArray();
    const QJsonArray& getArray() const;
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
    bool check(const QJsonArray& json, std::vector<QString> array);
    class SaveJSON: private NonInitializable
    {
    private:
        static QJsonObject* m_obj;
        static QString m_path;
        static bool info;
        static void save();
        static void add_JSONReader(const JSONReader& obj);
    public:
        template <typename First, typename ... Rest>
        static void save(First&& first, Rest&& ... rest);
        template<typename ...Args>
        static void save(Args&& ... args);
    };

    template <typename First, typename ... Rest>
    void SaveJSON::save(First&& first, Rest&& ... rest)
    {
        add_JSONReader(std::forward<First>(first));
        save(std::forward<Rest>(rest) ...);
    }

    template<typename ...Args>
    void SaveJSON::save(Args&& ... args)
    {
        save(std::forward<Args>(args) ...);
    }
}
#endif // JSONREADER_H
