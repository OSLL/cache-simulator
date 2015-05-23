#include "ReadAheadDecisionMaker.h"
#include <QDebug>


ReadAheadDecisionMaker::ReadAheadDecisionMaker(
        int readAheadSequenceLength, int readAheadLongevity,
        qulonglong readAheadSize, qulonglong raidSize):
    AbstractReadAheadDecisionMaker(readAheadSequenceLength, readAheadLongevity,
                                   readAheadSize, raidSize)
{}


bool ReadAheadDecisionMaker::statCacheAccess(qulonglong address)
{
    qDebug() << "RA_try "<< address;
    if (address == getLastAddress()+1){
        // Sequental pattern match
        incrementCurrentAccessSequence();
        if ( isCurrentAccessSequenceEnughForRA()  ){
            // RA is turned ON
            enableReadAhead(true);
            setCurrentAccessSequence(0);
        }
    }else{
        // Sequental pattern breack
        setCurrentAccessSequence(0);
    }

    setLastAddress(address);

    checkReadAheadAddress(address);


    return isReadAheadOn();
}


QVector<CacheLine> ReadAheadDecisionMaker::getReadAheadLines()
{

    qulonglong endAddress = qMin(getReadAheadAddress() + getReadAheadSize(), getRaidSize());
    QVector<CacheLine> readAheadLines;
    if (getReadAheadAddress() < endAddress){
        for (qulonglong i = getReadAheadAddress(); i < endAddress; i++)
            readAheadLines.push_back(CacheLine(i));

        qulonglong delta = endAddress - getReadAheadAddress();
        setReadAheadAddress( getReadAheadAddress()+delta);
    }else{
        enableReadAhead(false);
    }
    return readAheadLines;

}
