#include "mainwidget.h"
#include "globalconstants.h"
#include <QDebug>

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
{
    qDebug()<<Q_FUNC_INFO;

    this->setWindowTitle("Face Detection");

    mViewScreen = new QLabel(this);
    mStackWidgets = new QStackedWidget(this);
    mMenuWidget = new MenuWidget(this);
    mRegisterWidget = new RegisterWidget(this);
    mStreamer = new VideoStreamer();
    mFaceDetector = new FaceDetector();
    mRegisterTimer = new QTimer;

    QHBoxLayout* mHLayout = new QHBoxLayout;
    mHLayout = new QHBoxLayout(this);

    mHLayout->addWidget(mViewScreen);
    mHLayout->addWidget(mStackWidgets);

    mStackWidgets->addWidget(mMenuWidget);
    mStackWidgets->addWidget(mRegisterWidget);

    mViewScreen->setMinimumSize(QSize(200,200));
    mViewScreen->setStyleSheet("QLabel { background-color : black; }");

    mHLayout->setStretch(0,7);
    mHLayout->setStretch(1,3);

    //connections
    connect(mMenuWidget,SIGNAL(startStreamClicked()),this,SLOT(onStartStream()));
    connect(mMenuWidget,SIGNAL(stopStreamClicked()),this,SLOT(onStopStream()));
    connect(mMenuWidget,SIGNAL(registerNewClicked()),this,SLOT(onRegisterNew()));

    connect(mRegisterWidget,SIGNAL(takeSnapClicked()),this,SLOT(onTakeSnap()));
    connect(mRegisterWidget,SIGNAL(updateClicked()),this,SLOT(onUpdate()));
    connect(mRegisterWidget,SIGNAL(backClicked()),this,SLOT(onBack()));

    connect(mStreamer,SIGNAL(nextFrame(Mat)),this,SLOT(onNextFrameReceived(Mat)));
}

MainWidget::~MainWidget()
{
    qDebug()<<Q_FUNC_INFO;
    onStopStream();
}

void MainWidget::onStartStream()
{
    qDebug()<<Q_FUNC_INFO;

    if(mStreamer)
        mStreamer->startStream();
}

void MainWidget::onStopStream()
{
    qDebug()<<Q_FUNC_INFO;

    if(!mStreamer || !mViewScreen) return;
    mStreamer->stopStream();
    mViewScreen->setStyleSheet("QLabel { background-color : black; }");
}

void MainWidget::onRegisterNew()
{
    qDebug()<<Q_FUNC_INFO;

    if(!mRegisterWidget || !mStackWidgets || !mStreamer) return;
    mRegisterWidget->enableRegistration(mStreamer->isStreaming());
    mRegisterWidget->clearSnaps();
    mStackWidgets->setCurrentIndex(1);
}

void MainWidget::onBack()
{
    qDebug()<<Q_FUNC_INFO;

    if(!mStackWidgets || !mFaceDetector) return;

    mStackWidgets->setCurrentIndex(0);
    mFaceDetector->resetTrainData();
}

void MainWidget::onUpdate()
{
    qDebug()<<Q_FUNC_INFO;

    if(!mFaceDetector)return;
    mFaceDetector->train();
}

void MainWidget::onTakeSnap()
{
    qDebug()<<Q_FUNC_INFO;

    if(!mRegisterTimer || !mRegisterWidget)return;

    connect(mRegisterTimer,SIGNAL(timeout()),this,SLOT(registerCurrentFrame()));
    mRegisterTimer->stop();
    mRegisterWidget->clearSnaps();
    mRegisterTimer->start(UPDATE_NEW_FRAME_PER_MS);
}

void MainWidget::onNextFrameReceived(Mat frame)
{
    if(!mViewScreen || !mFaceDetector || !mMenuWidget) return;

    mCurrentFrame = frame;

    if(mMenuWidget->isFaceRecognitionEnabled())
    {
        QString lable = mFaceDetector->predict(frame);

        std::vector<Rect> foundFaces = mFaceDetector->detectFaces(frame);
        for(int i = 0; i < (int)foundFaces.size() ; i++)
        {
            rectangle(frame, foundFaces[0],Scalar(255.0,0.0,0.0));
        }
        if(!lable.isEmpty() && foundFaces.size()!=0)
        {
            Point p(foundFaces[0].x,foundFaces[0].y);
            putText(frame,lable.toStdString(),p,FONT_HERSHEY_PLAIN,2,Scalar(255.0,0.0,0.0));
        }
    }

    QImage img = QImage((const uchar *)frame.data,
                        frame.cols,
                        frame.rows,
                        frame.step,
                        QImage::Format_RGB888).rgbSwapped();

    QPixmap pix = QPixmap::fromImage(img);
    mViewScreen->setPixmap( pix.scaled( mViewScreen->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation) );
}

void MainWidget::registerCurrentFrame()
{
    qDebug()<<Q_FUNC_INFO;

    if(!mRegisterWidget || !mFaceDetector)return;
    qDebug()<<mRegisterWidget->getRegisteredImageCount();

    if(mRegisterWidget->getRegisteredImageCount() >= TOTAL_SNAPS)
    {
        disconnect(mRegisterTimer,SIGNAL(timeout()),this,SLOT(registerCurrentFrame()));
        mRegisterTimer->stop();
    }
    else
    {
        QImage img = QImage((const uchar *)mCurrentFrame.data,
                            mCurrentFrame.cols,
                            mCurrentFrame.rows,
                            mCurrentFrame.step,
                            QImage::Format_RGB888).rgbSwapped();

        mRegisterWidget->addSnap(mRegisterWidget->getRegisteredImageCount(),img);

        Mat frame_gray;
        cvtColor(mCurrentFrame, frame_gray, COLOR_BGR2GRAY);

        mFaceDetector->addTrainData(frame_gray,mRegisterWidget->getName());

    }
}

