#include "videostreamer.h"
#include <QDebug>

VideoStreamer::VideoStreamer()
{
    qDebug()<<Q_FUNC_INFO;

    mCamTimer = new QTimer(this);
}

VideoStreamer::~VideoStreamer()
{
    qDebug()<<Q_FUNC_INFO;

    if(mCamTimer)
        mCamTimer->stop();
}

void VideoStreamer::startStream()
{
    qDebug()<<Q_FUNC_INFO;

    if(mVideo.isOpened()) return;
    mVideo.open(0);

    if(!mVideo.isOpened())
    {
        qDebug()<<"cant start video camera";
        return;
    }
    connect(mCamTimer,SIGNAL(timeout()),this,SLOT(getNextFrame()));
    mCamTimer->start(10);
}

void VideoStreamer::stopStream()
{
    qDebug()<<Q_FUNC_INFO;

    disconnect(mCamTimer, SIGNAL(timeout()), this, SLOT(getNextFrame()));
    mVideo.release();
}

bool VideoStreamer::isStreaming()
{
    qDebug()<<Q_FUNC_INFO;
    return mVideo.isOpened();
}

void VideoStreamer::getNextFrame()
{
    Mat frame;
    mVideo >> frame;
    emit nextFrame(frame);
}
