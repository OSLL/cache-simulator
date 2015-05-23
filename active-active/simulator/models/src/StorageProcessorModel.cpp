#include "StorageProcessorModel.h"
#include "defines.h"
#include "SettingsReader.h"
#include "ApplicationModel.h"
#include "math.h"
#include "RaidModel.h"
#include "LimitedThroughput.h"
#include "StorageModel.h"
#include "Modeler.h"
#include "RedirectDecisionMaker.h"

#include <QDebug>
StorageProcessorModel::StorageProcessorModel():m_cache( Cache::createCache()),
    m_icThroughput(LimitedThroughput::createNewObject(QUEUE_WAITING_IC_LATENCY, MAX_THROUGHPUT_IC)),
    m_icQueue(0), m_decisionMaker(new RedirectDecisionMaker())
{
}

void StorageProcessorModel::setCache(Cache* cache){
    m_cache = cache;
}

qulonglong StorageProcessorModel::getIcQueue() const
{
    return m_icQueue;
}

void StorageProcessorModel::setIcQueueToZero()
{
    m_icQueue = 0;
}

void StorageProcessorModel::incrementIcQueue()
{
    qDebug() << "Interconnect queue";
    m_icQueue++;
}

void StorageProcessorModel::printIcQueueStatistics()
{
    QList<StorageProcessorModel*> sps =
            StorageModel::getInstance()->getStorageProcessors();
    foreach(StorageProcessorModel* sp, sps){

        qDebug() << "Interconnect queue,sp = " << sps.indexOf(sp) <<

                 "step ="<<Modeler::getStep() << " queue_size ="
                    << sp->m_icQueue;//sp->getIcQueue();
        sp->setIcQueueToZero();
    }
}

QString StorageProcessorModel::getElementName() const
{
    int spId = StorageModel::getInstance()->getStorageProcessorNumber(this);
    return QString("%1_%2").arg(STORAGE_PROCESSOR).arg(spId);
}

void StorageProcessorModel::processDataExistingInCache(GlobalState &currentState)
{
    // Data exists in cache - just return it to application
    qulonglong latency = SettingsReader::getValue(CACHE_DATA_RETRIVAL_LATENCY).toULongLong();
    currentState.setDataType(RESPONSE);
    currentState.increaseTotalTime(latency);
}


void StorageProcessorModel::processDataNotExistingInCache(GlobalState &currentState)
{

    bool decision = makeRedirectDecision();

    qDebug() << "REDIRECT_DECISION:" << decision;
       // Send request to other SP
    if (decision){
        qDebug() << "\tredirectIfCacheMiss";
        // Check data in other sp
        qulonglong latency =
                SettingsReader::getValue(INTERCONNECT_CHECKUP_LATENCY).toULongLong();
        currentState.increaseTotalTime(latency);
        StorageProcessorModel* otherSP =
                StorageModel::getInstance()->getOtherStorageProcessor(this);
        qDebug() << "checking " << currentState.getDataAddress() << "in OTHER SP";
        bool interconnectCheckupResult = otherSP->doesExistInCache(currentState);

        currentState.setCurrentElement(otherSP);


        if (interconnectCheckupResult){
            // Data exist in other SP, getting them
            qDebug() << "Data exists in other SP, "<< currentState.getDataAddress();

            requestDataFromOtherStorageProcessor(currentState);
        }else{
            // Data not exist in other SP, should ask raid
            qDebug() << "Data does not exists in other SP";
            requestDataFromRaid(currentState);
        }
    // Request data from raid
    }else{
        qDebug() << "Requesting data from RAID";
        requestDataFromRaid(currentState);
    }
}

void StorageProcessorModel::requestDataFromOtherStorageProcessor(GlobalState &currentState)
{
    // Setting request storage processor for requests forwarding
    currentState.setStorageProcessor(this);
  //  StorageProcessorModel* otherSP = StorageModel::getInstance()->getOtherStorageProcessor(this);
  //  currentState.setCurrentElement(otherSP);
}

