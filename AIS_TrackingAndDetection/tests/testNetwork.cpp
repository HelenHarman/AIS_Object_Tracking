#include "testNetwork.h"

//--------------------------------------------------------------------

void NetworkTest::initTestCase()
{
    Location loc;
    Mat testAppearance;
    //DistanceBase * distanceMeasure = new Moc_EuclideanDistance();
   // this->network = new Network(testAppearance, loc, distanceMeasure, 0.4, 0.2);
   // this->network->setUsePredictedLocation(true);
}

//--------------------------------------------------------------------

void NetworkTest::initialSizeOfNetworkTest()
{
    QVERIFY(this->network->getNumberOfARBs() == 1);
}

//--------------------------------------------------------------------

void NetworkTest::addNewAppearanceWithLargeDistanceTest()
{
    Mat newAppearance;
    Location loc;
    this->network->addAppearance(newAppearance, loc);//distance of 0.3
    QVERIFY(this->network->getNumberOfARBs() == 2);
}

//--------------------------------------------------------------------

void NetworkTest::addNewAppearanceWithSmallDistanceTest()
{
    Mat newAppearance;
    Location loc;
    int expected = this->network->getNumberOfARBs();
    this->network->addAppearance(newAppearance, loc);//distance of 0.08
    QCOMPARE(this->network->getNumberOfARBs(), expected);
}

//--------------------------------------------------------------------

void NetworkTest::getAllAppearancesTest()
{
    this->initTestCase();
    Mat newAppearance;
    Location loc;
    this->network->addAppearance(newAppearance, loc);//distance of 0.3
    this->network->addAppearance(newAppearance, loc);//distance of 0.3
    this->network->addAppearance(newAppearance, loc);//distance of 0.3
    int result = this->network->getAllAppearances().size();
    QCOMPARE(result, 3);
}

//--------------------------------------------------------------------

void NetworkTest::getLastAndHighestARBsTest()
{
    this->initTestCase();
    Mat newAppearance;
    Location loc;
    this->network->addAppearance(newAppearance, loc);//distance of 0.08
    this->network->addAppearance(newAppearance, loc);//distance of 0.3
    this->network->addAppearance(newAppearance, loc);//distance of 0.3

    int result = this->network->getLastAndHighestARBs().size();
    QCOMPARE(result, 2);
}

//--------------------------------------------------------------------

void NetworkTest::getARBsWithAboveAverageRLTest()
{
    this->initTestCase();
    Mat newAppearance;
    Location loc;
    this->network->addAppearance(newAppearance, loc);//distance of 0.3
    this->network->addAppearance(newAppearance, loc);//distance of 0.3
    this->network->addAppearance(newAppearance, loc);//distance of 0.3
    this->network->addAppearance(newAppearance, loc);//distance of 0.3
    this->network->addAppearance(newAppearance, loc);//distance of 0.3
    this->network->addAppearance(newAppearance, loc);//distance of 0.3

    int result = this->network->getARBsWithAboveAverageRL().size();
    QCOMPARE(result, 3);
}

//--------------------------------------------------------------------

void NetworkTest::getPredictedLocationTest()
{
    Mat newAppearance;
    Location loc1;
    loc1.x = 100;
    loc1.y = 100;
    loc1.rotation = 20;
    loc1.scaleX = 0.9;
    loc1.scaleY = 0.9;

    Location loc2;
    loc2.x = 110;
    loc2.y = 110;
    loc2.rotation = 25;
    loc2.scaleX = 0.7;
    loc2.scaleY = 0.7;

    this->network->addAppearance(newAppearance, loc1);//distance of 0.3
    this->network->addAppearance(newAppearance, loc2);//distance of 0.3

    Location prediction = this->network->getPredictedLocation();
    QVERIFY(prediction.x == 120);
    QVERIFY(prediction.y == 120);
    // Removed predicting rotation and scale from the code but maybe used again
    //QVERIFY(prediction.rotation == 30);
    //QVERIFY(fabs(prediction.scaleX - 0.5) < 0.001 );
    //QVERIFY(fabs(prediction.scaleY - 0.5) < 0.001 );
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------


