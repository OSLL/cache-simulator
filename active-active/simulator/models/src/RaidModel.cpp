#include "RaidModel.h"
#include "defines.h"
#include "SettingsReader.h"
#include "StorageProcessorModel.h"
#include "StorageModel.h"
#include "LimitedThroughput.h"

#include <QDebug>
#include <QFile>

RaidModel::RaidModel()
{
    QList<StorageProcessorModel*> spList = StorageModel::getInstance()->getStorageProcessors();
    for (int i=0; i<spList.size(); i++){
        LimitedThroughput* object =
                LimitedThroughput::createNewObject(QUEUE_WAITING_RAID_LATENCY, MAX_THROUGHPUT_RAID);
        m_spDataChannels.insert(spList[i], object);
    }
}


QString RaidModel::getElementName() const
{
    return RAID;
}

void RaidModel::calculateNextState(GlobalState &currentState)
{
    qulonglong latency;
    LimitedThroughput* channel = m_spDataChannels.value(currentState.getStorageProcessor());
    if (channel->isNotFull())
    {
        // Data is transfered
        qDebug() << "GlobalState #"<< currentState.getId() << "is transfering to SP";
        latency = SettingsReader::getValue(RAID_SP_DATA_SEND_LATENCY).toULongLong();
        StorageProcessorModel* sp = currentState.getStorageProcessor();
        currentState.setCurrentElement(sp);
        currentState.setDataType(RESPONSE);
        channel->incrementRequestCount();
    }else{
        // Data is waiting for being transfered
        qDebug() << "GlobalState #"<< currentState.getId() << "is waiting";
        latency = channel->getWaitingLatency();
    }
    currentState.increaseTotalTime(latency);
}

qulonglong RaidModel::getRaidQueueSize(StorageProcessorModel *sp)
{
    LimitedThroughput* channel = m_spDataChannels.value(sp);
    return channel->getWaitingRequestsCount();
}


