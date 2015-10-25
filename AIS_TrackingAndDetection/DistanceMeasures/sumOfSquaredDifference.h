/*!
 * \file sumOfSquaredDifference.h
 * \author Helen Harman (heh14@aber.ac.uk)
 * \date 24/03/2015
 * \version 1.0
 *
 * \brief Holds the SumOfSquaredDifference class
 */
#ifndef SUMOFSQUAREDDIFFERENCE_H
#define SUMOFSQUAREDDIFFERENCE_H

#include "distanceBase.h"

/*!
 * \class SumOfSquaredDifference
 * \brief Used to calculate the Sum Of Squared Difference between two appearances.
 */
class SumOfSquaredDifference : public DistanceBase
{
public:
    /*!
     * \fn SumOfSquaredDifference(Mat frame, Mat appearance)
     * \brief Will set the maxDistance the unnormalised SSD should return.
     *
     * \param frame [in]: The frame whch the appearance has been selected from
     * \param appearance [in]: The appearance the user has selected
     */
    SumOfSquaredDifference(Mat frame, Mat appearance);

    /*!
     * \fn SumOfSquaredDifference()
     * \brief Used by the unit tests.
     */
    SumOfSquaredDifference(){}

    /*!
     * \fn getDistance
     * \brief Calculates the distance between the image and the appearance
     * \param image [in]
     * \param appearance [in]
     * \return The normalised Euclidean distance (value between 0 and 1).
     */
    double getDistance(Mat image, Mat appearance, Location location);

    double getDistanceBetweenAppearances(Mat image, Mat appearance);


    ~SumOfSquaredDifference();

private:

    /*!
     * \brief getUnnormalisedDistance
     * \param image [in]
     * \param appearance [in]
     * \return
     */
    double getUnnormalisedDistance(Mat image, Mat appearance, Location location);
};

#endif // SUMOFSQUAREDDIFFERENCE_H
