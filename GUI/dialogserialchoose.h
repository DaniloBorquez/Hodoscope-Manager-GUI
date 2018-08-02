#ifndef DIALOGSERIALCHOOSE_H
#define DIALOGSERIALCHOOSE_H

#include <QDialog>
#include <QSerialPortInfo>

namespace Ui {
class DialogSerialChoose;
}

class DialogSerialChoose : public QDialog
{
    Q_OBJECT

public:
    explicit DialogSerialChoose(QWidget *parent = 0);
    ~DialogSerialChoose();

private:
    Ui::DialogSerialChoose *ui;
};

#endif // DIALOGSERIALCHOOSE_H
