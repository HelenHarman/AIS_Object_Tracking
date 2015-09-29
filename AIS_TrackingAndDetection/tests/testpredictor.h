#ifndef TESTPREDICTOR_H
#define TESTPREDICTOR_H
#include <QtTest/QtTest>
#include <QtCore>
#include "predictor.h"
#include "AutoTest.h"
class TestPredictor: public QObject
{
    Q_OBJECT
    private:
        Predictor *predictor;
    private slots:
        void initTestCase();
        void initialValuesForPredictorTest();

};
DECLARE_TEST(TestPredictor)
#endif // TESTPREDICTOR_H
