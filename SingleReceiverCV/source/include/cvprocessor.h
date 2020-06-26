// this class contains openCV methods to process a frame
// to use this class the .pro file needs to be modified:
// INCLUDEPATH += C:/opencv/opencv/build/include
// LIBS += -LC:\\opencv\\opencv_bin\\bin \
//     libopencv_core248d \
//     libopencv_highgui248d \
//     libopencv_imgproc248d \
//     libopencv_features2d248d \
//     libopencv_calib3d248d \

#ifndef CVPROCESSOR_H
#define CVPROCESSOR_H

#include <QObject>
#include "data_spatial.h"
#include "data_temporal.h"
#include "data_obj.h"

#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv/cv.h"

class CVProcessor : public QObject
{
    Q_OBJECT
public:
    explicit CVProcessor(QObject *parent = 0);
    // convertion between DataFrame and cv::Mat
    cv::Mat ds2Mat(data_spatial ds, int inPixelBits);
    data_spatial mat2ds(cv::Mat);
    void setPixelBits(int inBytes);
    // return calls
    double getM00();
    QVariantList getBlobs();
    QVector<double> getDescriptorVector(cv::Mat inFrame);
signals:

public slots:
    data_spatial processFrame(data_spatial inFrame);

private:
    void findBlobs(const cv::Mat &binary, std::vector < std::vector<cv::Point2i> > &blobs);
    int m_PixelBits;
    cv::Mat m_dcMat;
    QList<cv::Mat> m_bwFilterBuffer;

    int m_inPixelDepth;
    QVector<double> m_M;
    QVariantList m_BlobCircleData;
    QVector<double> m_Descriptor_Vector;
    QVector<data_obj> m_Objects;
    int m_numDes;
    int m_windowSize=100;
};

#endif // CVPROCESSOR_H
