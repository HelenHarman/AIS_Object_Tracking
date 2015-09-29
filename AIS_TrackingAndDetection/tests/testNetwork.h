
#ifndef TestEuclideanDistance_H
#define TestEuclideanDistance_H
//#include <QtTest/QtTest>
#include <AutoTest.h>
#include <QtCore>

#include "network.h"
// during testing using moc euclidean distance file to get controlable results.
// when ever this->network->addAppearance() is called you need to add an item to
// the test array inside moc_euclideanDistance.h
#include "moc_euclideanDistance.h"


class NetworkTest: public QObject
{
    Q_OBJECT
private:
    Mat appereance;
    Mat frame;
    Network *network;
private slots:
        void initTestCase();
        void initialSizeOfNetworkTest();
        void addNewAppearanceWithLargeDistanceTest();//causes new ARB to be created
        void addNewAppearanceWithSmallDistanceTest();//no new ARB should be created
        void getAllAppearancesTest();
        void getLastAndHighestARBsTest();
        void getARBsWithAboveAverageRLTest();
        void getPredictedLocationTest();
};
//DECLARE_TEST(NetworkTest)
#endif //TestEuclideanDistance_H
