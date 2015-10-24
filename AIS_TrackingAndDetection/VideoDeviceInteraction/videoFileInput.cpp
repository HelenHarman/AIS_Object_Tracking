/*!
 * \file videoFileInput.cpp
 * \author Helen Harman (heh14@aber.ac.uk)
 * \date 13/03/2015
 * \version 1.0
 *
 * \brief The source code for the VideoFileInput class.
 */

#include "videoFileInput.h"

//--------------------------------------------------------------

VideoFileInput::VideoFileInput(string videoConfigFilePathName)
{
    std::fstream configFile(videoConfigFilePathName, std::ios_base::in);
    string fileIn, temp;
    while (configFile >> fileIn)
    {
        if (fileIn == "video_file")
        {
            configFile >> temp >> this->videoFilePathName;
        }
        else if (fileIn == "location_x")
        {
            configFile >> temp >> this->x;
        }
        else if (fileIn == "location_y")
        {
            configFile >> temp >> this->y;
        }
        else if (fileIn == "width")
        {
            configFile >> temp >> this->width;
        }
        else if (fileIn == "height")
        {
            configFile >> temp >> this->height;
        }
    }
    this->startCamera();

}

//--------------------------------------------------------------

bool VideoFileInput::startCamera()
{
    return this->capture.open(this->videoFilePathName);
}

//--------------------------------------------------------------

bool VideoFileInput::startCamera(string videoFilePathName)
{
    this->videoFilePathName = videoFilePathName;
    return this->capture.open(this->videoFilePathName);
}

//--------------------------------------------------------------

Mat VideoFileInput::getNextFrame()
{
    Mat frame;
    if (!this->capture.read(frame))
    {
        return frame;
        //this->startCamera();
        //this->capture.read(frame);
    }

    cvtColor(frame, frame, CV_BGR2RGB);
    //resize(frame, frame, Size(), SCALE_FACTOR, SCALE_FACTOR);
    return frame;
}

//--------------------------------------------------------------
/*
void VideoFileInput::getInitialPosition(int *x, int *y, int *width, int *height)
{
    *x = this->x;
    *y = this->y;
    *width = this->width;
    *height = this->height;
}*/

//--------------------------------------------------------------

Location VideoFileInput::getInitialLocation(Mat frame)
{
    Location location(frame, this->width, this->height, this->x, this->y);
    /*location.x = this->x + (this->width/2);
    location.y = this->y + (this->height/2);
    location.scaleX = ((double)this->width/(double)frame.size().width)*100.00;
    location.scaleY = ((double)this->height/(double)frame.size().height)*100.00;
    location.rotation = 0;*/
    return location;
}

//--------------------------------------------------------------
//--------------------------------------------------------------

