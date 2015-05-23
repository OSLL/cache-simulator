#ifndef SETTINGSREADER_H
#define SETTINGSREADER_H

#include <QSettings>
#include <QMap>
#include <QList>
#include "Event.h"

class SettingsReader
{
    static QSettings* m_settings;
    static QString m_fileName;
    static QMap<QString, QVariant> m_settingsMap;
    static QList<Event> m_events;
    static void initSettingsMap();

public:

    static void init(const QString& fileName);
    static void setValue(const QString&, const QVariant&);

    static QString getFileName();
    static QList<Event> getEvents();
    static QVariant getValue(const QString &key, const QVariant &defaultValue = QVariant());
};

#endif // SETTINGSREADER_H
