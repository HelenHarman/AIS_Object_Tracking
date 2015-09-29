#include "testTransformations.h"

//-----------------------------------------------------------------

void TransformationsTest::rotatePositionByZeroDegreesTest()
{

    int x = 20, y = 20;
    rotatePosition(0, &x, &y, 50, 50);
    QCOMPARE(x, 20);
    QCOMPARE(y, 20);
}

//-----------------------------------------------------------------

void TransformationsTest::rotatePositionByNinetyDegreesTest()
{
    int x = 20, y = 20;
    rotatePosition(90, &x, &y, 50, 50);
    QCOMPARE(x, 80);
    QCOMPARE(y, 19);
}

//-----------------------------------------------------------------
//-----------------------------------------------------------------
