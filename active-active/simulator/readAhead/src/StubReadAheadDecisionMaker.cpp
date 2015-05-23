#include "StubReadAheadDecisionMaker.h"

StubReadAheadDecisionMaker::StubReadAheadDecisionMaker(int readAheadSequenceLength,
                                                       int readAheadLongevity,
                                                       qulonglong readAheadSize,
                                                       qulonglong raidSize):
  AbstractReadAheadDecisionMaker(readAheadSequenceLength, readAheadLongevity,
                                 readAheadSize, raidSize)
{
}

bool StubReadAheadDecisionMaker::statCacheAccess(qulonglong)
{
    return false;
}

QVector<CacheLine> StubReadAheadDecisionMaker::getReadAheadLines()
{
    return QVector<CacheLine>();
}


