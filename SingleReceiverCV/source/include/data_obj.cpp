#include "data_obj.h"

data_obj::data_obj()
{
    setNumDes(10);
    setWindowSize(100);
}

void data_obj::new_Des_Vector(QVector<double> newVec){
    m_Descriptor_Vector = newVec;
    for(int i=0; i<m_Descriptor_Vector.length();i++){
        m_Descriptor_Window[i].circleAppend(m_Descriptor_Vector[i]);
    }
}

void data_obj::setWindowSize(int newSize){
    m_WindowSize = newSize;
    for(int i=0; i<m_Descriptor_Window.length();i++){
        m_Descriptor_Window[i].setLength(m_WindowSize);
    }
}

void data_obj::setNumDes(int newNum){
    m_numDes = newNum;
    m_Descriptor_Vector.resize(m_numDes);
    m_Descriptor_Window.resize(m_numDes);
}
