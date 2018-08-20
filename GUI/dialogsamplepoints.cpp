#include "dialogsamplepoints.h"
#include "ui_dialogsamplepoints.h"

DialogSamplePoints::DialogSamplePoints(DataManager *dataManager, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogSamplePoints)
{
    this->dataManager = dataManager;
    ui->setupUi(this);
    this->show();
}

DialogSamplePoints::~DialogSamplePoints()
{
    delete ui;
}

void DialogSamplePoints::done(int r)
{
    if(QDialog::Accepted == r)  // ok was pressed
    {
        this->dataManager->setSamplePoints(ui->lineEditSamplePoints->text().toInt());
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
