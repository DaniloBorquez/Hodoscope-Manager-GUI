#include "serialcommunication.h"
#include <QDebug>

SerialCommunication::SerialCommunication(QObject *parent, QString portName, BaudRate baudRate,
                                         DataBits dataBitsUsed, Parity parity,
                                         StopBits numberOfStops, FlowControl flowControl):QSerialPort(parent)
{
    qDebug() << portName;
    this->ok = true;
    this->setPortName(portName);
    if (this->open(QIODevice::ReadWrite)){
        this->setBaudRate(baudRate);
        this->setDataBits(dataBitsUsed);
        this->setParity(parity);
        this->setStopBits(numberOfStops);
        this->setFlowControl(flowControl);
    }
    else
        this->ok = false;
    qDebug()<<" Conexión Completa";
    connect(this,&SerialCommunication::readyRead,this,&SerialCommunication::readData);
}

void SerialCommunication::readData()
{
        QByteArray data = this->readAll();
        qDebug() << "data read: "<<data;
}

void SerialCommunication::sendData(QString data)
{
    this->write(data.toStdString().c_str());
}

bool SerialCommunication::isOk() const
{
    return ok;
}

