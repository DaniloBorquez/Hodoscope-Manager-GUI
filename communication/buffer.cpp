#include "buffer.h"
#include <QDebug>

Buffer::Buffer(int maxSize)
{
    this->maxSize = maxSize;
    this->buf = new QVector<Data*>();
}

void Buffer::push(Data *data)
{
    this->buf->push_back(data);
    if(this->buf->size() > this->maxSize){
        this->buf->pop_front();
    }
}

SampleData Buffer::getNPointsFT(int n)
{
    double mean = 0;
    double rms = 0;
    QVector<double> x;
    QVector<double> y;
    for(int i = this->buf->size()-1;i>this->buf->size()-n-1;i--){
        x.push_back(this->buf->at(i)->getDate());
        y.push_back(this->buf->at(i)->getFrequency());
        mean += y.last();
        rms  += y.last()*y.last();
    }

    mean = mean/n;
    rms = ( rms/(n-1) > n/(n-1)*pow(mean,2) )?( sqrt(rms/(n-1) - n/(n-1)*pow(mean,2)) ):-1.0;
    SampleData data = SampleData();
    data.setX(x);
    data.setY(y);
    data.setMean(mean);
    data.setRms(rms);
    return data;
}

void Buffer::getIncomeMsg(QString msg)
{
    qDebug() << "buffer in: " << msg;
    if(msg.startsWith(QChar('#')) && msg.endsWith(QChar('*'))){
        qDebug() << msg.mid(3,5);
        qDebug() << msg.mid(10,5);
        qDebug() << msg.mid(17,5);
        qDebug() << msg.mid(24,5);
        emit frequencySignal(msg.mid(3,5));
        emit azimuthSignal(msg.mid(10,5));
        emit polarSignal(msg.mid(17,5));
        emit distanceSignal(msg.mid(24,5));

    }else{
        qDebug() << "INcorrect";
    }
}
