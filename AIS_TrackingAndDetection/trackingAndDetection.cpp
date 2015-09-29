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
/*
TrackingAndDetection::TrackingAndDetection()
{
    //this->usePredictedArea = true;
    this->useRotation = true;
    this->useScale = false;
    this->whichARBsToSearchWith = HIGHEST_AND_CONNECTED;
    this->state = UNINITIALISED;
    this->distanceMeasureType = EUCLIDEAN_DISTANCE;
    this->usePredictedLocation = true;

    this->simplexObjectDetector = NULL;
    this->videoInput = NULL;
    this->network = NULL;
    this->distanceMeasure = NULL;


    if(RUN_MANY)
    {
        this->stimulationThreshold = thresholdValues[numberOfVideoRun/9].stimulationThreshold;
        this->objectThreshold = thresholdValues[numberOfVideoRun/9].objectThresholds[numberOfVideoRun%9];
    }
    else
    {
        this->stimulationThreshold = 0.06;//0.6;
        this->objectThreshold = 0.1;//0.7;
    }

    this->setupVideoInput(WEBCAM);
}
*/

TrackingAndDetection::TrackingAndDetection(bool rotation, bool scale, ARBsToSearchWith whichARBsToSearchWith, DistanceMeasureType distanceMeasureType,
                                           bool usePredictedLocation, double stimulationThreshold, double objectThreshold, VideoInputType inputType, string configPathName, string directoryOutput)
{
    this->useRotation = rotation;
    this->useScale = scale;
    this->whichARBsToSearchWith = whichARBsToSearchWith;
    this->distanceMeasureType = distanceMeasureType;
    this->usePredictedLocation = usePredictedLocation;

    this->state = UNINITIALISED;
    this->simplexObjectDetector = NULL;
    this->videoInput = NULL;
    this->network = NULL;
    this->distanceMeasure = NULL;

    this->stimulationThreshold = stimulationThreshold;
    this->objectThreshold = objectThreshold;

    this->directoryOutput = directoryOutput;

    this->inputType = inputType;
    switch(inputType)
    {
        case(WEBCAM):
            std::cout << "WEBCAM" << std::endl;
            this->videoInput = new WebcamInput();
            break;
        case(FILE_INPUT):
            std::cout << "FILE_INPUT" << std::endl;
            changeVideoConfigFilePath(configPathName);
            break;
    }
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
        delete(this->simplexObjectDetector);
        this->simplexObjectDetector = NULL;
    }
    state = UNINITIALISED;
    this->setupVideoInput(inputType);
}

//--------------------------------------------------------------

void TrackingAndDetection::setupVideoInput(VideoInputType inputType)
{
    VideoInputBase *temp = NULL;
    switch(inputType)
    {
        case(WEBCAM):
            std::cout << "WEBCAM" << std::endl;
            if(this->videoInput != NULL) temp = this->videoInput;
            this->videoInput = new WebcamInput();
            if(temp != NULL) delete(temp);
            break;
        case(FILE_INPUT):
            std::cout << "FILE_INPUT" << std::endl;
            emit(grabVideoFileConfig()); // We require user input to where the video file is located
            break;
    }
}

//--------------------------------------------------------------

void TrackingAndDetection::changeVideoConfigFilePath(string filePathName)
{
    VideoFileInput *videoFileInput = new VideoFileInput(filePathName);
    int x, y, width, height;
    videoFileInput->getInitialPosition(&x, &y, &width, &height);

    VideoInputBase *temp = this->videoInput;
    this->videoInput = videoFileInput;
    delete(temp);//need to assign before free, as runVideoFeed() still being run

    Mat currentFrame = this->videoInput->getNextFrame();
   // std::cout << currentFrame.size().width << ", " << currentFrame.size().height << std::endl;
    Mat labFrame;
    cvtColor(currentFrame, labFrame, CV_RGB2Lab);
    labFrame.copyTo(this->initialFrame);
    initialiseTrackingFromPosition(x, y, width, height);
}

//--------------------------------------------------------------

