#-------------------------------------------------
#
# Project created by QtCreator 2016-11-01T20:29:15
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = colormap
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

INCLUDEPATH +=C:\\OPENCV-2.4.9\\opencv\\build\\include

LIBS +=-LC:\\OPENCV-2.4.9\\mybuild\\lib\\Debug \
    -lopencv_ocl249d \
    -lopencv_legacy249d \
    -lopencv_ts249d \
    -lopencv_calib3d249d \
    -lopencv_features2d249d \
    -lopencv_objdetect249d \
    -lopencv_highgui249d \
    -lopencv_photo249d \
    -lopencv_video249d \
    -lopencv_ml249d \
    -lopencv_flann249d \
    -lopencv_imgproc249d \
    -lopencv_core249d \
    -lopencv_contrib249d \
    -lopencv_stitching249d \
    -lopencv_videostab249d \
    -lopencv_nonfree249d \
    -lopencv_superres249d \
    -lopencv_gpu249d \
    -lopencv_haartraining_engined \
    -lKinect20 \
    -lKinect20.VisualGestureBuilder
