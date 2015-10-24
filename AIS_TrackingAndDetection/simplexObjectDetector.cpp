/*! \file simplexObjectDetection.cpp
 *  \author Helen Harman (heh14@aber.ac.uk)
 *  \date 29/03/2015
 *  \version 1.0
 *
 * \brief The source code for the SimplexObjectDetector class.
 * This code has been created using : https://www.gnu.org/software/gsl/manual/html_node/Multimin-Examples.html
 */

#include "simplexObjectDetector.h"

double SimplexObjectDetector::X_POSITION_STEP_SIZE = 20;//25;//6;//15.0;//10.0;
double SimplexObjectDetector::Y_POSITION_STEP_SIZE = 20;//25;//6;//15.0;//10.0;
double SimplexObjectDetector::SCALE_X_STEP_SIZE = 1;//0.01;//0.02//0.05;
double SimplexObjectDetector::SCALE_Y_STEP_SIZE = 1;//0.01;//0.02//0.05;
double SimplexObjectDetector::ROTATION_STEP_SIZE = 1.0;

//---------------------------------------------------------------------

SimplexObjectDetector::SimplexObjectDetector(DistanceBase *distanceMeasure)
{
    this->distanceMeasure = distanceMeasure;
}

//---------------------------------------------------------------------

Location SimplexObjectDetector::findObjectNoTransformations(Location predictedLocation, Mat frame, vector<Mat> appearances, int *mostMatchedAppearanceIndex)
{
    size_t numberOfDimensions = 2;
    return forEachAppearanceFindObject(appearances, frame, predictedLocation, numberOfDimensions, mostMatchedAppearanceIndex);
}

//---------------------------------------------------------------------

Location SimplexObjectDetector::findObjectWithRotation(Location predictedLocation, Mat frame, vector<Mat> appearances, int *mostMatchedAppearanceIndex)
{
    size_t numberOfDimensions = 3;
    return forEachAppearanceFindObject(appearances, frame, predictedLocation, numberOfDimensions, mostMatchedAppearanceIndex);
}

//---------------------------------------------------------------------

Location SimplexObjectDetector::findObjectWithScale(Location predictedLocation, Mat frame, vector<Mat> appearances, int *mostMatchedAppearanceIndex)
{
    size_t numberOfDimensions = 4;
    return forEachAppearanceFindObject(appearances, frame, predictedLocation, numberOfDimensions, mostMatchedAppearanceIndex);
}

//---------------------------------------------------------------------

Location SimplexObjectDetector::findObjectAllTransformations(Location predictedLocation, Mat frame, vector<Mat> appearances, int *mostMatchedAppearanceIndex)
{
    size_t numberOfDimensions = 5;
    return forEachAppearanceFindObject(appearances, frame, predictedLocation, numberOfDimensions, mostMatchedAppearanceIndex);
}

//---------------------------------------------------------------------

Location SimplexObjectDetector::forEachAppearanceFindObject(vector<Mat> appearances, Mat frame, Location predictedLocation, size_t numberOfDimensions, int *mostMatchedAppearanceIndex)
{
    Location foundLocation = predictedLocation;
    this->smallestDistance = 1;
    *mostMatchedAppearanceIndex = 0;
    gsl_vector *stepSize, *startingLocations;
    stepSize = gsl_vector_alloc (numberOfDimensions);
    startingLocations = gsl_vector_alloc (numberOfDimensions);
    for (int i = 0; i < (int)appearances.size(); i++)
    {
        this->currentDistance = 1;
        this->setupInitialVectors(stepSize, startingLocations, predictedLocation, numberOfDimensions);
        gsl_multimin_fminimizer *minimizer = findObject(frame, appearances[i], stepSize, startingLocations, numberOfDimensions);

        if(this->currentDistance <= this->smallestDistance)
        {
            foundLocation = getLocationFromVector(minimizer->x, numberOfDimensions, predictedLocation);
            //std::cout << "foundLocation : " << foundLocation.scaleX << ", " << foundLocation.scaleY << std::endl;

            this->smallestDistance = this->currentDistance;
            *mostMatchedAppearanceIndex = i;
            //std::cout << "this->smallestDistance : " << this->smallestDistance << std::endl;
        }
        gsl_multimin_fminimizer_free (minimizer);
    }

    // clean-up
    gsl_vector_free(startingLocations);
    gsl_vector_free(stepSize);
    //std::cout << "foundLocation : " << foundLocation.x << ", " << foundLocation.y << std::endl;

    //foundLocation = checkLocationInRange(foundLocation, appearances[*mostMatchedAppearanceIndex], frame);
    if (checkLocationWithinFrame(foundLocation, frame) != 0)
    {
        std::cout << "Objects location not found" << std::endl;
        foundLocation = Location(-1,-1,-1,-1,-1);
    }
    //std::cout << "num appearances : " << appearances.size() << std::endl;
    //std::cout << "foundLocation : " << foundLocation.x << ", " << foundLocation.y << std::endl;
    return foundLocation;
}

