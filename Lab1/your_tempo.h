#ifndef YOUR_TEMPO_H
#define YOUR_TEMPO_H

#include <QDialog>

#include "file_pipeline.h"
#include "base.h"

namespace Ui {
class your_tempo;
}

class your_tempo : public QDialog
{
    Q_OBJECT
    Base* m_base;
    std::shared_ptr<TOOLS::entries> m_entrie;
    std::shared_ptr<file> m_file;
    bool isFrozen;
public:
    explicit your_tempo(Base* base,
                        std::shared_ptr<TOOLS::entries> entr,
                        std::shared_ptr<file> file,
                        bool frozen,
                        QWidget *parent = nullptr);
    ~your_tempo();

    void on_edit_released();
private slots:
    void on_view_released();

private:
    Ui::your_tempo *ui;
};

#endif // YOUR_TEMPO_H
