#ifndef QMLAGENT_H
#define QMLAGENT_H
/*

COPYRIGHT

All contributions by Deutsches Forschungszentrum für Künstliche Intelligenz, DFKI
Copyright (c) 2016-2017, Bo Zhou
All rights reserved. Free for academic use only.

DESCRIPTION

This class is the QML interface that connects the c++ code to the qml visualization

*/
#include <QObject>
#include <QQmlApplicationEngine>
#include "include/data_spatial.h"
#include "include/imageprovider_matrix.h"
#include "include/imageprovider_plot.h"

class QMLAgent : public QObject
{
    Q_OBJECT
public:
    explicit QMLAgent(QObject *parent = 0);
    void drawFrame(data_spatial data2D);
    void addDataToGraph(QString graphKey, double dataPoint);
    void setYRange(double min, double max);
    void drawCircles(QVariantList circleData);
    void setLabel_1(QString info);

signals:

public slots:
    void respond_click(QString v);

private:
    QQmlApplicationEngine m_qmlEngine;
    QObject *m_qmlRootObject;
    ImageProvider_plot plotprovider_1;
    QObject *m_qmlPlotObject_1;
    ImageProvider_matrix m_MatrixProvider;
    QObject *m_qmlMatrixObject_1;
    QObject *m_qmlCanvasObject;
    QObject *m_qmlSigItemObject;
};

#endif // QMLAGENT_H
