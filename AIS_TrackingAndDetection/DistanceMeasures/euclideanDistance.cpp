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
    /*this->maxDistance = 0;
    double pixelAValue, pixelBValue, distanceBetweenPixels, distance;

    for(int x = 0; x <= appearance.size().height; x++)
    {
        for(int y = 0; y <= appearance.size().width; y++)
        {
            Vec3b & colourFrame = appearance.at<Vec3b>(Point(x, y));
            pixelAValue = (int)colourFrame[1];
            pixelBValue = (int)colourFrame[2];

            distance = abs(pixelAValue - 255) + abs(pixelBValue - 255);

            if (distance > this->maxDistance)
            {
                this->maxDistance = distance;
            }
        }
    }*/
   /* this->maxDistance = 0;
    double imageA, imageB, distanceBetweenPixels, distance;

    for(int x = 0; x <= appearance.size().height; x++)
    {
        for(int y = 0; y <= appearance.size().width; y++)
        {
            Vec3b & colourFrame = frame.at<Vec3b>(Point(x, y));
            imageA = (int)colourFrame[1];
            imageB = (int)colourFrame[2];

            distanceBetweenPixels = abs(imageA - 255) ;
            distanceBetweenPixels = distanceBetweenPixels + abs(imageB - 255);
            //distanceBetweenPixels = distanceBetweenPixels + (imageL - appearanceL);
            distance = (distanceBetweenPixels );// distanceBetweenPixels);

            if (distance > this->maxDistance)
            {
                this->maxDistance = distance;
            }
        }
    }*/
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

            AIS_Options::Location location = {i, j, 1, 1, 0}; // x, y, scaleX, scaleY, rotation
            double distance = this->getUnnormalisedDistance(frame, appearance, location) / sqrt(appearance.size().height * appearance.size().width);

            if (distance > this->maxDistance)
            {
                this->maxDistance = distance;
               // cout << this->maxDistance << endl;
            }
        }
    }

    this->maxDistance = this->maxDistance ;//+ (this->maxDistance ); // Add 10% contingency to the maxDistance,
                        // this will allow lighting to change overtime, hopefully will not change by more than 10%
}

//----------------------------------------------------------------------

double EuclideanDistance::getDistance(Mat image, Mat appearance, AIS_Options::Location location)
{   
    int imageWidth = appearance.size().width * location.scaleX;
    int imageHeight = appearance.size().height * location.scaleY;
    double distance = (this->getUnnormalisedDistance(image, appearance, location) / sqrt(MIN(imageHeight, appearance.size().height) * MIN(imageWidth, appearance.size().width))) / this->maxDistance; //TODO sqrt?
    //distance = sigmoid(distance);
    //cout << "distance : " << distance << endl;
    //return distance;
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
    double distance = 0;
    distance = (sqrt(distanceBetweenAppearancesSSD(image, appearance)) / sqrt(MIN(image.size().height, appearance.size().height) * MIN(image.size().width, appearance.size().width))) / this->maxDistance;
    //distance = sigmoid(distance);
    //cout << "distance : " << distance << endl;
    //return distance;
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

double EuclideanDistance::getUnnormalisedDistance(Mat frame, Mat appearance, AIS_Options::Location location)
{
    return sqrt(this->calculateSSD(frame, appearance, location));
}

//----------------------------------------------------------------------

EuclideanDistance::~EuclideanDistance()
{

}

//----------------------------------------------------------------------
//----------------------------------------------------------------------

