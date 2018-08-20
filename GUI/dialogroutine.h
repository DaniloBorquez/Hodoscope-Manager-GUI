#ifndef DIALOGROUTINE_H
#define DIALOGROUTINE_H

#include <QDialog>

#include <kernel/routine.h>

namespace Ui {
class DialogRoutine;
}

class DialogRoutine : public QDialog
{
    Q_OBJECT

public:
    explicit DialogRoutine(Routine *routine, QWidget *parent = 0);
    ~DialogRoutine();

public slots:
    void done(int r);

private:
    Ui::DialogRoutine *ui;
    Routine *routine;
};

#endif // DIALOGROUTINE_H
