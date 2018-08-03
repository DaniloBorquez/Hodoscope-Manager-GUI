#ifndef SAMPLEDATA_H
#define SAMPLEDATA_H

#include <QVector>

class SampleData
{
public:
    SampleData();

    QVector<double> getX() const;
    void setX(const QVector<double> &value);

    QVector<double> getY() const;
    void setY(const QVector<double> &value);

    double getMean() const;
    void setMean(double value);

    double getRms() const;
    void setRms(double value);

private:
    QVector<double> x;
    QVector<double> y;
    double mean;
    double rms;
};

#endif // SAMPLEDATA_H
