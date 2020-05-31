#include "registerwidget.h"
#include <QDebug>
#include "globalconstants.h"
RegisterWidget::RegisterWidget(QWidget *parent) : QWidget(parent),registeredImagesCounter(0)
{
    qDebug()<<Q_FUNC_INFO;

    mLineEdit = new QLineEdit(this);
    mLineEdit->setText("snap_name");
    mTakeSnap = new QPushButton(this);
    mTakeSnap->setText("Take Snap");
    mUpdate = new QPushButton(this);
    mUpdate->setText("Register");
    mBack = new QPushButton(this);
    mBack->setText("Back");

    for(int i=0;i<TOTAL_SNAPS;i++)
    {
        mSnapList.insert(i,new QLabel(this));
    }
    clearSnaps();

    QGridLayout *gLayout = new QGridLayout;
    int index =0;
    for(int i=0;i<REGISTER_SNAP_COLUMNS;i++)
    {
        for(int j=0;j<REGISTER_SNAP_ROWS;j++)
        {
            gLayout->addWidget(mSnapList[index++],i,j,1,1);
        }
    }

    QLabel *nameL= new QLabel;
    nameL->setText("Name ");
    QHBoxLayout *hLayout = new QHBoxLayout();
    hLayout->addWidget(nameL);
    hLayout->addWidget(mLineEdit);

    QVBoxLayout* vLayout = new QVBoxLayout();
    vLayout->addLayout(gLayout,8);
    vLayout->addLayout(hLayout,1);
    vLayout->addWidget(mTakeSnap,1);
    vLayout->addWidget(mUpdate,1);
    vLayout->addWidget(mBack,1);

    this->setLayout(vLayout);

    //connections
    connect(mTakeSnap,SIGNAL(clicked(bool)),this,SLOT(onTakeSnapClicked()));
    connect(mUpdate,SIGNAL(clicked(bool)),this,SLOT(onUpdateClicked()));
    connect(mBack,SIGNAL(clicked(bool)),this,SLOT(onBackClicked()));

}

void RegisterWidget::addSnap(const int index,const QImage img)
{
    qDebug()<<Q_FUNC_INFO;

    if(mSnapList[index])
    {
        QPixmap pix = QPixmap::fromImage(img);
        mSnapList[index]->setPixmap( pix.scaled( mSnapList[index]->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation) );
        registeredImagesCounter++;
    }
}

void RegisterWidget::clearSnaps()
{
    qDebug()<<Q_FUNC_INFO;

    registeredImagesCounter = 0;
    for(int i=0;i<TOTAL_SNAPS;i++)
    {
        if(mSnapList[i])
        {
            mSnapList[i]->setStyleSheet("QLabel { background-color : black; }");
            mSnapList[i]->setAlignment(Qt::AlignCenter);
            QPalette palette = mSnapList[i]->palette();
            palette.setColor(QPalette::WindowText, Qt::white);
            QFont f =  mSnapList[i]->font();
            f.setBold(true);
            mSnapList[i]->setFont(f);
            mSnapList[i]->setPalette(palette);
            mSnapList[i]->setText("Snap "+QString::number(i+1));
        }
    }
}

QString RegisterWidget::getName()
{
    qDebug()<<Q_FUNC_INFO;

    if(mLineEdit)
    {
        return mLineEdit->text();
    }
    return QString();
}

void RegisterWidget::enableRegistration(bool enable)
{
    if(mLineEdit)mLineEdit->setEnabled(enable);
    if(mTakeSnap)mTakeSnap->setEnabled(enable);
    if(mUpdate)mUpdate->setEnabled(enable);
}


void RegisterWidget::onTakeSnapClicked()
{
    emit takeSnapClicked();
}

void RegisterWidget::onUpdateClicked()
{
    emit updateClicked();
}

void RegisterWidget::onBackClicked()
{
    emit backClicked();
}
