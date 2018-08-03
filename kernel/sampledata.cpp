#include "sampledata.h"

SampleData::SampleData()
{

}

QVector<double> SampleData::getX() const
{
    return x;
}

void SampleData::setX(const QVector<double> &value)
{
    x = value;
}

QVector<double> SampleData::getY() const
{
    return y;
}

void SampleData::setY(const QVector<double> &value)
{
    y = value;
}

double SampleData::getMean() const
{
    return mean;
}

void SampleData::setMean(double value)
{
    mean = value;
}

double SampleData::getRms() const
{
    return rms;
}

void SampleData::setRms(double value)
{
    rms = value;
}
