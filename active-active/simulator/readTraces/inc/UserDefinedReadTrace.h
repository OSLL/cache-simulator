#ifndef USERDEFINEDREADTRACE_H
#define USERDEFINEDREADTRACE_H

#include "IReadTrace.h"
#include "TraceFileReader.h"

class UserDefinedReadTrace : public IReadTrace
{
    TraceFileReader m_traceFileReader;


public:
    UserDefinedReadTrace();
    ReadRequest* getNextReadRequest(qulonglong step);

    bool isTraceFinished(qulonglong step) const;
};

#endif // USERDEFINEDREADTRACE_H
