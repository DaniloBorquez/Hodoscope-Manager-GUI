#ifndef BUFFER_H
#define BUFFER_H

#include <QVector>
#include <QString>
#include <QObject>
#include <QChar>
#include <QTime>

#include <kernel/data.h>
#include <kernel/sampledata.h>

class Buffer : public QObject
{
    Q_OBJECT
public:
    Buffer(int maxSize);
    ~Buffer();

    void push(Data* data);
    void getNPointsFT(int n);
    void receiveParameter(QString parameter);
    void startMeasuring();

public slots:
    void getIncomeMsg(QString msg);

signals:
    void frequencySignal(QString msg, int elapsed);
    void azimuthSignal(QString msg);
    void polarSignal(QString msg);
    void distanceSignal(QString msg);
    void sendTask(QString parameter);
    void statsReady(SampleData sampleData);

private:
    int maxSize;
    QVector<Data*> *buf;
    QString incomingBufferMsg;
    QTime time;
    bool measuring;

};

#endif // BUFFER_H
