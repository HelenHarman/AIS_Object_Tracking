#ifndef DISTANCEBASETEST_H
#define DISTANCEBASETEST_H

#include <QtTest/QtTest>
#include <QtCore>
#include "DistanceBase.h"

#include "AutoTest.h"
class distanceBaseTest : public QObject, public DistanceBase
{
    Q_OBJECT
public:



    double getDistance(Mat frame, Mat appearance, AIS_Options::Location location) {};

     double getDistanceBetweenAppearances(Mat image, Mat appearance) {};

    ~distanceBaseTest(){};
 private slots:
     void calculateSSDTest();

};
DECLARE_TEST(distanceBaseTest)
#endif // DISTANCEBASETEST_H
