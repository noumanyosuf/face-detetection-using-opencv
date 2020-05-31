#ifndef MAINWIDGET_H
#define MAINWIDGET_H
#include <qlabel.h>
#include <QWidget>
#include <QStackedWidget>
#include <QHBoxLayout>
#include <QPointer>
#include <QTimer>
#include <menuwidget.h>
#include <registerwidget.h>
#include <videostreamer.h>
#include <facedetector.h>

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = nullptr);
    ~MainWidget();

private slots:
    void onStartStream();
    void onStopStream();
    void onRegisterNew();

    void onBack();
    void onUpdate();
    void onTakeSnap();

    void onNextFrameReceived(Mat frame);
    void registerCurrentFrame();

private:
    QPointer<QLabel>            mViewScreen;
    QPointer<QStackedWidget>    mStackWidgets;
    QPointer<MenuWidget>        mMenuWidget;
    QPointer<RegisterWidget>    mRegisterWidget;
    QPointer<VideoStreamer>     mStreamer;
    QPointer<FaceDetector>      mFaceDetector;
    QPointer<QTimer>            mRegisterTimer;
    Mat                         mCurrentFrame;

};
#endif // MAINWIDGET_H
