#ifndef BUFFER_H
#define BUFFER_H

#include <QVector>
#include <QString>
#include <QObject>
#include <QChar>

#include <kernel/data.h>
#include <kernel/sampledata.h>

class Buffer : public QObject
{
    Q_OBJECT
public:
    Buffer(int maxSize);

    void push(Data* data);
    SampleData getNPointsFT(int n);

public slots:
    void getIncomeMsg(QString msg);

signals:
    void frequencySignal(QString msg);
    void azimuthSignal(QString msg);
    void polarSignal(QString msg);
    void distanceSignal(QString msg);

private:
    int maxSize;
    QVector<Data*> *buf;

};

#endif // BUFFER_H
