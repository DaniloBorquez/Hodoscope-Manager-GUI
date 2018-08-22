#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTime>
#include <QTimer>
#include <QDir>

#include "communication/serialcommunication.h"
#include "kernel/datamanager.h"
#include "kernel/logdata.h"
#include "GUI/qcustomplot.h"
#include "GUI/dialogazimuth.h"
#include "GUI/dialoggate.h"
#include "GUI/dialogsamplepoints.h"
#include <kernel/routine.h>
#include <GUI/dialogroutine.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void frequencyChanged(float f, int elapsed);
    void azimuthChanged(float a);
    void polarChanged(float p);
    void distanceChanged(float d);
    void updateTimeElapsed();
    void updateAverageFrequency(double f);
    void updateRMS(double rms);
    void updateSampleSize(int n);

private slots:
    void on_pushButtonStart_clicked();

    void on_pushButtonAzimuth_clicked();

    void on_pushButtonGate_clicked();

    void on_pushButtonPlotPoints_clicked();

    void on_pushButtonStartRoutine_clicked();

private:
    Ui::MainWindow *ui;
    DataManager *dataManager;
    bool plotEnabled;
    QTime timeStarted;
    QTime timeElapsed;
    QTimer *counterTime;
    Routine *routine;
    LogData *log;

    void plotInit();
};

#endif // MAINWINDOW_H
