#ifndef PEAKCOUNTER_H
#define PEAKCOUNTER_H

#include <QObject>
#include <QDebug>

class PeakCounter : public QObject
{
    Q_OBJECT
public:
    explicit PeakCounter(QObject *parent = 0);
    int feedpoint(double newVal);

    double m_thresh_low;
    double m_thresh_high;
    double m_thresh_idle;
    int m_idleLim;
signals:

public slots:
private:
    int m_state;
    int m_counter;
    QVector<int> m_constraints_mincyc;
    QVector<int> m_constraints_maxcyc;
    int m_stateCounter;
    int m_idleCounter;
};

#endif // PEAKCOUNTER_H
