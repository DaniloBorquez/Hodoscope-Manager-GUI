#ifndef ROUTINE_H
#define ROUTINE_H

#include <QObject>
#include <QString>

#include <kernel/datamanager.h>

class Routine : public QObject
{
    Q_OBJECT
public:
    Routine(DataManager *dataManager);
    Routine(DataManager *dataManager, int angleSteps, int samplesByAngle, int gate);

    int getAngleSteps() const;
    void setAngleSteps(int value);

    int getSamplesByAngle() const;
    void setSamplesByAngle(int value);

    int getGate() const;
    void setGate(int value);

public slots:
    void newSample();
    void startRoutine();

signals:
    void routineFinished();
    void setParameter(QString parameter);

private:
    int angleSteps;
    int samplesByAngle;
    int actualSamples;
    int gate;
    bool routineStarted;
    DataManager *dataManager;
};

#endif // ROUTINE_H
