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
    activity ? m_name = activity->name : m_name = "";
    ui->name->setText(m_name);
}

your_project::~your_project()
{
    delete ui;
}

void your_project::on_pushButton_2_released()
{
    project_reports report(m_activity, m_base);
    report.exec();
}

