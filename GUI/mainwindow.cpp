#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    DialogSerialChoose *dialog = new DialogSerialChoose();
    //SerialCommunication *serial = new SerialCommunication(this,"/dev/ttyUSB0");
}

MainWindow::~MainWindow()
{
    delete ui;
}
