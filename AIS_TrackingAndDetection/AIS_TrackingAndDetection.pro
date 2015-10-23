#-------------------------------------------------
#
# Project created by QtCreator 2015-03-06T14:59:26
#
#-------------------------------------------------

QT       += core gui
CONFIG += c++11 -O2
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = AIS_TrackingAndDetection
TEMPLATE = app
INCLUDEPATH += VideoDeviceInteraction UI AIS DistanceMeasures

QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.9

# for openCV
INCLUDEPATH += /usr/local/include/
LIBS += -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_nonfree -lopencv_features2d -lopencv_calib3d -lopencv_flann -lopencv_video -L/usr/local/lib

# for GSL
INCLUDEPATH += /usr/local/Cellar/gsl/1.16/include
LIBS += -L/usr/local/Cellar/gsl/1.16/lib -lcblas -lgsl -lgslcblas -lm

SOURCES += main.cpp\
        UI/mainwindow.cpp \
        VideoDeviceInteraction/webcamInput.cpp \
    trackingAndDetection.cpp \
    UI/qtWidgetImageDisplay.cpp \
    AIS/arb.cpp \
    AIS/network.cpp \
    DistanceMeasures/euclideanDistance.cpp \
    linkTrackingAndUi.cpp \
    VideoDeviceInteraction/videoFileInput.cpp \
    DistanceMeasures/sumOfSquaredDifference.cpp \
    simplexObjectDetector.cpp \
    transformations.cpp \
    UI/outputData.cpp \
    DistanceMeasures/distanceBase.cpp \
    VideoDeviceInteraction/videoInputBase.cpp \
    argumentParser.cpp \
    objectDetector.cpp \
    globalObjectDetector.cpp \
    groundTruthDistances.cpp

HEADERS  += UI/mainwindow.h \
            VideoDeviceInteraction/webcamInput.h \
    trackingAndDetection.h \
    UI/qtWidgetImageDisplay.h \
    AIS/arb.h \
    AIS/network.h \
    DistanceMeasures/euclideanDistance.h \
    linkTrackingAndUi.h \
    VideoDeviceInteraction/videoFileInput.h \
    DistanceMeasures/sumOfSquaredDifference.h \
    simplexObjectDetector.h \
    transformations.h \
    UI/outputData.h \
    options.h \
    DistanceMeasures/distanceBase.h \
    VideoDeviceInteraction/videoInputBase.h \
    argumentParser.h \
    objectDetector.h \
    globalObjectDetector.h \
    groundTruthDistances.h

FORMS    += UI/mainwindow.ui

