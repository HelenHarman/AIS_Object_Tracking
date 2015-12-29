/*!
 * \file trackingAndDetection.cpp
 * \author Helen Harman (heh14@aber.ac.uk)
 * \date 12/03/2015
 * \version 1.0
 *
 * \brief The source code for the TrackingAndDetection class.
 */

#include "trackingAndDetection.h"

//--------------------------------------------------------------

TrackingAndDetection::TrackingAndDetection(bool rotation, bool scale, DistanceMeasureType distanceMeasureType,
                                           bool usePredictedLocation, double stimulationThreshold, double objectThreshold, double networkAffiliationThreshold, VideoInputType inputType, string configPathName, string directoryOutput, int numberOfinitialARBs, int numIteration)
{
    this->useRotation = rotation;
    this->useScale = scale;
    this->distanceMeasureType = distanceMeasureType;
    this->usePredictedLocation = usePredictedLocation;

    this->state = UNINITIALISED;
    this->objectDetector = NULL;
    this->videoInput = NULL;
    this->network = NULL;
    this->distanceMeasure = NULL;

    this->stimulationThreshold = stimulationThreshold;
    this->objectThreshold = objectThreshold;
    this->networkAffiliationThreshold = networkAffiliationThreshold;

    this->numberOfinitialARBs = numberOfinitialARBs;


    this->directoryOutput = directoryOutput;

    this->numIteration = numIteration;

    this->inputType = inputType;
    setupVideoInput(configPathName);
}

//--------------------------------------------------------------

void TrackingAndDetection::reset(VideoInputType inputType)
{
    this->inputType = inputType;
    if (state == TRACKING)
    {
        delete(network);
        network = NULL;
        delete(distanceMeasure);
        distanceMeasure = NULL;
        delete(this->objectDetector);
        this->objectDetector = NULL;
    }
    state = UNINITIALISED;
    this->setupVideoInput();
}

//--------------------------------------------------------------

void TrackingAndDetection::setupVideoInput(string configPathName)
{
    VideoInputBase *temp = NULL;
    switch(this->inputType)
    {
        case(WEBCAM):
            std::cout << "WEBCAM" << std::endl;
            if(this->videoInput != NULL) temp = this->videoInput;
            this->videoInput = new WebcamInput();
            if(temp != NULL) delete(temp);
            break;
        case(FILE_INPUT):
            std::cout << "FILE_INPUT" << std::endl;
            if (configPathName.empty())
            {
                emit(grabVideoFileConfig()); // We require user input to where the video file is located
            }
            else // command line parameter has been provided with location of video config file
            {
                changeVideoConfigFilePath(configPathName);
            }
            break;
    }
}

//--------------------------------------------------------------

void TrackingAndDetection::changeVideoConfigFilePath(string filePathName)
{
    VideoFileInput *videoFileInput = new VideoFileInput(filePathName);
    Mat currentFrame = videoFileInput->getNextFrame();
    Mat labFrame;

    cvtColor(currentFrame, labFrame, CV_RGB2Lab);
    labFrame.copyTo(this->initialFrame);

    Location location = videoFileInput->getInitialLocation(currentFrame);

    VideoInputBase *temp = this->videoInput;
    this->videoInput = videoFileInput;
    delete(temp);//need to assign before free, as runVideoFeed() still being run

    initialiseTrackingFromLocation(location);
}

//--------------------------------------------------------------

void TrackingAndDetection::runVideoFeed()
{
    Mat currentFrame = this->videoInput->getNextFrame();

    // check if no new frame available (ie. end of video reached)
    if (currentFrame.size().height == 0)
    {
        // save the results
        if ((inputType == FILE_INPUT) && (directoryOutput != ""))
        {
            mkdir((directoryOutput).c_str(), S_IRWXU);
            emit(saveNetwork(this->network, directoryOutput));
            exit(EXIT_SUCCESS);
        }
        // loop through the video again
        if((inputType == FILE_INPUT) && (this->iteration < this->numIteration))
        {
            this->videoInput->startCamera();
            currentFrame = this->videoInput->getNextFrame();
            Location location = ((VideoFileInput*)this->videoInput)->getInitialLocation(currentFrame);
            network->resetLocation(location);
            this->iteration = this->iteration + 1;
        }
        return;
    }

    Mat labFrame;
    cvtColor(currentFrame, labFrame, CV_RGB2Lab);
    if(state == TRACKING)
    {
        this->numberOfFrames++;
        this->detectObject(labFrame);
        emit(updateNumARBs(this->network->getNumberOfARBs()));
    }
    else
    {
        labFrame.copyTo(this->initialFrame);
    }
    emit(updateImage(currentFrame.data, currentFrame.cols, currentFrame.rows));
}

//--------------------------------------------------------------

void TrackingAndDetection::initialiseTrackingFromLocation(Location location)
{
    // get the initial appearance
    int x, y, width, height;
    location.getCornerPoint(&x, &y, this->initialFrame);
    location.getSize(&width, &height, this->initialFrame);
    Rect selectionRect(x, y, width, height);
    Mat selectedAppearance;
    selectedAppearance = this->initialFrame(selectionRect);

    switch(this->distanceMeasureType)
    {
        case(EUCLIDEAN_DISTANCE):
            this->distanceMeasure = new EuclideanDistance(this->initialFrame, selectedAppearance);
            break;
        case(SUM_OF_SQUARED_DIFFERENCE):
            this->distanceMeasure = new SumOfSquaredDifference(this->initialFrame, selectedAppearance);
            break;
    }
    this->objectDetector = new SimplexObjectDetector(this->distanceMeasure);//new GlobalObjectDetector(this->distanceMeasure);
    this->network = new Network(selectedAppearance, location, this->distanceMeasure, this->objectThreshold, this->stimulationThreshold, this->usePredictedLocation, this->networkAffiliationThreshold);

    this->network->setUsePredictedLocation(this->usePredictedLocation);
    this->state = TRACKING;
    this->iteration = 0;
}

