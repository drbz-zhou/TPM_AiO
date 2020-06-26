#include "emafilter.h"

EMAfilter::EMAfilter()
{
    oldSample = 0;
    alpha = 1.0/3.0;
    firsttime = true;
}

double EMAfilter::addSample(double newSample){
    if(firsttime){
        oldSample = newSample;
        firsttime=false;
    }else{
        oldSample = alpha * newSample + (1-alpha) * oldSample;
    }
    m_hp = newSample - oldSample;
    m_lp = oldSample;
    return oldSample;
}

double EMAfilter::getHighPass(){
    return m_hp;
}

double EMAfilter::getLowPass(){
    return m_lp;
}

void EMAfilter::setOld(double input){
    oldSample=input;
}

void EMAfilter::setAlpha(double input){
    alpha = input;
}
