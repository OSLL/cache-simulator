#ifndef IREADTRACE_H
#define IREADTRACE_H

#include <QtGlobal>

class ReadRequest;

class IReadTrace{

public:

    virtual ReadRequest* getNextReadRequest(qulonglong step) = 0;
    virtual bool isTraceFinished(qulonglong step) const =0;

};


#endif // IREADTRACE_H
