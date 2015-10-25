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

    /* std::cout << "appearanceScaleX " << appearanceScaleX << std::endl;
     std::cout << "appearanceHeight " << appearanceHeight << std::endl;
     std::cout << "appearanceScaleY " << appearanceScaleY << std::endl;
     std::cout << "appearanceWidth " << appearanceWidth << std::endl;


     std::cout << "imageScaleX " << imageScaleX << std::endl;
     std::cout << "fframeHeight " << frameHeight << std::endl;
     std::cout << "imageScaleY " << imageScaleY << std::endl;
     std::cout << "frameWidth " << frameWidth << std::endl;
 */
}



/*
double DistanceBase::calculateSSD(Mat frame, Mat appearance, AIS_Options::Location location)
{
    int imageWidth = (int)(((double)appearance.size().width * location.scaleX)+0.5);
    int imageHeight = (int)(((double)appearance.size().height * location.scaleY)+0.5);

    //double sumOfDistance = 0;
    double appearanceScaleX = 1, appearanceScaleY = 1, imageScaleX = 1, imageScaleY = 1;
    //double imageA, imageB, appearanceA, appearanceB, distanceBetweenPixels;

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
    return calculateDistance(frame, appearance, appearanceScaleX, imageScaleX, appearanceScaleY, imageScaleY, MIN(imageWidth, appearance.size().width), MIN(imageHeight, appearance.size().height), location.rotation, location.x, location.y);



}

//----------------------------------------------------------------------
/
double DistanceBase::distanceBetweenAppearancesSSD(Mat image, Mat appearance)
{
    AIS_Options::Location location = {0, 0, ((double)image.size().width / (double)appearance.size().width), ((double)image.size().height / (double)appearance.size().height), 0};
    return calculateSSD(image, appearance, location);
}

/
double DistanceBase::distanceBetweenAppearancesSSD(Mat image, Mat appearance)
{
    //double sumOfDistance = 0;
    double appearanceScaleX = 1, appearanceScaleY = 1, imageScaleX = 1, imageScaleY = 1;
   // double imageA, imageB, appearanceA, appearanceB, distanceBetweenPixels;

    if (image.size().width < appearance.size().width)
    {
        appearanceScaleX = (double)image.size().width / (double)appearance.size().width ;
    }
    else if (image.size().width > appearance.size().width)
    {
        imageScaleX = ((double)appearance.size().width / (double)image.size().width);//1.0 / location.scaleX;
    }

    if (image.size().height < appearance.size().height)
    {
        appearanceScaleY = (double)image.size().height / (double)appearance.size().height;
    }
    else if (image.size().height > appearance.size().height)
    {
        imageScaleY = ((double)appearance.size().height / (double)image.size().height);//1.0 / location.scaleY;
    }

    return calculateDistance(image, appearance, appearanceScaleX, imageScaleX, appearanceScaleY, imageScaleY, MIN((double)image.size().width, appearance.size().width), MIN((double)image.size().height, appearance.size().height), 0, 0, 0);
}


double DistanceBase::calculateDistance(Mat image, Mat appearance, double appearanceScaleX, double imageScaleX, double appearanceScaleY, double imageScaleY, int imageWidth, int imageHeight, int rotation, int offSetX, int offSetY)
{
    double sumOfDistance = 0;
    double imageA, imageB, appearanceA, appearanceB, distanceBetweenPixels;

    // Finds if the width of the image or apperance should be scaled
    for(int x = 0; x < imageWidth; x++)
    {
        for(int y = 0; y < imageHeight; y++)
        {
            int locX = offSetX + ((int)(((double)x*imageScaleX) + 0.5));
            int locY = offSetY + ((int)(((double)y*imageScaleY) + 0.5));

            if (rotation > 0)
            {
                rotatePosition(rotation, &locX, &locY, image.size().width / 2, image.size().height / 2);
            }

            Vec3b & colourFrame = image.at<Vec3b>(Point(locX, locY));
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
*/

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
