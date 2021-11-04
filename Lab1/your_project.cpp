#include "your_project.h"
#include "ui_your_project.h"
#include "exceptions.h"

your_project::your_project(std::shared_ptr<activities> activity, QWidget *parent) :
    QWidget(parent),
    m_activity(activity),
    ui(new Ui::your_project)
{
    Log(Info) << __FUNCTION__ << ", " << __LINE__;
    ui->setupUi(this);
    activity ? m_name = activity->name : m_name = "";
    ui->name->setText(m_name);
}

your_project::~your_project()
{
    delete ui;
}
