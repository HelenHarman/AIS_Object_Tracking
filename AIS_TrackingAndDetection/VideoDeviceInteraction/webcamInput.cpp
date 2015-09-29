/*!
 * \file webcamInput.cpp
 * \author Helen Harman (heh14@aber.ac.uk)
 * \date 06/03/2015
 * \version 1.0
 *
 * \brief The source code for the WebcamInput class.
 */

#include "webcaminput.h"

//--------------------------------------------------------------

WebcamInput::WebcamInput()
{
    this->startCamera();
}

//--------------------------------------------------------------

bool WebcamInput::startCamera()
{
    this->capture.open(0);
    return this->capture.isOpened();
}

//--------------------------------------------------------------

Mat WebcamInput::getNextFrame()
{
    Mat frame;
    this->capture >> frame;
    cvtColor(frame, frame, CV_BGR2RGB);
    resize(frame, frame, Size(), SCALE_FACTOR, SCALE_FACTOR);
    return frame;
}

WebcamInput::~WebcamInput()
{
    //this->capture.release();
}

//--------------------------------------------------------------
//--------------------------------------------------------------

