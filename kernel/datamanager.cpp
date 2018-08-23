#include "datamanager.h"
#include <QDebug>

DataManager::DataManager()
{
    qRegisterMetaType<SerialCommunication*>();
    DialogSerialChoose *dialog = new DialogSerialChoose();
    this->bufer = new Buffer(100);
    connect(dialog,&DialogSerialChoose::serialObject,this,&DataManager::getSerialObject);
    this->parent = parent;
    this->gate = 5;

    if(!QDir(QCoreApplication::applicationDirPath()+"/logData").exists()){
        QDir().mkdir(QCoreApplication::applicationDirPath()+"/logData");
    }
    this->log = new LogData(QCoreApplication::applicationDirPath()+"/logData/");
}

DataManager::~DataManager()
{
    delete this->bufer;
    delete this->log;
}

void DataManager::sendParameter(QString parameter)
{
    this->bufer->receiveParameter(parameter);
    if(parameter.split(":").at(0).compare(QString("g")) == 0){
        this->gate = parameter.split(":").at(1).split("\\").at(0).toInt();
    }
}

void DataManager::startMeasuring()
{
    this->bufer->startMeasuring();
    this->bufer->clear();
}

void DataManager::getSerialObject(SerialCommunication *serial)
{
    this->serial = serial;
    connect(serial,&SerialCommunication::incomingMsg,this->bufer,&Buffer::getIncomeMsg);
    connect(this->bufer,&Buffer::sendTask,serial,&SerialCommunication::sendTask);

    connect(this->bufer,&Buffer::frequencySignal,this,&DataManager::getFrequency);
    connect(this->bufer,&Buffer::azimuthSignal,this,&DataManager::getAzimuth);
    connect(this->bufer,&Buffer::polarSignal,this,&DataManager::getPolar);
    connect(this->bufer,&Buffer::distanceSignal,this,&DataManager::getDistance);
    connect(this->bufer,&Buffer::statsReady,this,&DataManager::getStats);
    connect(this->bufer,&Buffer::dataForLog,this->log,&LogData::writeInformation);
}

void DataManager::getFrequency(QString f, int elapsed)
{
    emit frequency(f.toFloat(), elapsed);
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

void DataManager::getStats(SampleData sampleData)
{
    emit AverageFrequency(sampleData.getMean());
    emit rms(sampleData.getRms());
    emit sampleSize(sampleData.getY().size());
}

int DataManager::getGate() const
{
    return gate;
}

void DataManager::setGate(int value)
{
    gate = value;
}

void DataManager::setSamplePoints(int value)
{
    this->bufer->setNumberOfSamplePoints(value);
}