void StorageProcessorModel::sendDataToOtherStorageProcessor(GlobalState &currentState)
{
    qulonglong latency;
    if (m_icThroughput->isNotFull()){

        latency = SettingsReader::getValue(INTERCONNECT_DATA_LOAD_LATENCY).toULongLong();
        currentState.setCurrentElement(currentState.getStorageProcessor());
        currentState.setDataType(RESPONSE);
        m_icThroughput->incrementRequestCount();
    }else{
        qDebug() << "GlobalState #" << currentState.getId() << "is waiting for Interconnect";
        latency = m_icThroughput->getWaitingLatency();
        incrementIcQueue();
    }

    currentState.increaseTotalTime(latency);

}

// Decide should we do redirect request or not
bool StorageProcessorModel::makeRedirectDecision()
{
    bool redirectIfCacheMiss = Cache::doesRedirectIfCacheMissOn();

    bool isRedirectControlEnabled = SettingsReader::getValue(IC_REDIRECT_CONTROL_ENABLED).toBool();


    qDebug() << "redirectIfCacheMiss: " << redirectIfCacheMiss;
    qDebug() << "isRedirectControlEnabled: " << isRedirectControlEnabled;

    if (!isRedirectControlEnabled)
        return redirectIfCacheMiss;

    if (!redirectIfCacheMiss)
            return true;

    StorageModel *storageModel = StorageModel::getInstance();
    qulonglong icQueueSize = storageModel->getOtherStorageProcessor(this)->getIcQueue();
    qulonglong raidQueueSize = storageModel->getRaidModel()->getRaidQueueSize(this);
    m_decisionMaker->stat(icQueueSize, raidQueueSize);

    return m_decisionMaker->makeDecision();
}

void StorageProcessorModel::requestDataFromRaid(GlobalState &currentState)
{
    // Setting request storage processor for requests forwarding
    //currentState.setStorageProcessor(this);
    qulonglong latency = SettingsReader::getValue(RAID_SP_REQUEST_SEND_LATENCY).toULongLong();
    currentState.increaseTotalTime(latency);
    currentState.setCurrentElement(StorageModel::getInstance()->getRaidModel());
}

void StorageProcessorModel::sendDataToApplication(GlobalState &currentState)
{
    qulonglong latency = SettingsReader::getValue(APP_SP_DATA_SEND_LATENCY).toULongLong();
    currentState.increaseTotalTime(latency);
    currentState.setCurrentElement(StorageModel::getInstance()->getApplicationModel());
}


void StorageProcessorModel::calculateNextState(GlobalState &currentState)
{
    if (currentState.getDataType() == REQUEST){
        // Check was request sent by other sp or not
        if (currentState.getStorageProcessor() == NULL ||
                currentState.getStorageProcessor() == this){
            currentState.setStorageProcessor(this);
            qulonglong cacheCheckupLatency =
                    SettingsReader::getValue(CACHE_CHECKUP_LATENCY).toULongLong();
            currentState.increaseTotalTime(cacheCheckupLatency);
            // Cache hit
            if (doesExistInCache(currentState)){
                //qDebug() << "\tCache hit";
                processDataExistingInCache(currentState);

            // Cache miss
            }else{
                //qDebug() << "\tCache miss";
                processDataNotExistingInCache(currentState);
            }
        }else{
            qDebug() << "Recieved request from other SP " << currentState.getStorageProcessor()<<
                        ", step = "<< Modeler::getStep();
            sendDataToOtherStorageProcessor(currentState);
        }
    }else if (currentState.getDataType() == RESPONSE){
        sendDataToApplication(currentState);
    }

}

bool StorageProcessorModel::doesExistInCache(GlobalState &currentState)
{

    bool result;

    if (this == currentState.getStorageProcessor())
        result = m_cache->contains(currentState.getDataAddress());
    else
        result = m_cache->simpleCheckup(currentState.getDataAddress());
    return result;
    qDebug() << QString("contains(%1)").arg(currentState.getDataAddress()) << getElementName();
}

StorageProcessorModel::~StorageProcessorModel()
{
}

