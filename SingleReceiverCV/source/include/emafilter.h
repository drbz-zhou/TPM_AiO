#ifndef EMAFILTER_H
#define EMAFILTER_H


class EMAfilter
{
public:
    EMAfilter();
    double addSample(double newSample);
    double getHighPass();
    double getLowPass();
    void setOld(double input);
    void setAlpha(double input);

private:
    double oldSample;
    double alpha;
    bool firsttime;
    double m_hp;
    double m_lp;
};

#endif // EMAFILTER_H