//---------------------------------------------------------------------

void SimplexObjectDetector::setupInitialVectors(gsl_vector *stepSize, gsl_vector *startingLocations, Location predictedLocation, size_t numberOfDimensions)
{
    //std::cout << X_POSITION_STEP_SIZE << std::endl;
    // setup for x and y
    gsl_vector_set(stepSize, 0, X_POSITION_STEP_SIZE);
    gsl_vector_set(stepSize, 1, Y_POSITION_STEP_SIZE);

    gsl_vector_set(startingLocations, 0, predictedLocation.getX());
    gsl_vector_set(startingLocations, 1, predictedLocation.getY());

    // setup for rotation
    if(numberOfDimensions == 3 || numberOfDimensions == 5)
    {
        gsl_vector_set(stepSize, numberOfDimensions-1, ROTATION_STEP_SIZE);
        gsl_vector_set(startingLocations, numberOfDimensions-1, predictedLocation.getRotation());
    }

    // setup for scale
    if(numberOfDimensions == 4 || numberOfDimensions == 5)
    {
        gsl_vector_set(stepSize, 2, SCALE_X_STEP_SIZE);
        gsl_vector_set(stepSize, 3, SCALE_Y_STEP_SIZE);
        gsl_vector_set(startingLocations, 2, predictedLocation.getScaleX());
        gsl_vector_set(startingLocations, 3, predictedLocation.getScaleY());
    }
}

//---------------------------------------------------------------------

Location SimplexObjectDetector::getLocationFromVector(const gsl_vector * locationVector, const size_t numberOfDimensions, Location location)
{
    //Location foundLocation(gsl_vector_get(locationVector, 0), gsl_vector_get(locationVector, 1), 100, 100, 0);
    // x and y
    location.setX(gsl_vector_get(locationVector, 0));
    location.setY(gsl_vector_get (locationVector, 1));
    /*foundLocation.rotation = 0;
    foundLocation.scaleX = 1;
    foundLocation.scaleY = 1;*/

    // rotation
    if(numberOfDimensions == 3 || numberOfDimensions == 5)
    {
        location.setRotation(gsl_vector_get(locationVector, numberOfDimensions-1));
    }

    // scale
    if(numberOfDimensions == 4 || numberOfDimensions == 5)
    {
        //std::cout << "foundLocation.scaleY : " <<  gsl_vector_get (locationVector, 2) << ", " << gsl_vector_get (locationVector, 3) << std::endl;

        location.setScaleX(fabs(gsl_vector_get (locationVector, 2)));
        location.setScaleY(fabs(gsl_vector_get (locationVector, 3)));//fabs(gsl_vector_get (locationVector, 3));
       // std::cout << "foundLocation.scaleY : " <<  foundLocation.scaleX << ", " << foundLocation.scaleY << std::endl;

    }
    return location;
}

//---------------------------------------------------------------------

gsl_multimin_fminimizer* SimplexObjectDetector::findObject(Mat frame, Mat appearance, gsl_vector * stepSize, gsl_vector * startingLocations, size_t numberOfDimensions)
{
    gsl_multimin_fminimizer *minimizer;
    gsl_multimin_function minimizerFunction;
    size_t iter = 0;
    int status;
    double size;
    void* params[3] = {(void*)this, (void*)&appearance, (void*)&frame};  

    // set the minimizerFunction to a lambda function which calls this.getDistance()
    minimizerFunction.f = [](const gsl_vector *v, void *params) -> double
        {
            void ** array = (void**)params;
            SimplexObjectDetector* simplexObjectDecector = (SimplexObjectDetector*)array[0];
            return simplexObjectDecector->getDistance(v, params);
        };
    minimizerFunction.n = numberOfDimensions;
    minimizerFunction.params = (void *)&params;

    minimizer = gsl_multimin_fminimizer_alloc (gsl_multimin_fminimizer_nmsimplex2 , numberOfDimensions);
    gsl_multimin_fminimizer_set (minimizer, &minimizerFunction, startingLocations, stepSize);
    do {
        iter++;
        status = gsl_multimin_fminimizer_iterate(minimizer);
        if (status) break;
        size = gsl_multimin_fminimizer_size (minimizer);
        status = gsl_multimin_test_size (size, 1e-3); // stop when gradient hits 0.001
    }
    while (status == GSL_CONTINUE && iter < 100);

    return minimizer;
}

