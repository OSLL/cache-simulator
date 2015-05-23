#ifndef IRANDOMREADTRACEADDRESSGENERATOR_H
#define IRANDOMREADTRACEADDRESSGENERATOR_H

#include <QtGlobal>

// Interface for different locality address generation algorithms

class IRandomReadTraceAddressGenerator
{

    qulonglong m_raidSize;

public:

    qulonglong getRaidSize() const;

    qulonglong getQulonglongRand(const qulonglong raidSize) const;


    IRandomReadTraceAddressGenerator(const qulonglong raidSize);

    virtual qulonglong getNextAddress()=0;
};

#endif // IRANDOMREADTRACEADDRESSGENERATOR_H
