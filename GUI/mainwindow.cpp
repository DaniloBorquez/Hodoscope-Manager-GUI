#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->dataManager = new DataManager();
    connect(this->dataManager,&DataManager::frequency,this,&MainWindow::frequencyChanged);
    connect(this->dataManager,&DataManager::azimuth,this,&MainWindow::azimuthChanged);
    connect(this->dataManager,&DataManager::polar,this,&MainWindow::polarChanged);
    connect(this->dataManager,&DataManager::distance,this,&MainWindow::distanceChanged);

    //SerialCommunication *serial = new SerialCommunication(this,"/dev/ttyUSB0");
    QVector<double> x(101), y(101); // initialize with entries 0..100
    for (int i=0; i<101; ++i)
    {
      x[i] = i/50.0 - 1; // x goes from -1 to 1
      y[i] = x[i]*x[i]; // let's plot a quadratic function
    }
    // create graph and assign data to it:

    this->ui->customPlot->addGraph();
    this->ui->customPlot->graph(0)->setData(x, y);
    // give the axes some labels:
    this->ui->customPlot->xAxis->setLabel("x");
    this->ui->customPlot->yAxis->setLabel("y");
    // set axes ranges, so we see all data:
    this->ui->customPlot->xAxis->setRange(-1, 1);
    this->ui->customPlot->yAxis->setRange(0, 1);
    this->ui->customPlot->replot();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::frequencyChanged(float f)
{

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
