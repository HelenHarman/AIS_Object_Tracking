
#ifndef TestSumOfSquaredDifference_H
#define TestSumOfSquaredDifference_H
#include <QtTest/QtTest>
#include <QtCore>
#include "sumOfSquaredDifference.h"
#include "AutoTest.h"
class SumOfSquaredDifferenceTest: public QObject
{
    Q_OBJECT
private:
    Mat appereance;
    Mat frame;
    SumOfSquaredDifference * sumOfSquaredDifference;
    private slots:
        void initTestCase();
        void maxSumOfSquaredDifferenceTest();
        void sameAppearanceTest();
        void sameAppearanceDiffSizes();
        void differentAppearanceTest();
        void cleanupTestCase();
};
//DECLARE_TEST(SumOfSquaredDifferenceTest)
#endif //SumOfSquaredDifference_H
