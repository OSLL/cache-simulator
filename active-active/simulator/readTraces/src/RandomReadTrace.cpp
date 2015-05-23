#include "RandomReadTrace.h"
#include "SettingsReader.h"
#include "defines.h"
#include "ReadRequest.h"
#include "Cache.h"

#include <cstdlib>
#include <QDebug>

#include "RandomReadTraceGeneratorSelector.h"

RandomReadTrace::RandomReadTrace():
    m_generator(RandomReadTraceGeneratorSelector::getGenerator())
{
}

bool RandomReadTrace::isCacheHit() const{
    int cacheRatio = SettingsReader::getValue(CACHE_RATIO).toInt();
    int randomNumber = qrand() % 100;

    return randomNumber < cacheRatio;

}

qulonglong RandomReadTrace::getQulonglongRand(qulonglong raidSize){
    qulonglong result=0;
    qulonglong n = raidSize / (qulonglong)RAND_MAX;

    for (qulonglong i=0; i<n+1; i++){
        result += qrand() % raidSize;
    }
    return result;
}


void RandomReadTrace::processReadRequest(ReadRequest * request) const
{
    QVector<GlobalState> states = request->getGlobalStates();
    qDebug() << "RandomReadTrace::processReadRequest(ReadRequest * request)";

    for (int i=0; i<states.size(); i++){
        qDebug() << "Processig " << i << " state";
        states[i].setFinished();
        states[i].increaseTotalTime(getRandomTime());
    }
    request->setGlobalStates(states);
}

// Return time, which is general for any type of request
qulonglong RandomReadTrace::getBaseTime() const{
    return  SettingsReader::getValue(APP_LB_REQUEST_SEND_LATENCY).toULongLong()+
            SettingsReader::getValue(LB_SELECTING_LATENCY).toULongLong();
           //+SettingsReader::getValue(APP_SP_DATA_SEND_LATENCY).toULongLong();
}

qulonglong RandomReadTrace::getCacheHitTime() const{
    qulonglong result = getBaseTime() +
            SettingsReader::getValue(CACHE_CHECKUP_LATENCY).toULongLong();

    if (Cache::doesRedirectIfCacheMissOn() && selectStorageProcessorNumber()!=0){
        // We hitted on other SP
        result +=
                SettingsReader::getValue(INTERCONNECT_CHECKUP_LATENCY).toULongLong()+
                SettingsReader::getValue(INTERCONNECT_DATA_LOAD_LATENCY).toULongLong();

    }else{
        // Hit on the same SP
        result +=
                SettingsReader::getValue(CACHE_DATA_RETRIVAL_LATENCY).toULongLong();
    }
    return result;
}

qulonglong RandomReadTrace::getCacheMissTime() const{
    qulonglong result = getBaseTime() +
            SettingsReader::getValue(RAND_RAID_SP_DATA_SEND_LATENCY).toULongLong()+
            SettingsReader::getValue(CACHE_CHECKUP_LATENCY).toULongLong();
    // Determine type of cross SP interaction
    if (Cache::doesRedirectIfCacheMissOn()){
        // Redirect is on -> longest time
        result +=
                SettingsReader::getValue(INTERCONNECT_CHECKUP_LATENCY).toULongLong()+
                SettingsReader::getValue(INTERCONNECT_DATA_LOAD_LATENCY).toULongLong();
    }

    return result;
}

// Select globalState processing time by information about
qulonglong RandomReadTrace::getRandomTime() const{
    qulonglong time = getCacheMissTime();
    if (isCacheHit())
        time = getCacheHitTime();

    qDebug() << "Random time generated == "<< time ;

    return time;
}

int RandomReadTrace::selectStorageProcessorNumber() const{
    return qrand() % SP_COUNT;
}

ReadRequest *RandomReadTrace::getNextReadRequest(qulonglong step)
{
    qulonglong readSize = SettingsReader::getValue(READ_BLOCK_SIZE).toULongLong();

    qulonglong address = m_generator->getNextAddress();

    ReadRequest* result = new ReadRequest(step, address, readSize);

    processReadRequest(result);

    return result;
}

bool RandomReadTrace::isTraceFinished(qulonglong step) const
{
    qulonglong modelingStepsNumber =
            SettingsReader::getValue(MODELING_STEPS_NUMBER).toULongLong();
    return step >= modelingStepsNumber;
}
