#include "dialogserialchoose.h"
#include "ui_dialogserialchoose.h"
#include <QDebug>
#include <QList>
#include <QString>

DialogSerialChoose::DialogSerialChoose(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogSerialChoose)
{
    ui->setupUi(this);
    QList<QSerialPortInfo> ports = QSerialPortInfo::availablePorts();
    for(int i=0; i<ports.count(); i++) {
        ui->listWidgetDevices->addItem(QString::number(i) + ": " + ports[i].portName());
    }
    this->show();
}

DialogSerialChoose::~DialogSerialChoose()
{
    delete ui;
}

void DialogSerialChoose::done(int r)
{
    if(QDialog::Accepted == r)  // ok was pressed
    {
        SerialCommunication *serial;
        QString selected = ui->listWidgetDevices->currentItem()->text();
        serial = new SerialCommunication(this,selected.split(": ")[1]);

        if(serial->isOk()){
            QDialog::done(r);
            return;
        }else{
            delete serial;
            QMessageBox msgBox;
            msgBox.setText("Connection failed.");
            msgBox.exec();
            return;
        }
    }
    else    // cancel, close or exc was pressed
    {
        QDialog::done(r);
        return;
    }
}