//--------------------------------------------------------------

void TrackingAndDetection::detectObject(Mat currentFrame)
{
    //std::cout << "detectObject called" << std::endl;
     /*namedWindow( "initialFrame", WINDOW_AUTOSIZE ); imshow( "initialFrame", initialFrame);
    namedWindow( "currentFrame", WINDOW_AUTOSIZE ); imshow( "currentFrame", currentFrame);*/

    vector<ARB*> appearances;
    this->network->getNearestAndConnectedARBs(&appearances);
    Location predictedLoc = this->network->getPredictedLocation();

    // FIND THE OBJECT //
    Location closestLoc = findObject(predictedLoc, currentFrame, appearances);

    // ADD THE APPEARANCE TO THE NETWORK //
    int x, y, width, height;
    closestLoc.getCornerPoint(&x, &y, currentFrame);
    closestLoc.getSize(&width, &height, currentFrame);

    if(closestLoc.getX() != -1)
    {
        Mat foundAppearance = this->createAppearance(currentFrame, closestLoc, width, height);
        if(this->numberOfFrames < this->numberOfinitialARBs)
        {
            predictedLoc = this->network->initialAppearanceAddition(foundAppearance, closestLoc);
        }
        else
        {
            predictedLoc = this->network->addAppearance(foundAppearance, closestLoc);
        }
    }
    predictedLoc.getCornerPoint(&x, &y, currentFrame);
    predictedLoc.getSize(&width, &height, currentFrame);

    // UPDATE UI/FILE/(future robot) WITH LOCATION OF OBJECT //
    emit(updateObjectsPosition(x, y, predictedLoc.getRotation(), width, height));
}

//--------------------------------------------------------------

Location TrackingAndDetection::findObject(Location predictedLoc, Mat currentFrame, vector<ARB*> appearances)
{
    if(!this->useRotation && !this->useScale)
    {
        return this->objectDetector->findObjectNoTransformations(predictedLoc, currentFrame, appearances);
    }
    else if(!this->useRotation && this->useScale)
    {
        return this->objectDetector->findObjectWithScale(predictedLoc, currentFrame, appearances);
    }
    else if(this->useRotation && !this->useScale)
    {
        return this->objectDetector->findObjectWithRotation(predictedLoc, currentFrame, appearances);
    }
    else
    {
        return this->objectDetector->findObjectAllTransformations(predictedLoc, currentFrame, appearances);
    }
}

//--------------------------------------------------------------

Mat TrackingAndDetection::createAppearance(Mat frame, Location location, int width, int height)
{
    int xStart, yStart;
    location.getCornerPoint(&xStart, &yStart, frame);
    Mat appearance(height, width, frame.type());
    for(int x = 0; x < width; x++)
    {
        for(int y = 0; y < height; y++)
        {
            int locX = x + xStart;
            int locY = y + yStart;
            rotatePosition(location.getRotation(), &locX, &locY, frame.size().width / 2, frame.size().height / 2);
            appearance.at<Vec3b>(Point(x,y)) = frame.at<Vec3b>(Point(locX, locY));
        }
    }
    return appearance;
}

//--------------------------------------------------------------

////////////////////////////////////////////////////
////// Setters for options changable in the UI /////

//--------------------------------------------------------------

void TrackingAndDetection::useRotationChanged(bool useRotation)
{
    this->useRotation = useRotation;
}

//--------------------------------------------------------------

void TrackingAndDetection::useScaleChanged(bool useScale)
{
    this->useScale = useScale;
}

//--------------------------------------------------------------

void TrackingAndDetection::distanceMeasureChanged(DistanceMeasureType distanceMeasureType)
{
    this->distanceMeasureType = distanceMeasureType;
}

//--------------------------------------------------------------

void TrackingAndDetection::getNetwork()
{
    emit(setNetwork(this->network));
}

//--------------------------------------------------------------

void TrackingAndDetection::usePredictedLocationChanged(bool usePredictedLocation)
{
    this->usePredictedLocation = usePredictedLocation;
    if (this->network != NULL)
    {
        this->network->setUsePredictedLocation(usePredictedLocation);
    }
}

//--------------------------------------------------------------

void TrackingAndDetection::stimulationThresholdChanged(double stimulationThreshold)
{
    if (this->network != NULL)
    {
        this->network->setStimulationThreshold(stimulationThreshold);
    }
    this->stimulationThreshold = stimulationThreshold;
}

//--------------------------------------------------------------

void TrackingAndDetection::objectThresholdChanged(double objectThreshold)
{
    if (this->network != NULL)
    {
        this->network->setObejctThreshold(objectThreshold);
    }
    this->objectThreshold = objectThreshold;
}

//--------------------------------------------------------------

void TrackingAndDetection::stateChanged(ProgramState state)
{
    this->state = state;
}

//--------------------------------------------------------------

TrackingAndDetection::~TrackingAndDetection()
{
    if (objectDetector != NULL)
        delete(objectDetector);
    if (videoInput != NULL)
        delete(videoInput);
    if (network != NULL)
        delete(network);
    if (distanceMeasure != NULL)
        delete(distanceMeasure);
}


//--------------------------------------------------------------
//--------------------------------------------------------------
