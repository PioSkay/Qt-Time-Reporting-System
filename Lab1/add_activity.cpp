#include "add_activity.h"
#include "ui_add_activity.h"
#include "subactivities_container.h"
#include "exceptions.h"
#include "mainwindow.h"
#include<QIntValidator>

add_activity::add_activity(Base* base, QWidget *parent) :
    QDialog(parent),
    m_base(base),
    ui(new Ui::add_activity)
{
    ui->setupUi(this);
    connect(ui->create_button, &QPushButton::released, this, &add_activity::create_button);
    connect(ui->add_button, &QPushButton::released, this, &add_activity::add_button);
    init();
}

void add_activity::init()
{
    Log(Info) << __FUNCTION__ << " " << __LINE__;
    QVBoxLayout* layout = new QVBoxLayout();
    ui->subactivities->widget()->setLayout(layout);
    ui->project_time_budge->setValidator(new QIntValidator(-1, 1000000, this));
}

void add_activity::create_button()
{
    Log(Info) << __FUNCTION__ << " " << __LINE__;
    try {
        std::list<std::pair<QString, QString>> sub;
        for (int i = 0; i < ui->subactivities->widget()->layout()->count(); ++i) {
            auto item = ui->subactivities->widget()->layout()->itemAt(i);
            auto itemWidget = dynamic_cast<subactivities_container*>(item->widget());
            sub.push_back(std::make_pair(itemWidget->getMaster(), itemWidget->getSecond()));
        }
        m_base->addActivityToMainScreen(
                    m_base->getActivities().addActivities(activities(
                                        ui->project_code->text(),
                                        m_base->getUser().username(),
                                        ui->project_name->text(),
                                        ui->project_time_budge->text().toInt(),
                                        true,
                                        sub)));
        close();
    }  catch (DEFAULT_CATCH x) {
        errorMsg(x.what());
    }
}

void add_activity::add_button()
{
    Log(Info) << __FUNCTION__ << " " << __LINE__;
    if(ui->sub_second->text().size() == 0)
    {
        errorMsg("Subactivity is empty!");
        return;
    }
    subactivities_container* x = new subactivities_container("code", ui->sub_second->text(), this);
    for (int i = 0; i < ui->subactivities->widget()->layout()->count(); ++i) {
        auto item = ui->subactivities->widget()->layout()->itemAt(i);
        auto itemWidget = dynamic_cast<subactivities_container*>(item->widget());
        if(*itemWidget == *x)
        {
            errorMsg("Subactivity already exists!");
            delete x;
            return;
        }
    }
    ui->subactivities->widget()->layout()->addWidget(x);
}

void add_activity::removeItem(QWidget* in)
{
    Log(Info) << __FUNCTION__ << " " << __LINE__;
    if(in)
    {
        ui->subactivities->widget()->layout()->removeWidget(in);
        delete in;
    }
}

void add_activity::errorMsg(const QString& in)
{
    Log(Error) << in.toStdString();
    ui->activity_error->setText(in);
}

std::shared_ptr<activities> add_activity::getActivity()
{
    return m_created;
}

add_activity::~add_activity()
{
    delete ui;
}
