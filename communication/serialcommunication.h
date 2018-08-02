#ifndef SERIALCOMMUNICATION_H
#define SERIALCOMMUNICATION_H

#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>


class SerialCommunication : public QSerialPort
{
    Q_OBJECT
public:
    SerialCommunication(QObject *parent, QString portName, BaudRate baudRate = QSerialPort::Baud57600,
                        DataBits dataBitsUsed = QSerialPort::Data8, Parity parity = QSerialPort::NoParity,
                        StopBits numberOfStops = QSerialPort::OneStop, FlowControl flowControl = QSerialPort::NoFlowControl);

public slots:
    void readData();
    void sendData(QString data);
};

#endif // SERIALCOMMUNICATION_H
