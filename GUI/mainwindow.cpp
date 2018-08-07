#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->dataManager = new DataManager();
    plotInit();
    connect(this->dataManager,&DataManager::frequency,this,&MainWindow::frequencyChanged);
    connect(this->dataManager,&DataManager::azimuth,this,&MainWindow::azimuthChanged);
    connect(this->dataManager,&DataManager::polar,this,&MainWindow::polarChanged);
    connect(this->dataManager,&DataManager::distance,this,&MainWindow::distanceChanged);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::frequencyChanged(float f)
{
    if(this->plotEnabled){
       //this->ui->customPlot->graph(0)->ad
    }
}

void MainWindow::azimuthChanged(float a)
{
    this->ui->labelAzimuth->setText(QString::number(a));
}

void MainWindow::polarChanged(float p)
{
    this->ui->labelPolar->setText(QString::number(p));
}

void MainWindow::distanceChanged(float d)
{
    this->ui->labelDistance->setText(QString::number(d));
}

void MainWindow::plotInit()
{
    this->plotEnabled = false;
    this->ui->customPlot->addGraph();
    // give the axes some labels:
    this->ui->customPlot->xAxis->setLabel("Time");
    this->ui->customPlot->yAxis->setLabel("#");
    // set axes ranges, so we see all data:
    QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
    timeTicker->setTimeFormat("%h:%m:%s");
    this->ui->customPlot->xAxis->setTicker(timeTicker);
    this->ui->customPlot->axisRect()->setupFullAxesBox();
    this->ui->customPlot->yAxis->setRange(0, 10);
    this->ui->customPlot->xAxis->setRange(0, 10);
    this->ui->customPlot->replot();
}

void MainWindow::on_pushButtonStart_clicked()
{
    this->plotEnabled = true;
}
