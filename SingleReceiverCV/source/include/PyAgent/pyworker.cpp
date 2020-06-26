#include "pyworker.h"

PyWorker::PyWorker(QObject *parent) : QObject(parent)
{

}

void PyWorker::callFuncSlot(QString callpara){
    QProcess m_Process;
    // shouldn't be created on start up since it needs to be moved to thread
    qDebug()<<QThread::currentThreadId()<<"PyWorker: "<<callpara;

    m_Process.start(callpara);

    bool processFinished=m_Process.waitForFinished(100000); // blocking up to 100 seconds
    qDebug()<<QThread::currentThreadId()<<"m_Process finished: "<<processFinished;

    QByteArray FuncOutput = m_Process.readAllStandardOutput();
    qDebug()<<QThread::currentThreadId()<<"m_Process returns: "<<FuncOutput;

    emit resultReturn(FuncOutput);
}

