#ifndef GLOBALOBJECTDETECTOR_H
#define GLOBALOBJECTDETECTOR_H

#include "objectDetector.h"
#include "arb.h"

class GlobalObjectDetector : public ObjectDetector
{
public:
    GlobalObjectDetector(DistanceBase *distanceMeasure);

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


    ~GlobalObjectDetector(){}
private:
    DistanceBase *distanceMeasure;

    double smallestDistance;
    double currentDistance;

    Location forEachAppearanceFindObject(vector<ARB*> appearances, Mat frame, Location predictedLocation);//, int *mostMatchedAppearanceIndex);
    Location findObject(Mat frame, Mat appearance, Location location);

};

#endif // GLOBALOBJECTDETECTOR_H
