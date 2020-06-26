#-------------------------------------------------
#
# Project created by QtCreator 2017-04-12T09:50:41
#
#-------------------------------------------------

QT       += core gui serialport opengl quick printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SingleReceiver
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    Ftdilistener.cpp

HEADERS  += mainwindow.h \
    Ftdilistener.h

FORMS    += \
    mainwindow.ui

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/./ -lftd2xx
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/./ -lftd2xxd
else:unix: LIBS += -L$$PWD/./ -lftd2xx

INCLUDEPATH += $$PWD/.
DEPENDPATH += $$PWD/.
