#include "add_time.h"
#include "ui_add_time.h"

#include <list>

add_time::add_time(Base* base, QWidget *parent) :
    QDialog(parent),
    m_base(base),
    ui(new Ui::add_time)
{
    ui->setupUi(this);
    const auto& array = base->getActivities().getArray();
    setSubactivity(array.front().get()->code);
    ui->amount->setValidator(new QIntValidator(1, 10000, this));
    ui->date->setDate(m_base->getTime());
    ui->date->setDisplayFormat("dd-MM-yyyy");
    foreach(auto& ele, array)
    {
        if(ele.get()->active)
            ui->project->addItem(ele.get()->code);
    }
}

void add_time::setSubactivity(const QString& project)
{
    const auto& act = m_base->getActivities().getArray();
    foreach(const auto& ele, act)
    {
        if(ele.get()->code == project)
        {
            current = ele;
            ui->subactivity1->clear();
            ui->subactivity1->addItem("");
            const auto& array = ele.get()->subactivities;
            for(const auto& x : array)
            {
                ui->subactivity1->addItem(x.second);
            }
            break;
        }
    }
}

add_time::~add_time()
{
    delete ui;
}
void add_time::on_project_currentIndexChanged(const QString &arg1)
{
    Log(Error) << __FUNCTION__ << ", " << __LINE__ << ", " << arg1.toStdString();
    setSubactivity(arg1);
}

void add_time::on_log_released()
{
    try{
        THROW_DEFAULT(ui->amount->text().size() == 0, "Please fill the time field!")
        TOOLS::entries x(ui->date->date(),
                  ui->project->currentText(),
                  ui->subactivity1->currentText(),
                  ui->amount->text().toInt(),
                  ui->description->toPlainText());
        std::shared_ptr<file> m_file = m_base->getFiles()->add_or_find(m_base->getUser().username(),
                                                                       ui->date->date().year(),
                                                                       ui->date->date().month());
        THROW_DEFAULT(!m_file->addEntries(x),
                      "This month is submitted!");
        m_base->update_temp();
        close();
    }
    catch(DEFAULT_CATCH x)
    {
        Log(Error) << x.what();
        ui->error->setText(x.what());
    }
}

