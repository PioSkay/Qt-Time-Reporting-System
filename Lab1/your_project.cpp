#include "your_project.h"
#include "ui_your_project.h"
#include "exceptions.h"

your_project::your_project(std::shared_ptr<activities> activity, const QString& name, QWidget *parent) :
    QWidget(parent),
    m_activity(activity),
    m_name(name),
    ui(new Ui::your_project)
{
    Log(Info) << __FUNCTION__ << ", " << __LINE__;
    ui->setupUi(this);
    ui->name->setText(name);
}

your_project::~your_project()
{
    delete ui;
}
