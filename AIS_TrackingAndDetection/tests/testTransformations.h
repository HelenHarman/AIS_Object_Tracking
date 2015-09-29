#ifndef TRANSFORMATIONSTEST_H
#define TRANSFORMATIONSTEST_H
#include <QtTest/QtTest>
#include <QtCore>
#include "transformations.h"
#include "AutoTest.h"

class TransformationsTest : public QObject, public Transformations
{
   Q_OBJECT
   private slots:
        void rotatePositionByZeroDegreesTest();
        void rotatePositionByNinetyDegreesTest();
};
//DECLARE_TEST(TransformationsTest)
#endif // TRANSFORMATIONSTEST_H
