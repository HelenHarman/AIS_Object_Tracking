/*! \file simplexObjectDetection.cpp
 *  \author Helen Harman (heh14@aber.ac.uk)
 *  \date 29/03/2015
 *  \version 1.0
 *
 * \brief The source code for the SimplexObjectDetector class.
 * This code has been created using : https://www.gnu.org/software/gsl/manual/html_node/Multimin-Examples.html
 */

#include "simplexObjectDetector.h"

double SimplexObjectDetector::X_POSITION_STEP_SIZE = 20;
double SimplexObjectDetector::Y_POSITION_STEP_SIZE = 20;
double SimplexObjectDetector::SCALE_X_STEP_SIZE = 0.3;
double SimplexObjectDetector::SCALE_Y_STEP_SIZE = 0.3;
double SimplexObjectDetector::ROTATION_STEP_SIZE = 1.0;

//---------------------------------------------------------------------

SimplexObjectDetector::SimplexObjectDetector(DistanceBase *distanceMeasure)
{
    this->distanceMeasure = distanceMeasure;
}

//---------------------------------------------------------------------

Location SimplexObjectDetector::findObjectNoTransformations(Location predictedLocation, Mat frame, vector<ARB*> appearances)//, int *mostMatchedAppearanceIndex)
{
    size_t numberOfDimensions = 2;
    return forEachAppearanceFindObject(appearances, frame, predictedLocation, numberOfDimensions);//, mostMatchedAppearanceIndex);
}

//---------------------------------------------------------------------

Location SimplexObjectDetector::findObjectWithRotation(Location predictedLocation, Mat frame, vector<ARB*> appearances)//, int *mostMatchedAppearanceIndex)
{
    size_t numberOfDimensions = 3;
    return forEachAppearanceFindObject(appearances, frame, predictedLocation, numberOfDimensions);//, mostMatchedAppearanceIndex);
}

//---------------------------------------------------------------------

Location SimplexObjectDetector::findObjectWithScale(Location predictedLocation, Mat frame, vector<ARB*> appearances)//, int *mostMatchedAppearanceIndex)
{
    size_t numberOfDimensions = 4;
    return forEachAppearanceFindObject(appearances, frame, predictedLocation, numberOfDimensions);//, mostMatchedAppearanceIndex);
}

//---------------------------------------------------------------------

Location SimplexObjectDetector::findObjectAllTransformations(Location predictedLocation, Mat frame, vector<ARB*> appearances)//, int *mostMatchedAppearanceIndex)
{
    size_t numberOfDimensions = 5;
    return forEachAppearanceFindObject(appearances, frame, predictedLocation, numberOfDimensions);//, mostMatchedAppearanceIndex);
}

//---------------------------------------------------------------------

Location SimplexObjectDetector::forEachAppearanceFindObject(vector<ARB*> appearances, Mat frame, Location predictedLocation, size_t numberOfDimensions)//, int *mostMatchedAppearanceIndex)
{
    Location foundLocation = predictedLocation;
    this->smallestDistance = 1;
    //int mostMatchedAppearanceIndex = 0;
    gsl_vector *stepSize, *startingLocations;
    stepSize = gsl_vector_alloc (numberOfDimensions);
    startingLocations = gsl_vector_alloc (numberOfDimensions);
    for (int i = 0; i < (int)appearances.size(); i++)
    {
        this->currentDistance = 1;
        this->setupInitialVectors(stepSize, startingLocations, predictedLocation, numberOfDimensions);
        gsl_multimin_fminimizer *minimizer = findObject(frame, appearances[i]->getAppearance(), stepSize, startingLocations, numberOfDimensions);

        if(this->currentDistance <= this->smallestDistance)
        {
            foundLocation = getLocationFromVector(minimizer->x, numberOfDimensions, predictedLocation);

            this->smallestDistance = this->currentDistance;
            //mostMatchedAppearanceIndex = i;
        }
        gsl_multimin_fminimizer_free (minimizer);
    }

    // clean-up
    gsl_vector_free(startingLocations);
    gsl_vector_free(stepSize);

    if (checkLocationWithinFrame(foundLocation, frame) != 0)
    {
        std::cout << "Objects location not found" << std::endl;
        foundLocation = Location(-1,-1,-1,-1,-1);
    }

    return foundLocation;
}

//---------------------------------------------------------------------

void SimplexObjectDetector::setupInitialVectors(gsl_vector *stepSize, gsl_vector *startingLocations, Location predictedLocation, size_t numberOfDimensions)
{
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
    // x and y
    location.setX(gsl_vector_get(locationVector, 0));
    location.setY(gsl_vector_get (locationVector, 1));

    // rotation
    if(numberOfDimensions == 3 || numberOfDimensions == 5)
    {
        location.setRotation(gsl_vector_get(locationVector, numberOfDimensions-1));
    }

    // scale
    if(numberOfDimensions == 4 || numberOfDimensions == 5)
    {
        location.setScaleX(fabs(gsl_vector_get (locationVector, 2)));
        location.setScaleY(fabs(gsl_vector_get (locationVector, 3)));
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

//---------------------------------------------------------------------
//---------------------------------------------------------------------
