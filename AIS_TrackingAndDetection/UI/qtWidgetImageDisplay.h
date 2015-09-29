/*!
 * \file qtWidgetImageDisplay.h
 * \author Helen Harman (heh14@aber.ac.uk)
 * \date 12/03/2015
 * \version 1.0
 *
 * \brief Holds the QtWidgetImageDisplay class
 * Made use of http://develnoter.blogspot.co.uk/2012/05/integrating-opencv-in-qt-gui.html (Marcelo Mottalli, 2012 [Accessed : April 2015]) to learn how to show a OpenCV Mat image in a Qt window.
 */
#ifndef QTWIDGETIMAGEDISPLAY_H
#define QTWIDGETIMAGEDISPLAY_H

#include <iostream>
#include <array>

#include <QFileDialog>
#include <QWidget>
#include <QImage>
#include <QPainter>
#include <QMouseEvent>
#include <opencv2/core/core.hpp>

#include "options.h"
#include "transformations.h"
#include "outputData.h"


using namespace AIS_Options;
using namespace cv;

/*!
 * \class QtWidgetImageDisplay
 * \brief Allows the video to be displayed and shows the position of the object being tracked.
 */
class QtWidgetImageDisplay : public QWidget, public Transformations
{
    Q_OBJECT
public:
    /*!
     * \fn QtWidgetImageDisplay(QWidget *parent = 0)
     * \brief Calls parent constuctor and sets default variables
     * \param parent
     */
    explicit QtWidgetImageDisplay(QWidget *parent = 0) : QWidget(parent), Transformations() {state = UNINITIALISED;
                                                                          this->numARBs = 0;
                                                                          this->numberOfFrames = 0;
                                                                          time(&this->startedTime);
                                                                          this->trackingRotation=0;}
    /*!
     * \fn whichARBsToSearchWithChanged
     * \see mainwindow.h
     * \param whichARBsToSearchWith [in]
     */
    void whichARBsToSearchWithChanged(ARBsToSearchWith whichARBsToSearchWith);

    /*!
     * \fn usePredictedLocationChanged
     * \see mainwindow.h
     * \param usePredictedLocation [in]
     */
    void usePredictedLocationChanged(bool usePredictedLocation);

    /*!
     * \fn distanceMeasureChanged
     * \see mainwindow.h
     * \param distanceMeasureType [in]
     */
    void distanceMeasureChanged(DistanceMeasureType distanceMeasureType);

    /*!
     * \fn useRotationChanged
     * \see mainwindow.h
     * \param useRotation [in]
     */
    void useRotationChanged(bool useRotation);

    /*!
     * \fn useScaleChanged
     * \see mainwindow.h
     * \param useScale [in]
     */
    void useScaleChanged(bool useScale);

    /*!
     * \fn videoInputChanged
     * \see mainwindow.h
     * \param videoInputType [in]
     */
    void videoInputChanged(VideoInputType videoInputType);

    /*!
     * \fn stimulationThresholdChanged
     * \see mainwindow.h
     * \param stimulationThreshold [in]
     */
    void stimulationThresholdChanged(double stimulationThreshold);

    /*!
     * \fn objectThresholdChanged
     * \see mainwindow.h
     * \param objectThreshold [in]
     */
    void objectThresholdChanged(double objectThreshold);
signals:
    /*!
     * \fn setStimulationThreshold
     * \param stimulationThreshold [in]
     */
    void setStimulationThreshold(double stimulationThreshold);

    /*!
     * \fn setObjectThreshold
     * \param objectThreshold [in]
     */
    void setObjectThreshold(double objectThreshold);

    /*!
     * \fn setInitialTrackingPostion
     * \brief Sets the initial position of the object
     * \param x [in]
     * \param y [in]
     * \param width [in]
     * \param height [in]
     */
    void setInitialTrackingPostion(int x, int y, int width, int height);

    /*!
     * \fn setState
     * \brief Sets if an obejct is being tracked or selected
     * \param state [in]
     */
    void setState(ProgramState state);

    /*!
     * \fn setVideoType
     * \param inputType [in]
     */
    void setVideoType(VideoInputType inputType);

    /*!
     * \fn setVideoFileConfigFilePath
     * \param filePathName [in]
     */
    void setVideoFileConfigFilePath(string filePathName);

    /*!
     * \fn setUseRotation
     * \param useRotation [in]
     */
    void setUseRotation(bool useRotation);

