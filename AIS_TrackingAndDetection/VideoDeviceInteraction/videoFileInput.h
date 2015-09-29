/*! \file videoFileInput.h
 *  \author Helen Harman (heh14@aber.ac.uk)
 *  \date 13/03/2015
 *  \version 1.0
 *
 * \brief Holds the VideoFileInput class
 */

#ifndef VIDEOFILEINPUT_H
#define VIDEOFILEINPUT_H

#include <fstream>

#include "videoInputBase.h"

using namespace cv;

/*!
 * \class VideoFileInput
 * \brief Allows the video feed to come from a video file.
 */
class VideoFileInput : public VideoInputBase
{
public:
    /*!
     * \fn VideoFileInput(string videoConfigFilePathName)
     * \brief Reads in the videoConfigFilePathName to get the location of the video
     *              and the inital position and size of the object that we want to track.
     * \param videoConfigFilePathName [in]
     */
    VideoFileInput(string videoConfigFilePathName);

    /*!
     * \fn getInitialPosition
     * \brief Gets the initial location of the object that will be tracked
     * \param x [out]
     * \param y [out]
     * \param width [out]
     * \param height [out]
     */
    void getInitialPosition(int *x, int *y, int *width, int *height);

    /*!
     * \fn startCamera
     * \return true if camera has successfully been started
     */
    bool startCamera();

    /*!
     * \fn getNextFrame
     * \brief Gets the frame in RGB colour space.
     * \return The frame
     */
    Mat getNextFrame();

private:
    /*!
     * \var x, y, width, height
     * \brief The initial location of the object
     */
    int x, y, width, height;

    /*!
     * \var videoFilePathName
     */
    string videoFilePathName;
};

#endif // VIDEOFILEINPUT_H
