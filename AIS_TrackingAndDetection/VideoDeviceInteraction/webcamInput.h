/*!
 * \file webcamInput.h
 * \author Helen Harman (heh14@aber.ac.uk)
 * \date 06/03/2015
 * \version 1.0
 *
 * \brief Holds the WebcamInput class
 */

#ifndef WEBCAMINPUT_H
#define WEBCAMINPUT_H

#include <iostream>

#include "videoInputBase.h"

using namespace cv;
using namespace std;


/*!
 * \fn WebcamInput
 * \brief Allows the video feed to be read from a webcam
 */
class WebcamInput: public VideoInputBase
{
public:
    WebcamInput();

    /*!
     * \fn startCamera
     * \brief Opens the video capture device
     * \return true if the video input has been successfully opened
     */
    bool startCamera();

    /*!
     * \fn getNextFrame
     * \brief Gets the frame in RGB colour space
     * \return The camera frame
     */
    Mat getNextFrame();

    ~WebcamInput();

};

#endif // WEBCAMINPUT_H
