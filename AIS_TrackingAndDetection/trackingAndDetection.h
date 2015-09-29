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

#include "simplexObjectDetector.h"

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
    //TrackingAndDetection();
    TrackingAndDetection(bool rotation = false, bool scale = false, ARBsToSearchWith whichARBsToSearchWith = HIGHEST_AND_CONNECTED, DistanceMeasureType distanceMeasureType = EUCLIDEAN_DISTANCE,
                                               bool usePredictedLocation = false, double stimulationThreshold = 0.6, double objectThreshold = 0.8, VideoInputType inputType = WEBCAM, string configPathName = "", string directoryOutput = "");


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
     * \fn whichARBsToSearchWithChanged
     * \param whichARBsToSearchWith [in]
     */
    void whichARBsToSearchWithChanged(ARBsToSearchWith whichARBsToSearchWith);

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

    /*!
     * \fn initialiseTrackingFromPosition
     * \brief Initialises the artifical immunue network with the initial appearance.
     * \param x [in]
     * \param y [in]
     * \param width [in]
     * \param height [in]
     */
    void initialiseTrackingFromPosition(int x, int y, int width, int height);

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
    SimplexObjectDetector *simplexObjectDetector;

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
     * \var whichARBsToSearchWith
     * \see options.h
     */
    ARBsToSearchWith whichARBsToSearchWith;

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
     * \var stimulationThreshold
     * \brief Are only stored in this class as a user may set them via the UI before the code has instantiated the network
     */
    double stimulationThreshold;
    /*!
     * \var objectThreshold
     * \brief Are only stored in this class as a user may set them via the UI before the code has instantiated the network
     */
    double objectThreshold;

    /*!
     * \fn detectObject
     * \param currentFrame [in]
     */
    void detectObject(Mat currentFrame);

    /*!
     * \fn setupVideoInput
     * \brief Checks what type of video input is being used, and creates an object of that type.
     * \param inputType [in]
     */
    void setupVideoInput(VideoInputType inputType);

    /*!
     * \fn checkIfObjectPredictionWithinFrame
     * \brief Checks the location is within the frame
     * \param predictedLoc [in, out]
     * \param currentFrame [in]
     * \param appearanceWidth [in]
     * \param appearanceHeight [in]
     */
    void checkIfObjectPredictionWithinFrame(Location *predictedLoc, Mat currentFrame,  int appearanceWidth, int appearanceHeight);

    Mat createAppearance(Mat frame, Location location, int width, int height);


    string directoryOutput = "";


    // used to allow out many threshold values, so the best result can be found
    bool const RUN_MANY = false;
    int numberOfVideoRun = 0;
    struct thresholds
    {
        double stimulationThreshold;
        double objectThresholds[5];
    };

    thresholds thresholdValues[12] = {{0.03, {0.034, 0.038, 0.04, 0.044, 0.048}},
                                      {0.04, {0.044, 0.048, 0.05, 0.054, 0.058}},
                                      {0.05, {0.06, 0.07, 0.08, 0.09, 0.10}},
                                      {0.06, {0.062, 0.066, 0.07, 0.073, 0.076}},
                                      {0.07, {0.072, 0.076, 0.08, 0.083, 0.086}},
                                      {0.08, {0.09, 0.10, 0.12, 0.13, 0.12}},
                                      {0.10, {0.12, 0.13, 0.14, 0.15, 0.16}},
                                      {0.12, {0.14, 0.15, 0.16, 0.18, 0.20}},
                                      {0.15, {0.17, 0.18, 0.19, 0.20, 0.22}},
                                      {0.18, {0.20, 0.22, 0.24, 0.25, 0.26}},
                                      {0.20, {0.22, 0.23, 0.24, 0.27, 0.30}},
                                      {0.24, {0.26, 0.30, 0.32, 0.33, 0.36}}
                                    };
};

#endif // TRACKINGANDDETECTION_H
