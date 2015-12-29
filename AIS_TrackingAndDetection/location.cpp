#include "location.h"

Location::Location(int x, int y, double scaleX, double scaleY, int rotation)
{
    this->x = x;
    this->y = y;
    this->scaleX = scaleX;
    this->scaleY = scaleY;
    this->rotation = rotation;
}

//----------------------------------------------------------------------

Location::Location(Location *location)
{
    this->x = location->x;
    this->y = location->y;
    this->scaleX = location->scaleX;
    this->scaleY = location->scaleY;
    this->rotation = location->rotation;
}

//----------------------------------------------------------------------

Location::Location(Mat frame, Mat appearance, int offSetX, int offSetY)
{
    this->constructor(frame, appearance.size().width, appearance.size().height, offSetX, offSetY);
}

//----------------------------------------------------------------------

Location::Location(Mat frame, int width, int height, int offSetX, int offSetY)
{
    this->constructor(frame, width, height, offSetX, offSetY);
}

//----------------------------------------------------------------------

void Location::constructor(Mat frame, int width, int height, int offSetX, int offSetY)
{
    this->scaleX = ((double)width/(double)frame.size().width)*100.00;
    this->scaleY = ((double)height/(double)frame.size().height)*100.00;
    this->x = offSetX + ((((double)frame.size().width / 100.00) * this->scaleX)/2);
    this->y = offSetY + ((((double)frame.size().height / 100.00) * this->scaleY)/2);
    this->rotation = 0;
}

//----------------------------------------------------------------------

int Location::getRotation() const
{
    return rotation;
}

//----------------------------------------------------------------------

void Location::setRotation(int value)
{
    rotation = value;
}

//----------------------------------------------------------------------

double Location::getScaleY() const
{
    return scaleY;
}

//----------------------------------------------------------------------

void Location::setScaleY(double value)
{
    scaleY = value;
}

//----------------------------------------------------------------------

double Location::getScaleX() const
{
    return scaleX;
}

//----------------------------------------------------------------------

void Location::setScaleX(double value)
{
    scaleX = value;
}

//----------------------------------------------------------------------

int Location::getY() const
{
    return y;
}

//----------------------------------------------------------------------

void Location::setY(int value)
{
    y = value;
}

//----------------------------------------------------------------------

int Location::getX() const
{
    return x;
}

//----------------------------------------------------------------------

void Location::setX(int value)
{
    x = value;
}

//----------------------------------------------------------------------

void Location::getCornerPoint(int *x, int *y, Mat frame)
{
    *x = this->x - ((((double)frame.size().width / 100.00) * this->scaleX)/2);
    *y = this->y - ((((double)frame.size().height / 100.00) * this->scaleY)/2);
}

//----------------------------------------------------------------------

void Location::getSize(int *width, int *height, Mat frame)
{
    *width = ((double)frame.size().width / 100.00) * this->scaleX;
    *height = ((double)frame.size().height / 100.00) * this->scaleY;
}

//----------------------------------------------------------------------
//----------------------------------------------------------------------




