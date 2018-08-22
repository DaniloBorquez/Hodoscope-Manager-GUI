#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <QObject>
#include <QDir>
#include <QCoreApplication>

#include "GUI/dialogserialchoose.h"
#include "communication/buffer.h"
#include "communication/serialcommunication.h"
#include "kernel/logdata.h"

class DataManager : public QObject
{
    Q_OBJECT
public:
    DataManager();

    ~DataManager();

    void sendParameter(QString parameter);
    void startMeasuring();

    int getGate() const;
    void setGate(int value);
    void setSamplePoints(int value);

public slots:
    void getSerialObject(SerialCommunication *serial);
    void getFrequency(QString f, int elapsed);
    void getAzimuth(QString a);
    void getPolar(QString p);
    void getDistance(QString d);
    void getStats(SampleData sampleData);

signals:
    void frequency(float f, int elapsed);
    void azimuth(float a);
    void polar(float p);
    void distance(float d);
    void AverageFrequency(double f);
    void rms(double f);
    void sampleSize(int n);

private:
    Buffer * bufer;
    SerialCommunication *serial;
    QObject *parent;
    int gate;
    LogData *log;
};

#endif // DATAMANAGER_H
