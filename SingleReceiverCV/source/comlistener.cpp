#include "comlistener.h"

COMListener::COMListener(QObject *parent) : QObject(parent)
{
    // defaults
    m_Header_1=-1;
    m_Header_2=-1;
    m_packetSize=1024*3 + 8;
    m_newData=false;
    m_port = "COM3";
    m_header = "ff000000";
    m_headerSize = m_header.length();
    m_connected = false;
    m_started = false;
    m_cmd_lodged = false;
    m_0dataCounter=0;
    m_fpscounter = 0;
    m_fps = 0;
    m_dir = "C:/data/";
    m_ifSave = true;
}

void COMListener::run(){
    if(!m_connected){
        //start port only after moving listener to its own thread
        m_0dataCounter = 0;
        receivedall=0;
        serial.close();
        serial.clear();
        serial.setPortName(m_port);
        serial.setBaudRate(921600);//921600
        serial.setDataBits(QSerialPort::Data8);
        serial.setParity(QSerialPort::NoParity);
        serial.setStopBits(QSerialPort::OneStop);
        serial.setFlowControl(QSerialPort::NoFlowControl);
        serial.setReadBufferSize(1352);
        serial.open(QIODevice::ReadWrite);
        while(!serial.isOpen()){
            qDebug()<<"Error opening device, err:"<<serial.error();
            qDebug()<<"port: "<<serial.portName()<<m_port;
            serial.close();
            QThread::sleep(1);
            serial.open(QIODevice::ReadWrite);
        }

        // save file
        if(m_ifSave){
            QString filename  = m_dir+m_fileName+".txt";
            pFileWorker.setFileName(filename.remove(" ") );
            while(!pFileWorker.open(QIODevice::ReadWrite | QIODevice::Text | QIODevice::Append)){
                qDebug()<<"cannot open file: "<<pFileWorker.fileName()<<pFileWorker.isOpen();
                qDebug()<<pFileWorker.errorString()<<pFileWorker.exists();
            }
        }
        qDebug()<<"COMListener: port opened!";
        m_connected = true;
        m_fpstimer.start();
    }else{
        //qDebug()<<serial.isOpen();
        if(serial.isOpen() ){


                m_mutex.lock();
                QByteArray newData = serial.readAll().toHex();
                //qDebug()<<QThread::currentThread()<<"received new data: "<<newData;
                if(!serial.isOpen()){
                    disconnect();
                    qDebug()<<QThread::currentThreadId()<<"disconnected";
                }

                data += newData;
                receivedall+=data.size();
                //qDebug()<<QThread::currentThreadId()<< "received all size: "<<receivedall;


                qDebug()<<QThread::currentThread()<<"COM Listener run process, read buffer size: "<<data.size()<<m_packetSize;
                m_Header_1 = data.indexOf(m_header);
                //qDebug()<<m_Header_1;
                if(m_Header_1 != -1){
                    m_Header_2 = data.indexOf(m_header, m_Header_1+m_headerSize);

                    if(m_Header_2 != -1){
                        if(m_Header_2-m_Header_1 == m_packetSize){
                            qDebug()<<QThread::currentThread()<<m_Header_1<<m_Header_2<<" Packet size: "<<m_Header_2-m_Header_1;
                            m_packetData = data.mid(m_Header_1+m_headerSize, m_packetSize-m_headerSize);
                            if(m_ifSave){
                                pFileWorker.write(t.currentTime().toString("hh:mm:ss:zzz").toUtf8().data());
                                pFileWorker.write(",");
                                pFileWorker.write(m_packetData);
                                pFileWorker.write("\n");
                            }

                            m_fpscounter++;

                            m_newData = true;
                        }
                        data.remove(0,m_Header_2);

                        //qDebug()<<"Packet Data size:"<<m_packetData.size();
                        m_Header_2 = -1;
                    }
                    m_Header_1 = -1;
                }

                // cleanse data buffer if overflows
                if(data.size()>10*m_packetSize){
                    qDebug()<<QThread::currentThreadId()<<"  Clear data overflow"<<data;
                    data.clear();
                    m_Header_1 = -1;
                    m_Header_2 = -1;
                }
                m_mutex.unlock();

        }
    }
}

QByteArray COMListener::get_Packet(){
    QByteArray dataout;
    m_mutex.lock();
    dataout = m_packetData;
    m_newData = false;
    m_packetData.clear();
    m_mutex.unlock();
    return dataout;
}
bool COMListener::ifNew(){
    return m_newData;
}
void COMListener::close(){
    serial.close();
}
bool COMListener::ifConnected(){
    return m_connected;
}
void COMListener::manualStart(){
    m_started = true;
}
void COMListener::disconnect(){
    m_connected = false;
}
double COMListener::calculateFPS(){
    if(m_fpstimer.elapsed()>1000){
        m_fps = m_fpscounter;
        m_fpstimer.restart();
        m_fpscounter = 0;
    }
    return m_fps;
}
/// settings
void COMListener::setPort(QString portname){
    m_port = portname;
}
void COMListener::setPacketSize(int packetSize){
    m_packetSize = packetSize;
}

void COMListener::setHeader(QByteArray new_Header){
    m_header = new_Header;
}

void COMListener::setFileName(QString FileName){
    m_fileName.clear();
    m_fileName.append(FileName);
    QString timestamp = QDateTime::currentDateTime().toString("yyMMdd_hhmmss");
    m_fileName.append(timestamp);
}

void COMListener::setSaveDir(QString dir){
    m_dir = dir;
}

void COMListener::setIfSave(bool ifSave){
    m_ifSave = ifSave;
}

/*
void COMListener::send_cmd(QByteArray cmd_type, QByteArray cmd_data){
    m_mutex.lock();
    m_cmd_lodged = true;
    m_cmd_sent = false;
    m_cmd_verified = false;
    m_cmd_type = cmd_type;
    m_cmd_data = cmd_data;
    m_cmd_back.clear();
    m_mutex.unlock();
}
bool COMListener::ifCMDverified(){
    return m_cmd_verified;
}*/
