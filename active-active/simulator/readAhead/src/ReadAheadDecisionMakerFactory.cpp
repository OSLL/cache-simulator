#include "ReadAheadDecisionMakerFactory.h"
#include "SmartReadAheadDecisionMaker.h"
#include "ReadAheadDecisionMaker.h"
#include "StubReadAheadDecisionMaker.h"
#include "SettingsReader.h"
#include "defines.h"

AbstractReadAheadDecisionMaker *ReadAheadDecisionMakerFactory::getDecisionMaker(
        int readAheadSequenceLength, int readAheadLongevity,
        qulonglong readAheadSize, qulonglong raidSize)
{
    QString readAheadType = SettingsReader::getValue(READ_AHEAD_TYPE).toString();
    if (readAheadType == READ_AHEAD_SIMPLE)
        return new ReadAheadDecisionMaker(readAheadSequenceLength, readAheadLongevity,
                                          readAheadSize, raidSize);
    else if (readAheadType == READ_AHEAD_SMART)
        return new SmartReadAheadDecisionMaker(readAheadSequenceLength, readAheadLongevity,
            readAheadSize, raidSize);
    else if (readAheadType == READ_AHEAD_NONE)
        return new StubReadAheadDecisionMaker(readAheadSequenceLength, readAheadLongevity,
                                              readAheadSize, raidSize);

    return NULL;
}

