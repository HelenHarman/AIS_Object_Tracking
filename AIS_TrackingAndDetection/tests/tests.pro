######################################################################
# Automatically generated by qmake (3.0) Tue Mar 3 09:30:19 2015
######################################################################

QT += testlib
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
CONFIG += c++11
QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.9
INCLUDEPATH += /usr/local/include/
INCLUDEPATH += ../
INCLUDEPATH += ../../external-libs

LIBS += -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_nonfree -lopencv_features2d -lopencv_calib3d -lopencv_flann -lopencv_video -L/usr/local/lib
TEMPLATE = app
TARGET = tests
INCLUDEPATH += . .. ../AIS ../DistanceMeasures ../VideoDeviceInteraction

# for GSL
INCLUDEPATH += /usr/local/Cellar/gsl/1.16/include
LIBS += -L/usr/local/Cellar/gsl/1.16/lib -lcblas -lgsl -lgslcblas -lm


# Input
HEADERS += ../../external-libs/AutoTest.h \
    ../AIS/network.h \
    ../AIS/arb.h \
    ../trackingAndDetection.h \
    ../DistanceMeasures/distanceBase.h \
    ../DistanceMeasures/euclideanDistance.h \
    ../DistanceMeasures/sumOfSquaredDifference.h \
    ../VideoDeviceInteraction/videoInputBase.h \
    ../VideoDeviceInteraction/webcamInput.h \
    ../VideoDeviceInteraction/videoFileInput.h \
    ../transformations.h \
    ../simplexObjectDetector.h \
    moc_euclideanDistance.h \
    testArb.h \
    testNetwork.h \
    testEuclideanDistance.h \
    testSumOfSquaredDifference.h \
    testTransformations.h \
    distancebasetest.h


SOURCES +=  ../AIS/network.cpp \
    ../AIS/arb.cpp \
    ../DistanceMeasures/distanceBase.cpp \
    ../DistanceMeasures/euclideanDistance.cpp \
    ../DistanceMeasures/sumOfSquaredDifference.cpp \
    ../trackingAndDetection.cpp \
    ../VideoDeviceInteraction/webcamInput.cpp \
    ../VideoDeviceInteraction/videoFileInput.cpp \
    ../VideoDeviceInteraction/videoInputBase.cpp\
    ../transformations.cpp \
    ../simplexObjectDetector.cpp \
    moc_euclideanDistance.cpp \
    testArb.cpp \
    testNetwork.cpp \
    testEuclideanDistance.cpp \
    testSumOfSquaredDifference.cpp \
    testTransformations.cpp \
    distancebasetest.cpp

