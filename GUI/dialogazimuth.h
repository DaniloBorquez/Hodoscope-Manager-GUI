#ifndef DIALOGAZIMUTH_H
#define DIALOGAZIMUTH_H

#include <QDialog>

#include "communication/buffer.h"
#include "kernel/datamanager.h"

namespace Ui {
class DialogAzimuth;
}

class DialogAzimuth : public QDialog
{
    Q_OBJECT

public:
    explicit DialogAzimuth(DataManager *dataManager, QWidget *parent = 0);
    ~DialogAzimuth();

public slots:
    void done(int r);

private:
    Ui::DialogAzimuth *ui;
    DataManager *dataManager;
};

#endif // DIALOGAZIMUTH_H
