#include "your_project.h"
#include "ui_your_project.h"
#include "exceptions.h"
#include "project_reports.h"

your_project::your_project(std::shared_ptr<TOOLS::activities> activity, Base* base, QWidget *parent) :
    QWidget(parent),
    m_activity(activity),
    m_base(base),
    ui(new Ui::your_project)
{
    Log(3) << __FUNCTION__ << ", " << __LINE__;
    ui->setupUi(this);
    THROW_DEFAULT(activity.get() == nullptr, "Activity does not exist");
    update();
}

your_project::~your_project()
{
    Log(3) << __FUNCTION__ << ", " << __LINE__;
    delete ui;
}

void your_project::update()
{
    Log(3) << __FUNCTION__ << ", " << __LINE__;
    ui->code->setText(m_activity->code);
    ui->name->setText(m_activity->name);
    ui->status->setText(m_activity->active == true ? "Open" : "Closed");
}

void your_project::on_reports_released()
{
    Log(3) << __FUNCTION__ << ", " << __LINE__;
    project_reports report(m_activity, m_base, std::bind(&your_project::update, this));
    report.exec();
}
