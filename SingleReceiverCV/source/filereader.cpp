#include "filereader.h"

FileReader::FileReader(QObject *parent) : QObject(parent)
{
    m_curFrame = 0;
}
FileReader::~FileReader(){
    m_file.close();
}
void FileReader::loadFile(QString fileName){

    m_file.setFileName(fileName);
    m_fileinfo.setFile(fileName);

    m_posInFile = 0;

    qDebug() << "Loading file: " << fileName;

    if (!m_file.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug() << "Error reading file";
        return;
    }
    QTextStream in(&m_file);
    QString line = in.readLine();
    m_lineLength = in.pos();
    m_totalFrames = m_fileinfo.size()/m_lineLength;
    qDebug() << "line: " << m_lineLength <<" total:" << m_fileinfo.size() << "frames: "<< m_totalFrames;

}
void FileReader::junpToFrame(qint64 frame){

    m_posInFile = m_lineLength*frame;
}
QByteArray FileReader::get_Packet(){

        // pop next line
        QTextStream in(&m_file);
        in.seek(m_posInFile);
        QString line = in.readLine();
        m_curFrame = m_posInFile/m_lineLength;

        qDebug() << "seek: " << m_posInFile ;
        m_posInFile = in.pos();
        m_packetData=line.mid(13).toUtf8();
        //qDebug() << "packet: " << line.size()<<line.mid(13,10000);
        //qDebug() << "packet: " << line.size()<<line.mid(10013,10000);
        //qDebug() << "packet: " << line.size()<<line.mid(20013);
        //qDebug() << "empty message" ;
        // 13 is for jumping timestamp
        return m_packetData;
}
