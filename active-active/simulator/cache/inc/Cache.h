#ifndef CACHE_H
#define CACHE_H

#include "CacheLine.h"
#include "GlobalState.h"
#include "AbstractReadAheadDecisionMaker.h"

#include <QVector>
#include <QtGlobal>
#include <QList>
class Cache
{
    static int s_id;
    static QList<Cache*> s_caches;

    int m_id;
    
    qulonglong m_accessCount;
    qulonglong m_cacheMissCount;

    QVector<CacheLine> m_lines;

    AbstractReadAheadDecisionMaker* m_raDecisionMaker;

    qulonglong m_cacheSize;
    qulonglong m_readAheadAddress;
    qulonglong m_readAheadSize;

    // Init cache
    void initCache();

    // Two functions below work only for *this object
    void excludeElements(qulonglong linesCount);
    void includeElement(qulonglong address);

    // General interface for exclude/include - if coherency enabled this
    // functions propogate changes to other caches.
    void doExcludeAction(qulonglong linesCount = 1);
    void doIncludeAction(qulonglong address);

    // Read ahead : take m_readAheadSize elements staring from startAddress
    // to the cache
    void doReadAhead();

    QString getCacheStatistic() const;

    void writeStringResult(qulonglong address, bool result);
    Cache();

    static bool checkCachePolicy(const QString& value);

public:

    static QString getCacheStatistics();

    bool simpleCheckup(qulonglong address);
    bool contains(qulonglong address);

    qulonglong getCacheSize() const;

    static Cache* createCache();

    static bool isCoherencyOn();
    static bool doesRedirectIfCacheMissOn();
};

#endif // CACHE_H
