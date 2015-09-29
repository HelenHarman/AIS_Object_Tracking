/*! \file transformations.h
 *  \author Helen Harman (heh14@aber.ac.uk) Aberystwyth University
 *  \date 30/03/2015
 *  \version 1.0
 *
 * \brief The source code for the Transformations class.
 */
#include "transformations.h"
/*
void Transformations::rotateFrameAndPosition(int rotation, Mat *frame, int *x, int *y)
{
    rotateFrame(rotation, frame);
    rotatePosition(rotation, x, y, frame->size().width/2, frame->size().height/2);
}

//---------------------------------------------------------------------

void Transformations::rotateFrame(int rotation, Mat *frame)
{
    Point2f pt(frame->cols/2., frame->rows/2.);
    Mat r = getRotationMatrix2D(pt, rotation, 1.0);
    warpAffine(*frame, *frame, r, frame->size());
}*/

//---------------------------------------------------------------------

void Transformations::rotatePosition(int degrees, int *x, int *y, int rotationCenterX, int rotationCenterY)
{
    if (degrees == 0) return;
    //used http://stackoverflow.com/questions/7953316/rotate-a-point-around-a-point-with-opencv for rotation calculation.  //accessed 23rd March
    double radians = (double)degrees * (M_PI / 180.00);
    double translatedX = (double)(*x - rotationCenterX);
    double translatedY = (double)(*y - rotationCenterY);

    double rotatedX = (translatedX * cos(radians)) - (translatedY * sin(radians));
    double rotatedY = (translatedX * sin(radians)) + (translatedY * cos(radians));

    *x = rotatedX + rotationCenterX;
    *y = rotatedY + rotationCenterY;
}

//---------------------------------------------------------------------



