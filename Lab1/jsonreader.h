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
    JSONReader(const QString& path = "", const QString& class_name = "", std::initializer_list<QString> check = {}, bool initNow = true);
    QJsonArray& getArray();
    void update()
    {
        m_object[m_name] = m_array;
    }
    void setArray(const QJsonArray& newArray)
    {
        m_array = newArray;
    }
    const QJsonArray& getArray() const;
    const QJsonObject& getObject() const
    {
        return m_object;
    }
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
    template<typename Type, typename What, typename Where>
    static int setup(What& what, Where& where)
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
}
#endif // JSONREADER_H
