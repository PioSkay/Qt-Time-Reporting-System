#include "view_tempo.h"
#include "ui_view_tempo.h"

view_tempo::view_tempo(std::shared_ptr<TOOLS::entries> entr, QWidget *parent) :
    QDialog(parent),
    m_entr(entr),
    ui(new Ui::view_tempo)
{
    ui->setupUi(this);
    THROW_DEFAULT(entr.get() == nullptr, "Incorrect object");
    ui->project->setText(entr->code);
    ui->date->setText(entr->date.toString("dd/MM/yyyy"));
    ui->time->setText(QString::number(entr->time));
    ui->subcode->setText(entr->subcode);
    ui->description->setText(entr->description);
}

view_tempo::~view_tempo()
{
    delete ui;
}

void view_tempo::on_pushButton_released()
{
    close();
}

