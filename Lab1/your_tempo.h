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
    std::shared_ptr<entries> m_file;
    bool isFrozen;
public:
    explicit your_tempo(QDate date, std::shared_ptr<entries> file, bool frozen, QWidget *parent = nullptr);
    ~your_tempo();

private slots:
    void on_pushButton_released();

private:
    Ui::your_tempo *ui;
};

#endif // YOUR_TEMPO_H
