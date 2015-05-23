#ifndef SPACIALLOCALITYGENERATOR_H
#define SPACIALLOCALITYGENERATOR_H

#include "IRandomReadTraceAddressGenerator.h"

class SpacialLocalityGenerator : public IRandomReadTraceAddressGenerator
{
    qulonglong m_leftAddress;
    qulonglong m_rightAddress;
    int m_probability;
public:
    SpacialLocalityGenerator(const qulonglong raidSize);
    qulonglong getNextAddress();
    void setParameters(const qulonglong leftAddress, const qulonglong rightAddress, int probability);

};

#endif // SPACIALLOCALITYGENERATOR_H
