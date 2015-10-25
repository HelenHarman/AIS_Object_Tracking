/*!
 * \file network.h
 * \author Helen Harman (heh14@aber.ac.uk)
 * \date 06/03/2015
 * \version 1.0
 *
 * \brief Holds the Network class
 */
#ifndef NETWORK_H
#define NETWORK_H
#include<iostream>

#include <vector>
#include <opencv2/core/core.hpp>

#include "arb.h"
#include "distanceBase.h"
#include "options.h"

using namespace cv;
using namespace AIS_Options;

/*!
 * \class Network
 * \brief Holds the network of ARBs. Handles the adding and removing of ARBs.
 */
class Network
{
public:
    /*!
     * \fn Network(Mat initialApperance, Location currentLocation, DistanceBase *distanceMeasure, double objectThreshold, double stimulationThreshold)
     * \brief Constructor for the Network.
     *
     * \param initialApperance [in] : The appearance that the user has selected.
     * \param currentLocation [in] : The initial location.
     */
    Network(Mat initialApperance, Location currentLocation, DistanceBase *distanceMeasure, double objectThreshold, double stimulationThreshold, bool usePredictedLocation, double linkingThreshold = 0);//TODO has through DistanceInterface distanceMeasure

    /*!
     * \fn addAppearance
     * \brief Finds the closest ARB and if the distance is below the
     * STIMULATION_THRESHOLD increases the resource of that ARB. If the distance is not
     * below the STIMULATION_THRESHOLD then creates a new ARB. The ARB is linked to the previous
     * known ARB.
     *
     * \param appearance [in] : The appearance the network is being exposed to
     * \param currentLocation [in] : The location the appearance is at
     */
    Location addAppearance(Mat appearance, Location currentLocation);


    void getHighestRLAndConnectedARBs(vector<ARB*>* mostLikely);
    void getNearestAndConnectedARBs(vector<ARB*>* mostLikely);

    /*!
     * \fn getPredictedLocation
     * \return The objects predicted location
     */
    Location getPredictedLocation();


    /*!
     * \fn getNumberOfARBs
     * \return The number of ARBs
     */
    int getNumberOfARBs();

    /*!
     * \fn getARBs
     * \return A list of all ARBs in the network
     */
    vector<ARB*> getARBs();

    /*!
     * \fn setUsePredictedLocation
     * \param usePredictedLocation [in]
     */
    void setUsePredictedLocation(bool usePredictedLocation);


    /*!
     * \fn setObejctThreshold
     * \param objectThreshold
     */
    void setObejctThreshold(double objectThreshold);

    /*!
     * \fn setStimulationThreshold
     * \param stimulationThreshold
     */
    void setStimulationThreshold(double stimulationThreshold);


    vector<Mat> getLastAndConnectedARBs();

    Location initialAppearanceAddition(Mat appearance, Location currentLocation);

    void resetLocation(Location location);
    ~Network();

private:
    /*!
     * \var objectThreshold
     * \brief If the distance between the new appearance
     * and the appearances already in the network is below this threshold
     * (and not below the STIMULATION_THRESHOLD), then a new ARB is created.
     */
    double objectThreshold;//OBJECT_THRESHOLD = 0.4;//0.027;//0.4;

    /*!
     * \var stimulationThreshold
     * \brief If the distance between the new
     * appearance and a appearace in the network is below this
     * threshold, then the resource level of the closest ARB is increased.
     */
    double stimulationThreshold;//STIMULATION_THRESHOLD = 0.2;//0.019;//0.2;


    double linkThreshold;

    /*!
     * \var REMOVE_THRESHOLD
     * \brief If a ARB's resource level falls below
     * this threshold, then the ARB will be deleted.
     */
    const double REMOVAL_THRESHOLD = 0.6;

    const double initialARBsResourceLevel = 15;

    /*!
     * \var averageResourceLevel
     * \brief The averageResourceLevel is set when
     * checking if any ARBs should be removed from the network. It is used
     * by getARBsWithAboveAverageRL(). We is set in the removeARBs() function
     * so that the number of times looping through all the ARBs is reduced.
     */
    double averageResourceLevel;

    /*!
     * \var aRBs
     * \brief A list of all the ARBs that are within the network
     */
    vector<ARB *> aRBs;

    /*!
     * \var numARBs
     */
    int numARBs;

    /*!
     * \var distanceMeasure
     * \brief Used to calculate the distance between a new appearance and the appearances already in the network.
     */
    DistanceBase *distanceMeasure;

    /*!
     * \var usePredictedLocation
     */
    bool usePredictedLocation;

    /*!
     * \var previousLocation
     */
    Location previousLocation;

    /*!
     * \var predictedLocation
     */
    Location predictedLocation;

    /*!
     * \var previousARB
     * \brief The last ARB to be added or to have their stimulation level increased
     */
    ARB * previousARB;

    /*!
     * \fn removeARBs
     * \brief Removes the ARBs which fall below the REMOVAL_THRESHOLD.
     */
    void removeARBs();


    /*!
     * \fn setPredictedLocation
     * \param currentLocation [in] : The current known location of the object.
     */
    void setPredictedLocation(Location currentLocation);

    /*!
     * \fn calculatePredictedLocation
     * \brief Sets the predicted location based on the difference between previousLocation and the current location
     * \param currentLocation [in]
     */
    void calculatePredictedLocation(Location currentLocation);


    void checkAllARBs(Mat appearance, std::map<ARB *, double> *arbsBelowLinkThreshold, ARB ** closestArb, double *smallestDistance);
};

#endif // NETWORK_H


/*!
 * \fn getARBsWithAboveAverageRL
 * \brief Gets the nodes that performs the inital search for the
 * object within a video frame.
 * \return The previous appearance and the most stimulated appearance
 */
//vector<Mat> getARBsWithAboveAverageRL();

/*!
 * \fn getAllAppearances
 * \return A list of all appearances in the network
 */
//vector<Mat> getAllAppearances();

/*!
 * \fn getLastAndHighestARBs
 * \return The last ARB to be used and the ARB which has the highest resource level
 */
//vector<Mat> getLastAndHighestARBs();
