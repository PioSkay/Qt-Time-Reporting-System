#ifndef PROJECT_PENDING_REQUEST_H
#define PROJECT_PENDING_REQUEST_H

#include <QWidget>
#include <functional>

#include "entries.h"
#include "file_pipeline.h"

namespace Ui {
class project_pending_request;
}

class project_pending_request : public QWidget
{
    Q_OBJECT
    std::shared_ptr<TOOLS::entries> m_entrie;
    std::shared_ptr<file> m_file;
    std::function<void(int, int)> m_todo;
public:
    explicit project_pending_request(std::shared_ptr<TOOLS::entries> entrie,
                                     std::shared_ptr<file> file,
                                     std::function<void(int, int)> todo,
                                     QWidget *parent = nullptr);
    ~project_pending_request();

private slots:
    void on_adjust_released();
    void on_accept_released();

signals:
    void sendRemoveItem(QWidget* in);

private:
    Ui::project_pending_request *ui;
};

#endif // PROJECT_PENDING_REQUEST_H
