/*!
 * \file euclideanDistance.cpp
 * \author Helen Harman (heh14@aber.ac.uk) Aberystwyth University
 * \date 07/03/2015
 * \version 1.0
 *
 * \brief The source code for the EuclideanDistance class.
 */
#include "euclideandistance.h"


//----------------------------------------------------------------------

EuclideanDistance::EuclideanDistance(Mat frame, Mat appearance)
{
    this->maxDistance = 0;
    // Search the frame for the max euclidean distance
    for (int i = 0; i < (frame.size().width - appearance.size().width); i+=appearance.size().width/2)//++)
    {
        if (i > (frame.size().width - appearance.size().width))
        {
            break;
        }
        for(int j = 0; j < (frame.size().height - appearance.size().height); j+=appearance.size().height/2)//++)
        {
            if (j > (frame.size().height - appearance.size().height))
            {
                break;
            }

            Location location(frame, appearance, i, j);

            double distance = this->getUnnormalisedDistance(frame, appearance, location);

            if (distance > this->maxDistance)
            {
                this->maxDistance = distance;
            }
        }
    }
    this->maxDistance = this->maxDistance / sqrt(appearance.size().width * appearance.size().height);
}

//----------------------------------------------------------------------

double EuclideanDistance::getDistance(Mat image, Mat appearance, Location location)
{   
    int imageWidth, imageHeight;
    location.getSize(&imageWidth, &imageHeight, image);
    double distance = (this->getUnnormalisedDistance(image, appearance, location) ) / (this->maxDistance * sqrt(imageWidth*imageHeight));

    if (distance > 1)
    {
        return 1;
    }
    else
    {
        return distance;
    }
}

//----------------------------------------------------------------------

double EuclideanDistance::getDistanceBetweenAppearances(Mat image, Mat appearance)
{
    Location location(image.size().width/2, image.size().height/2, 100, 100, 0);
    return this->getDistance(image, appearance, location);
}

//----------------------------------------------------------------------

double EuclideanDistance::getUnnormalisedDistance(Mat frame, Mat appearance, Location location)
{
    return sqrt(this->calculateSSD(frame, appearance, location));
}

//----------------------------------------------------------------------

EuclideanDistance::~EuclideanDistance()
{

}

//----------------------------------------------------------------------
//----------------------------------------------------------------------

