#ifndef PYWORKER_H
#define PYWORKER_H

#include <QObject>
#include <QDebug>
#include <QThread>
#include <QProcess>

class PyWorker : public QObject
{
    Q_OBJECT
public:
    explicit PyWorker(QObject *parent = 0);

signals:
    void resultReturn(QByteArray results);
public slots:
    void callFuncSlot(QString callpara);
private:

};

#endif // PYWORKER_H
