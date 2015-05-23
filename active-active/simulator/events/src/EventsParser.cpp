#include "EventsParser.h"
#include <QStringList>
#include "defines.h"
#include <QDebug>

EventsParser::EventsParser(QSettings &settings)
{
    // Build arrays of valid keys for both event type
    QStringList sharedEventKeys;
    sharedEventKeys.append(APPLY_STEP);
    sharedEventKeys.append(PARAMETER_NAME);

    QStringList instantEventKeys = sharedEventKeys;
    instantEventKeys.append(NEW_VALUE);
    instantEventKeys.sort();

    QStringList gradualEventKeys = sharedEventKeys;
    gradualEventKeys.append(VALUE_DELTA);
    gradualEventKeys.append(STEPS_NUMBER_TO_APPLY);
    gradualEventKeys.sort();

    // Iterate all events in ini file
    QStringList groups = settings.childGroups();
    qDebug() << groups;
    groups.removeAll(QString(MAIN_INI_SECTION));

    foreach (QString group, groups){

        settings.beginGroup(group);
        QStringList keys = settings.childKeys();
        keys.sort();
        qDebug() << keys;

        if (keys != instantEventKeys && keys != gradualEventKeys){
            qDebug() << "Event format is wrong, checking next one.";
            settings.endGroup();
            continue;
        }

        Event event;

        qulonglong applyStep = settings.value(APPLY_STEP).toULongLong();
        QString parameterName = settings.value(PARAMETER_NAME).toString();


        // Find out event type
        if (keys == instantEventKeys){
            // Construct instant event
            QVariant newValue = settings.value(NEW_VALUE);
            event = Event(parameterName, applyStep, newValue);
        }else if (keys == gradualEventKeys){
            // Contstruct gradual event
            qulonglong valueDelta = settings.value(VALUE_DELTA).toULongLong();
            qulonglong stepsNumberToApply = settings.value(STEPS_NUMBER_TO_APPLY).toULongLong();
            event = Event(parameterName, applyStep, valueDelta, stepsNumberToApply);
        }

        m_events.append(event);
        settings.endGroup();
    }
    qSort(m_events);
    qDebug() << "Events size == " << m_events.size();
    foreach (Event event, m_events){
        qDebug() << event.toString();
    }


}

QList<Event> EventsParser::getEvents() const
{
    return m_events;
}
