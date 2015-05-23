#include "StorageProcessorsStatistic.h"
#include "defines.h"
#include "StorageModel.h"

#include <QDebug>

StorageProcessorsStatistic* StorageProcessorsStatistic::m_instance = NULL;

StorageProcessorsStatistic::StorageProcessorsStatistic()
{
    for ( int i=0; i<SP_COUNT; i++){
        m_statistic.append(0);
    }
}

void StorageProcessorsStatistic::updateStatistic(int index, int statistic)
{
    qDebug() << "MinQueueDepth updating" << index << statistic;

    if (m_statistic[index] > 0 || statistic > 0)
        m_statistic[index] = m_statistic[index] + statistic;

}

StorageProcessorsStatistic *StorageProcessorsStatistic::getInstance()
{
    if (m_instance == NULL)
        m_instance = new StorageProcessorsStatistic();

    return m_instance;
}

int StorageProcessorsStatistic::getMinimalQueueSP() const
{
    int minIndex = 0;

    for(int i=1; i < m_statistic.size(); i++){
        if (m_statistic[minIndex] > m_statistic[i])
            minIndex = i;
    }

    for (int i=0; i< m_statistic.size(); i++)
        qDebug() << "MinQueueDepth element" << i << m_statistic[i];

    qDebug() << "MinQueueDepth minIndex" << minIndex;
    return minIndex;
}


