#include "NoneLocalityGenerator.h"

NoneLocalityGenerator::NoneLocalityGenerator(const qulonglong raidSize):
    IRandomReadTraceAddressGenerator(raidSize)
{
}

qulonglong NoneLocalityGenerator::getNextAddress()
{
    return getQulonglongRand(getRaidSize());
}
