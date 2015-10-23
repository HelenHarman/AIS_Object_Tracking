#include "globalObjectDetector.h"

GlobalObjectDetector::GlobalObjectDetector(DistanceBase *distanceMeasure)
{
    this->distanceMeasure = distanceMeasure;
}

Location GlobalObjectDetector::findObjectAllTransformations(Location predictedLocation, Mat frame, vector<Mat> appearances, int *mostMatchedAppearanceIndex)
{
    return forEachAppearanceFindObject(appearances, frame, predictedLocation, mostMatchedAppearanceIndex);
}

Location GlobalObjectDetector::findObjectWithScale(Location predictedLocation, Mat frame, vector<Mat> appearances, int *mostMatchedAppearanceIndex)
{
    return forEachAppearanceFindObject(appearances, frame, predictedLocation, mostMatchedAppearanceIndex);
}

Location GlobalObjectDetector::findObjectWithRotation(Location predictedLocation, Mat frame, vector<Mat> appearances, int *mostMatchedAppearanceIndex)
{
    return forEachAppearanceFindObject(appearances, frame, predictedLocation, mostMatchedAppearanceIndex);
}

Location GlobalObjectDetector::findObjectNoTransformations(Location predictedLocation, Mat frame, vector<Mat> appearances, int *mostMatchedAppearanceIndex)
{
    return forEachAppearanceFindObject(appearances, frame, predictedLocation, mostMatchedAppearanceIndex);
}



Location GlobalObjectDetector::forEachAppearanceFindObject(vector<Mat> appearances, Mat frame, Location predictedLocation, int *mostMatchedAppearanceIndex)
{
    smallestDistance = 1;
    Location foundLocation = predictedLocation;
    for (int i = 0; i < (int)appearances.size(); i++)
    {
        this->currentDistance = 1;
        Location location = findObject(frame, appearances[i], predictedLocation);
        if(this->currentDistance <= smallestDistance)
        {
            foundLocation = location;
            smallestDistance = this->currentDistance;
            *mostMatchedAppearanceIndex = i;
        }
    }
    return foundLocation;
}

Location GlobalObjectDetector::findObject(Mat frame, Mat appearance, Location location)
{
    currentDistance = 100;
    Location bestLocation;
    for (int i = 0; i < frame.size().width - appearance.size().width*location.scaleX; i++)
    {
        for (int j = 0; j < frame.size().height - appearance.size().height*location.scaleY; j++)
        {
            location.x = i;
            location.y = j;
            double distance = distanceMeasure->getDistance(frame, appearance, location);
            if (distance < currentDistance)
            {
                currentDistance = distance;
                bestLocation = location;
            }
        }
    }
    return bestLocation;
}





