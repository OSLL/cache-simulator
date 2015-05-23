#include "AbstractReadAheadDecisionMaker.h"


AbstractReadAheadDecisionMaker::AbstractReadAheadDecisionMaker(
        int readAheadSequenceLength, int readAheadLongevity,
        qulonglong readAheadSize, qulonglong raidSize):
    m_readAheadSequenceLength(readAheadSequenceLength),
    m_readAheadLongevity(readAheadLongevity),
    m_readAheadSize(readAheadSize),
    m_raidSize(raidSize),
    m_lastAddress(0),
    m_currentAccessSequence(0),
    m_isReadAheadAddressValid(false)
{
}

bool AbstractReadAheadDecisionMaker::isReadAheadOn() const
{
    return m_currentReadAheadCount != -1;
}

void AbstractReadAheadDecisionMaker::enableReadAhead(bool enabled)
{
    if (enabled)
        m_currentReadAheadCount = 0;
    else
        m_currentReadAheadCount = -1;
}

void AbstractReadAheadDecisionMaker::incrementReadAheadCount()
{
      if (++m_currentReadAheadCount == m_readAheadLongevity )
          m_currentReadAheadCount = -1;
}

int AbstractReadAheadDecisionMaker::getReadAheadLongevity() const
{
    return m_readAheadLongevity;
}

int AbstractReadAheadDecisionMaker::getReadAheadSequenceLength() const
{
    return m_readAheadSequenceLength;
}

qulonglong AbstractReadAheadDecisionMaker::getReadAheadSize() const
{
    return m_readAheadSize;
}

qulonglong AbstractReadAheadDecisionMaker::getRaidSize() const
{
    return m_raidSize;
}

qulonglong AbstractReadAheadDecisionMaker::getLastAddress() const
{
    return m_lastAddress;
}

void AbstractReadAheadDecisionMaker::setLastAddress(const qulonglong lastAddress)
{
    m_lastAddress = lastAddress;
}

void AbstractReadAheadDecisionMaker::incrementCurrentAccessSequence()
{
    m_currentAccessSequence++;
}

bool AbstractReadAheadDecisionMaker::isCurrentAccessSequenceEnughForRA() const
{
    return ( m_currentAccessSequence == (qulonglong)getReadAheadSequenceLength() );
}

void  AbstractReadAheadDecisionMaker::setCurrentAccessSequence(
        const qulonglong currentAccessSequence){
    m_currentAccessSequence = currentAccessSequence;
}

qulonglong AbstractReadAheadDecisionMaker::getReadAheadAddress() const
{
    return m_readAheadAddress;
}

void AbstractReadAheadDecisionMaker::setReadAheadAddress(const qulonglong readAheadAddress)
{
    m_readAheadAddress = readAheadAddress;
}

void AbstractReadAheadDecisionMaker::checkReadAheadAddress(const qulonglong address){
    if (isReadAheadOn() ){
        if (m_isReadAheadAddressValid == false)
            setReadAheadAddress(address);
    }else{
        m_isReadAheadAddressValid = false;
    }
}

