#include "files_pipeline.h"

files_pipeline::files_pipeline(const std::list<QString>& usernames):
    m_usernames(usernames)
{
    Log(3) << __FUNCTION__ << ", " << __LINE__;
    QDir directory;
    QStringList images = directory.entryList(QStringList() << "*.json", QDir::Files);
    foreach(QString dir, images)
    {
        Log(3) << "Directory found: " << dir.toStdString();
        for(const auto& x : m_usernames)
        {
            if(dir.contains(x))
            {
                try{
                    file_name file_n(dir);
                    m_files.emplace_back(std::make_shared<file>(dir, file_n));
                }
                catch(const TOOLS::Exceptions<fileError>& x)
                {
                    Log(Error) << __FUNCTION__;
                    continue;
                }
            }
        }
    }
}

std::shared_ptr<file> files_pipeline::add(const file_name& dir)
{
    m_files.emplace_back(std::make_shared<file>(dir.toString(), dir, true));
    return m_files.back();
}

std::shared_ptr<file> files_pipeline::add_or_find(const QString& user, int year, int month)
{
    std::shared_ptr<file> ele = find(user, year, month);
    if(ele.get() == nullptr)
    {
        return add(file_name(user, year, month));
    }
    else
    {
        return ele;
    }
}

std::shared_ptr<file> files_pipeline::find(const QString& user, int year, int month)
{
    file_name name(user, year, month);
    for(std::shared_ptr<file> x: m_files)
    {
        if(*x.get() == name)
        {
            return x;
        }
    }
    return nullptr;
}

std::list<std::shared_ptr<file>> files_pipeline::getFileList()
{
    return m_files;
}
