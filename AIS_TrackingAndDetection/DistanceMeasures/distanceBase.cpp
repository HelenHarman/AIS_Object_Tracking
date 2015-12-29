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

double DistanceBase::calculateSSD(Mat frame, Mat appearance, Location location)
{
    int width, height, offSetX, offSetY;
    location.getSize(&width, &height, frame);
    location.getCornerPoint(&offSetX, &offSetY, frame);

    double appearanceScaleX = 1, appearanceScaleY = 1, imageScaleX = 1, imageScaleY = 1;
    this->getScales(width, height, appearance.size().width, appearance.size().height, &appearanceScaleX, &appearanceScaleY, &imageScaleX, &imageScaleY);

    double sumOfDistance = 0;
    double imageA, imageB, appearanceA, appearanceB, distanceBetweenPixels;

    // Finds if the width of the image or apperance should be scaled
    for(int x = 0; x < MIN(width, appearance.size().width); x++)
    {
        for(int y = 0; y < MIN(height, appearance.size().height); y++)
        {
            int locX = offSetX + ((int)(((double)x*imageScaleX) + 0.5));
            int locY = offSetY + ((int)(((double)y*imageScaleY) + 0.5));

            if (location.getRotation() > 0)
            {
                rotatePosition(location.getRotation(), &locX, &locY, frame.size().width / 2, frame.size().height / 2);
            }

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

//--------------------------------------------------------------

void DistanceBase::getScales(int frameWidth, int frameHeight, int appearanceWidth, int appearanceHeight, double *appearanceScaleX, double *appearanceScaleY, double *imageScaleX, double *imageScaleY)
{
    if (frameWidth < appearanceWidth)
    {
        *appearanceScaleX = (double)frameWidth / (double)appearanceWidth;
    }
    else if (frameWidth > appearanceWidth)
    {
        *imageScaleX = ((double)appearanceWidth / (double)frameWidth);
    }

    if (frameHeight < appearanceHeight)
    {
        *appearanceScaleY = (double)frameHeight / (double)appearanceHeight;
    }
    else if (frameHeight > appearanceHeight)
    {
        *imageScaleY = ((double)appearanceHeight / (double)frameHeight);
    }
}
//----------------------------------------------------------------------
//----------------------------------------------------------------------
