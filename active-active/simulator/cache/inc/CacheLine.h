#ifndef CACHELINE_H
#define CACHELINE_H

#include <QtGlobal>
#include <QDateTime>

class CacheLine
{
    qulonglong m_address;

    qulonglong m_lastAccessTime;


public:
    explicit CacheLine(qulonglong address);

    CacheLine(const  CacheLine&other);

    CacheLine &operator=(const CacheLine &other);


    qulonglong getAddress() const;

    qulonglong getLastAccessTime() const;

    void touchLastAccessTime();

    QString toString() const;
    CacheLine();
};

bool operator ==(CacheLine a, CacheLine b);
bool operator <(CacheLine a, CacheLine b);

#endif // CACHELINE_H
