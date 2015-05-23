#include "Cache.h"
#include "StorageModel.h"
#include "SettingsReader.h"
#include "defines.h"
#include "RaidModel.h"
#include "ResultsFileWriter.h"
#include "ReadAheadDecisionMakerFactory.h"

#include <QDebug>
#include <QtGlobal>



int Cache::s_id = 0;
QList<Cache*> Cache::s_caches = QList<Cache*>();

Cache* Cache::createCache()
{
    Cache* cache = new Cache();
    s_caches.append(cache);
    return cache;
} 

QString Cache::getCacheStatistic() const
{
    double cacheFullingPercentage = 100.*((double)m_lines.size())/((double)m_cacheSize);
    QString result=QString("cache_miss:%1 cache_access_count:%2 fullness_percentage:%3")
            .arg(m_cacheMissCount).arg(m_accessCount).arg(cacheFullingPercentage);

    return result;
}

Cache::Cache():m_id(s_id++),m_accessCount(0),m_cacheMissCount(0){
    qDebug() << "Cache::Cache()";
    m_cacheSize = SettingsReader::getValue(CACHE_SIZE).toULongLong();
    m_readAheadSize = SettingsReader::getValue(READ_AHEAD_BLOCK).toULongLong();

    qulonglong readAheadSize = SettingsReader::getValue(READ_AHEAD_BLOCK).toULongLong();
    qulonglong raidSize = SettingsReader::getValue(RAID_SIZE).toULongLong();
    int readAheadSequenceLength = SettingsReader::getValue(READ_AHEAD_SEQUENCE_LENGTH).toInt();
    int readAheadLongevity = SettingsReader::getValue(READ_AHEAD_DISTANCE).toInt();

    m_raDecisionMaker = ReadAheadDecisionMakerFactory::getDecisionMaker(
                readAheadSequenceLength, readAheadLongevity,
                readAheadSize, raidSize);

    initCache();
}

void Cache::writeStringResult(qulonglong address, bool result)
{
    QString stringResult = QString("cache access, cache.id = %1, address = %2, cache.contains = %3").
            arg(m_id).arg(address).arg(result);

    ResultsFileWriter::getInstance()->writeString(stringResult);
}

bool Cache::contains(qulonglong address)
{
    for (int i=0;i<m_lines.size(); i++){
        qDebug() << m_lines.at(i).getAddress();
    }

    m_accessCount++;
    bool result = simpleCheckup(address);

    // Make a decision can be RA executed or not
    bool runReadAhead = m_raDecisionMaker->statCacheAccess(address);
    if (runReadAhead)
        doReadAhead();


    if (!result){
        m_cacheMissCount++;
        //Address not found in cache
        //qDebug() << "Cache miss, address=" << address;
        // Remove one element, add element, which was stated
        doExcludeAction();
        doIncludeAction(address);
    }else{
        //qDebug() << "Cache hit, address=" << address;
    }

    //writeStringResult(address, result);

    return result;
}

qulonglong Cache::getCacheSize() const
{
    return m_cacheSize;
}

void Cache::doReadAhead()
{
    m_raDecisionMaker->incrementReadAheadCount();

    // Find addresses which are not cached from
    // [m_readAheadAddress m_readAheadAddress+m_readAheadSize]
    QVector<CacheLine> notCachedLines;
   // qulonglong endAddress = m_readAheadAddress + m_readAheadSize;

    QVector<CacheLine> readAheadLines = m_raDecisionMaker->getReadAheadLines();

    foreach (CacheLine line, readAheadLines){
        int j = m_lines.indexOf(line);

        if (j == -1){
            // Found not cached line
            notCachedLines.append(line);
        } else{
            // Preventing accedental removing of already cached addresses
            // from readahead block
            m_lines[j].touchLastAccessTime();
        }
    }

    if (notCachedLines.size() == 0) return;

    // Do excluding
    doExcludeAction(notCachedLines.size());

    //m_lines += notCachedLines;
    foreach (CacheLine line, notCachedLines){
        doIncludeAction(line.getAddress());
    }
    
}

void Cache::initCache()
{}

void Cache::doExcludeAction(qulonglong linesCount )
{
    bool coherencyFlag = isCoherencyOn();

    excludeElements(linesCount);

    if (coherencyFlag){
        qDebug() << "Cache::doExcludeAction(qulonglong linesCount ) Coherency is ON";
        for (int i=0; i<s_caches.size(); i++){
            if ( s_caches[i] != this)
                s_caches[i]->excludeElements(linesCount);
        }
    }
}

void Cache::doIncludeAction(qulonglong  address)
{
    bool coherencyFlag = isCoherencyOn();

    includeElement(address);

    if (coherencyFlag){
        qDebug() << "Cache::doIncludeAction(qulonglong  address) Coherency is ON";
        for (int i=0; i<s_caches.size(); i++){
            if ( s_caches[i] != this)
                s_caches[i]->includeElement(address);
        }
    }
}

void Cache::excludeElements(qulonglong linesCount)
{
    // Remove linesCount elements from m_lines, which were accessed earlier than other lines
    qSort(m_lines);

    if (m_lines.size() >= m_cacheSize )
        m_lines = m_lines.mid(linesCount);
}


void Cache::includeElement(qulonglong  address)
{
    qDebug() << s_caches.indexOf(this)  <<  "includeElement " << address;
    m_lines.push_front(CacheLine(address));
}

bool Cache::checkCachePolicy(const QString& value) {


    QString policy = SettingsReader::getValue(CACHE_POLICY).toString();

    return (policy.compare(value, Qt::CaseInsensitive) == 0);
}

bool Cache::isCoherencyOn() {
    return checkCachePolicy(CACHE_POLICY_COHERENT);
}



bool Cache::doesRedirectIfCacheMissOn() {
    return checkCachePolicy(CACHE_POLICY_NON_COHERENT_WITH_CROSS_SP_LOOKUP);
}

QString Cache::getCacheStatistics()
{
    QString result;
    for (int i=0; i<s_caches.size();i++)
    {
        QString cacheStatistic = (s_caches[i])->getCacheStatistic();
        result+=QString("cache%1=%2").arg(i).arg(cacheStatistic);

        if (i != s_caches.size()-1) result += "\t";
    }

    return result;
}

bool Cache::simpleCheckup(qulonglong address)
{
    return m_lines.contains(CacheLine(address));
}
