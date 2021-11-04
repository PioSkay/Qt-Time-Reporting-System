#include "subactivities_container.h"
#include "ui_subactivities_container.h"
#include"add_activity.h"

subactivities_container::subactivities_container(const QString& master, const QString& second, QWidget *parent):
    QWidget(parent),
    m_master(master),
    m_second(second),
    ui(new Ui::subactivities_container)
{
    ui->setupUi(this);
    ui->master->setText(master);
    ui->second->setText(second);
    connect(ui->remove, &QPushButton::released, this, &subactivities_container::on_toolButton_clicked);
    connect(this, SIGNAL(sendRemoveItem(QWidget*)), parent, SLOT(removeItem(QWidget*)));
}

const QString& subactivities_container::getMaster() const
{
    return m_master;
}

const QString& subactivities_container::getSecond() const
{
    return m_second;
}

bool subactivities_container::operator==(const subactivities_container& in) const
{
    return m_master == in.m_master && m_second == in.m_second;
}

void subactivities_container::on_toolButton_clicked()
{
    emit sendRemoveItem(this);
}

subactivities_container::~subactivities_container()
{
    delete ui;
}
