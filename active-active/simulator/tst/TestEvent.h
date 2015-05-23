#ifndef TESTEVENT_H
#define TESTEVENT_H

#include <QtTest>
#include <QObject>
#include "Event.h"

class TestEvent : public QObject
{
    Q_OBJECT
    Event m_gradualEvent0;
    Event m_gradualEvent1;

    Event m_instantEvent;
public:
    TestEvent(QObject *parent = 0);
    

private slots:
    void testGetValueForStep();
    void testShouldBeApplied();
};

#endif // TESTEVENT_H
