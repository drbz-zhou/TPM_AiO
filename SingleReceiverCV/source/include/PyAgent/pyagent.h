#ifndef PYAGENT_H
#define PYAGENT_H

#include <QObject>
#include "pyworker.h"
#include <QThread>
#include <QVector>

class PyAgent : public QObject
{
    Q_OBJECT
public:
    explicit PyAgent(QObject *parent = 0);
    void FuncCall(QString FuncName, QString Arg);
    void FuncCall(QString FuncName, QVector<double> Arg);
    QVector<double> FuncReturn();
    bool FuncFinished();

    void setPyPath(QString PyPath);
    void setScriptPath(QString ScriptPath);

    QVector<double> QBArray2Vector(QByteArray inData);
    QByteArray Vector2QBArray(QVector<double> inData);

    void emptyCall();

signals:
    void callFunc(QString callpara);
public slots:
    void handle_result(QByteArray results);
private:
    PyWorker* m_PyWorker;
    QThread m_Thread;

    QString m_PyPath = "C:\\Python\\Anaconda3\\python";
    QString m_ScriptPath = "C:/owncloud/Git/dfki-3017/TPM/PyTPM/CMD.py";

    bool m_Returned = false;
    QVector<double> m_returnData;
};

#endif // PYAGENT_H
