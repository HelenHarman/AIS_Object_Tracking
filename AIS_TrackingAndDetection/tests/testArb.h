#ifndef TestARB_H
#define TestARB_H

#include <QtTest/QtTest>
#include <QtCore>
#include "arb.h"
#include "AutoTest.h"
class ArbTest: public QObject
{
    Q_OBJECT
private:
    ARB *arb;
    private slots:
        void initTestCase();
        void initalResourceLevelTest();
        void addALinkTest();
        void decreaseResourceLevelTest();
        void increaseResourceLevelTest();
        void increaseResourceLevelWithLinksTest();
        void removeALinkTest();
        void addSameLinkTwiceTest();
};
//DECLARE_TEST(ArbTest)
#endif //TestARB_H
