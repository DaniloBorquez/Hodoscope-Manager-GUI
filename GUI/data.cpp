#include "data.h"

Data::Data()
{

}

double Data::getFrequency() const
{
    return frequency;
}

void Data::setFrequency(double value)
{
    frequency = value;
}

double Data::getPosition() const
{
    return position;
}

void Data::setPosition(double value)
{
    position = value;
}

double Data::getAzimuth() const
{
    return azimuth;
}

void Data::setAzimuth(double value)
{
    azimuth = value;
}

double Data::getPolar() const
{
    return polar;
}

void Data::setPolar(double value)
{
    polar = value;
}

double Data::getDistance() const
{
    return distance;
}

void Data::setDistance(double value)
{
    distance = value;
}

double Data::getDate() const
{
    return date;
}

void Data::setDate(double value)
{
    date = value;
}
