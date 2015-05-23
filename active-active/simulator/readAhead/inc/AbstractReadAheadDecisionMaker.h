#ifndef ABSTRACTREADAHEADDECISIONMAKER_H
#define ABSTRACTREADAHEADDECISIONMAKER_H

#include <QtGlobal>
#include <QVector>

#include "CacheLine.h"
#define INVALID_READ_AHEAD_ADDRESS -1

class AbstractReadAheadDecisionMaker
{
    qulonglong m_readAheadSize;
    qulonglong m_raidSize;

    // How many requests should be done sequentialy for enabling RA
    int m_readAheadSequenceLength;

    // How many ticks RA will last
    int m_readAheadLongevity;

    // How many times RA was done
    int m_currentReadAheadCount;

    // Last accessed address
    qulonglong m_lastAddress;

    // Match count with pattern
    qulonglong m_currentAccessSequence;

    qulonglong m_readAheadAddress;
    bool m_isReadAheadAddressValid;
public:
    AbstractReadAheadDecisionMaker(int readAheadSequenceLength, int readAheadLongevity,
              qulonglong readAheadSize, qulonglong raidSize);

    virtual bool statCacheAccess(qulonglong address) = 0;

    bool isReadAheadOn() const;

    void enableReadAhead(bool enabled);

    void incrementReadAheadCount();

    virtual QVector<CacheLine> getReadAheadLines() = 0;

    int getReadAheadLongevity() const;

    int getReadAheadSequenceLength() const;

    qulonglong getReadAheadSize() const;

    qulonglong getRaidSize() const;

    qulonglong getLastAddress() const;

    void setLastAddress(const qulonglong lastAddress);

    void incrementCurrentAccessSequence();
    bool isCurrentAccessSequenceEnughForRA() const;
    void setCurrentAccessSequence(const qulonglong currentAccessSequence);

    qulonglong getReadAheadAddress() const;
    void setReadAheadAddress(const qulonglong readAheadAddress);

    void checkReadAheadAddress(const qulonglong address);
};

#endif // ABSTRACTREADAHEADDECISIONMAKER_H
