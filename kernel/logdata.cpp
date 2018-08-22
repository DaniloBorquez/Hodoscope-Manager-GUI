#include "logdata.h"
#include <QStandardPaths>

LogData::LogData(QString path)
{
    QDateTime date = QDateTime(QDateTime::currentDateTime());
    this->file.setFileName(path.append("/").append(date.toString("yyyy_MM_dd.log")));

    this->file.open(QIODevice::Append | QIODevice::Text);
    this->file.write("#\n#");
    this->file.write(date.toString("dd/MM/yyyy HH:mm:ss").toLatin1().data());
    this->file.write("\n#Year, Month, Day, Hours, minutes, seconds, frequency, azimuth, polar angle, distance\n");
    this->file.close();
}

void LogData::writeInformation(QString f, QString a, QString p, QString d, QString status)
{
    QDateTime date = QDateTime(QDateTime::currentDateTime());
    this->file.open(QIODevice::Append | QIODevice::Text);
    this->file.write(date.toString("yyyy").append(",").toLatin1().data());
    this->file.write(date.toString("MM").append(",").toLatin1().data());
    this->file.write(date.toString("dd").append(",").toLatin1().data());
    this->file.write(date.toString("HH").append(",").toLatin1().data());
    this->file.write(date.toString("mm").append(",").toLatin1().data());
    this->file.write(date.toString("ss").append(",").toLatin1().data());
    this->file.write(f.append(",").toLatin1().data());
    this->file.write(a.append(",").toLatin1().data());
    this->file.write(p.append(",").toLatin1().data());
    this->file.write(d.append(",").toLatin1().data());
    this->file.write(status.append("\n").toLatin1().data());
    this->file.close();
}
