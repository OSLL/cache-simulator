#ifndef NONELOCALITYGENERATOR_H
#define NONELOCALITYGENERATOR_H

#include "IRandomReadTraceAddressGenerator.h"

class NoneLocalityGenerator: public IRandomReadTraceAddressGenerator
{
public:
    NoneLocalityGenerator(const qulonglong raidSize);
    qulonglong getNextAddress();

};

#endif // NONELOCALITYGENERATOR_H
