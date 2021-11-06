#include "your_tempo.h"
#include "ui_your_tempo.h"
#include "error_msg.h"

your_tempo::your_tempo(QDate date, std::shared_ptr<TOOLS::entries> entr, std::shared_ptr<file> file, bool frozen, QWidget *parent) :
    QDialog(parent),
    m_date(date),
    m_entrie(entr),
    m_file(file),
    isFrozen(frozen),
    ui(new Ui::your_tempo)
{
    ui->setupUi(this);
    ui->project->setText(entr.get()->code);
    ui->time->setText(QString::number(entr.get()->time));
}

your_tempo::~your_tempo()
{
    delete ui;
}

void your_tempo::on_pushButton_released()
{
    if(isFrozen)
    {
        error_msg error("This month is already submitted!");
        error.exec();
    }
    else
    {
        Log(Info) << "TODO";
    }
}


void your_tempo::on_edit_released()
{
    m_file->modifyFile();

}

