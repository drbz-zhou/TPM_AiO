#include "cvprocessor.h"

CVProcessor::CVProcessor(QObject *parent) : QObject(parent)
{
    m_inPixelDepth = 3;
    qDebug()<<"started CV processor";
    m_numDes = 10;
    m_Objects.resize(1);
}

data_spatial CVProcessor::processFrame(data_spatial inFrame){
    // Convert data_spatial format to cv::Mat
    cv::Mat frameMat = ds2Mat(inFrame, m_PixelBits);

    //-----------------------------
    // Crop frame
    //cv::Rect roi(0, 12, 32, 32);
    //frameMat = frameMat(roi);

    // transpose to get the correct rotation
    //cv::transpose(frameMat,frameMat);

    //-----------------------------
    // Calculate and remove pixelwise DC
    if(m_dcMat.empty()){
       m_dcMat = cv::Mat::zeros(frameMat.rows,frameMat.cols,CV_32F);
    }
    float dcThres = 0.0005;

    cv::Scalar mean, stddev;
    cv::meanStdDev(frameMat,mean,stddev);

    if(stddev[0] < dcThres){
        // update DC mat
        cv::accumulateWeighted(frameMat,m_dcMat,0.1);
    }
    frameMat = frameMat - m_dcMat;

    //-----------------------------
    // Upsample
    int scale = 3;
    int rowsNew = frameMat.rows * scale;
    int colsNew = frameMat.cols * scale;
    cv::Mat frameMatScaled = cv::Mat::zeros(rowsNew,colsNew,CV_32F);
    cv::resize(frameMat,frameMatScaled,cv::Size(rowsNew,colsNew),0,0,cv::INTER_LINEAR);

    //-----------------------------
    // Threshold
    cv::Mat bwFrame;
    double threshold = 0.01;
    //frameMatScaled -= threshold;
    cv::threshold(frameMatScaled, bwFrame, threshold, 1.0, cv::THRESH_BINARY);
// may smooth threshold mask but doesn't seem too be necessary
    int bwFilterBufferSize = 1;
    if(m_bwFilterBuffer.size() < bwFilterBufferSize){
        m_bwFilterBuffer.push_front(bwFrame);
    }
    else{
        m_bwFilterBuffer.pop_back();
        m_bwFilterBuffer.push_front(bwFrame.clone());
    }

    for(int i = 0; i < m_bwFilterBuffer.size(); i++){
        bwFrame = bwFrame.mul(m_bwFilterBuffer[i]);
    }

    //-----------------------------
    // Calculate frame descriptors for object 0
    cv::Mat bwFrameFloat;
    bwFrame.convertTo(bwFrameFloat,CV_32F);
    cv::Mat maskedFrame = frameMatScaled.mul(bwFrameFloat);
    m_Descriptor_Vector=getDescriptorVector(maskedFrame);

    m_Objects[0].m_Pixmap = mat2ds(frameMatScaled);
    m_Objects[0].new_Des_Vector(m_Descriptor_Vector);
    QVector<double> locinfo(4);
    locinfo[0] = 0;
    locinfo[1] = 0;
    locinfo[2] = frameMatScaled.size[0];
    locinfo[3] = frameMatScaled.size[1];
    qDebug()<<locinfo;
    m_Objects[0].m_locinfo =locinfo;


    //-----------------------------
    // Find blobs
    cv::Point minPos, maxPos;
    double min, max;

    bwFrame.convertTo(bwFrame, CV_8U);
    std::vector<std::vector<cv::Point> > contours;
    cv::findContours(bwFrame, contours,CV_RETR_LIST, CV_CHAIN_APPROX_NONE);

    std::vector < std::vector<cv::Point2i> > blobs;

    findBlobs(bwFrame, blobs);

    //qDebug() << blobs.size();

    //find blob centers

    QVariantList circleData;

    int blobMinArea = 64; //8 x 8

    std::vector<cv::Moments> mu(contours.size() );
    for(int i = 0; i < contours.size(); i++){

        cv::Mat blobMat = cv::Mat::zeros(frameMatScaled.rows,frameMatScaled.cols,CV_32F);
        std::vector<cv::Point> pixels = contours[i];

        // skip blobs that are too small
        if(pixels.size() < blobMinArea)
            continue;
        // created a mask frame using blob pixels
        for(int j = 0; j < pixels.size(); j++){
            int x = pixels[j].x;
            int y = pixels[j].y;
            blobMat.at<float>(y,x) = 1;
        }

        cv::Moments mu = cv::moments(contours[i],true);
        if(mu.m00 > 0){
            cv::floodFill(blobMat,cv::Point(mu.m10/mu.m00,mu.m01/mu.m00),1);
        }
        blobMat = blobMat.mul(frameMatScaled);
        cv::imshow("Out", blobMat);

        cv::minMaxLoc(blobMat, &min, &max, &minPos, &maxPos);

        if(mu.m00 > 0){
            double cowX = mu.m10 / mu.m00 / frameMatScaled.cols; // center of weight x, between 0 and 1
            double cowY = mu.m01 / mu.m00 / frameMatScaled.rows; // center of weight y, between 0 and 1
            double weight = mu.m00;

            circleData << cowX << cowY << max; //
        }
        //qDebug() << i << " " << mu[i].m01/mu[i].m00 << " " << mu[i].m02/mu[i].m00 << " " << mu[i].m00;
    }
    qDebug()<<"circleData: "<<circleData;
    m_BlobCircleData = circleData;

    return mat2ds(frameMatScaled);
}
// return calls
double CVProcessor::getM00(){
    return m_M.at(0);
}

