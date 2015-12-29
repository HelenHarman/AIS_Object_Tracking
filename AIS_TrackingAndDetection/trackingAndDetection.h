/*!
 * \file trackingAndDetection.h
 * \author Helen Harman (heh14@aber.ac.uk)
 * \date 12/03/2015
 * \version 1.0
 *
 * \brief Holds the TrackingAndDetection class
 */
#ifndef TRACKINGANDDETECTION_H
#define TRACKINGANDDETECTION_H

#include <iostream>
#include <cmath>
#include <qthread.h>
#include <qtimer.h>
#include <sys/stat.h>

#include "videoInputBase.h"
#include "webcamInput.h"
#include "videoFileInput.h"

#include "network.h"

#include "euclideanDistance.h"
#include "sumOfSquaredDifference.h"

#include "options.h"

#include "ObjectFinders/simplexObjectDetector.h"
#include "ObjectFinders/globalObjectDetector.h"

#include "location.h"

using namespace AIS_Options;

/*!
 * \class TrackingAndDetection
 * \brief The class that handles and runs the tracking and detection of an object.
 */
class TrackingAndDetection : public QObject, public Transformations
{
    Q_OBJECT
public:
    /*!
     * \fn TrackingAndDetection
     * \brief Default constructor
     * \param inputType
     */
    TrackingAndDetection(bool rotation = false, bool scale = false, DistanceMeasureType distanceMeasureType = EUCLIDEAN_DISTANCE,
                                               bool usePredictedLocation = false, double stimulationThreshold = 0.6, double objectThreshold = 0.8, double networkAffiliationThreshold = 0, VideoInputType inputType = WEBCAM, string configPathName = "", string directoryOutput = "", int numberOfinitialARBs = 0, int numIteration = 0);


    ~TrackingAndDetection();

signals:
    void saveNetwork(Network *network, string path);

    /*!
     * \fn updateImage
     * \brief Allows the qtWidgetImageDisplay to show the image
     * \param data [in]
     * \param cols [in]
     * \param rows [in]
     */
    void updateImage(uchar* data, int cols, int rows);

    /*!
     * \fn updateObjectsPosition
     * \brief Allows the UI to show the objects location
     * \param x [in]
     * \param y [in]
     * \param rotation [in]
     * \param width [in]
     * \param height [in]
     */
    void updateObjectsPosition(int x, int y, int rotation, int width, int height);

    /*!
     * \fn updateNumARBs
     * \param numARBs [in]
     */
    void updateNumARBs(int numARBs);

    /*!
     * \fn grabVideoFileConfig
     */
    void grabVideoFileConfig();

    /*!
     * \fn setNetwork
     * \brief Allows the network to be saved to file.
     * \param network [in]
     */
    void setNetwork(Network * network);

public slots:

    /*!
     * \fn setDistanceMeasure
     * \param distanceMeasureType [in]
     */
    void distanceMeasureChanged(DistanceMeasureType distanceMeasureType);

    /*!
     * \fn useRotationChanged
     * \param useRotation [in]
     */
    void useRotationChanged(bool useRotation);

    /*!
     * \fn useScaleChanged
     * \param useScale [in]
     */
    void useScaleChanged(bool useScale);

    /*!
     * \fn usePredictedLocationChanged
     * \param usePredictedLocation [in]
     */
    void usePredictedLocationChanged(bool usePredictedLocation);

    /*!
     * \fn stateChanged
     * \param state [in]
     */
    void stateChanged(ProgramState state);

    /*!
     * \fn getNetwork
     */
    void getNetwork();

    /*!
     * \fn changeVideoConfigFilePath
     * \brief Called when the user selects the video config file that should be used
     * \param filePathName [in]
     */
    void changeVideoConfigFilePath(string filePathName);

    /*!
     * \fn reset
     * \brief When a new video type is selected by the user we need to reset the tracking
     * \param inputType [in] : What video source should be used
     */
    void reset(VideoInputType inputType);

    /*!
     * \fn startVideoFeed
     * \brief Called by QTimer. Reads and Emits the new video frame.
     *              Calls the detectObject() method.
     */
    void runVideoFeed();


    void initialiseTrackingFromLocation(Location location);


    /*!
     * \fn stimulationThresholdChanged
     * \param stimulationThreshold [in]
     */
    void stimulationThresholdChanged(double stimulationThreshold);

    /*!
     * \fn objectThresholdChanged
     * \param objectThreshold [in]
     */
    void objectThresholdChanged(double objectThreshold);
private:

    /*!
     * \fn simplexObjectDetector
     * \brief The omptimised detection algorithm
     */
    ObjectDetector *objectDetector;

    /*!
     * \var state
     */
    ProgramState state;

    /*!
     * \var inputType
     */
    VideoInputType inputType;

    /*!
     * \var distanceMeasureType
     */
    DistanceMeasureType distanceMeasureType;

    /*!
     * \var useRotation
     */
    bool useRotation;

    /*!
     * \var useScale
     */
    bool useScale;


    /*!
     * \var usePredictedLocation
     */
    bool usePredictedLocation;

    /*!
     * \var initialFrame
     * \brief Used to allow the section of an object. Uses Lab colour space.
     */
    Mat initialFrame;

    /*!
     * \var videoInput
     */
    VideoInputBase * videoInput;

    /*!
     * \var network
     */
    Network * network;

    /*!
     * \var distanceMeasure
     */
    DistanceBase * distanceMeasure;

    /*!
     * \var stimulationThreshold, objectThreshold, networkAffiliationThreshold
     * \brief Are only stored in this class as a user may set them via the UI before the code has instantiated the network
     */
    double stimulationThreshold;
    double objectThreshold;
    double networkAffiliationThreshold;

    string directoryOutput = "";

    int numberOfinitialARBs = 5;
    int iteration = 0;
    int numIteration = 0;
    int numberOfFrames = 0;

    /*!
     * \fn detectObject
     * \param currentFrame [in]
     */
    void detectObject(Mat currentFrame);

    Location findObject(Location predictedLoc, Mat currentFrame, vector<ARB*> appearances);

    /*!
     * \fn setupVideoInput
     * \brief Checks what type of video input is being used, and creates an object of that type.
     * \param inputType [in]
     */
    void setupVideoInput(string configPathName = "");

    Mat createAppearance(Mat frame, Location location, int width, int height);

};

#endif // TRACKINGANDDETECTION_H
