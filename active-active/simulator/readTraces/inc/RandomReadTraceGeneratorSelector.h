#ifndef RANDOMREADTRACEGENERATORSELECTOR_H
#define RANDOMREADTRACEGENERATORSELECTOR_H

#include "IRandomReadTraceAddressGenerator.h"

class RandomReadTraceGeneratorSelector
{
public:
    static IRandomReadTraceAddressGenerator* getGenerator();
};

#endif // RANDOMREADTRACEGENERATORSELECTOR_H
