#ifndef RANDOMREADTRACE_H
#define RANDOMREADTRACE_H

#include "IReadTrace.h"


class IRandomReadTraceAddressGenerator;


class RandomReadTrace : public IReadTrace
{
    IRandomReadTraceAddressGenerator * m_generator;

    bool isCacheHit() const;

    qulonglong getRandomTime() const;
    qulonglong getCacheMissTime() const;
    qulonglong getCacheHitTime() const;
    qulonglong getBaseTime() const;
    int selectStorageProcessorNumber() const;

    void processReadRequest(ReadRequest *request) const;

public:
    static qulonglong getQulonglongRand(qulonglong raidSize);

    RandomReadTrace();

    ReadRequest *getNextReadRequest(qulonglong step);
    bool isTraceFinished(qulonglong step) const;

};

#endif // RANDOMREADTRACE_H
