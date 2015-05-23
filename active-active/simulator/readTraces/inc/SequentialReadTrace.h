#ifndef SEQUENTIALREADTRACE_H
#define SEQUENTIALREADTRACE_H

#include "IReadTrace.h"

class ReadRequest;

class SequentialReadTrace: public IReadTrace
{
    qulonglong m_lastAddress;
    qulonglong getAddressToRead();

public:
    SequentialReadTrace();
    ReadRequest *getNextReadRequest(qulonglong step);
    bool isTraceFinished(qulonglong step) const;
};

#endif // SEQUENTIALREADTRACE_H
