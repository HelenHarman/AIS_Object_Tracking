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

//--------------------------------------------------------------
/*
int getArgument(const char *id, char *argv[], int argc)
{
    for(int i = 0; i < argc; i++)
    {
        if (strcmp ( id, argv[i]) == 0)
        {
            return i;
        }
    }
    return -1;
}
*/
int main(int argc, char *argv[])
{
    bool rotation = false;
    bool scale = false;
    ARBsToSearchWith whichARBsToSearchWith = HIGHEST_AND_CONNECTED;
    DistanceMeasureType distanceMeasureType = EUCLIDEAN_DISTANCE;
    bool usePredictedLocation = false;
    double stimulationThreshold = 0.4;
    double objectThreshold = 0.6;
    VideoInputType inputType = WEBCAM;
    string configPathName = "";
    string directoryOutput = "";

    ArgumentParser argParser(argc, argv);
    argParser.getArguments(&rotation, &scale, &whichARBsToSearchWith, &distanceMeasureType, &usePredictedLocation, &stimulationThreshold, &objectThreshold, &inputType, &configPathName, &directoryOutput);

    QApplication a(argc, argv);
    MainWindow window;
    window.show();

    TrackingAndDetection trackingAndDetection(rotation, scale, whichARBsToSearchWith, distanceMeasureType, usePredictedLocation, stimulationThreshold, objectThreshold, inputType, configPathName, directoryOutput);
    LinkTrackingAndUi linkTrackingAndUi(window.getImageWidget(), &trackingAndDetection);
    return a.exec();
}





//----------------------------------------------------------------
//----------------------------------------------------------------
