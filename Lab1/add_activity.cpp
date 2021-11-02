#include "add_activity.h"
#include "ui_add_activity.h"
#include "subactivities_container.h"

int add_activity::ID = 0;

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
    subactivities_container* x = new subactivities_container(ID++, ui->sub_master->text(), ui->sub_second->text(), this);
    ui->subactivities->widget()->layout()->addWidget(x);
}

void add_activity::removeItem(int ID)
{
    Log(Info) << __FUNCTION__ << " " << __LINE__;
    for (int i = 0; i < ui->subactivities->widget()->layout()->count(); ++i) {
        auto item = ui->subactivities->widget()->layout()->itemAt(i);
        auto itemWidget = dynamic_cast<subactivities_container*>(item->widget());
        if (itemWidget && itemWidget->getID() == ID){
            ui->subactivities->widget()->layout()->removeItem(item);
            itemWidget->close();
            delete item;
            break;
        }
    }
}

add_activity::~add_activity()
{
    delete ui;
}
