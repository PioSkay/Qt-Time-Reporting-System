#include "request_report.h"
#include "ui_request_report.h"
#include "request_data.h"

request_report::request_report(std::shared_ptr<file> entr, QWidget *parent) :
    QDialog(parent),
    m_entr(entr),
    ui(new Ui::request_report)
{
    ui->setupUi(this);
    THROW_DEFAULT(entr.get() == nullptr, "File does not exist!");
    std::map<std::string, std::pair<int, int>> entr_map;
    foreach(std::shared_ptr<TOOLS::entries> ele, entr.get()->getEntries())
    {
        if(ele.get() != nullptr)
            entr_map[ele.get()->code.toStdString()] =
                    std::pair<int,int>(
                        ele.get()->time + entr_map[ele.get()->code.toStdString()].first,
                        0 + entr_map[ele.get()->code.toStdString()].second);
    }
    foreach(std::shared_ptr<TOOLS::accepted> ele, entr.get()->getAccepted())
    {
        Log(Info) << "Accepted" << ele.get()->time;
        if(ele.get() != nullptr)
            entr_map[ele.get()->code.toStdString()] =
                    std::pair<int,int>(
                        0 + entr_map[ele.get()->code.toStdString()].first,
                        ele.get()->time + entr_map[ele.get()->code.toStdString()].second);
    }
    Log(Info) << __FUNCTION__ << " " << __LINE__ << " " << entr_map.size();
    QVBoxLayout* layout = new QVBoxLayout();
    ui->main_area->widget()->setLayout(layout);
    for(const auto& [key, value] : entr_map)
    {
        ui->main_area->widget()->layout()->addWidget(new request_data(QString(key.c_str()), value.first, value.second, this));
    }
}

request_report::~request_report()
{
    delete ui;
}

void request_report::on_pushButton_released()
{
    close();
}

