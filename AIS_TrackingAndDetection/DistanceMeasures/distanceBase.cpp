/*!
 * \file distanceBase.cpp
 * \author Helen Harman (heh14@aber.ac.uk)
 * \date 03/04/2015
 * \version 1.0
 *
 * \brief The source code for the DistanceBase class.
 *
 */
#include "distanceBase.h"

//----------------------------------------------------------------------

double DistanceBase::calculateSSD(Mat frame, Mat appearance, AIS_Options::Location location)
{
    int imageWidth = (int)(((double)appearance.size().width * location.scaleX)+0.5);
    int imageHeight = (int)(((double)appearance.size().height * location.scaleY)+0.5);

    double sumOfDistance = 0;
    double appearanceScaleX = 1, appearanceScaleY = 1, imageScaleX = 1, imageScaleY = 1;
    double imageA, imageB, appearanceA, appearanceB, distanceBetweenPixels;

    if (location.scaleX > 1)
    {
        imageScaleX = location.scaleX;
    }
    else if (location.scaleX < 1)
    {
        appearanceScaleX = ((double)appearance.size().width / (double)imageWidth);//1.0 / location.scaleX;
    }

    if (location.scaleY > 1)
    {
        imageScaleY = location.scaleY;
    }
    else if (location.scaleY < 1)
    {
        appearanceScaleY = ((double)appearance.size().height / (double)imageHeight);//1.0 / location.scaleY;
    }

    // Finds if the width of the image or apperance should be scaled
    for(int x = 0; x < MIN(imageWidth, appearance.size().width); x++)
    {
        for(int y = 0; y < MIN(imageHeight, appearance.size().height); y++)
        {
            int locX = location.x + ((int)(((double)x*imageScaleX) + 0.5));
            int locY = location.y + ((int)(((double)y*imageScaleY) + 0.5));

            //std::cout << "pixel image : " << locX << ", " << locY << std::endl;

            rotatePosition(location.rotation, &locX, &locY, frame.size().width / 2, frame.size().height / 2);

            Vec3b & colourFrame = frame.at<Vec3b>(Point(locX, locY));
            imageA = (int)colourFrame[1];
            imageB = (int)colourFrame[2];

            locX = (int)(((double)x*appearanceScaleX) + 0.5);
            locY = (int)(((double)y*appearanceScaleY) + 0.5);

            Vec3b & colourAppearance = appearance.at<Vec3b>(Point(locX, locY));
            appearanceA = (int)colourAppearance[1];
            appearanceB = (int)colourAppearance[2];

            // get the difference between the pixel values, square them, then add them to the sum of distances
            distanceBetweenPixels = abs(imageA - appearanceA) ;
            distanceBetweenPixels = distanceBetweenPixels + abs(imageB - appearanceB);
            //distanceBetweenPixels = distanceBetweenPixels + (imageL - appearanceL);
            sumOfDistance = sumOfDistance + (distanceBetweenPixels * distanceBetweenPixels);
        }
    }
    return sumOfDistance;
}

//----------------------------------------------------------------------

double DistanceBase::distanceBetweenAppearancesSSD(Mat image, Mat appearance)
{
    AIS_Options::Location location = {0, 0, ((double)image.size().width / (double)appearance.size().width), ((double)image.size().height / (double)appearance.size().height), 0};
    return calculateSSD(image, appearance, location);
}

//----------------------------------------------------------------------

double DistanceBase::getMaxDistance()
{
    return this->maxDistance;
}

/*
double DistanceBase::sigmoid(double x)
{
    double result = 1.0 / (1.0 + exp(-x));
    std::cout << "1 result : " << result << std::endl;
    result = (result - 0.5) / 0.5; // x will never be negative, so sigmoid will be between 0.5 and 1
    std::cout << "2 result : " << result << std::endl;
    return result;
}*/
//----------------------------------------------------------------------
//----------------------------------------------------------------------
