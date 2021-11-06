#ifndef YOUR_TEMPO_H
#define YOUR_TEMPO_H

#include <QDialog>

#include "file_pipeline.h"

namespace Ui {
class your_tempo;
}

class your_tempo : public QDialog
{
    Q_OBJECT
    QDate m_date;
    std::shared_ptr<TOOLS::entries> m_entrie;
    std::shared_ptr<file> m_file;
    bool isFrozen;
public:
    explicit your_tempo(QDate date, std::shared_ptr<TOOLS::entries> entr, std::shared_ptr<file> file, bool frozen, QWidget *parent = nullptr);
    ~your_tempo();

private slots:
    void on_pushButton_released();

    void on_edit_released();

private:
    Ui::your_tempo *ui;
};

#endif // YOUR_TEMPO_H
