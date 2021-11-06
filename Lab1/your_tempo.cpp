#include "your_tempo.h"
#include "ui_your_tempo.h"
#include "error_msg.h"

your_tempo::your_tempo(QDate date, std::shared_ptr<entries> file, bool frozen, QWidget *parent) :
    QDialog(parent),
    m_date(date),
    m_file(file),
    isFrozen(frozen),
    ui(new Ui::your_tempo)
{
    ui->setupUi(this);
    ui->project->setText(file.get()->code);
    ui->time->setText(QString::number(file.get()->time));
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

