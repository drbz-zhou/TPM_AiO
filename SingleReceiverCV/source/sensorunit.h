#ifndef SENSORUNIT_H
#define SENSORUNIT_H
/*

COPYRIGHT

All contributions by Deutsches Forschungszentrum für Künstliche Intelligenz, DFKI
Copyright (c) 2016-2017, Bo Zhou
All rights reserved. Free for academic use only.

DESCRIPTION

This class is a container of a sensor's data

*/
#include <QObject>
#include <QVector>
#include <QTime>
#include <QDebug>
#include "include/lpfilter.h"
#include "include/emafilter.h"
#include "include/data_spatial.h"
#include "include/data_temporal.h"

class SensorUnit : public QObject
{
    Q_OBJECT
public:
    explicit SensorUnit(QObject *parent = 0);
    void setDims(int xdim, int ydim);
    void updateValsVector(QVector<double> vals);
    void setValAt(double val, int x, int y);
    QVector<double> getValsVector();
    void setFirstInd(int first);
    void setData2D(data_spatial inData2D);
    void temp_setLength(int length);
    void temp_append(double value);
    double filter_apply(double newSample);

    int m_firstind;
    int m_lastind;
    int m_numel;

    data_spatial copyData2D();
    data_temporal m_wave;
    EMAfilter m_filter;
signals:

public slots:
private:
    //QVector<double> m_vals;
    QVector<int> m_x;
    QVector<int> m_y;
    QTime m_timestamp;

    int m_xdim;
    int m_ydim;

    data_spatial m_data2D;


    //lpfilter m_filter;
};

#endif // SENSORUNIT_H
