#ifndef BUFFER_H
#define BUFFER_H

#include <QVector>

#include <kernel/data.h>
#include <kernel/sampledata.h>

class Buffer
{
public:
    Buffer(int maxSize);

    void push(Data* data);
    SampleData getNPointsFT(int n);

private:
    int maxSize;
    QVector<Data*> *buf;
};

#endif // BUFFER_H
