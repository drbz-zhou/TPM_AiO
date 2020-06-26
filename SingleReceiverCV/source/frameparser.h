#ifndef FRAMEPARSER_H
#define FRAMEPARSER_H
/*

COPYRIGHT

All contributions by Deutsches Forschungszentrum für Künstliche Intelligenz, DFKI
Copyright (c) 2016-2017, Bo Zhou
All rights reserved. Free for academic use only.

DESCRIPTION

This class contains the process to parse a data packet from hex to a linear double vector

*/
#include <QObject>
#include <QVector>
#include <QDebug>

class frameparser : public QObject
{
    Q_OBJECT
public:
    explicit frameparser(QObject *parent = 0);
    QVector<double> parseBytePacket(QByteArray byteData);
    double mean(QVector<double> input);
    double max(QVector<double> input);
    QString VecDouble2Str(QVector<double>  input);
    void setFormat(int ptr_step, bool two);

private:
    int m_ptr_step;
    bool m_twocomp = false;
};

#endif // FRAMEPARSER_H
