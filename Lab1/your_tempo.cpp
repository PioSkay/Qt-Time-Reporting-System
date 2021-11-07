#include "your_tempo.h"
#include "ui_your_tempo.h"
#include "error_msg.h"
#include "view_tempo.h"
#include "add_time.h"

your_tempo::your_tempo(Base* base,
                       std::shared_ptr<TOOLS::entries> entr,
                       std::shared_ptr<file> file,
                       bool frozen,
                       QWidget *parent) :
    QDialog(parent),
    m_base(base),
    m_entrie(entr),
    m_file(file),
    isFrozen(frozen),
    ui(new Ui::your_tempo)
{
    ui->setupUi(this);
    if(m_entrie.get() != nullptr)
    {
        ui->project->setText(entr.get()->code);
        ui->time->setText(QString::number(entr.get()->time));
    } else {
        THROW_DEFAULT(true, "Incorrect input parameters in ");
    }
    if(isFrozen)
    {
        ui->gridLayout->removeWidget(ui->edit);
        delete ui->edit;
    }
}

your_tempo::~your_tempo()
{
    delete ui;
}



void your_tempo::on_edit_released()
{
    add_time time(m_base, this, m_entrie, m_file);
    time.exec();
}


void your_tempo::on_view_released()
{
    view_tempo tempo(m_entrie);
    tempo.exec();
}

