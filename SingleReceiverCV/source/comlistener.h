#ifndef COMLISTENER_H
#define COMLISTENER_H
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

class COMListener : public QObject
{
    Q_OBJECT
public:
    explicit COMListener(QObject *parent = 0);
    QByteArray get_Packet();
    bool ifNew();
    void close();
    bool ifConnected();
    void manualStart();
    void disconnect();
    //void send_cmd(QByteArray cmd_type, QByteArray cmd_data);
    //bool ifCMDverified();
    double calculateFPS();
    /// settings
    void setPort(QString portname);
    void setPacketSize(int packetsize);
    void setHeader(QByteArray new_Header);
    void setFileName(QString FileName);
    void setSaveDir(QString dir);
    void setIfSave(bool ifSave);
signals:

public slots:
    void run();

private:

    QSerialPort serial;
    QByteArray data;
    long int receivedall;

    QString m_port;

    int m_Header_1;
    int m_Header_2;
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
    QString m_dir;
    bool m_ifSave;

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

#endif // COMLISTENER_H
