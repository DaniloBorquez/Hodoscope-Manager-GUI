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

void Buffer::receiveParameter(QString parameter)
{
    emit sendTask(parameter);
}

void Buffer::getIncomeMsg(QString msg)
{
    qDebug() << "buffer in: " << msg;
    if(msg.split("*").size() == 2 && msg.split("*").at(1).compare("R") == 0){
        msg = msg.split("*").front().append('*');
    }else if(msg.compare("R") == 0){
        msg = QString("");
    }
    qDebug() << "buffer in after: " << msg;
    if(msg.startsWith(QChar('#')) && msg.endsWith(QChar('*'))){
        emit frequencySignal(msg.mid(3,5));
        emit azimuthSignal(msg.mid(10,5));
        emit polarSignal(msg.mid(17,5));
        emit distanceSignal(msg.mid(24,5));

    }else if(msg.startsWith(QChar('#'))){
        this->incomingBufferMsg = msg;
    }else if(msg.endsWith(QChar('*'))){
        this->incomingBufferMsg.append(msg);
        if(this->incomingBufferMsg.size() == 37){
            emit frequencySignal(this->incomingBufferMsg.mid(3,5));
            emit azimuthSignal(this->incomingBufferMsg.mid(10,5));
            emit polarSignal(this->incomingBufferMsg.mid(17,5));
            emit distanceSignal(this->incomingBufferMsg.mid(24,5));
        }else{
            qDebug() << "Incorrect: "<< this->incomingBufferMsg;
        }
    }else{
        this->incomingBufferMsg.append(msg);
    }
}
