#include "dialogroutine.h"
#include "ui_dialogroutine.h"

DialogRoutine::DialogRoutine(Routine *routine, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogRoutine)
{
    ui->setupUi(this);
    this->routine = routine;
    this->show();
}

DialogRoutine::~DialogRoutine()
{
    delete ui;
}

void DialogRoutine::done(int r)
{
    if(QDialog::Accepted == r)  // ok was pressed
    {
        this->routine->setAngleSteps(this->ui->lineEditRoutineAngleStep->text().toInt());
        this->routine->setSamplesByAngle(this->ui->lineEditRoutineSamplesbyAngle->text().toInt());
        this->routine->setGate(this->ui->lineEditRoutineGate->text().toInt());
        this->routine->startRoutine();
        QDialog::done(r);
        return;
   /*     if(serial->isOk()){
            QDialog::done(r);
            return;
        }else{
            delete serial;
            QMessageBox msgBox;
            msgBox.setText("Connection failed.");
            msgBox.exec();
            return;
        }*/
    }
    else    // cancel, close or exc was pressed
    {
        QDialog::done(r);
        return;
    }
}
