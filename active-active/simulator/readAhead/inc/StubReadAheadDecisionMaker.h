#ifndef STUBREADAHEADDECISIONMAKER_H
#define STUBREADAHEADDECISIONMAKER_H

#include "AbstractReadAheadDecisionMaker.h"


class StubReadAheadDecisionMaker : public AbstractReadAheadDecisionMaker
{
public:
    StubReadAheadDecisionMaker(int readAheadSequenceLength, int readAheadLongevity,
              qulonglong readAheadSize, qulonglong raidSize);

    bool statCacheAccess(qulonglong);

    QVector<CacheLine> getReadAheadLines();
};

#endif // STUBREADAHEADDECISIONMAKER_H
