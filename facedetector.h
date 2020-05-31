#ifndef FACEDETECTOR_H
#define FACEDETECTOR_H

#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/objdetect.hpp"
#include "opencv2/face.hpp"
#include <QImage>
#include <QObject>
#include <QMap>

using namespace cv;
using namespace  cv::face;

class FaceDetector : public QObject
{
public:
    FaceDetector();
    std::vector<Rect> detectFaces(const Mat &frame);
    void trainFromPath(QString path);
    void addTrainData(Mat img,QString lable);
    void train();
    QString predict(Mat img);
    void resetTrainData();

private:
    bool                     mIsInit;
    bool                     mIsRecognizerTrained;
    CascadeClassifier        mFaceClassifier;
    Ptr<FaceRecognizer>      mFaceRecognizer;

    std::vector<Mat>         images;
    std::vector<int>         labels;
    QMap<int,QString>        mFaceLabels;
    int                      mCurrentFaceLabelCount;

};

#endif // FACEDETECTOR_H
