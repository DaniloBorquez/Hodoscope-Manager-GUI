#-------------------------------------------------
#
# Project created by QtCreator 2018-08-02T10:15:35
#
#-------------------------------------------------

QT       += core gui serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = hodoscopeManagerGUI
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
    GUI/mainwindow.cpp \
    kernel/data.cpp \
    communication/serialcommunication.cpp \
    GUI/dialogserialchoose.cpp \
    communication/buffer.cpp \
    kernel/sampledata.cpp \
    GUI/qcustomplot.cpp \
    kernel/datamanager.cpp \
    GUI/dialogazimuth.cpp \
    GUI/dialoggate.cpp \
    GUI/dialogsamplepoints.cpp \
    GUI/dialogroutine.cpp \
    kernel/routine.cpp \
    kernel/logdata.cpp

HEADERS  += GUI/mainwindow.h \
    kernel/data.h \
    communication/serialcommunication.h \
    GUI/dialogserialchoose.h \
    communication/buffer.h \
    kernel/sampledata.h \
    GUI/qcustomplot.h \
    kernel/datamanager.h \
    GUI/dialogazimuth.h \
    GUI/dialoggate.h \
    GUI/dialogsamplepoints.h \
    GUI/dialogroutine.h \
    kernel/routine.h \
    kernel/logdata.h

FORMS    += GUI/mainwindow.ui \
    GUI/dialogserialchoose.ui \
    GUI/dialogazimuth.ui \
    GUI/dialoggate.ui \
    GUI/dialogsamplepoints.ui \
    GUI/dialogroutine.ui

RESOURCES += \
    resource.qrc