QVariantList CVProcessor::getBlobs(){
    return m_BlobCircleData;
}

void CVProcessor::setPixelBits(int inBytes){
    m_PixelBits = inBytes*4-1;
}


QVector<double> CVProcessor::getDescriptorVector(cv::Mat inFrame){
    QVector<double> v_des_vec;
    v_des_vec.reserve(10);
    cv::Moments m = cv::moments(inFrame,false);
    // Calculate global center of weight
    float cowX = 0.5;
    float cowY = 0.5;
    if(m.m00 > 0){
        cowX = m.m10/m.m00/inFrame.rows;
        cowY = m.m01/m.m00/inFrame.cols;
    }
    v_des_vec.append(m.m00);
    v_des_vec.append(cowX);
    v_des_vec.append(cowY);
    v_des_vec.append(m.mu20);
    v_des_vec.append(m.mu11);
    v_des_vec.append(m.mu02);
    v_des_vec.append(m.mu03);
    v_des_vec.append(m.mu21);
    v_des_vec.append(m.mu12);
    v_des_vec.append(m.mu03);

    return v_des_vec;
}

cv::Mat CVProcessor::ds2Mat(data_spatial ds, int inPixelBits){
    int rows = ds.numRows();
    int cols = ds.numCols();
    cv::Mat mat = cv::Mat::zeros(rows,cols,CV_32F);
    long int denominator = 2 << inPixelBits;
    // to scale value between 0 and 1
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            mat.at<float>(i,j) = ds.value(i,j)/denominator;
        }
    }
    return mat;
}

data_spatial CVProcessor::mat2ds(cv::Mat mat){
    int rows = mat.rows;
    int cols = mat.cols;

    data_spatial ds(rows,cols);
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            double value = mat.at<float>(i,j);
            ds.setValue(i,j,value);
        }
    }
    return ds;
}


void CVProcessor::findBlobs(const cv::Mat &binary, std::vector < std::vector<cv::Point2i> > &blobs)
{
    // Finds connected components
    // code from http://nghiaho.com/uploads/code/opencv_connected_component/blob.cpp

    blobs.clear();

    // Fill the label_image with the blobs
    // 0  - background
    // 1  - unlabelled foreground
    // 2+ - labelled foreground

    cv::Mat label_image;
    binary.convertTo(label_image, CV_32SC1);

    int label_count = 2; // starts at 2 because 0,1 are used already

    for(int y=0; y < label_image.rows; y++) {
        int *row = (int*)label_image.ptr(y);
        for(int x=0; x < label_image.cols; x++) {
            if(row[x] != 1) {
                continue;
            }

            cv::Rect rect;
            cv::floodFill(label_image, cv::Point(x,y), label_count, &rect, 0, 0, 8);

            std::vector <cv::Point2i> blob;

            for(int i=rect.y; i < (rect.y+rect.height); i++) {
                int *row2 = (int*)label_image.ptr(i);
                for(int j=rect.x; j < (rect.x+rect.width); j++) {
                    if(row2[j] != label_count) {
                        continue;
                    }

                    blob.push_back(cv::Point2i(j,i));
                }
            }

            blobs.push_back(blob);

            label_count++;
        }
    }
}