void TrackingAndDetection::runVideoFeed()
{
    Mat currentFrame = this->videoInput->getNextFrame();
    if (currentFrame.size().height == 0)
    {
        if(RUN_MANY)
        {
            if (numberOfVideoRun < (int)(sizeof(thresholdValues)/sizeof(*thresholdValues) * sizeof(thresholdValues[0].objectThresholds)/sizeof(*thresholdValues[0].objectThresholds)))
            {
                mkdir(("/Users/helen/Documents/UniWork/Dissertation_MMP/Results/auto4/results" + to_string(numberOfVideoRun)).c_str(), S_IRWXU);
                emit(saveNetwork(this->network, "/Users/helen/Documents/UniWork/Dissertation_MMP/Results/auto4/results" + to_string(numberOfVideoRun)));
                numberOfVideoRun++;
            }
            if (numberOfVideoRun < (int)(sizeof(thresholdValues)/sizeof(*thresholdValues) * sizeof(thresholdValues[0].objectThresholds)/sizeof(*thresholdValues[0].objectThresholds)))
            {
                this->stimulationThreshold = thresholdValues[numberOfVideoRun/5].stimulationThreshold;
                this->objectThreshold = thresholdValues[numberOfVideoRun/5].objectThresholds[numberOfVideoRun%5];

                std::cout << "this->stimulationThreshold : " << this->stimulationThreshold << std::endl;
                std::cout << "this->objectThreshold : " << this->objectThreshold << std::endl;
                this->videoInput->close();
                this->videoInput->startCamera();

                currentFrame = this->videoInput->getNextFrame();
               // std::cout << currentFrame.size().width << ", " << currentFrame.size().height << std::endl;
                Mat labFrame;
                cvtColor(currentFrame, labFrame, CV_RGB2Lab);
                labFrame.copyTo(this->initialFrame);

                int x, y, width, height;
                ((VideoFileInput*)this->videoInput)->getInitialPosition(&x, &y, &width, &height);

                initialiseTrackingFromPosition(x, y, width, height);
            }
        }

        if ((inputType == FILE_INPUT) && (directoryOutput != ""))
        {
            mkdir((directoryOutput).c_str(), S_IRWXU);
            emit(saveNetwork(this->network, directoryOutput));
            exit(EXIT_SUCCESS);
        }

        return;
    }

    //std::cout << "Width : " << currentFrame.size().width << std::endl;
    //std::cout << "Height : " << currentFrame.size().height << std::endl;

    Mat labFrame;
    cvtColor(currentFrame, labFrame, CV_RGB2Lab);
    if(state == TRACKING)
    {
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

void TrackingAndDetection::stateChanged(ProgramState state)
{
    this->state = state;
}

//--------------------------------------------------------------

void TrackingAndDetection::initialiseTrackingFromPosition(int x, int y, int width, int height)
{
    Location initalLocation;
    initalLocation.x = x;
    initalLocation.y = y;
    initalLocation.rotation = 0;
    initalLocation.scaleX = 1.0;
    initalLocation.scaleY = 1.0;

    Rect selectionRect(initalLocation.x, initalLocation.y, width, height);
    Mat selectedAppearance;
    //this->initialFrame(selectionRect).copyTo(selectedAppearance);
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
    this->simplexObjectDetector = new SimplexObjectDetector(this->distanceMeasure);    

    this->network = new Network(selectedAppearance, initalLocation, this->distanceMeasure, this->objectThreshold, this->stimulationThreshold, this->usePredictedLocation);

    //namedWindow( "selectedAppearance", WINDOW_AUTOSIZE );
   // imshow( "selectedAppearance", selectedAppearance);

    this->network->setUsePredictedLocation(this->usePredictedLocation);
    this->state = TRACKING;
}

//--------------------------------------------------------------

void TrackingAndDetection::detectObject(Mat currentFrame)
{
 /*   namedWindow( "initialFrame", WINDOW_AUTOSIZE );
    imshow( "initialFrame", initialFrame);

    namedWindow( "currentFrame", WINDOW_AUTOSIZE );
    imshow( "currentFrame", currentFrame);
*/
    vector<Mat> appearances;
    switch (this->whichARBsToSearchWith) {
    case ABOVE_AVERAGE:
        appearances = this->network->getARBsWithAboveAverageRL();
        break;
    case LAST_AND_HIGHEST:
        appearances = this->network->getLastAndHighestARBs();
        break;
    case ALL:
        appearances = this->network->getAllAppearances();
        break;
    case LAST_AND_CONNECTED:
        appearances = this->network->getLastAndConnectedARBs();
        break;
    default:
        appearances = this->network->getHighestRLAndConnectedARBs();
        break;
    }

    Location predictedLoc = this->network->getPredictedLocation();
    Location closestLoc = predictedLoc;
    int mostMatchedAppearanceIndex = 0;

    // find object : bellow object threshold, and closest measure and closest transformation
    if(!this->useRotation && !this->useScale)
    {
        closestLoc = this->simplexObjectDetector->findObjectNoTransformations(predictedLoc, currentFrame, appearances, &mostMatchedAppearanceIndex);
    }
    else if(!this->useRotation && this->useScale)
    {
        closestLoc = this->simplexObjectDetector->findObjectWithScale(predictedLoc, currentFrame, appearances, &mostMatchedAppearanceIndex);
    }
    else if(this->useRotation && !this->useScale)
    {
        closestLoc = this->simplexObjectDetector->findObjectWithRotation(predictedLoc, currentFrame, appearances, &mostMatchedAppearanceIndex);
    }
    else
    {
        closestLoc = this->simplexObjectDetector->findObjectAllTransformations(predictedLoc, currentFrame, appearances, &mostMatchedAppearanceIndex);
    }

    int width = appearances[mostMatchedAppearanceIndex].size().width;
    int height = appearances[mostMatchedAppearanceIndex].size().height;

    if(closestLoc.x != -1)
    {

    Mat foundAppearance = this->createAppearance(currentFrame, closestLoc, width, height);

    appearances.clear();
    predictedLoc = this->network->addAppearance(foundAppearance, closestLoc);
    }
    emit(updateObjectsPosition(predictedLoc.x, predictedLoc.y, predictedLoc.rotation, width * predictedLoc.scaleX, height * predictedLoc.scaleY));
    //emit(updateObjectsPosition(closestLoc.x, closestLoc.y, closestLoc.rotation, width * closestLoc.scaleX, height * closestLoc.scaleY));
}

//--------------------------------------------------------------

Mat TrackingAndDetection::createAppearance(Mat frame, Location location, int width, int height)
{
    int cols = (int)(((double)width * location.scaleX) + 0.5);
    int rows = (int)(((double)height * location.scaleY) + 0.5);
   // Rect rect(1, 1, cols, rows);
    Mat appearance(rows, cols, frame.type());//frame(rect);//(rows, cols, frame.type());
    for(int x = 0; x < cols; x++)
    {
        for(int y = 0; y < rows; y++)
        {
            int locX = x + location.x;
            int locY = y + location.y;
            rotatePosition(location.rotation, &locX, &locY, frame.size().width / 2, frame.size().height / 2);
            appearance.at<Vec3b>(Point(x,y)) = frame.at<Vec3b>(Point(locX, locY));
        }
    }
    //( "appearance", WINDOW_AUTOSIZE );
    //imshow( "appearance", appearance);

    return appearance;
}

//--------------------------------------------------------------

void TrackingAndDetection::checkIfObjectPredictionWithinFrame(Location *predictedLoc, Mat currentFrame, int appearanceWidth, int appearanceHeight)
{
    if(predictedLoc->x < 1)
    {
        predictedLoc->x = 1;
    }
    else if (predictedLoc->x + appearanceWidth > currentFrame.size().width - 2)
    {
        predictedLoc->x = currentFrame.size().width - appearanceWidth - 2;
    }

    if(predictedLoc->y < 1)
    {
        predictedLoc->y = 1;
    }
    else if (predictedLoc->y + appearanceHeight > currentFrame.size().height - 2)
    {
        predictedLoc->y = currentFrame.size().height - appearanceHeight - 2;
    }
}

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

void TrackingAndDetection::whichARBsToSearchWithChanged(ARBsToSearchWith whichARBsToSearchWith)
{
    this->whichARBsToSearchWith = whichARBsToSearchWith;
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

TrackingAndDetection::~TrackingAndDetection()
{
    if (simplexObjectDetector != NULL)
        delete(simplexObjectDetector);
    if (videoInput != NULL)
        delete(videoInput);
    if (network != NULL)
        delete(network);
    if (distanceMeasure != NULL)
        delete(distanceMeasure);
}

//--------------------------------------------------------------
//--------------------------------------------------------------

