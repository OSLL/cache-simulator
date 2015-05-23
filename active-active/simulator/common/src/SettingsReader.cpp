#include "SettingsReader.h"
#include "EventsParser.h"
#include <QDebug>
#include <QStringList>

QSettings* SettingsReader::m_settings = NULL;
QString SettingsReader::m_fileName = "";
QMap<QString, QVariant> SettingsReader::m_settingsMap = QMap<QString, QVariant>();
QList<Event> SettingsReader::m_events = QList<Event>();

void SettingsReader::init(const QString& fileName){

    SettingsReader::m_fileName = fileName;
    SettingsReader::m_settings = new QSettings(fileName, QSettings::IniFormat);
    initSettingsMap();
    EventsParser eventsParser(*m_settings);
    m_events = eventsParser.getEvents();

    qDebug() << "SettingsReader initialized for "<< fileName;
}

void SettingsReader::initSettingsMap(){
    m_settings->beginGroup("main");
    QStringList keys = m_settings->allKeys();
    foreach(const QString& key, keys){
        qDebug() << "Adding into m_settingsMap " << key << m_settings->value(key) ;
        m_settingsMap.insert(key,  m_settings->value(key));
    }
    m_settings->endGroup();
}

QVariant SettingsReader::getValue(const QString& key, const QVariant& defaultValue){
    return m_settingsMap.value(key, defaultValue);
}

void SettingsReader::setValue(const QString& key, const QVariant& value){
    m_settingsMap.insert(key, value);
}

QString SettingsReader::getFileName(){
    return m_fileName;
}

QList<Event> SettingsReader::getEvents()
{
    return m_events;
}
