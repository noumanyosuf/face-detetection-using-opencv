#ifndef MENUWIDGET_H
#define MENUWIDGET_H

#include <QObject>
#include <QWidget>
#include <QVBoxLayout>
#include <QPointer>
#include <QPushButton>
#include <QCheckBox>

class MenuWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MenuWidget(QWidget *parent = nullptr);
     bool isFaceRecognitionEnabled();

private slots:
    void onStartStreamClicked();
    void onStopStreamClicked();
    void onRegisterNewClicked();

signals:
    void startStreamClicked(void);
    void stopStreamClicked(void);
    void registerNewClicked(void);

private:
    QPointer<QPushButton>       mStartVideo;
    QPointer<QPushButton>       mStopVideo;
    QPointer<QPushButton>       mRegister;
    QPointer<QCheckBox>         mEnableFaceDetectCB;
};

#endif // MENUWIDGET_H
