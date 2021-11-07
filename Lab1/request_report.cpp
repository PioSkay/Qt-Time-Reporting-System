#include "request_report.h"
#include "ui_request_report.h"

request_report::request_report(std::shared_ptr<file> entr, QWidget *parent) :
    QDialog(parent),
    m_entr(entr),
    ui(new Ui::request_report)
{
    ui->setupUi(this);
    THROW_DEFAULT(entr.get() == nullptr, "File does not exist!");
    foreach(std::shared_ptr<TOOLS::entries> ele, entr.get()->getEntries())
    {

    }
}

request_report::~request_report()
{
    delete ui;
}
