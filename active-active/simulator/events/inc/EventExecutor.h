#ifndef EVENTEXECUTOR_H
#define EVENTEXECUTOR_H

#include <QList>
#include "Event.h"

class EventExecutor
{
private:


    QList<Event> m_events;
public:
    EventExecutor();
    void setEvents(const QList<Event> &events);
    void executeEvents(const qulonglong step);
};

#endif // EVENTEXECUTOR_H
