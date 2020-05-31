QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    facedetector.cpp \
    main.cpp \
    mainwidget.cpp \
    menuwidget.cpp \
    registerwidget.cpp \
    videostreamer.cpp

HEADERS += \
    facedetector.h \
    globalconstants.h \
    mainwidget.h \
    menuwidget.h \
    registerwidget.h \
    videostreamer.h

LIBS += -LD:\\open_cv\\x64\vc16\\lib -lopencv_core430 -lopencv_imgproc430 -lopencv_highgui430 -lopencv_imgcodecs430 -lopencv_videoio430 -lopencv_video430 -lopencv_calib3d430 -lopencv_photo430 -lopencv_features2d430 -lopencv_dnn430 -lopencv_flann430 -lopencv_gapi430 -lopencv_ml430 -lopencv_objdetect430 -lopencv_stitching430 -lopencv_face430


INCLUDEPATH += D:\\open_cv\\include
DEPENDPATH += D:\\open_cv\\include
