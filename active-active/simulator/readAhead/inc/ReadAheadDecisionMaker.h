#ifndef SMARTREADAHEAD_H
#define SMARTREADAHEAD_H

#include <QtGlobal>

#include "CacheLine.h"
#include "AbstractReadAheadDecisionMaker.h"
#include <QVector>

class ReadAheadDecisionMaker: public AbstractReadAheadDecisionMaker
{

    // How many times sequential access was done
    int m_currentAccessSequence;

    qulonglong m_readAheadAddress;

public:
    ReadAheadDecisionMaker(int readAheadSequenceLength, int readAheadLongevity,
              qulonglong readAheadSize, qulonglong raidSize);

    bool statCacheAccess(qulonglong address);

    QVector<CacheLine> getReadAheadLines();
};

#endif // SMARTREADAHEAD_H
