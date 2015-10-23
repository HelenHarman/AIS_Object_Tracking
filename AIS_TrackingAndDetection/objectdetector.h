#ifndef OBJECTDETECTOR_H
#define OBJECTDETECTOR_H

#include <iostream>

#include "distanceBase.h"
#include "options.h"
#include "transformations.h"

using namespace AIS_Options;

class ObjectDetector : public Transformations
{
public:
    ObjectDetector(){}

    /*!
     * \fn findObjectAllTransformations
     * \brief Find the object using rotation and scale.
     * \param predictedLocation [in] : The location to start looking for the object
     * \param frame [in] : The image the search is being performed on
     * \param appearances [in] : The apperances used to find the object in the frame
     * \param mostMatchedAppearanceIndex [out]
     * \return The location of the object.
     */
    virtual Location findObjectAllTransformations(Location predictedLocation, Mat frame, vector<Mat> appearances, int *mostMatchedAppearanceIndex) = 0;

    /*!
     * \fn findObjectWithScale
     * \brief Finds the object using just the scale transformation
     * \param predictedLocation [in]
     * \param frame [in]
     * \param appearances [in]
     * \param mostMatchedAppearanceIndex [out]
     * \return The location of the object.
     */
    virtual Location findObjectWithScale(Location predictedLocation, Mat frame, vector<Mat> appearances, int *mostMatchedAppearanceIndex) = 0;

    /*!
     * \fn findObjectWithRotation
     * \brief Finds the object using just the rotation transformation
     * \param predictedLocation [in]
     * \param frame [in]
     * \param appearances [in]
     * \param mostMatchedAppearanceIndex [out]
     * \return The location of the object.
     */
    virtual Location findObjectWithRotation(Location predictedLocation, Mat frame, vector<Mat> appearances, int *mostMatchedAppearanceIndex) = 0;

    /*!
     * \fn findObjectNoTransformations
     * \brief Finds the object without the use of scale or rotation
     * \param predictedLocation [in]
     * \param frame [in]
     * \param appearances [in]
     * \param mostMatchedAppearanceIndex [out]
     * \return The location of the object.
     */
    virtual Location findObjectNoTransformations(Location predictedLocation, Mat frame, vector<Mat> appearances, int *mostMatchedAppearanceIndex) = 0;

    virtual ~ObjectDetector(){}
};

#endif // OBJECTDETECTOR_H
