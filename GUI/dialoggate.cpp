#include "dialoggate.h"
#include "ui_dialoggate.h"

DialogGate::DialogGate(DataManager *dataManager, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogGate)
{
    ui->setupUi(this);
    this->dataManager = dataManager;
    this->show();
}

DialogGate::~DialogGate()
{
    delete ui;
}

void DialogGate::done(int r)
{
    if(QDialog::Accepted == r)  // ok was pressed
    {
        dataManager->sendParameter(QString("g:").append(ui->lineEditGate->text()).append('\r'));
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
