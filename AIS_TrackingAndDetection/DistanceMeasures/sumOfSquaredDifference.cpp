/*!
 * \file sumOfSquaredDifference.cpp
 * \author Helen Harman (heh14@aber.ac.uk)
 * \date 24/03/2015
 * \version 1.0
 *
 * \brief The source code for the SumOfSquaredDifference class.
 */

#include "sumOfSquaredDifference.h"

//----------------------------------------------------------------------

SumOfSquaredDifference::SumOfSquaredDifference(Mat frame, Mat appearance)
{
    this->maxDistance = 0;
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
            distance = (distanceBetweenPixels * distanceBetweenPixels);

            if (distance > this->maxDistance)
            {
                this->maxDistance = distance;
            }
        }
    }

    /*
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
            AIS_Options::Location location = {i, j, 1, 1, 0};
            double distance = this->getUnnormalisedDistance(frame, appearance, location) / (appearance.size().height * appearance.size().width);



            if (distance > this->maxDistance)
            {
                this->maxDistance = distance;
            }
        }
    }
    this->maxDistance = this->maxDistance + (this->maxDistance / 5);*/
}

//----------------------------------------------------------------------

double SumOfSquaredDifference::getDistance(Mat image, Mat appearance, AIS_Options::Location location)
{
  /*  int imageWidth = appearance.size().width * location.scaleX;
    int imageHeight = appearance.size().height * location.scaleY;
    double distance =  (this->getUnnormalisedDistance(image, appearance, location) / (MIN(imageHeight, appearance.size().height) * MIN(imageWidth, appearance.size().width))) / 510;
*/

    int imageWidth = appearance.size().width * location.scaleX;
    int imageHeight = appearance.size().height * location.scaleY;
    double distance = (this->getUnnormalisedDistance(image, appearance, location) / (MIN(imageHeight, appearance.size().height) * MIN(imageWidth, appearance.size().width))) / this->maxDistance;/// 40000;
    //distance = sigmoid(distance);
    //std::cout << "distance : " << distance << std::endl;
    //return distance;
   // std::cout << distance << std::endl;

//std::cout << "getUnnormalisedDistance : " << this->getUnnormalisedDistance(image, appearance, location) << std::endl;

//std::cout << "MIN : " << (MIN(imageHeight, appearance.size().height) * MIN(imageWidth, appearance.size().width)) << std::endl;



    if (distance > 1)
    {
        return 1;
    }
    else
    {
        return distance;
    }
}


double SumOfSquaredDifference::getDistanceBetweenAppearances(Mat image, Mat appearance)
{
    /*int height = MIN(image.size().height, appearance.size().height);
    int width = MIN(image.size().width, appearance.size().width);
    double distance = (this->distanceBetweenAppearancesSSD(image, appearance) / (height * width)) / 510;
*/
    double distance = ((distanceBetweenAppearancesSSD(image, appearance)) / (MIN(image.size().height, appearance.size().height) * MIN(image.size().width, appearance.size().width))) / this->maxDistance;/// 40000;
    //distance = sigmoid(distance);
    //std::cout << "distance : " << distance << std::endl;
    //return distance;
    //std::cout << "getDistanceBetweenAppearances :" << distance << std::endl;
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

double SumOfSquaredDifference::getUnnormalisedDistance(Mat image, Mat appearance, AIS_Options::Location location)
{
    return this->calculateSSD(image, appearance, location);
}

//----------------------------------------------------------------------

SumOfSquaredDifference::~SumOfSquaredDifference()
{

}

