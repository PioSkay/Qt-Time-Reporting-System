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
    const QJsonArray& getArray() const;
    const QString& getName() const;
    const QString& getPath() const;
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
        static void save()
        {
            Log(1) << "Saving file to: " << m_path.toStdString();
            QFile file(m_path);
            LOG_THROW_ERROR_IF("Could not open a file!", !file.open(QIODevice::ReadWrite | QIODevice::Text), JSONReaderErrors, JSONReaderErrors::CouldNotOpen);
            file.write(QJsonDocument(*m_obj).toJson());
            file.close();
            m_path = "";
            info = false;
            if(m_obj != nullptr)
            {
                delete m_obj;
            }
        }
        static void add_JSONReader(const JSONReader& obj)
        {
            if(m_obj == nullptr)
            {
                m_obj = new QJsonObject();
            }
            if(info == false && m_path.size() != 0)
            {
                if(m_path != obj.getName())
                {
                    Log(Info) << "JSONReader has a different path. The file will be saved in the path of the top file.";
                    info = true;
                }
            }
            else if(m_path.size() == 0)
            {
                m_path = obj.getPath();
            }
            (*m_obj)[obj.getName()] = obj.getArray();
        }
    public:
        template <typename First, typename ... Rest>
        static void save(First&& first, Rest&& ... rest)
        {
            add_JSONReader(std::forward<First>(first));
            save(std::forward<Rest>(rest) ...);
        }
        template<typename ...Args>
        static void save(Args&& ... args)
        {
            save(std::forward<Args>(args) ...);
        }
    };
}
#endif // JSONREADER_H
