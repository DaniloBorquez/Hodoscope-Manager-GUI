#ifndef DIALOGSERIALCHOOSE_H
#define DIALOGSERIALCHOOSE_H

#include <QDialog>
#include <QSerialPortInfo>
#include <QMessageBox>

#include <communication/serialcommunication.h>

namespace Ui {
class DialogSerialChoose;
}

class DialogSerialChoose : public QDialog
{
    Q_OBJECT

public:
    explicit DialogSerialChoose(QWidget *parent = 0);
    ~DialogSerialChoose();

public slots:
    void done(int r);

private:
    Ui::DialogSerialChoose *ui;
};

#endif // DIALOGSERIALCHOOSE_H
