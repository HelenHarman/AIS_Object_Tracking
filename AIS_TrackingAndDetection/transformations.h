/*! \file transformations.h
 *  \author Helen Harman (heh14@aber.ac.uk) Aberystwyth University
 *  \date 30/03/2015
 *  \version 1.0
 *
 * \brief Holds the Transformations class
 */
#ifndef TRANSFORMATIONS_H
#define TRANSFORMATIONS_H

#include <math.h>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;

/*!
 * \class Transformations
 * \brief Performs the rotation of a position and an image.
 * Stopped code being repeated in several places.
 */
class Transformations
{
protected:
    /*!
     * \fn rotatePosition
     * \param degrees [in]
     * \param x [in, out]
     * \param y [in, out]
     * \param rotationCenterX [in]
     * \param rotationCenterY [in]
     */
    void rotatePosition(int degrees, int *x, int *y, int rotationCenterX, int rotationCenterY);
};

#endif // TRANSFORMATIONS_H
