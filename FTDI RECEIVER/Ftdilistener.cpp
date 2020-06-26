#include "Ftdilistener.h"

FTDIListener::FTDIListener(QObject *parent) : QObject(parent)
{
    m_packetHead=-1;
    m_packetTail=-1;
    m_packetSize=1024*8*4 + 8;
    m_newData=false;
    m_header = "ff000000";
    m_headerSize = m_header.length();
    m_connected = false;
    m_started = false;
    m_cmd_lodged = false;
    m_0dataCounter=0;
    m_fpscounter = 0;
    m_fps = 0;
}

void FTDIListener::setPacketSize(int packetSize){
    m_packetSize = packetSize;
}

void FTDIListener::startlistener(){

}

void FTDIListener::run(){
    if(!m_connected){
        //start port only after moving listener to its own thread
        m_0dataCounter = 0;
        receivedall=0;

        ftStatus=FT_CreateDeviceInfoList(&iNumDevs);
        if (ftStatus == FT_OK)
        {
            qDebug()<<iNumDevs<<" FTDI devices connected\n";
        }

        ftStatus = FT_Open(0, &ftHandle);
        while(ftStatus != FT_OK)
        {
            qDebug()<<" FT_OPEN failed";
            QThread::sleep(10);
            ftStatus = FT_Open(0, &ftHandle);
        }

        ftStatus = FT_SetBitMode(ftHandle, Mask, Mode);
        if (ftStatus == FT_OK) {
            qDebug()<<"Value set";
        }
        else
        {
            qDebug()<<"Value Failed";
        }
        QString filename  = m_fileName+".txt"; //"C:/Users/IVI_PRIFTI/Desktop/QT Project DFKI/build Single Receiver/"+m_fileName+".txt"; doesnt work

        pFileWorker.setFileName(filename.remove(" ") );

        while(!pFileWorker.open(QIODevice::ReadWrite | QIODevice::Text | QIODevice::Append)){
            qDebug()<<"cannot open file: "<<pFileWorker.fileName()<<pFileWorker.isOpen();
            qDebug()<<pFileWorker.errorString()<<pFileWorker.exists();
        }
        qDebug()<<"FTDIListener Connected";
        m_connected = true;
        m_fpstimer.start();
    }else{
        FT_GetStatus(ftHandle, &RxBytes, &TxBytes, &EventDWord);
        if(RxBytes >1){
                ftStatus=FT_Read(ftHandle, RxBuffer, RxBytes, &BytesReceived);
                //qDebug()<<"read"<<RxBytes<<QByteArray((char*)RxBuffer).size()<<ftStatus;
                if(ftStatus == FT_OK){
                    //qDebug()<<"debug: here";
                    //return;
                    m_mutex.lock();

                    QByteArray newData = QByteArray((char*)RxBuffer,RxBytes).toHex(); //How big to set?
                    //qDebug()<<QThread::currentThread()<<"starting com run"<<newData.size();
                    data += newData;
                    receivedall+=data.size();
                    //qDebug()<<QThread::currentThreadId()<< "received all size: "<<receivedall;
                    qDebug()<<QThread::currentThread()<<"starting com run"<<data.size()<<RxBytes;
                    m_packetHead = data.indexOf(m_header);

                    if(m_packetHead != -1){

                        m_packetTail = data.indexOf(m_header, m_packetHead+m_packetSize);
                        qDebug()<<m_packetHead<<m_packetTail<<m_packetTail-m_packetHead;
                        if(m_packetTail != -1){

                            m_packetData = data.mid(m_packetHead+m_headerSize, m_packetSize-m_headerSize);
                            pFileWorker.write(t.currentTime().toString("hh:mm:ss:zzz").toUtf8().data());
                            pFileWorker.write(",");
                            pFileWorker.write(m_packetData);
                            pFileWorker.write("\n");

                            m_fpscounter++;

                            m_newData = true;

                            data.remove(0,m_packetTail);

                            qDebug()<<"Data size:"<<data.size();
                            m_packetTail = -1;
                        }
                        m_packetHead = -1;
                    }

                    // clean data buffer if overflows
                    if(data.size()>4*m_packetSize){
                        qDebug()<<QThread::currentThreadId()<<"  Clear data overflow"<<data;
                        data.clear();
                        m_packetHead = -1;
                        m_packetTail = -1;
                    }
                    m_mutex.unlock();
                }
                else{
                        disconnect();
                        qDebug()<<QThread::currentThreadId()<<"disconnected";
                        qDebug()<<"ft_read failed\n";
                }
        }

        }
    }

QByteArray FTDIListener::get_Packet(){
    QByteArray dataout;
    m_mutex.lock();
    dataout = m_packetData;
    m_newData = false;
    m_packetData.clear();
    m_mutex.unlock();
    return dataout;
}
bool FTDIListener::ifNew(){
    return m_newData;
}
bool FTDIListener::ifConnected(){
    return m_connected;
}
void FTDIListener::manualStart(){
    m_started = true;
}
void FTDIListener::disconnect(){
    m_connected = false;
}
void FTDIListener::setFileName(QString FileName){
    m_fileName.clear();
    m_fileName.append(FileName);
    QString timestamp = QDateTime::currentDateTime().toString("yyMMdd_hhmmss");
    m_fileName.append(timestamp);
}
double FTDIListener::calculateFPS(){
    if(m_fpstimer.elapsed()>1000){
        m_fps = m_fpscounter;
        m_fpstimer.restart();
        m_fpscounter = 0;
    }
    return m_fps;
}

/*
void FTDIListener::send_cmd(QByteArray cmd_type, QByteArray cmd_data){
    m_mutex.lock();
    m_cmd_lodged = true;
    m_cmd_sent = false;
    m_cmd_verified = false;
    m_cmd_type = cmd_type;
    m_cmd_data = cmd_data;
    m_cmd_back.clear();
    m_mutex.unlock();
}
bool FTDIListener::ifCMDverified(){
    return m_cmd_verified;
}*/
