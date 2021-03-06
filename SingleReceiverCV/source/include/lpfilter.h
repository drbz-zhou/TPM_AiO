#ifndef LPFILTER_H
#define LPFILTER_H


class lpfilter
{
public:
    // exponential moving average (EMA)
    lpfilter();
    double applyfilter(double newSample);
    void setOld(double input);
    void setAlpha(double input);
private:
    double oldSample;
    double alpha;
    bool firsttime;
};

#endif // LPFILTER_H
