#include "testSumOfSquaredDifference.h"

//-----------------------------------------------------------------

void SumOfSquaredDifferenceTest::initTestCase()
{
    this->appereance = imread("/Users/helen/Documents/UniWork/Dissertation/EuclideanDistance/tests/testData/apperance.jpg");
    this->frame = imread("/Users/helen/Documents/UniWork/Dissertation/EuclideanDistance/tests/testData/frame.jpg");
    resize(this->appereance, this->appereance, Size(), 0.2, 0.2);
    resize(this->frame, this->frame, Size(), 0.2, 0.2);
    this->sumOfSquaredDifference = new SumOfSquaredDifference(this->frame, this->appereance);
}

//-----------------------------------------------------------------

void SumOfSquaredDifferenceTest::sameAppearanceTest()
{
    //qDebug("%f", sumOfSquaredDifference->getDistance(this->appereance, this->appereance));
    //QVERIFY(sumOfSquaredDifference->getDistance(this->appereance, this->appereance) == 0);
}

//-----------------------------------------------------------------

void SumOfSquaredDifferenceTest::maxSumOfSquaredDifferenceTest()
{
    //qDebug("%f", this->sumOfSquaredDifference->getMaxDistance());
    QVERIFY((int)this->sumOfSquaredDifference->getMaxDistance() == 102256482);
}

//-----------------------------------------------------------------

void SumOfSquaredDifferenceTest::sameAppearanceDiffSizes()
{
    Mat smallerImage;
    resize(this->appereance, smallerImage, Size(), 0.8, 0.8, INTER_AREA);
    //qDebug("%f", sumOfSquaredDifference->getDistance(this->appereance, smallerImage));
   // QVERIFY(sumOfSquaredDifference->getDistance(this->appereance, smallerImage) < 0.02);
}

//-----------------------------------------------------------------

void SumOfSquaredDifferenceTest::differentAppearanceTest()
{
    Mat appearance2 = imread("/Users/helen/Documents/UniWork/Dissertation/EuclideanDistance/tests/testData/appearance2.jpg");
    resize(appearance2, appearance2, Size(), 0.2, 0.2);
    //double result = this->sumOfSquaredDifference->getDistance(this->appereance, appearance2);
    //qDebug("this distance : %f", result);
    //QVERIFY(result > 0.3 && result < 0.32);
}

//-----------------------------------------------------------------

void SumOfSquaredDifferenceTest::cleanupTestCase()
{
    delete(this->sumOfSquaredDifference);
}

//-----------------------------------------------------------------
//-----------------------------------------------------------------



