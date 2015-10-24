/*! \file options.h
 *  \author Helen Harman (heh14@aber.ac.uk)
 *  \date 10/03/2015
 *  \version 1.0
 *
 * \brief Holds the enums and structs
 */

#ifndef PROGRAMSTATE
#define PROGRAMSTATE

namespace AIS_Options{

    /*!
     * \enum ProgramState
     * \brief Allows the TrackingAndDetection class and the UI to know the state of the system
     */
    enum ProgramState
    {
        UNINITIALISED,
        SELECTING,
        TRACKING
    } ;


    /*!
     * \enum VideoInputType
     */
    enum VideoInputType
    {
        WEBCAM,
        FILE_INPUT
    };

    /*!
     * \enum DistanceMeasureType
     */
    enum DistanceMeasureType
    {
        EUCLIDEAN_DISTANCE,
        SUM_OF_SQUARED_DIFFERENCE
    };

    /*!
     * \enum ARBsToSearchWith
     */
    enum ARBsToSearchWith
    {
        ALL,
        ABOVE_AVERAGE,
        LAST_AND_HIGHEST,
        LAST_AND_CONNECTED,
        HIGHEST_AND_CONNECTED
    };

    /*!
     * \struct Location
     */
    /*struct Location
    {
        int x;
        int y;
        double scaleX;
        double scaleY;
        int rotation;
    };*/

}
#endif // PROGRAMSTATE

