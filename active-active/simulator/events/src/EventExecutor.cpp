#include "EventExecutor.h"
#include "SettingsReader.h"

#include <QDebug>


EventExecutor::EventExecutor()
{
}


void EventExecutor::setEvents(const QList<Event> &events)
{
    m_events = events;
}

void EventExecutor::executeEvents(const qulonglong step)
{
    // Events are sorted by apply time in ascending order
    foreach (Event event, m_events)
    {
        qDebug() << "Checking event: " <<  event.toString();
        if (event.shouldBeApplied(step)){
            qDebug() << "Executing event: "<< step  << event.toString();

            SettingsReader::setValue(event.getParameterName(), event.getValueForStep(step));
            if (event.isFinished(step))
                m_events.removeAll(event);
        }else{
            break;
        }
    }


}
