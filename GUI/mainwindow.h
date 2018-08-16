#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTime>
#include <QTimer>

#include "communication/serialcommunication.h"
#include "GUI/qcustomplot.h"
#include "kernel/datamanager.h"
#include "GUI/dialogazimuth.h"
#include "GUI/dialoggate.h"

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

private slots:
    void on_pushButtonStart_clicked();

    void on_pushButtonAzimuth_clicked();

    void on_pushButtonGate_clicked();

private:
    Ui::MainWindow *ui;
    DataManager *dataManager;
    bool plotEnabled;
    QTime timeStarted;
    QTime timeElapsed;
    QTimer *counterTime;

    void plotInit();
};

#endif // MAINWINDOW_H
