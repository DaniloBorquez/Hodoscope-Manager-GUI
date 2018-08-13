#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTime>

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
    void frequencyChanged(float f);
    void azimuthChanged(float a);
    void polarChanged(float p);
    void distanceChanged(float d);

private slots:
    void on_pushButtonStart_clicked();

    void on_pushButtonAzimuth_clicked();

    void on_pushButtonGate_clicked();

private:
    Ui::MainWindow *ui;
    DataManager *dataManager;
    bool plotEnabled;
    QTime time;

    void plotInit();
};

#endif // MAINWINDOW_H
