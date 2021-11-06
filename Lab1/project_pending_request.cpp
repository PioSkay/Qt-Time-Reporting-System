#include "project_pending_request.h"
#include "ui_project_pending_request.h"
#include "exceptions.h"
#include "adjust_window.h"

project_pending_request::project_pending_request(std::shared_ptr<TOOLS::entries> entrie,
                                                 std::shared_ptr<file> file,
                                                 std::function<void(int, int)> todo,
                                                 QWidget *parent) :
    QWidget(parent),
    m_entrie(entrie),
    m_file(file),
    m_todo(todo),
    ui(new Ui::project_pending_request)
{
    ui->setupUi(this);
    THROW_DEFAULT(entrie.get() == nullptr, "Entrie is a nullptr");
    ui->date->setText(entrie->date.toString());
    ui->time->setText(QString::number(entrie->time));
    ui->subcode->setText(entrie->subcode);
    ui->description->setText(entrie->description);
    ui->reporter->setText(file->owner());
    connect(this, SIGNAL(sendRemoveItem(QWidget*)), parent, SLOT(removeItem(QWidget*)));
}

project_pending_request::~project_pending_request()
{
    delete ui;
}

void project_pending_request::on_adjust_released()
{
    adjust_window window(m_entrie->time);
    window.exec();
    if(window.adjusted())
    {
        ui->time->setText(QString::number(m_entrie->time));
        m_file->modifyFile();
        m_todo(window.after - window.before, 0);
    }
}


void project_pending_request::on_accept_released()
{
    m_todo(-ui->time->text().toInt(), ui->time->text().toInt());
    TOOLS::accepted acc(m_entrie->code, m_entrie->time);
    m_file->removeEntrie(m_entrie);
    m_file->addAccepted(acc);
    emit sendRemoveItem(this);
}

