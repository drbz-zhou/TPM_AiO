#include "frameparser.h"

frameparser::frameparser(QObject *parent) : QObject(parent)
{
    // member initializers
    m_ptr_step = 3;
}

QVector<double> frameparser::parseBytePacket(QByteArray byteData){
    // from hex string to the vector of double, output still linear, not 2D
    int ptr;
    QVector<double> currentPacket;
    for(ptr=0; ptr<byteData.size();ptr=ptr+m_ptr_step){
        QByteArray byteField = byteData.mid(ptr, m_ptr_step);
        bool ok;
        double dataValue = byteField.toLong(&ok, 16); //hex to int

        /// correct for twos complement
        if(m_twocomp){
            if(dataValue>32768){
                dataValue = dataValue - 65536;
            }
            dataValue = dataValue + 32768;
        }
        /// end twos complement
        currentPacket.append(dataValue);
    }
    qDebug()<<currentPacket.size()<<byteData.size()<<ptr;
    return currentPacket;
}

double frameparser::mean(QVector<double> input){
    double meanval = 0;
    for(int i=0; i<input.size(); i++){
        meanval += input.at(i);
    }
    meanval /= input.size();
    return meanval;
}
double frameparser::max(QVector<double> input){
    double maxval = 0;
    for(int i=0; i<input.size(); i++){
        maxval = maxval>input.at(i)?maxval:input.at(i);
    }
    return maxval;
}

QString frameparser::VecDouble2Str(QVector<double>  input){
    QString output;
    qDebug()<<input.size()<<input;
    for(int i=0; i<input.size(); i++){
        output.append(QString::number(input.at(i))).append(",");
    }
    return output;
}

void frameparser::setFormat(int ptr_step, bool two){
    m_ptr_step = ptr_step;
    m_twocomp = two;
    qDebug()<<"format set: step "<<ptr_step <<" twos comp: " << two;
}
