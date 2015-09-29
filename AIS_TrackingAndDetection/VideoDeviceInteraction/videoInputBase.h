/*!
 * \file videoInputBase.cpp
 * \author Helen Harman (heh14@aber.ac.uk)
 * \date 06/03/2015
 * \version 1.0
 *
 * \brief Holds the VideoInputBase class
 */

#ifndef VIDEOINPUTBASE_H
#define VIDEOINPUTBASE_H

#include <iostream>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>


using namespace cv;
using namespace std;

/*!
 * \class VideoInputBase
 * \brief This acts as and interface and holds the implementation
 * common to VideoFileInput and WebcamInput
 */
class VideoInputBase
{
public:
    /*!
     * \var startCamera
     * \brief Opens the connection to the webcam
     * \param cameraId
     * \return true if the video input has been successfully opened
     */
    virtual bool startCamera() = 0;

    /*!
     * \fn getNextFrame
     * \brief Gets the video frame in RGB colour space
     * \return the video frame
     */
    virtual Mat getNextFrame() = 0;

    /*!
     * \fn close
     * \brief Closes the connection to the Webcam
     */
    void close();

    virtual ~VideoInputBase();
protected:
    /*!
     * \fn SCALE_FACTOR
     * \brief Video input is too high a resolution to work in real-time when using semi-exustive appearance matching
     */
    const double SCALE_FACTOR = 0.5;
    /*!
     * \fn capture
     * \brief The capture object the frame will be read from
     */
    VideoCapture capture;
};

#endif // VIDEOINPUTBASE_H
