#include "routine.h"
#include <QDebug>

Routine::Routine(DataManager *dataManager)
{
    this->dataManager = dataManager;
    this->actualSamples = 0;
    this->routineStarted = false;
}

Routine::Routine(DataManager *dataManager, int angleSteps, int samplesByAngle, int gate)
{
    this->angleSteps = angleSteps;
    this->samplesByAngle = samplesByAngle;
    this->gate = gate;
    this->actualSamples = 0;
    this->dataManager = dataManager;
    this->routineStarted = false;
}

void Routine::newSample()
{
    if(this->routineStarted){
        if(this->actualSamples/this->samplesByAngle == 90){
            emit routineFinished();
            this->routineStarted = false;
            delete this;
        }else if(this->actualSamples != 0 && this->actualSamples%this->samplesByAngle == 0){
            this->dataManager->sendParameter(QString("a:").append(QString::number(this->angleSteps*this->actualSamples/this->samplesByAngle)).append('\r'));
        }
        this->actualSamples++;
    }
}

void Routine::startRoutine()
{
    this->routineStarted = true;
}

int Routine::getGate() const
{
    return gate;
}

void Routine::setGate(int value)
{
    gate = value;
}

int Routine::getSamplesByAngle() const
{
    return samplesByAngle;
}

void Routine::setSamplesByAngle(int value)
{
    samplesByAngle = value;
}

int Routine::getAngleSteps() const
{
    return angleSteps;
}

void Routine::setAngleSteps(int value)
{
    angleSteps = value;
}
