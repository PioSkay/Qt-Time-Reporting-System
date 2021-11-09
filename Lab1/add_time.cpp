#include "add_time.h"
#include "ui_add_time.h"

#include <list>

add_time::add_time(Base* base, QWidget *parent, std::shared_ptr<TOOLS::entries> entr, std::shared_ptr<file> file) :
    QDialog(parent),
    m_base(base),
    m_entr(entr),
    m_file(file),
    ui(new Ui::add_time)
{
    ui->setupUi(this);
    const auto& array = base->getActivities().getArray();
    ui->amount->setValidator(new QIntValidator(1, 10000, this));
    ui->date->setDate(m_base->getTime());
    ui->date->setDisplayFormat("dd-MM-yyyy");
    bool subactivSet = false;
    foreach(auto& ele, array)
    {
        if(ele.get()->active)
        {
            if(subactivSet == false)
            {
                setSubactivity(ele.get()->code);
                subactivSet = true;
            }
            ui->project->addItem(ele.get()->code);
        }

    }
    if(entr.get() != nullptr)
    {
        bool isSet = false;
        for(int i = 0; i < ui->project->count(); i++)
        {
            if(ui->project->itemText(i) == entr->code)
            {
                ui->project->setCurrentIndex(i);
                isSet = true;
                break;
            }
        }
        if(!isSet)
        {
            ui->project->addItem(entr->code);
            ui->project->setCurrentIndex(ui->project->count()-1);
        }
        ui->date->setDate(entr->date);
        setSubactivity(entr->code, entr->subcode);
        ui->amount->setText(QString::number(entr->time));
        ui->description->setText(entr->description);
    }
    connect(ui->project, SIGNAL(currentTextChanged(const QString&)), this, SLOT(on_project_currentIndexChanged(const QString &)));
}

void add_time::setSubactivity(const QString& project, const QString& subactivity)
{
    Log(3) << __FUNCTION__ << " " << __LINE__;
    const auto& act = m_base->getActivities().getArray();
    foreach(const auto& ele, act)
    {
        if(ele.get()->code == project)
        {
            Log(3) << __FUNCTION__ << " " << ele.get()->code.toStdString();
            current = ele;
            ui->subactivity1->clear();
            ui->subactivity1->addItem("");
            const auto& array = ele.get()->subactivities;
            for(const auto& x : array)
            {
                ui->subactivity1->addItem(x.second);
                if(subactivity.size() != 0 && subactivity == x.second)
                {
                    ui->subactivity1->setCurrentText(x.second);
                }
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
    Log(3) << __FUNCTION__ << ", " << __LINE__ << ", " << arg1.toStdString();
    setSubactivity(arg1);
}

void add_time::on_log_released()
{
    try{
        THROW_DEFAULT(ui->amount->text().size() == 0, "Please fill the time field!");
        if(m_entr.get() != nullptr)
        {
            m_file->removeEntrie(m_entr);
        }
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
        m_base->updateTotalTime();
        m_base->update_temp();
        close();
    }
    catch(DEFAULT_CATCH x)
    {
        Log(Error) << x.what();
        ui->error->setText(x.what());
    }
}

