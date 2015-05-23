#ifndef SMARTREADAHEADDECISIONMAKER_H
#define SMARTREADAHEADDECISIONMAKER_H

#include "AbstractReadAheadDecisionMaker.h"

// This class detects next sequencies
/*
    1 2 7 8 13 14 ...
    sequentalLength = 2
    gap = 5
*/

class SmartReadAheadDecisionMaker : public AbstractReadAheadDecisionMaker
{
    // Address where sequence where found
    qulonglong m_startAddressForReadAhead;

    // Pattern parameters -
    // length of the sequental part
    qulonglong m_sequentalLength;
    // gap between sequental parts
    qulonglong m_gap;

    // Counter for checking sequentalLength
    qulonglong m_sequentalBunch;

    // Counter for sequentalLength during getReadAheadLines
    qulonglong m_sequentalPartCounter;
public:
    SmartReadAheadDecisionMaker(int readAheadSequenceLength, int readAheadLongevity,
                                qulonglong readAheadSize, qulonglong raidSize);

    bool statCacheAccess(qulonglong address);

    QVector<CacheLine> getReadAheadLines();
};

#endif // SMARTREADAHEADDECISIONMAKER_H
