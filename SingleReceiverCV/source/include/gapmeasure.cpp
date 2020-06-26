#include "gapmeasure.h"

GapMeasure::GapMeasure(QObject *parent) : QObject(parent)
{
    m_gapWidth = 0;
    m_thresh = 15;
    m_state = 0; // 0: before, 1: gap counting, 2: after, ready to read gap
    m_gapCounter = 0;
}
int GapMeasure::feedpoint(double newVal){
    switch (m_state) {
    case 0:
        m_gapCounter = 0;
        if(newVal<m_thresh){
            m_state = 1;
            break;
        }
        break;
    case 1:
        if(newVal>m_thresh){
            m_state = 2;
            break;
        }else if(m_gapCounter>40){ //reset
            m_state = 0;
        }else{
            m_gapCounter++;
            break;
        }
    case 2:
        m_gapWidth = m_gapCounter;
        m_state = 0;
        break;
    default:
        break;
    }
    qDebug()<<"gap measure: "<< m_state << m_gapCounter;
    return m_state;
}
