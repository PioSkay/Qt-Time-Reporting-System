#ifndef VIEW_TEMPO_H
#define VIEW_TEMPO_H

#include <QDialog>

#include"entries.h"

namespace Ui {
class view_tempo;
}

class view_tempo : public QDialog
{
    Q_OBJECT
    std::shared_ptr<TOOLS::entries> m_entr;
public:
    explicit view_tempo(std::shared_ptr<TOOLS::entries> entr, QWidget *parent = nullptr);
    ~view_tempo();

private slots:
    void on_pushButton_released();

private:
    Ui::view_tempo *ui;
};

#endif // VIEW_TEMPO_H
