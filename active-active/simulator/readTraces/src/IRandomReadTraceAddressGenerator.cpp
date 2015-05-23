#include "IRandomReadTraceAddressGenerator.h"


qulonglong IRandomReadTraceAddressGenerator::getRaidSize() const
{
    return m_raidSize;
}

qulonglong IRandomReadTraceAddressGenerator::getQulonglongRand(const qulonglong raidSize) const
{
    qulonglong result=0;
    qulonglong n = raidSize / (qulonglong)RAND_MAX;

    for (qulonglong i=0; i<n+1; i++){
        result += qrand() % raidSize;
    }
    return result;
}


IRandomReadTraceAddressGenerator::IRandomReadTraceAddressGenerator(const qulonglong raidSize): m_raidSize(raidSize)
{
}
