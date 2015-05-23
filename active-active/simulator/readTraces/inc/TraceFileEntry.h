#ifndef TRACEFILEENTRY_H
#define TRACEFILEENTRY_H

#include <QMap>
#include <QString>
#include <QVariant>

class TraceFileEntry
{
    QMap<QString, QVariant> m_map;
public:
    TraceFileEntry();
    TraceFileEntry(const QMap<QString, QVariant>& map );
    TraceFileEntry(const QString& string);

    QVariant getElement(const QString& element) const;

    qulonglong getAddress() const;
    qulonglong getOffset() const;
    int getOpcode() const;

    bool isReadRequest() const;
};

#endif // TRACEFILEENTRY_H
