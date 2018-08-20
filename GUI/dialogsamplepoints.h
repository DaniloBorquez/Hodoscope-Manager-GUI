#ifndef DIALOGSAMPLEPOINTS_H
#define DIALOGSAMPLEPOINTS_H

#include <QDialog>

#include <kernel/datamanager.h>

namespace Ui {
class DialogSamplePoints;
}

class DialogSamplePoints : public QDialog
{
    Q_OBJECT

public:
    explicit DialogSamplePoints(DataManager *dataManager, QWidget *parent = 0);
    ~DialogSamplePoints();

public slots:
    void done(int r);

private:
    Ui::DialogSamplePoints *ui;
    DataManager *dataManager;
};

#endif // DIALOGSAMPLEPOINTS_H
