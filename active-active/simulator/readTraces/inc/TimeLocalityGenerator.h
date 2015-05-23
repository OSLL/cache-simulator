#ifndef TIMELOCALITYGENERATOR_H
#define TIMELOCALITYGENERATOR_H

#include "IRandomReadTraceAddressGenerator.h"
#include <QList>

class TimeLocalityGenerator : public IRandomReadTraceAddressGenerator
{
    QList<qulonglong> m_queue;
    qulonglong m_memorizedQueueLength;
    int m_probability;

    void statAddressGeneration(const qulonglong address);
public:
    TimeLocalityGenerator(const qulonglong raidSize);
    qulonglong getNextAddress();

    void setParameters(const qulonglong memorizedQueueLength, const int probability);

};

#endif // TIMELOCALITYGENERATOR_H
