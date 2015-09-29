/*!
 * \file linkTrackingAndUi.h
 * \author Helen Harman (heh14@aber.ac.uk)
 * \date 12/03/2015
 * \version 1.0
 *
 * \brief Holds the LinkTrackingAndUi class
 */
#ifndef LINKTRACKINGANDUI_H
#define LINKTRACKINGANDUI_H

#include "qtWidgetImageDisplay.h"
#include "trackingAndDetection.h"

/*!
 * \class LinkTrackingAndUi
 * \brief Links the backend tracking code to the front end (UI) code
 */
class LinkTrackingAndUi : public QObject
{
    Q_OBJECT
public:
    /*!
     * \fn LinkTrackingAndUi(QtWidgetImageDisplay * imageWidget, TrackingAndDetection *trackingAndDetection)
     * \brief The tracking and detection is run in a different thread to the UI
     * so this is used to allow data to be passed between the trackingAndDetection object and the imageWidget object.
     * \param imageWidget [in]
     * \param trackingAndDetection [in]
     */
    LinkTrackingAndUi(QtWidgetImageDisplay * imageWidget, TrackingAndDetection *trackingAndDetection);
};

#endif // LINKTRACKINGANDUI_H
