#ifndef REGISTERWIDGET_H
#define REGISTERWIDGET_H

#include <QObject>
#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QGridLayout>
#include <QPointer>
#include <QLabel>
#include <QLineEdit>
#include <QList>

class RegisterWidget : public QWidget
{
    Q_OBJECT
public:
    explicit RegisterWidget(QWidget *parent = nullptr);
    void addSnap(const int index,const QImage img);
    void clearSnaps();
    QString getName();
    int getRegisteredImageCount(){return registeredImagesCounter;}
    void setRegisteredImageCount(const int count){registeredImagesCounter=count;}
    void enableRegistration(bool enable);

private slots:
    void onTakeSnapClicked();
    void onUpdateClicked();
    void onBackClicked();

signals:
    void takeSnapClicked(void);
    void updateClicked(void);
    void backClicked(void);

private:
    QPointer<QLineEdit>         mLineEdit;
    QPointer<QPushButton>       mTakeSnap;
    QPointer<QPushButton>       mUpdate;
    QPointer<QPushButton>       mBack;
    QList<QLabel*>              mSnapList;
    int                         registeredImagesCounter;
};

#endif // REGISTERWIDGET_H
