#ifndef READAHEADDECISIONMAKERFACTORY_H
#define READAHEADDECISIONMAKERFACTORY_H

#include "AbstractReadAheadDecisionMaker.h"

class ReadAheadDecisionMakerFactory
{
public:
    static AbstractReadAheadDecisionMaker* getDecisionMaker(int readAheadSequenceLength, int readAheadLongevity,
                                                            qulonglong readAheadSize, qulonglong raidSize);
};

#endif // READAHEADDECISIONMAKERFACTORY_H
