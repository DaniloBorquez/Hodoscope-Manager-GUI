#ifndef DIALOGGATE_H
#define DIALOGGATE_H

#include <QDialog>

#include <kernel/datamanager.h>

namespace Ui {
class DialogGate;
}

class DialogGate : public QDialog
{
    Q_OBJECT

public:
    explicit DialogGate(DataManager *dataManager, QWidget *parent = 0);
    ~DialogGate();

public slots:
    void done(int r);

private:
    Ui::DialogGate *ui;
    DataManager *dataManager;
};

#endif // DIALOGGATE_H