//---------------------------------------------------------------------

double SimplexObjectDetector::getDistance(const gsl_vector*v, void* params)
{
    void ** array = (void**)params;
    Mat appearance = *(Mat*)array[1];
    Mat frameOriginal = *(Mat*)array[2];
    Mat frame;
    frameOriginal.copyTo(frame); // otherwise we rotate all instances of currentFrame
    Location location(frame, appearance);
    location = getLocationFromVector(v, v->size, location);

    //if not check withint frame return max double
    int result = checkLocationWithinFrame(location, frame);
    if(result != 0)
    {
        return result;
    }

    double distance = distanceMeasure->getDistance(frame, appearance, location);
    if(distance <= this->currentDistance)
    {
        this->currentDistance = distance;
    }

    return distance;
}

//---------------------------------------------------------------------
/*
int SimplexObjectDetector::checkSizeInRange(int size, int frameSize)
{
    if(size < 1)
    {
        size = 1;
    }
    else if(size > frameSize - 2)
    {
        size = frameSize - 2;
    }
    return size;
}
*/
//---------------------------------------------------------------------
/*
Location SimplexObjectDetector::checkLocationInRange(Location location, Mat appearance, Mat frame)
{
    int bottomLeftX = location.x;
    int bottomLeftY = location.y;

    int bottomRightX = location.x + (int)(((double)appearance.size().width * location.scaleX)+0.5);
    int bottomRightY = location.y;

    int topRightX = location.x + (int)(((double)appearance.size().width * location.scaleX)+0.5);
    int topRightY = location.y + (int)(((double)appearance.size().height * location.scaleY)+0.5);

    int topLeftX = location.x;
    int topLeftY = location.y + (int)(((double)appearance.size().height * location.scaleY)+0.5);

    if (location.rotation != 0)
    {
        this->rotatePosition(location.rotation, &bottomLeftX, &bottomLeftY, frame.size().width/2, frame.size().height/2);
        this->rotatePosition(location.rotation, &bottomRightX, &bottomRightY, frame.size().width/2, frame.size().height/2);
        this->rotatePosition(location.rotation, &topRightX, &topRightY, frame.size().width/2, frame.size().height/2);
        this->rotatePosition(location.rotation, &topLeftX, &topLeftY, frame.size().width/2, frame.size().height/2);
    }

    int minX = MIN(MIN(bottomLeftX, topLeftX), MIN(bottomRightX, topRightX));
    int maxX = MAX(MAX(bottomLeftX, topLeftX), MAX(bottomRightX, topRightX));
    int minY = MIN(MIN(bottomLeftY, topLeftY), MIN(bottomRightY, topRightY));
    int maxY = MAX(MAX(bottomLeftY, topLeftY), MAX(bottomRightY, topRightY));

    if(minX <= 1)
    {
        location = {-1, -1, -1, -1, -1};
        //location.x = 0; // add 1 incase minX is 0
    }
    else if (minY <= 1)
    {
        location = {-1, -1, -1, -1, -1};
        //location.y = 0; // add 1 incase minX is 0
    }
    else if(maxX >= frame.size().width-2)
    {
        location = {-1, -1, -1, -1, -1};
        //location.scaleX = frame.size().width / appearance.size().width;
    }
    else if(maxY >= frame.size().height-2)
    {
        location = {-1, -1, -1, -1, -1};
        //location.scaleY = frame.size().width / appearance.size().width;
    }


/
    if((int)(((double)appearance.size().width * location.scaleX)+0.5) <= 0 || (int)(((double)appearance.size().height * location.scaleY)+0.5) <= 0)
    {
        return (1000 * location.scaleY) + 1;
    }/

//std::cout << "hello " << std::endl;
    return location;

    /  if(numberOfDimensions == 4 || numberOfDimensions == 5)
    {
        location.scaleX = (checkSizeInRange((int)(((double)appearance.size().width * location.scaleX)+0.5), frame.size().width) / (double)appearance.size().width);
        location.scaleY = (checkSizeInRange((int)(((double)appearance.size().height * location.scaleY)+0.5), frame.size().height) / (double)appearance.size().height);
    }
    checkPostionInRange(&location.x, &location.y, location.scaleX * (double)appearance.size().width, location.scaleY * (double)appearance.size().height, location.rotation, frame);
    return location;/
}*/

