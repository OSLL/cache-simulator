#include "TestEvent.h"
#include <QDebug>
#include <QVariant>

#define TEST_KEY_ULONGLONG "TEST_KEY_ULONGLONG"
#define TEST_KEY_STRING "TEST_KEY_STRING"
#define TEST_STRING_VALUE "TEST_STRING_VALUE"
#define TEST_STRING_NEW_VALUE QVariant("TEST_STRING_NEW_VALUE")

#define TEST_APPLY_STEP 2
#define TEST_WRONG_INSTANT_APPLY_STEP 3
#define TEST_VALID_INSTANT_APPLY_STEP 2

#define TEST_VALUE_DELTA 1
#define TEST_STEPS_NUMBER_TO_APPLY 2
#define TEST_WRONG_GRADUAL_APPLY_STEP 7
#define TEST_VALID_GRADUAL_APPLY_STEP0 2
#define TEST_VALID_GRADUAL_APPLY_STEP1 3
#define TEST_GRADUAL_VALUE QVariant((qulonglong)13)

#define TEST_VALUE_DELTA_NEAGTIVE -1
#define TEST_GRADUAL_VALUE_NEGATIVE QVariant((qulonglong)11)


TestEvent::TestEvent(QObject *parent) :
    QObject(parent)
{
    m_instantEvent = Event(TEST_KEY_STRING, TEST_APPLY_STEP, TEST_STRING_NEW_VALUE);
    m_gradualEvent0 = Event(TEST_KEY_ULONGLONG, TEST_APPLY_STEP, TEST_VALUE_DELTA,
                           TEST_STEPS_NUMBER_TO_APPLY);

    m_gradualEvent1 = Event(TEST_KEY_ULONGLONG, TEST_APPLY_STEP, TEST_VALUE_DELTA_NEAGTIVE,
                           TEST_STEPS_NUMBER_TO_APPLY);

}


void TestEvent::testGetValueForStep()
{
    QCOMPARE(m_instantEvent.getValueForStep(TEST_VALID_INSTANT_APPLY_STEP), TEST_STRING_NEW_VALUE);

    QCOMPARE(m_gradualEvent0.getValueForStep(TEST_VALID_GRADUAL_APPLY_STEP0), TEST_GRADUAL_VALUE);
    QCOMPARE(m_gradualEvent0.getValueForStep(TEST_VALID_GRADUAL_APPLY_STEP1), TEST_GRADUAL_VALUE);

    QCOMPARE(m_gradualEvent1.getValueForStep(TEST_VALID_GRADUAL_APPLY_STEP0), TEST_GRADUAL_VALUE_NEGATIVE);
    QCOMPARE(m_gradualEvent1.getValueForStep(TEST_VALID_GRADUAL_APPLY_STEP1), TEST_GRADUAL_VALUE_NEGATIVE);
}

void TestEvent::testShouldBeApplied()
{
    Q_ASSERT(m_instantEvent.shouldBeApplied(TEST_VALID_INSTANT_APPLY_STEP));
    Q_ASSERT(! m_instantEvent.shouldBeApplied(TEST_WRONG_INSTANT_APPLY_STEP));

    Q_ASSERT(m_gradualEvent0.shouldBeApplied(TEST_VALID_GRADUAL_APPLY_STEP0));
    Q_ASSERT(m_gradualEvent0.shouldBeApplied(TEST_VALID_GRADUAL_APPLY_STEP1));
    Q_ASSERT(! m_gradualEvent0.shouldBeApplied(TEST_WRONG_GRADUAL_APPLY_STEP));
}
