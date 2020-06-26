#ifndef GAPMEASURE_H
#define GAPMEASURE_H

#include <QObject>
#include <QDebug>

class GapMeasure : public QObject
{
    Q_OBJECT
public:
    explicit GapMeasure(QObject *parent = 0);
    int feedpoint(double newVal);
    int m_gapWidth;
    double m_thresh;

signals:

public slots:

private:
    int m_state;
    int m_gapCounter;
};

#endif // GAPMEASURE_H
