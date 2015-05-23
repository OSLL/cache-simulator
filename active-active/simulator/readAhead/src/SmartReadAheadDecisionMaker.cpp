#include "SmartReadAheadDecisionMaker.h"


SmartReadAheadDecisionMaker::SmartReadAheadDecisionMaker(int readAheadSequenceLength,
                                                         int readAheadLongevity,
                                                         qulonglong readAheadSize,
                                                         qulonglong raidSize):
    AbstractReadAheadDecisionMaker(readAheadSequenceLength, readAheadLongevity,
                                   readAheadSize, raidSize),
//    m_startAddressForReadAhead(INVALID_READ_AHEAD_ADDRESS),
    m_sequentalPartCounter(0)
{
}

bool SmartReadAheadDecisionMaker::statCacheAccess(qulonglong address)
{
    qulonglong nextAddress = getLastAddress()+1;
    if (address == nextAddress || (address > nextAddress && m_sequentalBunch > 0) ){

        incrementCurrentAccessSequence();
        if ( isCurrentAccessSequenceEnughForRA()  ){
            // RA is turned ON
            enableReadAhead(true);
            setCurrentAccessSequence(0);
        }

        if (address == nextAddress){
            // Sequental part
            m_sequentalBunch++;
        }else if (address > nextAddress && m_sequentalBunch > 0){
            // Gap

            qulonglong newGap = address - getLastAddress();
            qulonglong newLength = m_sequentalBunch+1;

            if ((newGap != m_gap || m_sequentalLength != newLength)
                    && isReadAheadOn()){
                // Gap or SequentalLength changed + RA is on ->
                // we need to restart readAhead from current address

                setReadAheadAddress(address);
                m_sequentalPartCounter = 0;
            }

            m_gap = newGap;
            m_sequentalLength = newLength;
            m_sequentalBunch  = 0;
        }

    }else{
        // Pattern break
        setCurrentAccessSequence(0);
        m_gap = 0;
        m_sequentalLength = 0;
        m_sequentalBunch  = 0;
//        m_startAddressForReadAhead = INVALID_READ_AHEAD_ADDRESS;
        m_sequentalPartCounter = 0;
    }

    setLastAddress(address);

    checkReadAheadAddress(address);

    return isReadAheadOn();

}

QVector<CacheLine> SmartReadAheadDecisionMaker::getReadAheadLines()
{
    // TODO add RA data generation using m_gap and m_sequentalLength values usage
    qulonglong readAheadSize = getReadAheadSize();
    QVector<CacheLine> readAheadLines;
    // Fill readAheadLines until raid address space limit will be reached or
    //
    for (qulonglong i = 0; (i < readAheadSize) && (getReadAheadAddress() < getRaidSize()) ; i++){

        readAheadLines.push_back(CacheLine(getReadAheadAddress()));

        // Increment readAheadAddress
        if (m_sequentalPartCounter != m_sequentalLength){
            // Too early for it
            setReadAheadAddress(getReadAheadAddress()+1);
            m_sequentalPartCounter++;
        }else{
            // Ready for gap
            setReadAheadAddress(getReadAheadAddress()+m_gap);
            m_sequentalPartCounter = 0;
        }


    }

    return readAheadLines;
}
