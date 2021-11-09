#include "project_reports.h"
#include "ui_project_reports.h"
#include "project_pending_request.h"
#include "accepted.h"

project_reports::project_reports(std::shared_ptr<TOOLS::activities> activity, Base* base, std::function<void()> fun, QWidget *parent) :
    QDialog(parent),
    m_base(base),
    m_activity(activity),
    pending_time(0),
    accepted_time(0),
    notifyParent(fun),
    ui(new Ui::project_reports)
{
    Log(3) << __FUNCTION__ << " " << __LINE__;
    ui->setupUi(this);
    if(!activity.get()->active)
    {
        ui->frame_5->layout()->removeWidget(ui->close_project);
        delete ui->close_project;
    }
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
                pending_data.emplace_back(new project_pending_request(entries,
                                                                           x,
                                                                           [&](int x, int y){
                                                                                pending_time += x;
                                                                                accepted_time += y;
                                                                                updateTime();
                                                                                m_base->updateTotalTime();
                                                                                m_base->update_temp();
                                                                            },
                                                                            this));
                if(!activity.get()->active)
                {
                    pending_data.back()->disable();
                }
                pending_time += entries->time;
                ui->pending->widget()->layout()->addWidget(pending_data.back());
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
    Log(3) << __FUNCTION__ << " " << __LINE__;
    if(item)
    {
        ui->pending->widget()->layout()->removeWidget(item);
        delete item;
    }
}
void project_reports::updateTime()
{
    Log(3) << __FUNCTION__ << " " << __LINE__;
    ui->pending_time->setText(QString::number(pending_time));
    ui->accepted_time->setText(QString::number(accepted_time));
}

project_reports::~project_reports()
{
    Log(3) << __FUNCTION__ << " " << __LINE__;
    delete ui;
}

void project_reports::on_pushButton_2_released()
{
    Log(3) << __FUNCTION__ << " " << __LINE__;
    close();
}


void project_reports::on_close_project_released()
{
    Log(3) << __FUNCTION__ << " " << __LINE__;
    m_activity->active = false;
    m_base->getActivities().modify();
    notifyParent();
    ui->frame_5->layout()->removeWidget(ui->close_project);
    delete ui->close_project;
    for(auto& x : pending_data)
    {
        x->disable();
    }
}