    /*!
     * \fn setUseScale
     * \param useScale [in]
     */
    void setUseScale(bool useScale);

    /*!
     * \fn setUsePredictedLocation
     * \param usePredictedLocation [in]
     */
    void setUsePredictedLocation(bool usePredictedLocation);

    /*!
     * \fn setDistanceMeasure
     * \param distanceMeasureType [in]
     */
    void setDistanceMeasure(DistanceMeasureType distanceMeasureType);

    /*!
     * \fn setUseMostLikelyAppearances
     * \param whichARBsToSearchWith [in]
     */
    void setWhichARBsToSearchWith(ARBsToSearchWith whichARBsToSearchWith);

    /*!
     * \fn getNetwork
     * \brief A request for a copy of the network to be emited to this class
     */
    void getNetwork();

public slots:

    /*!
     * \fn printNumberArbsInNetwork
     * \brief Asks the user for the file that the list of the
     * number of ARBs should be written to.
     */
    void printNumberArbsInNetwork();

    /*!
     * \fn saveNetwork
     * \brief Asks the user for a directory to save the appearances in the network to.
     */
    void saveNetwork();

    /*!
     * \fn setNetworkToSaveNetwork
     * \brief The request for a copy of the Network gets passed to here.
     * \see getNetwork()
     * \param network [in]
     */
    void setNetworkToSaveNetwork(Network*);

    /*!
     * \fn getVideoFileConfig
     * \brief Allows the user to select the video configuration file that should be used.
     */
    void getVideoFileConfig();

    /*!
     * \fn displayMat
     * \brief Shows the current video frame
     * \param data [in] : the image data
     * \param cols [in] : number of columns the image has
     * \param rows [in] : number of rows the image has
     */
    void displayMat(uchar* data, int cols, int rows);

    /*!
     * \fn setTrackingPosition
     * \brief Sets the current position of the object being track, so that the box can be drawn.
     *
     * \param x [in]
     * \param y [in]
     * \param rotation [in]
     * \param width [in]
     * \param height [in]
     */
    void setTrackingPosition(int x, int y, int rotation, int width, int height);

    /*!
     * \fn setNumARBs
     * \brief Sets the number of ARBs so that it can be displayed to the user.
     * \param numARBs [in]
     */
    void setNumARBs(int numARBs);

    void saveNetworkToPath(Network *network, string path);
protected:
    void paintEvent(QPaintEvent*);
    QImage _qimage;

    /*!
     * \fn mousePressEvent
     * \brief Allows the user to select the object they wish to track
     * \param event
     */
    void mousePressEvent(QMouseEvent *event);

    /*!
     * \fn mouseMoveEvent
     * \brief Allows the user to select the object they wish to track
     * \param event
     */
    void mouseMoveEvent(QMouseEvent *event);

    /*!
     * \fn mouseReleaseEvent
     * \brief Allows the user to select the object they wish to track
     * \param event
     */
    void mouseReleaseEvent(QMouseEvent *event);

private:
    /*!
     * \var state
     */
    ProgramState state;

    /*!
     * \var inputType
     */
    VideoInputType inputType;

    /*!
     * \var outputData
     */
    OutputData outputData;

    /*!
     * \var mousePressedPosition
     * \brief Used to allow the user to select an obejct to follow
     */
    int mousePressedPosition[2];
    /*!
     * \var mouseCurrentPosition
     * \brief Used to allow the user to select an obejct to follow
     */
    int mouseCurrentPosition[2];

    /*!
     * \var trackingX, trackingY, trackingWidth, trackingHeight, trackingRotation
     * \brief The current location of the object that is being tracked
     */
    int trackingX;
    int trackingY;
    int trackingWidth;
    int trackingHeight;
    int trackingRotation;

    /*!
     * \var numARBsList
     * \brief Allows the list of the number of ARBs to be saved to file
     */
    vector<int> numARBsList;
    int numARBs;


    /*!
     * \var numberOfFrames
     * \brief for calculating the frame rate
     */
    int numberOfFrames;
    /*!
     * \var startedTime
     * \brief for calculating the frame rate
     */
    time_t startedTime;
    /*!
     * \var frameRates
     * \brief Allows the list of the frame rates to be saved to file
     */
    vector<double> frameRates;

    vector< std::array<int, 5> > locations;

//int test=0;
};

#endif // QTWIDGETIMAGEDISPLAY_H
