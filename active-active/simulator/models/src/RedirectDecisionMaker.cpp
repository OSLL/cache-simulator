#include "RedirectDecisionMaker.h"
#include "SettingsReader.h"
#include "defines.h"
#include <cmath>
#include <QDebug>

qulonglong RedirectDecisionMaker::getMaxICQueueLength(qulonglong raidQueueSize) const
{

    qulonglong maxQueueLength = SettingsReader::getValue(IC_REDIRECT_CONTROL_MAX_QUEUE_LENGTH,
      DEFAULT_MAX_QUEUE_LENGTH).toULongLong();


    if (maxQueueLength == DEFAULT_MAX_QUEUE_LENGTH){

        qulonglong raidAccessTime =
                SettingsReader::getValue(RAID_SP_DATA_SEND_LATENCY).toULongLong() +
                SettingsReader::getValue(RAID_SP_REQUEST_SEND_LATENCY).toULongLong();

        qulonglong waitingRaidQueueTime =
                SettingsReader::getValue(QUEUE_WAITING_RAID_LATENCY).toULongLong();

        qulonglong waitingICQueueTime =
                SettingsReader::getValue(QUEUE_WAITING_IC_LATENCY).toULongLong();

        qulonglong icCheckupTime =
                SettingsReader::getValue(INTERCONNECT_CHECKUP_LATENCY).toULongLong() +
                SettingsReader::getValue(INTERCONNECT_DATA_LOAD_LATENCY).toULongLong();

        qulonglong totalRaidAccessTime = raidQueueSize*waitingRaidQueueTime + raidAccessTime;

        maxQueueLength = (totalRaidAccessTime - icCheckupTime)/ waitingICQueueTime;
    }


    qDebug() << "maxQueueLength == " << maxQueueLength;

    return maxQueueLength;

}

RedirectDecisionMaker::RedirectDecisionMaker(): m_stepsToApply(0)
{
}

void RedirectDecisionMaker::stat(qulonglong icQueueSize, qulonglong raidQueueSize)
{
    qulonglong maxQueueLength = SettingsReader::getValue(IC_REDIRECT_CONTROL_MAX_QUEUE_LENGTH,
      DEFAULT_MAX_QUEUE_LENGTH).toULongLong();

    bool isNeedToDirectRaidSend = (icQueueSize > getMaxICQueueLength(raidQueueSize));

    if (maxQueueLength != DEFAULT_MAX_QUEUE_LENGTH){
        //// Using algo parameters

        // IC queue is still too big - forward request directly to RAID
        if (isNeedToDirectRaidSend)
            m_stepsToApply =
                    SettingsReader::getValue(IC_REDIRECT_CONTROL_LONGEVITY).toULongLong() + 1 ;

        // If force direct send of requests to RAID is turned off
        // decrease number of steps to apply it
        if (isForcedDirectSendingEnabled())
            m_stepsToApply--;
    } else {

        // Using adaptive mode
        qulonglong icMaxThroughput =
                SettingsReader::getValue(MAX_THROUGHPUT_IC).toULongLong();
        qulonglong raidMaxThroughput =
                SettingsReader::getValue(MAX_THROUGHPUT_RAID).toULongLong();

        int stepsAtIc = (int)ceil((double)icQueueSize /double(icMaxThroughput));
        int stepsAtRaid = (int)ceil((double)raidQueueSize /double(raidMaxThroughput));


        if (isNeedToDirectRaidSend || stepsAtIc>stepsAtRaid)
            m_stepsToApply = 1;
        else
            m_stepsToApply = 0;
    }

    qDebug() << "Steps to apply" << m_stepsToApply;
}

bool RedirectDecisionMaker::isForcedDirectSendingEnabled() const
{
    return m_stepsToApply > 0;
}


bool RedirectDecisionMaker::makeDecision()
{
    return ! isForcedDirectSendingEnabled();
}