//---------------------------------------------------------------------
/*
int SimplexObjectDetector::checkPostionInRange(int * positionX, int * positionY, int appearanceWidth, int appearanceHeight, int rotation, Mat frame)//int frameSize)
{
    int topLeftX = 1;
    int topLeftY = 1;
    this->rotatePosition(rotation, &topLeftX, &topLeftY, frame.size().width/2, frame.size().height/2);
    int topRightX = frame.size().width;
    int topRightY = 1;
    this->rotatePosition(rotation, &topRightX, &topRightY, frame.size().width/2, frame.size().height/2);
    int bottomLeftX = 1;
    int bottomLeftY = frame.size().height;
    this->rotatePosition(rotation, &bottomLeftX, &bottomLeftY, frame.size().width/2, frame.size().height/2);
    int bottomRightX = frame.size().width;;
    int bottomRightY = frame.size().height;
    this->rotatePosition(rotation, &bottomRightX, &bottomRightY, frame.size().width/2, frame.size().height/2);
    int maxX = MIN(topRightX, bottomRightX);
    int minX = MAX(topLeftX, bottomLeftX);
    int maxY = MIN(bottomLeftY, bottomRightY);
    int minY = MAX(topLeftY, topRightY);

    int newXposition;
    int newYposition;
    newXposition = checkXorYPostionInRange(*positionX, appearanceWidth, maxX, minX);
    newYposition = checkXorYPostionInRange(*positionY, appearanceHeight, maxY, minY);

    if(*positionX != newXposition || *positionY != newYposition)
    {
        int xDiff = MAX(*positionX, newXposition) - MIN(*positionX, newXposition);
        int yDiff = MAX(*positionY, newYposition) - MIN(*positionY, newYposition);
        return ((xDiff + yDiff) * (xDiff + yDiff));
    }
    else
    {
        *positionX = newXposition;
        *positionY = newYposition;
        return 0;
    }
}
*/
//--------------------------------------------------------------

int SimplexObjectDetector::checkLocationWithinFrame(Location location, Mat frame)
{
    int bottomLeftX,bottomLeftY;//  = location.x;
    location.getCornerPoint(&bottomLeftX, &bottomLeftY, frame);
    int width, height;
    location.getSize(&width, &height, frame);
    //int bottomLeftY = location.y;

    int bottomRightX = bottomLeftX + width;
    int bottomRightY = bottomLeftY;

    int topRightX = bottomLeftX + width;
    int topRightY = bottomLeftY + height;

    int topLeftX = bottomLeftX;
    int topLeftY = bottomLeftY + height;

    if (location.getRotation() != 0)
    {
        this->rotatePosition(location.getRotation(), &bottomLeftX, &bottomLeftY, frame.size().width/2, frame.size().height/2);
        this->rotatePosition(location.getRotation(), &bottomRightX, &bottomRightY, frame.size().width/2, frame.size().height/2);
        this->rotatePosition(location.getRotation(), &topRightX, &topRightY, frame.size().width/2, frame.size().height/2);
        this->rotatePosition(location.getRotation(), &topLeftX, &topLeftY, frame.size().width/2, frame.size().height/2);
    }

    int minX = MIN(MIN(bottomLeftX, topLeftX), MIN(bottomRightX, topRightX));
    int maxX = MAX(MAX(bottomLeftX, topLeftX), MAX(bottomRightX, topRightX));
    int minY = MIN(MIN(bottomLeftY, topLeftY), MIN(bottomRightY, topRightY));
    int maxY = MAX(MAX(bottomLeftY, topLeftY), MAX(bottomRightY, topRightY));

    if(minX <= 1)
    {
        return abs(minX) * abs(minX) + 1; // add 1 incase minX is 0
    }
    else if (minY <= 1)
    {
        return abs(minY) * abs(minY) + 1; // add 1 incase minX is 0
    }
    else if(maxX >= frame.size().width-2)
    {
        return (maxX - (frame.size().width-2)) * (maxX - (frame.size().width-2))+1;
    }
    else if(maxY >= frame.size().height-2)
    {
        return (maxY - (frame.size().height-2)) * (maxY - (frame.size().height-2))+1;
    }
    else if(width <= 0 )
    {
        return maxY * maxY + 1;
    }
    else if (height <= 0)
    {
        return maxX * maxX + 1;
    }
    return 0;
}

//--------------------------------------------------------------
/*
int SimplexObjectDetector::checkXorYPostionInRange(int position, int appearanceSize, int maxPosition, int minPosition)//int frameSize)
{
    if((position + appearanceSize + 2 > maxPosition))
    {
        position = maxPosition - appearanceSize - 2;
    }
    else if (position < minPosition)
    {
        position = minPosition;
    }
    return position;
}
*/

//---------------------------------------------------------------------
//---------------------------------------------------------------------
