#ifndef LIMITEDTHROUGHPUT_H
#define LIMITEDTHROUGHPUT_H

#include <QString>
#include "SettingsReader.h"

class LimitedThroughput
{
    static QList<LimitedThroughput*> s_objects;

    qulonglong m_passedRequestCount;

    QString m_latencyParameter;
    QString m_throughputParameter;

    LimitedThroughput(const QString& latencyParameter,
                      const QString& throughputParameter);

    // Clear m_passedRequestCount variable
    void clearRequestCount();

    static void removeObject(LimitedThroughput* object);

public:

    static LimitedThroughput* createNewObject(const QString& latencyParameter,
                                              const QString& throughputParameter);

    // Compare m_passedRequestCount with value, stored by m_throughputParameter key
    bool isNotFull() const;

    void incrementRequestCount();

    // Get latency stored by m_latencyParameter
    qulonglong getWaitingLatency() const;

    // Apply clearRequestCount() for all created
    static void clearForNextStep();

    ~LimitedThroughput();
    qulonglong getMaxRequestCount() const;
    qulonglong getWaitingRequestsCount() const;

};

#endif // LIMITEDTHROUGHPUT_H
