
#ifndef TestEuclideanDistance_H
#define TestEuclideanDistance_H
#include <QtTest/QtTest>
#include <QtCore>
#include "euclideandistance.h"
#include "AutoTest.h"
#include "options.h"
class EuclideanDistanceTest: public QObject
{
    Q_OBJECT
private:
    Mat appereance;
    Mat frame;
    EuclideanDistance * euclideanDistance;
    private slots:
        void initTestCase();
        void maxEuclideanDistanceTest();
        void sameAppearanceTest();
        void sameAppearanceDiffSizes();
        void differentAppearanceTest();

        void withTransformationTest();

        void cleanupTestCase();
};
//DECLARE_TEST(EuclideanDistanceTest)
#endif //TestEuclideanDistance_H
