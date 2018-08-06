#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include "GUI/dialogserialchoose.h"
#include "communication/buffer.h"
#include "communication/serialcommunication.h"

class DataManager : public QObject
{
    Q_OBJECT
public:
    DataManager();

    ~DataManager();

public slots:
    void getSerialObject(SerialCommunication *serial);

private:
    Buffer * bufer;
    SerialCommunication *serial;
};

#endif // DATAMANAGER_H
