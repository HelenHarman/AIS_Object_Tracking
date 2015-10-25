#include "globalObjectDetector.h"

GlobalObjectDetector::GlobalObjectDetector(DistanceBase *distanceMeasure)
{
    this->distanceMeasure = distanceMeasure;
}

Location GlobalObjectDetector::findObjectAllTransformations(Location predictedLocation, Mat frame, vector<ARB*> appearances)//, int *mostMatchedAppearanceIndex)
{
    return forEachAppearanceFindObject(appearances, frame, predictedLocation);//, mostMatchedAppearanceIndex);
}

Location GlobalObjectDetector::findObjectWithScale(Location predictedLocation, Mat frame, vector<ARB*> appearances)//, int *mostMatchedAppearanceIndex)
{
    return forEachAppearanceFindObject(appearances, frame, predictedLocation);//, mostMatchedAppearanceIndex);
}

Location GlobalObjectDetector::findObjectWithRotation(Location predictedLocation, Mat frame, vector<ARB*> appearances)//, int *mostMatchedAppearanceIndex)
{
    return forEachAppearanceFindObject(appearances, frame, predictedLocation);//, mostMatchedAppearanceIndex);
}

Location GlobalObjectDetector::findObjectNoTransformations(Location predictedLocation, Mat frame, vector<ARB*> appearances)//, int *mostMatchedAppearanceIndex)
{
    return forEachAppearanceFindObject(appearances, frame, predictedLocation);//, mostMatchedAppearanceIndex);
}



Location GlobalObjectDetector::forEachAppearanceFindObject(vector<ARB*> appearances, Mat frame, Location predictedLocation)//, int *mostMatchedAppearanceIndex)
{
    smallestDistance = 1;
    Location foundLocation(predictedLocation);
    for (int i = 0; i < (int)appearances.size(); i++)
    {
        this->currentDistance = 1;
        Location location = findObject(frame, appearances[i]->getAppearance(), predictedLocation);
        if(this->currentDistance <= smallestDistance)
        {
            foundLocation = location;
            smallestDistance = this->currentDistance;
            //*mostMatchedAppearanceIndex = i;
        }
    }
    return foundLocation;
}

Location GlobalObjectDetector::findObject(Mat frame, Mat appearance, Location location)
{
    currentDistance = 100;
    Location bestLocation;
    int width, height;
    location.getSize(&width, &height, frame);
    for (int i = 0; i < frame.size().width - width; i++)
    {
        for (int j = 0; j < frame.size().height - height; j++)
        {
            location.setX(i + ((((double)frame.size().width / 100.00) * location.getScaleX())/2));
            location.setY(j + ((((double)frame.size().height / 100.00) * location.getScaleY())/2));;
            double distance = distanceMeasure->getDistance(frame, appearance, location);
            if (distance < currentDistance)
            {
                currentDistance = distance;
                bestLocation = Location(location);
            }
        }
    }
    return bestLocation;
}





