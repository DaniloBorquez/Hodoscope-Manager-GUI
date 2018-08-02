#ifndef SERIALCOMMUNICATION_H
#define SERIALCOMMUNICATION_H

#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>


class SerialCommunication : public QSerialPort
{
    Q_OBJECT
public:
    SerialCommunication(QObject *parent);
};

#endif // SERIALCOMMUNICATION_H
