#ifndef FILES_PIPELINE_H
#define FILES_PIPELINE_H

#include"Log.h"
#include"file_pipeline.h"
#include"exceptions.h"

#include <QDir>

class files_pipeline
{
    const std::list<QString>& m_usernames;
    std::list<std::shared_ptr<file>> m_files;
public:
    files_pipeline(const std::list<QString>& usernames);
    std::shared_ptr<file> add(const file_name& dir);
    std::shared_ptr<file> add_or_find(const QString& user, int year, int month);
    std::shared_ptr<file> find(const QString& user, int year, int month);
    std::list<std::shared_ptr<file>> getFileList();
};

#endif // FILES_PIPELINE_H
