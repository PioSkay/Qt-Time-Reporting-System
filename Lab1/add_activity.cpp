#include "add_activity.h"
#include "ui_add_activity.h"
#include<QGroupBox>

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
    QVBoxLayout* layout = new QVBoxLayout();
    ui->subactivities->widget()->setLayout(layout);
}

void add_activity::create_button()
{

}

void add_activity::add_button()
{
    Log(Info) << __FUNCTION__ << " " << __LINE__;
    QGroupBox *sale = new QGroupBox();
    sale->setTitle("minha venda");
    QPushButton* x = new QPushButton();
    x->setText("ssss, ssss");
    x->setStyleSheet("QPushButton:focus:pressed {background-color: red;}");
    ui->subactivities->widget()->layout()->addWidget(x);
}

add_activity::~add_activity()
{
    delete ui;
}
