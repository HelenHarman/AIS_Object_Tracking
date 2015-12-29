/*! \file simplexObjectDetection.h
 *  \author Helen Harman (heh14@aber.ac.uk)
 *  \date 29/03/2015
 *  \version 1.0
 *
 * \brief Holds the SimplexObjectDetector class
 */
#ifndef SIMPLEXOBJECTDETECTOR_H
#define SIMPLEXOBJECTDETECTOR_H

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <gsl/gsl_multimin.h>
#include <gsl/gsl_vector.h>

#include "objectDetector.h"
#include "arb.h"

/*!
 * \class SimplexObjectDetector
 * \brief Uses the Simplex functionality of GSL to locate the object being tracked.
 */
class SimplexObjectDetector : public ObjectDetector
{
public:
    /*!
     * \var X_POSITION_STEP_SIZE, Y_POSITION_STEP_SIZE, SCALE_X_STEP_SIZE, SCALE_Y_STEP_SIZE, ROTATION_STEP_SIZE
     */
    static double X_POSITION_STEP_SIZE;
    static double Y_POSITION_STEP_SIZE;
    static double SCALE_X_STEP_SIZE;
    static double SCALE_Y_STEP_SIZE;
    static double ROTATION_STEP_SIZE;

    /*!
     * \fn SimplexObjectDetector(DistanceBase *distanceMeasure)
     * \brief Constructor
     * \param distanceMeasure [in]
     */
    SimplexObjectDetector(DistanceBase *distanceMeasure);

    /*!
     * \fn findObjectAllTransformations
     * \brief Find the object using rotation and scale.
     * \param predictedLocation [in] : The location to start looking for the object
     * \param frame [in] : The image the search is being performed on
     * \param appearances [in] : The apperances used to find the object in the frame
     * \param mostMatchedAppearanceIndex [out]
     * \return The location of the object.
     */
    Location findObjectAllTransformations(Location predictedLocation, Mat frame, vector<ARB*> appearances);//, int *mostMatchedAppearanceIndex);

    /*!
     * \fn findObjectWithScale
     * \brief Finds the object using just the scale transformation
     * \param predictedLocation [in]
     * \param frame [in]
     * \param appearances [in]
     * \param mostMatchedAppearanceIndex [out]
     * \return The location of the object.
     */
    Location findObjectWithScale(Location predictedLocation, Mat frame, vector<ARB*> appearances);//, int *mostMatchedAppearanceIndex);

    /*!
     * \fn findObjectWithRotation
     * \brief Finds the object using just the rotation transformation
     * \param predictedLocation [in]
     * \param frame [in]
     * \param appearances [in]
     * \param mostMatchedAppearanceIndex [out]
     * \return The location of the object.
     */
    Location findObjectWithRotation(Location predictedLocation, Mat frame, vector<ARB*> appearances);//, int *mostMatchedAppearanceIndex);

    /*!
     * \fn findObjectNoTransformations
     * \brief Finds the object without the use of scale or rotation
     * \param predictedLocation [in]
     * \param frame [in]
     * \param appearances [in]
     * \param mostMatchedAppearanceIndex [out]
     * \return The location of the object.
     */
    Location findObjectNoTransformations(Location predictedLocation, Mat frame, vector<ARB*> appearances);//, int *mostMatchedAppearanceIndex);


    Location forEachAppearanceFindObject(vector<ARB*> appearances, Mat frame, Location predictedLocation);//, int *mostMatchedAppearanceIndex);


    ~SimplexObjectDetector(){}
private:
    /*!
     * \var distanceMeasure
     */
    DistanceBase *distanceMeasure;

    /*!
     * \var smallestDistance
     * \brief The smallest distance achieved when searching for the object
     */
    double smallestDistance;

    /*!
     * \var currentDistance
     * \brief The last distance to be calculated
     */
    double currentDistance;

    /*!
     * \fn forEachAppearanceFindObject
     * \brief Loops through each of the appearances to find the object.
     * \param appearances [in]
     * \param frame [in]
     * \param predictedLocation [in]
     * \param numberOfDimensions [in]
     * \param mostMatchedAppearanceIndex [out]
     * \return
     */
    Location forEachAppearanceFindObject(vector<ARB*> appearances, Mat frame, Location predictedLocation, size_t numberOfDimensions);// int *mostMatchedAppearanceIndex);

    /*!
     * \fn findObject
     * \brief Runs GSL's simplex to find the location of the object
     * \param frame [in]
     * \param appearance [in]
     * \param stepSize [in] gsl_vector containing the step size for each of the dimensions of the location
     * \param startingLocations [in]
     * \param numberOfDimensions [in]
     * \return the minimizer containing the location of the object
     */
    gsl_multimin_fminimizer* findObject(Mat frame, Mat appearance, gsl_vector * stepSize, gsl_vector * startingLocations, size_t numberOfDimensions);

    /*!
     * \fn setupInitialVectors
     * \brief Sets up the vectors that the simplex function makes use of.
     * \param stepSize [in]
     * \param startingLocations [in]
     * \param predictedLocation [in]
     * \param numberOfDimensions [in]
     */
    void setupInitialVectors(gsl_vector *stepSize, gsl_vector *startingLocations, Location predictedLocation, size_t numberOfDimensions);

    /*!
     * \fn getLocationFromVector
     * \brief Extracts a Location from the gsl_vector
     * \param locationVector [in]
     * \param numberOfDimensions [in]
     * \return
     */
    Location getLocationFromVector(const gsl_vector * locationVector, const size_t numberOfDimensions, Location location);

    /*!
     * \fn getDistance
     * \brief The function passed to the minimizer.
     * \param v [in] : Contains the location on the frame to look for the object
     * \param params [in] : Contains : [0]insitance of SimplexObjectDetector, [1] the appearance, [2] the frame
     * \return The distance between the appearance and the frame at the given location
     */
    double getDistance(const gsl_vector*v, void* params);

    int checkLocationWithinFrame(Location location, Mat frame);
};

#endif // SIMPLEXOBJECTDETECTOR_H
