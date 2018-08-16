#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include "GUI/dialogserialchoose.h"
#include "communication/buffer.h"
#include "communication/serialcommunication.h"

class DataManager : public QObject
{
    Q_OBJECT
public:
    DataManager();

    ~DataManager();

    void sendParameter(QString parameter);
    void startMeasuring();

public slots:
    void getSerialObject(SerialCommunication *serial);
    void getFrequency(QString f, int elapsed);
    void getAzimuth(QString a);
    void getPolar(QString p);
    void getDistance(QString d);

signals:
    void frequency(float f, int elapsed);
    void azimuth(float a);
    void polar(float p);
    void distance(float d);

private:
    Buffer * bufer;
    SerialCommunication *serial;
    QObject *parent;
};

#endif // DATAMANAGER_H
