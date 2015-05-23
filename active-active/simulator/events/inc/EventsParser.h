#ifndef EVENTSPARSER_H
#define EVENTSPARSER_H

// This class extracts events from ini file
// and return sorted vector of them

#include <QSettings>
#include <QVector>

#include "Event.h"



class EventsParser
{
    QList<Event> m_events;
public:
    EventsParser(QSettings &settings);
    QList<Event> getEvents() const;

};

#endif // EVENTSPARSER_H
