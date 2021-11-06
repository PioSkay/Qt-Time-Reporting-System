#include "adjust_window.h"
#include "ui_adjust_window.h"

adjust_window::adjust_window(int &to_adjust, QWidget *parent) :
    QDialog(parent),
    m_to_adjust(to_adjust),
    isAdjusted(false),
    ui(new Ui::adjust_window)
{
    ui->setupUi(this);
}

bool adjust_window::adjusted()
{
    return isAdjusted;
}

adjust_window::~adjust_window()
{
    delete ui;
}

void adjust_window::on_pushButton_released()
{
    isAdjusted = true;
    before = m_to_adjust;
    m_to_adjust = ui->lineEdit->text().toInt();
    after = m_to_adjust;
    close();
}


void adjust_window::on_pushButton_2_released()
{
    close();
}

