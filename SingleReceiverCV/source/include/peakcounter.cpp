#include "peakcounter.h"

PeakCounter::PeakCounter(QObject *parent) : QObject(parent)
{
    m_state = 0;
    // 0: low/idle, 1: rise, 2: high,  3: fall
    m_counter = 0;
    m_constraints_mincyc.resize(4);
    m_constraints_mincyc.fill(3);
    m_constraints_maxcyc.resize(4);
    m_constraints_maxcyc.fill(40);
    m_stateCounter = 0;
    m_thresh_idle = 10;
    m_idleLim = 100;
}
int PeakCounter::feedpoint(double newVal){
    /// reset peak counter if been idle for m_idleLim samples;
    if(newVal < m_thresh_idle) {
        m_idleCounter++;
        m_state = 0;
    } else{
        m_idleCounter = 0;
    }
    if(m_idleCounter > m_idleLim ){
        m_idleCounter = 0;
        m_counter = 0;
    }
    /// state transition
    switch (m_state) {
    case 0:
        m_stateCounter++;
        if(newVal>m_thresh_low && newVal > m_thresh_idle){
            m_state = 1;
            m_stateCounter=0;
        }
        break;
    case 1:
        m_stateCounter++;
        // check for state max/min limits
        if(m_stateCounter > m_constraints_maxcyc[1]){
            m_state = 0;
            m_stateCounter = 0;
            break;
        }else if(m_stateCounter > m_constraints_mincyc[1]){
            if(newVal>m_thresh_high){
                m_state = 2;
                m_stateCounter = 0;
                break;
            }
        }
        break;
    case 2:
        m_stateCounter++;
        // check for state max/min limits
        if(m_stateCounter > m_constraints_maxcyc[2]){
            m_state = 0;
            m_stateCounter = 0;
            break;
        }else if(m_stateCounter > m_constraints_mincyc[2]){
            if(newVal<m_thresh_high){
                m_state = 3;
                m_counter++;
                m_stateCounter = 0;
                break;
            }
        }
        break;
    case 3:
        m_stateCounter++;
        // check for state max/min limits
        if(m_stateCounter > m_constraints_maxcyc[3]){
            m_state = 0;
            m_stateCounter = 0;
            break;
        }else if(m_stateCounter > m_constraints_mincyc[3]){
            if(newVal < m_thresh_low){
                m_state = 0;
                m_stateCounter = 0;
                break;
            }
        }
        break;
    default:
        break;
    }
    qDebug()<<"peak counter:"<<m_state<<m_counter;
    return m_counter;
}
