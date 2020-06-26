#ifndef FILEREADER_H
#define FILEREADER_H
/*

COPYRIGHT

All contributions by Deutsches Forschungszentrum für Künstliche Intelligenz, DFKI
Copyright (c) 2016-2017, Bo Zhou
All rights reserved. Free for academic use only.

DESCRIPTION

This class is the class that handles reading a saved data file and retrive data packet

*/
#include <QObject>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QFileInfo>

class FileReader : public QObject
{
    Q_OBJECT
public:
    explicit FileReader(QObject *parent = 0);
    ~FileReader();
    // Load file into file reader
    void loadFile(QString fileName);

    // Read a data line from file

    QByteArray get_Packet();

    void junpToFrame(qint64 frame);
    int m_totalFrames;
    int m_curFrame;

signals:

public slots:

private:
    QString m_data;
    QFile m_file;
    QFileInfo m_fileinfo;
    qint64 m_posInFile;
    qint64 m_lineLength;

    QTextStream m_textStream;

    QByteArray m_packetData;
};

#endif // FILEREADER_H
