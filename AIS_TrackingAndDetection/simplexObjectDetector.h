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

//#include "network.h"

#include "objectDetector.h"

/*!
 * \class SimplexObjectDetector
 * \brief Uses the Simplex functionality of GSL to locate the object being tracked.
 */
class SimplexObjectDetector : public ObjectDetector
{
public:
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
    Location findObjectAllTransformations(Location predictedLocation, Mat frame, vector<Mat> appearances, int *mostMatchedAppearanceIndex);

    /*!
     * \fn findObjectWithScale
     * \brief Finds the object using just the scale transformation
     * \param predictedLocation [in]
     * \param frame [in]
     * \param appearances [in]
     * \param mostMatchedAppearanceIndex [out]
     * \return The location of the object.
     */
    Location findObjectWithScale(Location predictedLocation, Mat frame, vector<Mat> appearances, int *mostMatchedAppearanceIndex);

    /*!
     * \fn findObjectWithRotation
     * \brief Finds the object using just the rotation transformation
     * \param predictedLocation [in]
     * \param frame [in]
     * \param appearances [in]
     * \param mostMatchedAppearanceIndex [out]
     * \return The location of the object.
     */
    Location findObjectWithRotation(Location predictedLocation, Mat frame, vector<Mat> appearances, int *mostMatchedAppearanceIndex);

    /*!
     * \fn findObjectNoTransformations
     * \brief Finds the object without the use of scale or rotation
     * \param predictedLocation [in]
     * \param frame [in]
     * \param appearances [in]
     * \param mostMatchedAppearanceIndex [out]
     * \return The location of the object.
     */
    Location findObjectNoTransformations(Location predictedLocation, Mat frame, vector<Mat> appearances, int *mostMatchedAppearanceIndex);

    //void setupStepSize(double X_POSITION_STEP_SIZE = 20, double Y_POSITION_STEP_SIZE = 20, double SCALE_X_STEP_SIZE = 0.01, double SCALE_Y_STEP_SIZE = 0.01, double ROTATION_STEP_SIZE = 1.0);

    /*!
     * \var X_POSITION_STEP_SIZE, Y_POSITION_STEP_SIZE, SCALE_X_STEP_SIZE, SCALE_Y_STEP_SIZE, ROTATION_STEP_SIZE
     */
    static double X_POSITION_STEP_SIZE; //= 20;//25;//6;//15.0;//10.0;
    static double Y_POSITION_STEP_SIZE;// = 20;//25;//6;//15.0;//10.0;
    static double SCALE_X_STEP_SIZE;// = 0.01;//0.01;//0.02//0.05;
    static double SCALE_Y_STEP_SIZE;// = 0.01;//0.01;//0.02//0.05;
    static double ROTATION_STEP_SIZE;// = 1.0;

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
    Location forEachAppearanceFindObject(vector<Mat> appearances, Mat frame, Location predictedLocation, size_t numberOfDimensions, int *mostMatchedAppearanceIndex);

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

    /*!
     * \fn checkPostionInRange
     * \brief Checks the x,y position is within the frame
     * \param positionX [in, out]
     * \param positionY [in, out]
     * \param appearanceWidth [in]
     * \param appearanceHeight [in]
     * \param rotation [in]
     * \param frame [in]
     * \return How far off the edge of the frame the position is, squared. Stops the distance being constant when the edge of the image is reached.
     */
   // int checkPostionInRange(int * positionX, int * positionY, int appearanceWidth, int appearanceHeight, int rotation, Mat frame);

    /*!
     * \fn checkXorYPostionInRange
     * \brief Used by checkPostionInRange()
     * \param position [in] The closest position within the frame.
     * \param appearanceSize [in]
     * \param maxPosition [in]
     * \param minPosition [in]
     * \return
     */
    //int checkXorYPostionInRange(int position, int appearanceSize, int maxPosition, int minPosition);

    /*!
     * \fn checkSizeInRange
     * \brief Checks the size is bigger than 1 and less than the size of the frame.
     * \param size [in]
     * \param frameSize [in]
     * \return
     */
    //int checkSizeInRange(int size, int frameSize);

    /*!
     * \fn checkLocationInRange
     * \brief Checks that the location of the object is within the frame.
     * \param location [in]
     * \param numberOfDimensions [in]
     * \param appearance [in]
     * \param frame [in]
     * \return
     */
    //Location checkLocationInRange(Location location, Mat appearance, Mat frame);

    int checkLocationWithinFrame(Location location, Mat frame);

};

#endif // SIMPLEXOBJECTDETECTOR_H
