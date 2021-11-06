#include "project_reports.h"
#include "ui_project_reports.h"
#include "project_pending_request.h"
#include "accepted.h"

project_reports::project_reports(std::shared_ptr<TOOLS::activities> activity, Base* base, QWidget *parent) :
    QDialog(parent),
    m_base(base),
    m_activity(activity),
    pending_time(0),
    accepted_time(0),
    ui(new Ui::project_reports)
{
    ui->setupUi(this);
    QVBoxLayout* layout = new QVBoxLayout();
    ui->pending->widget()->setLayout(layout);

    ui->code->setText(activity->code);
    ui->name->setText(activity->name);
    ui->manager->setText(base->getUser().username());
    ui->time_budget->setText(QString::number(activity->budget));
    std::shared_ptr<files_pipeline> files = base->getFiles();
    THROW_DEFAULT(files.get() == nullptr, "Files are a nullptr!");
    foreach(std::shared_ptr<file> x, files.get()->getFileList())
    {
        THROW_DEFAULT(files.get() == nullptr, "Files are a nullptr!");
        std::list<std::shared_ptr<TOOLS::entries>> ent_list = x.get()->getEntries();
        foreach(std::shared_ptr<TOOLS::entries> entries, ent_list)
        {
            if(entries->code == activity->code)
            {
                project_pending_request* reg = new project_pending_request(entries,
                                                                           x,
                                                                           [this](int x, int y){
                                                                                pending_time += x;
                                                                                accepted_time += y;
                                                                                updateTime();
                                                                            },
                                                                            this);
                pending_time += entries->time;
                ui->pending->widget()->layout()->addWidget(reg);
            }
        }
        std::list<std::shared_ptr<TOOLS::accepted>> acc_list = x.get()->getAccepted();
        foreach(std::shared_ptr<TOOLS::accepted> acce, acc_list)
        {
            if(acce->code == activity->code)
            {
                accepted_time += acce->time;
            }
        }
    }
    updateTime();
}
void project_reports::removeItem(QWidget* item)
{
    Log(Info) << __FUNCTION__ << " " << __LINE__;
    if(item)
    {
        ui->pending->widget()->layout()->removeWidget(item);
        delete item;
    }
}
void project_reports::updateTime()
{
    ui->pending_time->setText(QString::number(pending_time));
    ui->accepted_time->setText(QString::number(accepted_time));
}

project_reports::~project_reports()
{
    delete ui;
}

void project_reports::on_pushButton_2_released()
{
    close();
}

