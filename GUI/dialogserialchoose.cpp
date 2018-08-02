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
