#ifndef LOGDATA_H
#define LOGDATA_H

#include <QObject>
#include <QFile>
#include <QDateTime>
#include <QString>

class LogData : public QObject
{
    Q_OBJECT
public:
    LogData(QString path);

public slots:
    void writeInformation(QString f, QString a, QString p, QString d, QString status);
private:
    QFile file;
};

#endif // LOGDATA_H
