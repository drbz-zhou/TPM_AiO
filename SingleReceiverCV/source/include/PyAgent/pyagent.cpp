#include "pyagent.h"
#include "pyworker.h"
PyAgent::PyAgent(QObject *parent) : QObject(parent)
{
    m_PyWorker = new PyWorker;
    m_PyWorker->moveToThread(&m_Thread);
    m_Thread.start();
    connect(this, &PyAgent::callFunc, m_PyWorker, &PyWorker::callFuncSlot);
    connect(m_PyWorker, &PyWorker::resultReturn, this, &PyAgent::handle_result);
}

void PyAgent::FuncCall(QString FuncName, QString Arg){
    QString commands = m_PyPath + " " + m_ScriptPath + " " + FuncName + " " + Arg;
    m_Returned = false;
    qDebug()<<QThread::currentThreadId()<<"PyAgent calling: "<<commands;
    emit callFunc(commands);
}

void PyAgent::FuncCall(QString FuncName, QVector<double> Arg){
    QString ArgStr = Vector2QBArray(Arg);
    QString commands = m_PyPath + " " + m_ScriptPath + " " + FuncName + " " + ArgStr;
    m_Returned = false;
    emit callFunc(commands);
}

void PyAgent::handle_result(QByteArray results){
    qDebug()<<QThread::currentThreadId()<<"PyAgent have results: "<<results;
    m_Returned = true;
    QByteArray FuncReturnArray = results.mid(results.indexOf("[")+1,
                                             results.indexOf("]")-results.indexOf("[")-1);
    m_returnData = QBArray2Vector(FuncReturnArray);
}

QVector<double> PyAgent::FuncReturn(){
    // this should be checked with a timer event, so that the thread is not fully occupied
    return m_returnData;
}

bool PyAgent::FuncFinished(){
    return m_Returned;
}

void PyAgent::setPyPath(QString PyPath){
    m_PyPath = PyPath;
}

void PyAgent::setScriptPath(QString ScriptPath){
    m_ScriptPath = ScriptPath;
}

QVector<double> PyAgent::QBArray2Vector(QByteArray inData){
    // from space seperated qbytearray to qvector
    // use this to read data from Python
    QByteArray sep = " ";
    int ind1 = 0;
    int ind2 = 0;
    bool ok;
    QVector<double> outData;
    if(inData.indexOf(sep,0)==-1){// only one value
        outData.append(inData.toDouble(&ok));
    }
    while( inData.indexOf(sep, ind1) != -1 && ind1<inData.length()-1){
        ind2=inData.indexOf(sep, ind1+1);
        if(ind2==-1){// last value
            outData.append(inData.mid(ind1).toDouble(&ok));
        }else if(ind2-ind1>1){ // ignore continuous spaces
            outData.append(inData.mid(ind1,ind2-ind1).toDouble(&ok));
        }
        ind1=ind2;
    }
    return outData;
}

QByteArray PyAgent::Vector2QBArray(QVector<double> inData){
    QByteArray outData;
    QByteArray sep = ",";
    for(int i=0; i<inData.length(); i++){
        outData.append(QString::number(inData.at(i)));
        if(i<inData.length()-1){
            outData.append(sep);
        }
    }
    return outData;
}

void PyAgent::emptyCall(){
    qDebug()<<QThread::currentThreadId()<<"PyAgent empty call";
}
