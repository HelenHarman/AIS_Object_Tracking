/*!
 * \file euclideanDistance.h
 * \author Helen Harman (heh14@aber.ac.uk) Aberystwyth University
 * \date 07/03/2015
 * \version 1.0
 *
 * \brief Holds the EuclideanDistance class
 */
#ifndef EUCLIDEANDISTANCE_H
#define EUCLIDEANDISTANCE_H

#include "distanceBase.h"
#include "options.h"

using namespace std;

/*!
 * \class EuclideanDistance
 * \brief Used to calculate the Euclidean distance between two appearances.
 */
class EuclideanDistance : public DistanceBase
{
public:
    /*!
     * \fn EuclideanDistance(Mat frame, Mat appearance)
     * \brief Will set the maxDistance the unnormalised euclidean distance should return.
     *
     * \param frame [in] : The frame whch the appearance has been selected from
     * \param appearance [in] : The appearance the user has selected
     */
    EuclideanDistance(Mat frame, Mat appearance);

    /*!
     * \fn EuclideanDistance()
     * \brief Used by the unit tests
     */
    EuclideanDistance(){}

    /*!
     * \fn getEuclideanDistance
     * \brief Calculates the euclidean distance between the image and the appearance
     * \param image [in]
     * \param appearance [in]
     * \return The normalised Euclidean distance (value between 0 and 1).
     */
    double getDistance(Mat image, Mat appearance, Location location);

    double getDistanceTransformation(Mat frame, Mat apperance, Location location);
    void rotatePosition(int degrees, int *x, int *y, int rotationCenterX, int rotationCenterY);

    double getDistanceBetweenAppearances(Mat image, Mat appearance);

    ~EuclideanDistance();

private:
    /*!
     * \fn getUnNormEuclideanDistance
     * \brief Calculates the euclidan distance between the image and the appearance
     *
     * \param image [in]
     * \param appearance [in]
     * \return the euclidean distance
     */
    double getUnnormalisedDistance(Mat image, Mat appearance, Location location);

};

#endif // EUCLIDEANDISTANCE_H
