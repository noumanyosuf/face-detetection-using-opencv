#include "menuwidget.h"
#include <QDebug>
#include <QLabel>
#include <QHBoxLayout>

MenuWidget::MenuWidget(QWidget *parent) : QWidget(parent)
{
    qDebug()<<Q_FUNC_INFO;

    mStartVideo = new QPushButton(this);
    mStartVideo->setText("Start Camera");
    mStopVideo = new QPushButton(this);
    mStopVideo->setText("Stop Camera");
    mRegister = new QPushButton(this);
    mRegister->setText("Register");
    mEnableFaceDetectCB = new QCheckBox(this);
    mEnableFaceDetectCB->setChecked(true);

    QLabel *name = new QLabel(this);
    name->setText("Enable face recognition ");
    QHBoxLayout* hLayout = new QHBoxLayout;
    hLayout->setAlignment(Qt::AlignLeft);
    hLayout->addWidget(mEnableFaceDetectCB);
    hLayout->addWidget(name);

    QVBoxLayout* vLayout = new QVBoxLayout(this);
    vLayout->addLayout(hLayout);
    vLayout->addWidget(mStartVideo);
    vLayout->addWidget(mStopVideo);
    vLayout->addWidget(mRegister);
    this->setLayout(vLayout);

    //connections
    connect(mStartVideo,SIGNAL(clicked(bool)),this,SLOT(onStartStreamClicked()));
    connect(mStopVideo,SIGNAL(clicked(bool)),this,SLOT(onStopStreamClicked()));
    connect(mRegister,SIGNAL(clicked(bool)),this,SLOT(onRegisterNewClicked()));
}

void MenuWidget::onStartStreamClicked()
{
    emit startStreamClicked();
}

void MenuWidget::onStopStreamClicked()
{
    emit stopStreamClicked();
}

void MenuWidget::onRegisterNewClicked()
{
    emit registerNewClicked();
}

bool MenuWidget::isFaceRecognitionEnabled()
{
    qDebug()<<Q_FUNC_INFO;

    if(!mEnableFaceDetectCB)return false;
    return mEnableFaceDetectCB->isChecked();
}
