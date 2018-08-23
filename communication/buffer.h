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
    void getNPointsFT();
    void receiveParameter(QString parameter);
    void startMeasuring();

    int getNumberOfSamplePoints() const;
    void setNumberOfSamplePoints(int value);
    void clear();

public slots:
    void getIncomeMsg(QString msg);

signals:
    void frequencySignal(QString msg, int elapsed);
    void azimuthSignal(QString msg);
    void polarSignal(QString msg);
    void distanceSignal(QString msg);

    void dataForLog(QString f, QString a, QString p, QString d, QString status);

    void sendTask(QString parameter);
    void statsReady(SampleData sampleData);

private:
    int maxSize;
    QVector<Data*> *buf;
    QString incomingBufferMsg;
    QTime time;
    bool measuring;
    int numberOfSamplePoints;

};

#endif // BUFFER_H
