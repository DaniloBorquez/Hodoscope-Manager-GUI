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
        double key = this->time.elapsed()/1000.0;
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
    this->ui->customPlot->yAxis->setRange(-0.1, 10);
    this->ui->customPlot->xAxis->setRange(0, 10);
    this->ui->customPlot->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 5));
    this->ui->customPlot->replot();
}

void MainWindow::on_pushButtonStart_clicked()
{
    this->plotEnabled = true;
    this->time = QTime::currentTime();
}

void MainWindow::on_pushButtonAzimuth_clicked()
{
    new DialogAzimuth(this->dataManager);
}

void MainWindow::on_pushButtonGate_clicked()
{
    new DialogGate(this->dataManager);
}
