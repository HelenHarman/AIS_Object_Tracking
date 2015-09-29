/*!
 * \file distanceInterface.h
 * \author Helen Harman (heh14@aber.ac.uk)
 * \date 06/03/2015
 * \version 1.0
 *
 * \brief Holds the DistanceBase class
 */
#ifndef DISTANCEBASE_H
#define DISTANCEBASE_H

#include <iostream>
#include <cmath>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/nonfree/features2d.hpp>

#include "execinfo.h"

#include "options.h"
#include "transformations.h"

using namespace cv;

/*!
 * \class DistanceBase
 * \brief This acts as and interface and holds the implementation
 * common to EuclideanDistanace and SumOfSquaredDifference
 */
class DistanceBase : public Transformations
{
public:
    /*!
     * \fn getDistance
     * \brief Gets the distance normalised between 0 and 1.
     * \param image [in]
     * \param appearance [in]
     * \return the distance
     */
    virtual double getDistance(Mat frame, Mat appearance, AIS_Options::Location location) = 0;

    virtual double getDistanceBetweenAppearances(Mat image, Mat appearance) = 0;


    /*!
     * \fn getMaxDistance
     * \brief Gets the highest distance value between the initial appearance and the intial frame
     * \return the maximum distance
     */
    double getMaxDistance();

    virtual ~DistanceBase() {}

    double sigmoid(double x);
protected:
    /*!
     * \var maxDistance
     */
    double maxDistance;

    /*!
     * \fn calculateSSD
     * \brief Both euclideanDistance and sumOfSquaredDifference
     * use a similar method to calculate the distance, so this is used to
     * prevent repeared code.
     *
     * \param image [in]
     * \param appearance [in]
     * \return the distance between the image and the appearance
     */
    double calculateSSD(Mat image, Mat appearance, AIS_Options::Location location);

    double distanceBetweenAppearancesSSD(Mat image, Mat appearance);
};

#endif // DISTANCEBASE_H
