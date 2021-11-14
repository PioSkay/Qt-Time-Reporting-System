#ifndef FILE_PIPELINE_H
#define FILE_PIPELINE_H

#include"json_base.h"
#include"jsonreader.h"
#include"entries.h"
#include"accepted.h"

enum class fileError
{
    CouldNotFindFrozen,
    CouldNotFindEntries,
    CouldNotFindAccepted,
    IncorrectFileName
};

struct file_name
{
    QString m_name;
    int year;
    int month;
    bool isInit;
    file_name();
    file_name(const QString& m_path);
    file_name(const file_name& x);
    file_name(const QString& in, int y, int m);
    bool operator==(const file_name& in) const;
    QString toString() const;
};

class file: public json_base
{
    bool isModified;
    JSONReader m_json;
    bool isFrozen;
    file_name m_data;
    std::list<std::shared_ptr<TOOLS::entries>> formated_entries;
    std::list<std::shared_ptr<TOOLS::accepted>> formated_accepted;
    void initExisting();
    template<typename What, typename Where>
    bool add(Where& where, const QJsonObject& in);
public:
    file(const QString& path, const file_name& name, bool create = false);
    QJsonObject toJSONObject() const override;
    bool addEntries(const QJsonObject& in);
    bool addAccepted(const QJsonObject& in);
    bool addEntries(const TOOLS::entries& in);
    bool addAccepted(const TOOLS::accepted& in);
    bool removeEntrie(std::shared_ptr<TOOLS::entries> in);
    bool isSubmited() const;
    void modifyFile();
    void submitFile();
    std::list<std::shared_ptr<TOOLS::entries>> getEntries();
    std::list<std::shared_ptr<TOOLS::accepted>> getAccepted();
    bool operator==(const file& in) const;
    bool operator==(const file_name& in) const;
    const QString& owner() const;
    ~file();
};

template<typename What, typename Where>
bool file::add(Where& where, const QJsonObject& in)
{
    try {
        What obj(in);
        where.emplace_back(std::make_shared<What>(std::move(obj)));
    }  catch (DEFAULT_CATCH x) {
        Log(Error) << x.what();
        return false;
    }
    isModified = true;
    return true;
}

#endif // FILE_PIPELINE_H
