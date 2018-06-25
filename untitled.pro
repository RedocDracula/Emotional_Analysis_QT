#-------------------------------------------------
#
# Project created by QtCreator 2018-05-30T15:01:07
#
#-------------------------------------------------

QT      += core widgets multimedia multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = untitled
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    parser.cpp

HEADERS += \
        mainwindow.h \
    qextend.h

FORMS += \
        mainwindow.ui

RESOURCES += \
    resources.qrc

DISTFILES += \
    haarcascade_eye_tree_eyeglasses.xml \
    haarcascade_frontalcatface.xml \
    emotion.py \
    thrones2vec.w2v \
    label_saved \
    svm_trained

INCLUDEPATH += "-I/usr/local/include/opencv"

LIBS += -L/usr/local/lib -lopencv_videostab -lopencv_ml -lopencv_dnn -lopencv_photo -lopencv_stitching -lopencv_objdetect -lopencv_calib3d -lopencv_features2d -lopencv_flann -lopencv_superres -lopencv_shape -lopencv_video -lopencv_highgui -lopencv_videoio -lopencv_imgcodecs -lopencv_imgproc -lopencv_core

