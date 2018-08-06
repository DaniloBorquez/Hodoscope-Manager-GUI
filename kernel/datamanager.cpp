#include "datamanager.h"
#include <QDebug>

DataManager::DataManager()
{
    qRegisterMetaType<SerialCommunication*>();
    DialogSerialChoose *dialog = new DialogSerialChoose();
    this->bufer = new Buffer(100);
    connect(dialog,&DialogSerialChoose::serialObject,this,&DataManager::getSerialObject);
    this->parent = parent;
}

DataManager::~DataManager()
{
    delete this->bufer;
}

void DataManager::getSerialObject(SerialCommunication *serial)
{
    this->serial = serial;
    connect(serial,&SerialCommunication::incomingMsg,this->bufer,&Buffer::getIncomeMsg);
    connect(this->bufer,&Buffer::frequencySignal,this,&DataManager::getFrequency);
    connect(this->bufer,&Buffer::azimuthSignal,this,&DataManager::getAzimuth);
    connect(this->bufer,&Buffer::polarSignal,this,&DataManager::getPolar);
    connect(this->bufer,&Buffer::distanceSignal,this,&DataManager::getDistance);
}

void DataManager::getFrequency(QString f)
{
    emit frequency(f.toFloat());
}

void DataManager::getAzimuth(QString a)
{
    emit azimuth(a.toFloat());
}

void DataManager::getPolar(QString p)
{
    emit polar(p.toFloat());
}

void DataManager::getDistance(QString d)
{
    emit distance(d.toFloat());
}
