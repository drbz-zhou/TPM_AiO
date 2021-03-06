#include "data_temporal.h"

data_temporal::data_temporal()
{
    m_lengthLim = -1;
}
data_temporal::data_temporal(int lengthLim)
{
    setLength(lengthLim);
}

void data_temporal::setValue(int index, double value){
    if(index < 0 || index >= m_dataLinear.length()){
        qDebug()<< "data_temporal::setValue: Error: index out of bound, index" << index;
        return;
    }
    m_dataLinear[index] = value;
}

void data_temporal::insert(int index, double value){
    m_dataLinear.insert(index, value);
}

void data_temporal::append(double value){
    m_dataLinear.append(value);
}

void data_temporal::circleAppend(double value){
    m_dataLinear.append(value);
    trim();
}

void data_temporal::setLength(int lengthLim){
    m_lengthLim = lengthLim;
    m_dataLinear.reserve(m_lengthLim);
}

void data_temporal::prepend(double value){
    m_dataLinear.prepend(value);
}

double data_temporal::at(int index){
    return m_dataLinear.at(index);
}

QVector<double> data_temporal::mid(int index, int length){
    return m_dataLinear.mid(index, length);
}

data_temporal data_temporal::copy(){
    data_temporal newData(m_lengthLim);
    for(int i=0; i<m_dataLinear.length(); i++){
        newData.append(m_dataLinear.at(i));
    }
    return newData;
}

double data_temporal::min(){
    if(m_dataLinear.length()>0){
        double minVal = m_dataLinear[0];
        for(int i=0; i<m_dataLinear.length(); i++){
            minVal = minVal < m_dataLinear[i] ? minVal : m_dataLinear[i];
        }
        return minVal;
    }else{
        return 0;
    }
}

double data_temporal::max(){
    if(m_dataLinear.length()>0){

        double maxVal = m_dataLinear[0];
        for(int i=0; i<m_dataLinear.length(); i++){
            maxVal = maxVal > m_dataLinear[i] ? maxVal : m_dataLinear[i];
        }
        return maxVal;
    }else{
        return 0;
    }
}

double data_temporal::sum(){
    double v_sum = 0;
    for(int i=0; i<m_dataLinear.length(); i++){
        v_sum += m_dataLinear[i];
    }
    return v_sum;
}
double data_temporal::mean(){
    if(m_dataLinear.length()==0){
        return 0;
    }
    return sum()/m_dataLinear.length();
}

void data_temporal::trim(){ //cut
    if(m_lengthLim <0){
        qDebug()<< "data_temporal::trim: no length limit";
        return;
    }
    while(m_dataLinear.length()>m_lengthLim){
        m_dataLinear.removeFirst();
    }
}
int data_temporal::size(){
    return m_dataLinear.size();
}

QVector<double> data_temporal::data(){
    return m_dataLinear;
}
