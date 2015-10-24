#ifndef LOCATION_H
#define LOCATION_H

#include <opencv2/core/core.hpp>

using namespace cv;

class Location
{
public:
    Location(int x, int y, double scaleX, double scaleY, int rotation);
    Location(Mat frame, Mat appearance, int offSetX = 0, int offSetY = 0);
    Location(Mat frame, int width, int height, int offSetX = 0, int offSetY = 0);
    Location(Location *location);
    Location(){}

    int getRotation() const;
    void setRotation(int value);

    double getScaleY() const;
    void setScaleY(double value);

    double getScaleX() const;
    void setScaleX(double value);

    int getY() const;
    void setY(int value);

    int getX() const;
    void setX(int value);

    void getCornerPoint(int *x, int *y, Mat frame);
    void getSize(int *width, int *height, Mat frame);

private:
    int x;
    int y;
    double scaleX;
    double scaleY;
    int rotation;

    void constructor(Mat frame, int width, int height, int offSetX = 0, int offSetY = 0);
};

#endif // LOCATION_H
