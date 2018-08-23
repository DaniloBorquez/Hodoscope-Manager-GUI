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
    connect(this->dataManager,&DataManager::AverageFrequency,this,&MainWindow::updateAverageFrequency);
    connect(this->dataManager,&DataManager::rms,this,&MainWindow::updateRMS);
    connect(this->dataManager,&DataManager::sampleSize,this,&MainWindow::updateSampleSize);
}

MainWindow::~MainWindow()
{
    delete counterTime;
    delete ui;
}

void MainWindow::frequencyChanged(float f, int elapsed)
{
    if(this->plotEnabled){
        double key = elapsed/1000.0;
        this->ui->customPlot->graph(0)->addData(key, f);
        if(key > 1200){
            this->ui->customPlot->xAxis->setRange(key, 1200, Qt::AlignRight); //1200 segundos
        }else{
            this->ui->customPlot->xAxis->setRange(key, key, Qt::AlignRight); //1200 segundos
        }
        bool foundRange;
        QCPRange range = this->ui->customPlot->graph(0)->getValueRange(foundRange,QCP::sdPositive);
        if(foundRange){
            this->ui->customPlot->yAxis->setRange(-0.1,range.upper);
        }
        this->ui->customPlot->replot();
    }
    this->ui->labelLastFrequency->setText(QString::number(f).append(" Hz"));
    this->ui->labelGate->setText(QString::number(this->dataManager->getGate()));
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

void MainWindow::updateTimeElapsed()
{
    this->timeElapsed = QTime(0,0,0,0);
    this->ui->labelTimeElapsed->setText(timeElapsed.addMSecs(this->timeStarted.elapsed()).toString("hh:mm:ss"));
}

void MainWindow::updateAverageFrequency(double f)
{
    this->ui->labelAverage->setText(QString::number(f).append(" Hz"));
}

void MainWindow::updateRMS(double rms)
{
    this->ui->labelRMS->setText(QString::number(rms).append(" Hz"));
}

void MainWindow::updateSampleSize(int n)
{
    this->ui->labelPlotPoints->setText(QString::number(n));
}

void MainWindow::plotInit()
{
    this->plotEnabled = false;
    this->ui->customPlot->addGraph();
    // give the axes some labels:
    this->ui->customPlot->xAxis->setLabel("Time");
    this->ui->customPlot->yAxis->setLabel("Frequency");
    // set axes ranges, so we see all data:
    QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
    timeTicker->setTimeFormat("%h:%m:%s");
    this->ui->customPlot->xAxis->setTicker(timeTicker);
    this->ui->customPlot->axisRect()->setupFullAxesBox();
    this->ui->customPlot->yAxis->setRange(-0.1, 10);
    this->ui->customPlot->xAxis->setRange(0, 10);
    this->ui->customPlot->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 5));
    this->ui->customPlot->setInteraction(QCP::iRangeDrag, true);
    this->ui->customPlot->axisRect()->setRangeDrag(Qt::Horizontal);
    this->ui->customPlot->replot();
}

void MainWindow::on_pushButtonStart_clicked()
{
    this->plotEnabled = true;
    this->dataManager->startMeasuring();
    this->ui->labelStatus->setText(QString("Measuring"));
    this->timeStarted = QTime::currentTime();
    this->ui->labelTimeStarted->setText(timeStarted.toString("hh:mm:ss AP"));
    this->counterTime = new QTimer();
    connect(this->counterTime, SIGNAL(timeout()), this, SLOT(updateTimeElapsed()));
    this->counterTime->start(1000);
}

void MainWindow::on_pushButtonAzimuth_clicked()
{
    new DialogAzimuth(this->dataManager);
}

void MainWindow::on_pushButtonGate_clicked()
{
    new DialogGate(this->dataManager);
}

void MainWindow::on_pushButtonPlotPoints_clicked()
{
    new DialogSamplePoints(this->dataManager);
}

void MainWindow::on_pushButtonStartRoutine_clicked()
{
    this->routine = new Routine(this->dataManager);
    connect(this->dataManager,&DataManager::frequency,this->routine,&Routine::newSample);
    connect(this->routine,&Routine::setParameter,this->dataManager,&DataManager::sendParameter);
    new DialogRoutine(this->routine);
    on_pushButtonStart_clicked();
    this->ui->labelStatus->setText(QString("Routine started"));
}
