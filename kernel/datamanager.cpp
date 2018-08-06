#include "datamanager.h"

DataManager::DataManager()
{
    qRegisterMetaType<SerialCommunication*>();
    DialogSerialChoose *dialog = new DialogSerialChoose();
    this->bufer = new Buffer(100);
    connect(dialog,&DialogSerialChoose::serialObject,this,&DataManager::getSerialObject);
}

DataManager::~DataManager()
{
    delete this->bufer;
}

void DataManager::getSerialObject(SerialCommunication *serial)
{
    this->serial = serial;
    connect(serial,&SerialCommunication::incomingMsg,this->bufer,&Buffer::getIncomeMsg);
}
