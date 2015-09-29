#include "distancebasetest.h"



void distanceBaseTest::calculateSSDTest()
{
    Mat initialImage = imread("/Users/helen/Documents/UniWork/Dissertation/EuclideanDistance/tests/testData/apperance.jpg");
    Mat appearance (initialImage, Rect(0, 0, 10, 10) );
    Mat image (initialImage, Rect(0, 0, 5, 5) );

    AIS_Options::Location loc = {0, 0, 0.5, 0.5, 0};

    qDebug("%f", this->calculateSSD(image, appearance, loc));

}
