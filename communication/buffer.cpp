#include "buffer.h"
#include <QDebug>

Buffer::Buffer(int maxSize)
{
    this->maxSize = maxSize;
    this->buf = new QVector<Data*>();
    this->measuring = false;
    this->numberOfSamplePoints = 10;
}

Buffer::~Buffer()
{
    for(int i = 0; i < this->buf->size();i++){
        delete this->buf->at(i);
    }
    this->buf->clear();
    delete this->buf;
}

void Buffer::push(Data *data)
{
    this->buf->push_back(data);
    if(this->buf->size() > this->maxSize){
        this->buf->pop_front();
    }
}

void Buffer::getNPointsFT()
{
    double mean = 0;
    double rms = 0;
    QVector<double> x;
    QVector<double> y;
    int n = this->numberOfSamplePoints;
    for(int i = this->buf->size()-1;i>this->buf->size()-n-1 && i >= 0;i--){
        x.push_back(this->buf->at(i)->getDate());
        y.push_back(this->buf->at(i)->getFrequency());
        mean += y.last();
        rms  += y.last()*y.last();
    }
    n = x.size();
    if(n > 1){
        mean = mean/n;
        rms = ( rms/(n-1) > n/(n-1)*pow(mean,2) )?( sqrt(rms/(n-1) - n/(n-1)*pow(mean,2)) ):-1.0;
        SampleData data = SampleData();
        data.setX(x);
        data.setY(y);
        data.setMean(mean);
        data.setRms(rms);
        emit statsReady(data);
    }
}

void Buffer::receiveParameter(QString parameter)
{
    emit sendTask(parameter);
}

void Buffer::startMeasuring()
{
    this->measuring = true;
    this->time = QTime::currentTime();
}

void Buffer::getIncomeMsg(QString msg)
{
    int elapsed = this->time.elapsed();
    if(msg.split("*").size() == 2 && msg.split("*").at(1).compare("R") == 0){
        msg = msg.split("*").front().append('*');
    }else if(msg.compare("R") == 0){
        msg = QString("");
    }
    //qDebug() << "buffer in after: " << msg;
    if(msg.startsWith(QChar('#')) && msg.endsWith(QChar('*'))){
        float f = msg.mid(3,5).toFloat();
        if(f < 20){
            emit frequencySignal(msg.mid(3,5), elapsed);
            emit azimuthSignal(msg.mid(10,5));
            emit polarSignal(msg.mid(17,5));
            emit distanceSignal(msg.mid(24,5));
            if(measuring){

                Data *data = new Data();
                data->setFrequency(msg.mid(3,5).toDouble());
                data->setAzimuth(msg.mid(10,5).toDouble());
                data->setPolar(msg.mid(17,5).toDouble());
                data->setDistance(msg.mid(24,5).toDouble());
                data->setDate(elapsed);
                this->push(data);
                this->getNPointsFT();
            }
        }else{
            float az = msg.mid(10,5).toFloat();
            receiveParameter(QString("a:").append(QString::number(az-1)).append("\r"));
        }
    }else if(msg.startsWith(QChar('#'))){
        this->incomingBufferMsg = msg;
    }else if(msg.endsWith(QChar('*'))){
        this->incomingBufferMsg.append(msg);
        if(this->incomingBufferMsg.size() == 37){
            float f = this->incomingBufferMsg.mid(3,5).toFloat();
            if(f < 20){
                emit frequencySignal(this->incomingBufferMsg.mid(3,5),elapsed);
                emit azimuthSignal(this->incomingBufferMsg.mid(10,5));
                emit polarSignal(this->incomingBufferMsg.mid(17,5));
                emit distanceSignal(this->incomingBufferMsg.mid(24,5));
                if(measuring){
                    Data *data = new Data();
                    data->setFrequency(this->incomingBufferMsg.mid(3,5).toDouble());
                    data->setAzimuth(this->incomingBufferMsg.mid(10,5).toDouble());
                    data->setPolar(this->incomingBufferMsg.mid(17,5).toDouble());
                    data->setDistance(this->incomingBufferMsg.mid(24,5).toDouble());
                    data->setDate(elapsed);
                    this->push(data);
                    this->getNPointsFT();
                }
            }else{
                float az = this->incomingBufferMsg.mid(10,5).toFloat();
                receiveParameter(QString("a:").append(QString::number(az-1)).append("\r"));
            }
        }else{
            qDebug() << "Incorrect: "<< this->incomingBufferMsg;
        }
    }else{
        this->incomingBufferMsg.append(msg);
    }
}

int Buffer::getNumberOfSamplePoints() const
{
    return numberOfSamplePoints;
}

void Buffer::setNumberOfSamplePoints(int value)
{
    numberOfSamplePoints = value;
}
