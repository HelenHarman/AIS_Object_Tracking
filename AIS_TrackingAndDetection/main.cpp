/*! \mainpage
 *
 * \section intro_sec Introduction
 *
 * The AIS tracking and detection software was created for my(Helen Harman's) dissertation project.
 *
 * \section contact_sec Contact
 *
 * Helen Harman (heh14@aber.ac.uk)
 * Aberystwyth University MEng Software Engineering Student.
 *
 */

/*! \file main.cpp
 *  \author Helen Harman (heh14@aber.ac.uk) Aberystwyth University
 *  \date 06/03/2015
 *  \version 1.0
 */
#include "mainwindow.h"
#include <QApplication>

#include "trackingAndDetection.h"
#include "linkTrackingAndUi.h"
#include "argumentParser.h"
#include "groundTruthDistances.h"

//--------------------------------------------------------------

int main(int argc, char *argv[])
{
    bool rotation = false;
    bool scale = true;
    ARBsToSearchWith whichARBsToSearchWith = HIGHEST_AND_CONNECTED;
    DistanceMeasureType distanceMeasureType = EUCLIDEAN_DISTANCE;
    bool usePredictedLocation = false;
    double stimulationThreshold = 0;//0.4;
    double objectThreshold = 1;//0.6
    double linkingThreshold = 0.4;
    VideoInputType inputType = WEBCAM;
    string configPathName = "";
    string directoryOutput = "";
    int numberOfinitialARBs = 10;

    int numIteration = 0;

    ArgumentParser argParser(argc, argv);
    argParser.getArguments(&rotation, &scale, &whichARBsToSearchWith, &distanceMeasureType, &usePredictedLocation, &stimulationThreshold, &objectThreshold, &linkingThreshold, &inputType, &configPathName, &directoryOutput, &numberOfinitialARBs, &numIteration);

    QApplication a(argc, argv);
    MainWindow window;
    window.show();

    TrackingAndDetection trackingAndDetection(rotation, scale, whichARBsToSearchWith, distanceMeasureType, usePredictedLocation, stimulationThreshold, objectThreshold, linkingThreshold, inputType, configPathName, directoryOutput, numberOfinitialARBs, numIteration);
    LinkTrackingAndUi linkTrackingAndUi(window.getImageWidget(), &trackingAndDetection);
    return a.exec();
}

/*
int main(int argc, char *argv[])
{
    GroundTruthDistances *groundTruthDistances = new GroundTruthDistances();
    string gtFileName = "/Users/helen/Documents/UniWork/AIS_Object_Tracking/DataSets/Tiger1/groundtruth_rect.txt";
    string outputFileName = "/Users/helen/Documents/UniWork/AIS_Object_Tracking/Results/gtDistances.txt";
    string videoFileName = "/Users/helen/Documents/UniWork/AIS_Object_Tracking/DataSets/Tiger1/img/%4d.jpg";
    groundTruthDistances->compareDistances(gtFileName, outputFileName, videoFileName);
    return 1;
}

*/


//----------------------------------------------------------------
//----------------------------------------------------------------
