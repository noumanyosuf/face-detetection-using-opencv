#include "facedetector.h"
#include <QDebug>
#include <QDir>
#include "globalconstants.h"

using namespace cv;
using namespace  cv::face;

FaceDetector::FaceDetector(): mIsInit(false),
    mIsRecognizerTrained(false),
    mCurrentFaceLabelCount(0)
{
    qDebug()<<Q_FUNC_INFO;

    if(mFaceClassifier.load(CASCADE_NAME.toStdString()))
    {
        mIsInit=true;
        mFaceRecognizer = LBPHFaceRecognizer::create();
    }
}

std::vector<Rect> FaceDetector::detectFaces(const Mat &frame)
{
    qDebug()<<Q_FUNC_INFO;

    std::vector<Rect> foundFaces;
    if(mIsInit)
    {
        Mat frame_gray;
        cvtColor(frame, frame_gray, COLOR_BGR2GRAY);
        equalizeHist(frame_gray, frame_gray);
        mFaceClassifier.detectMultiScale(frame_gray,foundFaces);
    }
    return foundFaces;
}

void FaceDetector::trainFromPath(QString path)
{
    qDebug()<<Q_FUNC_INFO;

    QDir directory(path);
    std::vector<Mat> images;
    std::vector<int> labels;

    QStringList imagespath = directory.entryList(QStringList() << "*.jpg" <<"*.jpeg"<<".*JPEG"<< "*.JPG",QDir::Files);
    imagespath.sort();

    QString prevFileName;
    foreach(QString filename, imagespath)
    {
        if(prevFileName!=filename)
        {
            prevFileName = filename;
            mCurrentFaceLabelCount++;
        }
        images.push_back(imread((path+"\\"+filename).toStdString(),0));
        labels.push_back(mCurrentFaceLabelCount);

        int index = filename.lastIndexOf('.');
        mFaceLabels[mCurrentFaceLabelCount] = filename.mid(0,filename.size()-index);;

    }
    mFaceRecognizer->train(images,labels);
    mIsRecognizerTrained = true;

}

void FaceDetector::addTrainData(Mat img, QString lable)
{
    qDebug()<<Q_FUNC_INFO;

    images.push_back(img);
    int lableName = static_cast<int>(labels.size());
    labels.push_back(lableName);
    mFaceLabels[lableName]=lable;
}

void FaceDetector::train()
{
    qDebug()<<Q_FUNC_INFO;

    if(TOTAL_SNAPS != images.size() || TOTAL_SNAPS != labels.size())
    {
        qDebug()<<"images.size() or labels.size() not suffecient";
        return;
    }

    mFaceRecognizer->train(images,labels);
    mIsRecognizerTrained = true;

}

QString FaceDetector::predict(Mat frame)
{
    qDebug()<<Q_FUNC_INFO;

    int lable;
    if(mIsRecognizerTrained && mFaceRecognizer)
    {
        cvtColor(frame,frame, COLOR_BGR2GRAY);
        lable = mFaceRecognizer->predict(frame);
    }
    return mFaceLabels[lable];
}

void FaceDetector::resetTrainData()
{
    qDebug()<<Q_FUNC_INFO;

    images.clear();
    labels.clear();
    mIsRecognizerTrained = false;
}
