#include "CacheLine.h"
#include "TimeUtil.h"

CacheLine::CacheLine(): m_lastAccessTime(getCurrentTime())
{

}

CacheLine::CacheLine(qulonglong address):
    m_address(address), m_lastAccessTime(getCurrentTime())
{
}

CacheLine::CacheLine(const CacheLine &other)
{
    m_address = other.m_address;
    m_lastAccessTime = other.m_lastAccessTime;
}

CacheLine &CacheLine::operator =(const CacheLine &other)
{
    m_address = other.m_address;
    m_lastAccessTime = other.m_lastAccessTime;
    return *this;
}


qulonglong CacheLine::getAddress() const
{
    return m_address;
}

qulonglong CacheLine::getLastAccessTime() const
{
    return m_lastAccessTime;
}

void CacheLine::touchLastAccessTime()
{
    m_lastAccessTime = getCurrentTime();
}

QString CacheLine::toString() const
{
    return QString("CacheLine: address=%1, time=%2").arg(m_address).arg(m_lastAccessTime);
}

bool operator ==(CacheLine a, CacheLine b)
{
    return a.getAddress() == b.getAddress();
}

bool operator <(CacheLine a, CacheLine b)
{
    return a.getLastAccessTime() < b.getLastAccessTime();
}
