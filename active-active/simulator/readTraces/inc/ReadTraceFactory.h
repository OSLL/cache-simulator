#ifndef READTRACEFACTORY_H
#define READTRACEFACTORY_H

#include "IReadTrace.h"

class ReadTraceFactory
{
    static IReadTrace* m_readTrace;
    static void createReadTrace();
public:
    static IReadTrace* getReadTrace();
};

#endif // READTRACEFACTORY_H
