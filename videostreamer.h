#ifndef VIDEOSTREAMWIDGET_H
#define VIDEOSTREAMWIDGET_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QTimer>

#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/objdetect.hpp"

using namespace cv;

class VideoStreamer : public QObject
{
    Q_OBJECT
public:
    explicit VideoStreamer();
    ~VideoStreamer();
    void startStream();
    void stopStream();
    bool isStreaming();

signals:
    void nextFrame(Mat);

private slots:
     void getNextFrame();

private:
    VideoCapture    mVideo;
    QTimer*         mCamTimer;

};

#endif // VIDEOSTREAMWIDGET_H
