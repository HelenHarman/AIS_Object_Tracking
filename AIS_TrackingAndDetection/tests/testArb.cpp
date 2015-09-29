#include "testArb.h"
TEST_MAIN
void ArbTest::initTestCase()
{
   Mat appearance;
   this->arb = new ARB(appearance);
}

//-----------------------------------------------------------------

void ArbTest::initalResourceLevelTest()
{
    QVERIFY(fabs(this->arb->getResourceLevel() - 0.9) < 0.001);
}

//-----------------------------------------------------------------

void ArbTest::addALinkTest()
{
    int expectedValue = this->arb->getLinks().size() + 1;
    Mat appearance;
    ARB * arb2 = new ARB(appearance);
    this->arb->addNewLink(arb2, 0.5);

    vector<ARB*> arbs = this->arb->getLinks();
    int result = arbs.size();
    QCOMPARE(expectedValue, result);
    QCOMPARE(arbs[arbs.size()-1], arb2);
}

//-----------------------------------------------------------------

void ArbTest::decreaseResourceLevelTest()
{
    this->arb->decayResourceLevel();
    QVERIFY(fabs(this->arb->getResourceLevel() - 0.81) < 0.001);
}

//-----------------------------------------------------------------

void ArbTest::increaseResourceLevelTest()
{
    this->initTestCase();
    this->arb->increaseResourceLevel(0.5);
    QVERIFY(fabs(this->arb->getResourceLevel() - 1.26) < 0.001);

    this->initTestCase();
    this->arb->increaseResourceLevel(0.3);
    QVERIFY(fabs(this->arb->getResourceLevel() - 1.44) < 0.001);
}

//-----------------------------------------------------------------

void ArbTest::increaseResourceLevelWithLinksTest()
{
    this->initTestCase();
    Mat appearance;
    ARB * arb2 = new ARB(appearance);
    this->arb->addNewLink(arb2, 0.5);
    ARB * arb3 = new ARB(appearance);
    this->arb->addNewLink(arb3, 0.5);

    this->arb->increaseResourceLevel(0.5);
    qDebug("%f", this->arb->getResourceLevel());
    QVERIFY(fabs(this->arb->getResourceLevel() - 1.71) < 0.001);
}

//--------------------------------------------------------------------

void ArbTest::removeALinkTest()
{
    Mat appearance;
    ARB * arb2 = new ARB(appearance);
    this->arb->addNewLink(arb2, 0.5);

    int expectedValue = this->arb->getLinks().size() - 1;
    this->arb->removeLink(arb2);
    int result = this->arb->getLinks().size();
    QCOMPARE(expectedValue, result);
}

//--------------------------------------------------------------------

void ArbTest::addSameLinkTwiceTest()
{
    Mat appearance;
    ARB * arb2 = new ARB(appearance);

    this->arb->addNewLink(arb2, 0.5);
    int expectedValue = this->arb->getLinks().size();
    this->arb->addNewLink(arb2, 0.8);
    int result = this->arb->getLinks().size();

    QCOMPARE(expectedValue, result);
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------

