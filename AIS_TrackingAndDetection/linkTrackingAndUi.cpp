/*!
 * \file linkTrackingAndUi.cpp
 * \author Helen Harman (heh14@aber.ac.uk)
 * \date 12/03/2015
 * \version 1.0
 *
 * \brief The source code for the LinkTrackingAndUi class.
 */
#include "linkTrackingAndUi.h"

//--------------------------------------------------------------

LinkTrackingAndUi::LinkTrackingAndUi(QtWidgetImageDisplay * imageWidget, TrackingAndDetection *trackingAndDetection)
{
    QTimer *trackingThread = new QTimer(trackingAndDetection);
    connect(trackingThread, SIGNAL(timeout()), trackingAndDetection, SLOT(runVideoFeed()));

    // connect TrackingAndDetectionto UI (in future this can be used for PTZ camera)
    connect(trackingAndDetection, SIGNAL(updateImage(uchar*, int, int)), imageWidget, SLOT(displayMat(uchar*, int, int)));
    connect(trackingAndDetection, SIGNAL(updateObjectsPosition(int, int, int, int, int)), imageWidget, SLOT(setTrackingPosition(int, int, int, int, int)));

    // connect the TrackingAndDetection signals to the UI slots
    connect(trackingAndDetection, SIGNAL(updateNumARBs(int)), imageWidget, SLOT(setNumARBs(int)));
    connect(trackingAndDetection, SIGNAL(grabVideoFileConfig()), imageWidget, SLOT(getVideoFileConfig()));
    connect(trackingAndDetection, SIGNAL(saveNetwork(Network*, string)), imageWidget, SLOT(saveNetworkToPath(Network*, string)));

    // connect the UI signals to the TrackingAndDetection slots
    connect(imageWidget, SIGNAL(setState(ProgramState)), trackingAndDetection, SLOT(stateChanged(ProgramState)));
    connect(imageWidget, SIGNAL(setVideoType(VideoInputType)), trackingAndDetection, SLOT(reset(VideoInputType)));
    connect(imageWidget, SIGNAL(setVideoFileConfigFilePath(string)), trackingAndDetection, SLOT(changeVideoConfigFilePath(string)));
    connect(imageWidget, SIGNAL(setUseRotation(bool)), trackingAndDetection, SLOT(useRotationChanged(bool)));
    connect(imageWidget, SIGNAL(setUseScale(bool)), trackingAndDetection, SLOT(useScaleChanged(bool)));
    connect(imageWidget, SIGNAL(setDistanceMeasure(DistanceMeasureType)), trackingAndDetection, SLOT(distanceMeasureChanged(DistanceMeasureType)));
    connect(imageWidget, SIGNAL(setUsePredictedLocation(bool)), trackingAndDetection, SLOT(usePredictedLocationChanged(bool)));
    connect(imageWidget, SIGNAL(setStimulationThreshold(double)), trackingAndDetection, SLOT(stimulationThresholdChanged(double)));
    connect(imageWidget, SIGNAL(setObjectThreshold(double)), trackingAndDetection, SLOT(objectThresholdChanged(double)));

    // to save the network to file
    connect(imageWidget, SIGNAL(getNetwork()), trackingAndDetection, SLOT(getNetwork()));
    connect(trackingAndDetection, SIGNAL(setNetwork(Network*)), imageWidget, SLOT(setNetworkToSaveNetwork(Network*)));

    trackingThread->start(1);
}

//--------------------------------------------------------------
//--------------------------------------------------------------


