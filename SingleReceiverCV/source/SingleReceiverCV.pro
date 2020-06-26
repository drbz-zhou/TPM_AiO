#-------------------------------------------------
#
# Project created by QtCreator 2017-04-12T09:50:41
#
#-------------------------------------------------

QT       += core gui serialport opengl quick printsupport webchannel widgets websockets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SingleReceiver
TEMPLATE = app

#include path for openCV
INCLUDEPATH += C:/opencv/opencv/build/include

SOURCES += main.cpp\
        mainwindow.cpp \
    comlistener.cpp \
    qmlagent.cpp \
    frameparser.cpp \
    sensorunit.cpp \
    include/data_spatial.cpp \
    include/data_temporal.cpp \
    include/lpfilter.cpp \
    include/imageprovider_matrix.cpp \
    include/qcustomplot/qcustomplot.cpp \
    include/imageprovider_plot.cpp \
    filereader.cpp \
    include/PyAgent/pyagent.cpp \
    include/PyAgent/pyworker.cpp \
    include/WebChannelWrapper/webchanneldataobj.cpp \
    include/WebChannelWrapper/webchannelwrapper.cpp \
    include/WebChannelWrapper/websocketclientwrapper.cpp \
    include/WebChannelWrapper/websockettransport.cpp \
    Ftdilistener.cpp \
    include/cvprocessor.cpp \
    include/data_obj.cpp \
    include/peakcounter.cpp \
    include/gapmeasure.cpp \
    include/emafilter.cpp

HEADERS  += mainwindow.h \
    comlistener.h \
    qmlagent.h \
    frameparser.h \
    sensorunit.h \
    include/data_spatial.h \
    include/data_temporal.h \
    include/lpfilter.h \
    include/imageprovider_matrix.h \
    include/qcustomplot/qcustomplot.h \
    include/imageprovider_plot.h \
    filereader.h \
    include/PyAgent/pyagent.h \
    include/PyAgent/pyworker.h \
    include/WebChannelWrapper/webchanneldataobj.h \
    include/WebChannelWrapper/webchannelwrapper.h \
    include/WebChannelWrapper/websocketclientwrapper.h \
    include/WebChannelWrapper/websockettransport.h \
    Ftdilistener.h \
    include/cvprocessor.h \
    include/data_obj.h \
    include/peakcounter.h \
    include/gapmeasure.h \
    include/emafilter.h

FORMS    += mainwindow.ui

DISTFILES += \
    QMLGUI.qml

RESOURCES += \
    resources.qrc

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/./ -lftd2xx
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/./ -lftd2xx
else:unix: LIBS += -L$$PWD/./ -lftd2xx

INCLUDEPATH += $$PWD/.
DEPENDPATH += $$PWD/.

# openCV libraries
LIBS += -LC:\\opencv\\opencv_bin\\bin \
    libopencv_core248d \
    libopencv_highgui248d \
    libopencv_imgproc248d \
    libopencv_features2d248d \
    libopencv_calib3d248d \
