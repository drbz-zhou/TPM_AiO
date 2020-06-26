#ifndef MAINWINDOW_H
#define MAINWINDOW_H
/*

COPYRIGHT

All contributions by Deutsches Forschungszentrum für Künstliche Intelligenz, DFKI
Copyright (c) 2016-2017, Bo Zhou
All rights reserved. Free for academic use only.

DESCRIPTION

This class is the main function hub for receiving data, visualizing (optional) and
send out through web socket

*/

#include <QMainWindow>
#include <comlistener.h>
#include <filereader.h>
#include <QTimer>
#include <QElapsedTimer>
#include <QComboBox>
#include "qmlagent.h"
#include "frameparser.h"
#include "sensorunit.h"
#include <QThread>
#include "include/PyAgent/pyagent.h"
#include "include/WebChannelWrapper/webchannelwrapper.h"
#include "include/data_temporal.h"
#include "include/data_spatial.h"
#include <Ftdilistener.h>
#include "include/cvprocessor.h"
#include "include/peakcounter.h"
#include "include/gapmeasure.h"
#include "include/emafilter.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
public slots:
    void mainRoutine();
    void callPython();
    void sendToJS();

private slots:
    void on_Button_ScanPorts_clicked();

    void on_Button_Start_clicked();

    void on_DIM_X_editingFinished();

    void on_DIM_Y_editingFinished();

    void on_Button_Browse_clicked();

    void on_Button_Browse_Save_clicked();

    void on_checkBox_basic_clicked(bool checked);

    void on_PosInFileBar_sliderReleased();

private:
    void setupListener();
    void setupFTListener();
    void setupFilereader();
    QStringList scanPorts();
    int getPacketSize();
    void setHardParameter();

    Ui::MainWindow *ui;

    COMListener m_listener;
    FileReader m_fileReader;
    QTimer m_listenerTimer;
    QComboBox m_portSelect;
    QTimer m_mainTimer;
    QMLAgent m_QMLAgent;
    frameparser m_FrameParser;
    SensorUnit m_Sensor;

    int m_sourceMode = 0; // 0: COM, 1: File

    int m_DIMX;
    int m_DIMY;
    int m_PixelDepth;
    QByteArray m_Header;

    PyAgent m_PyAgent;
    QTimer m_PyTimer;

    WebChannelWrapper m_WebChannel;

    FTDIListener m_FTlistener;
    data_temporal m_valueRoundBuffer;
    CVProcessor m_CVProcessor;
    QMap<QString, bool> m_flags;

    PeakCounter m_PKcounter;
    GapMeasure m_GPmeasure;
};

#endif // MAINWINDOW_H
