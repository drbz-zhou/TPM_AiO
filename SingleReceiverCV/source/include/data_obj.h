#ifndef DATA_OBJ_H
#define DATA_OBJ_H

#include "data_spatial.h"
#include "data_temporal.h"

class data_obj
{
public:
    data_obj();
    void new_Des_Vector(QVector<double> newVec);
    void setWindowSize(int newSize);
    void setNumDes(int newNum);

    QVector<data_temporal> m_Descriptor_Window;
    QVector<double> m_Descriptor_Vector;
    data_spatial m_Pixmap;
    QVector<double> m_locinfo; //x, y, w, h
    int m_WindowSize;
    int m_numDes;

private:


};

#endif // DATA_OBJ_H
