#ifndef FTDILISTENER_H
#define FTDILISTENER_H
/*

COPYRIGHT

All contributions by Deutsches Forschungszentrum für Künstliche Intelligenz, DFKI
Copyright (c) 2016-2017, Bo Zhou
All rights reserved. Free for academic use only.

DESCRIPTION

This class contains the serial/bluetooth receiving functionalities

*/

#include <QObject>
#include <QtSerialPort/QtSerialPort>
#include <QTimer>
#include <QFile>
#include <QTime>
#include <QVector>
#include <QElapsedTimer>
#include <windows.h>
#include "ftd2xx.h"

class FTDIListener : public QObject
{
    Q_OBJECT
public:
    explicit FTDIListener(QObject *parent = 0);
    void startlistener();
    QByteArray get_Packet();
    void setPacketSize(int packetsize);
    bool ifNew();
    void close();
    bool ifConnected();
    void manualStart();
    void disconnect();
    void setFileName(QString FileName);
    //void send_cmd(QByteArray cmd_type, QByteArray cmd_data);
    //bool ifCMDverified();
    QVector<double> currentPacket;
    double calculateFPS();
signals:

public slots:
    void run();

private:
    DWORD iNumDevs;
    FT_STATUS ftStatus;
    FT_HANDLE ftHandle; //handler for the external device
    UCHAR Mask = 0xff;
    UCHAR Mode = 0x40; // Set synchronous parallel FIFO
    DWORD TxBytes;
    DWORD RxBytes; //variable that indicates how many bytes are in buffer
    DWORD EventDWord;
    DWORD BytesReceived; //indicates how many bytes were read from buffer
    UCHAR RxBuffer[65536];//max. value of bytes that can be read from buffer //in each access
    unsigned int count=0, i=0, jval=0 , err_count = 0; //j1 is used in library maths... I have no idea but gives an error

    QByteArray data; //replace store with data
    long int receivedall;

    int m_packetHead;
    int m_packetTail;
    int m_packetSize;
    int m_headerSize;
    QByteArray m_header;

    QByteArray m_packetData;
    bool m_newData;
    bool m_connected;
    bool m_started;

    QMutex m_mutex;

    int m_0dataCounter;

    QFile pFileWorker;
    QTime t;
    QString m_fileName;

    bool m_cmd_lodged;
    bool m_cmd_sent;
    bool m_cmd_verified;
    QByteArray m_cmd_type;
    QByteArray m_cmd_data;
    QByteArray m_cmd_back;

    double m_fpscounter;
    QElapsedTimer m_fpstimer;
    double m_fps;
};

#endif // FTDIListener_H
