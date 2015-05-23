#include "TestReadAheadDecisionMakers.h"
#include "AbstractReadAheadDecisionMaker.h"
#include "SmartReadAheadDecisionMaker.h"
#include "ReadAheadDecisionMaker.h"
#include <QDebug>
#include <QtTest>

#define TEST_RA_SEQUENCE 3
#define TEST_RA_DISTANCE 2
#define TEST_RA_BLOCK 2
#define TEST_RAID_SIZE 100

#define TEST_ARRAY_SIMPLE_RA {1, 5, 6, 9, 10, 11}
#define VALID_STEP_SIMPLE_RA_TURN_ON 5

#define TEST_ARRAY_SMART_RA {9, 6, 7, 5, 6, 11 }
#define VALID_STEP_SMART_RA_TURN_ON 5

TestReadAheadDecisionMakers::TestReadAheadDecisionMakers() :
    QObject()
{
}

void TestReadAheadDecisionMakers::testReadAheadDecisionMaker()
{
    qDebug() << "Checking ReadAheadDecisionMaker";
    ReadAheadDecisionMaker * maker = new ReadAheadDecisionMaker(
                TEST_RA_SEQUENCE, TEST_RA_DISTANCE, TEST_RA_BLOCK, TEST_RAID_SIZE);
    qulonglong testArray[] = TEST_ARRAY_SIMPLE_RA;
    checkDecisionMaker(maker, testArray, 6, VALID_STEP_SIMPLE_RA_TURN_ON);
}

void TestReadAheadDecisionMakers::testSmartReadAheadDecisionMaker()
{
    qDebug() << "Checking SmartReadAheadDecisionMaker";
    SmartReadAheadDecisionMaker * maker = new SmartReadAheadDecisionMaker(
                TEST_RA_SEQUENCE, TEST_RA_DISTANCE, TEST_RA_BLOCK, TEST_RAID_SIZE);
    qulonglong testArray[] = TEST_ARRAY_SMART_RA;
    checkDecisionMaker(maker, testArray, 6, VALID_STEP_SMART_RA_TURN_ON);
}

void TestReadAheadDecisionMakers::checkDecisionMaker(AbstractReadAheadDecisionMaker *maker,
                                                     qulonglong testArray[], unsigned int size,
                                                     unsigned int validTurnOnIndex)
{
    qDebug() << "size == " << size;
    for (unsigned int i=0; i<size; i++){
        bool result = maker->statCacheAccess(testArray[i]);

        qDebug() << "Checking element: i ==" << i << ", testArray[i] =="
                 << testArray[i] << ", result == "<< result
                 << ", validTurnOnIndex ==" << validTurnOnIndex;

        if (result == true && i == validTurnOnIndex){
            qDebug() << "RA is turned on";
            return;
        }

    }

    QVERIFY(false);
}
