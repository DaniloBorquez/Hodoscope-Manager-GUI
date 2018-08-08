#include "serialcommunication.h"
#include <QDebug>

SerialCommunication::SerialCommunication(QObject *parent, QString portName, BaudRate baudRate,
                                         DataBits dataBitsUsed, Parity parity,
                                         StopBits numberOfStops, FlowControl flowControl):QSerialPort(parent)
{
    qDebug() << portName;
    this->ok = true;
    this->autoRspMsg = QString("-1\r");
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
    connect(this,&SerialCommunication::incomingMsg,this,&SerialCommunication::autoResponse);
}

void SerialCommunication::readData()
{
        QByteArray data = this->readAll();
        qDebug() << "data read: "<<data;
        emit incomingMsg(QString(data));
}

void SerialCommunication::sendData(QString data)
{
    this->write(data.toStdString().c_str());
}

void SerialCommunication::autoResponse(QString data)
{
    qDebug() << data;
    if(data.compare("0") == 0){
        qDebug() << data<<this->autoRspMsg;
        this->sendData(this->autoRspMsg);
        if(this->autoRspMsg.compare("-1\r") != 0){
            this->autoRspMsg = QString("-1\r");
        }
    }
}

void SerialCommunication::sendTask(QString data)
{
    this->autoRspMsg = data;
}

bool SerialCommunication::isOk() const
{
    return ok;
}

