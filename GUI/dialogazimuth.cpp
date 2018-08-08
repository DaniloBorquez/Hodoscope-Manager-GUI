#include "dialogazimuth.h"
#include "ui_dialogazimuth.h"

DialogAzimuth::DialogAzimuth(DataManager *dataManager, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAzimuth)
{
    ui->setupUi(this);
    this->dataManager = dataManager;
    this->show();
}

DialogAzimuth::~DialogAzimuth()
{
    delete ui;
}

void DialogAzimuth::done(int r)
{
    if(QDialog::Accepted == r)  // ok was pressed
    {
        dataManager->sendParameter(QString("a:").append(ui->lineEditAzimuth->text()));
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

