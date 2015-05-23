#include "TimeLocalityGenerator.h"
#include <QDebug>

void TimeLocalityGenerator::statAddressGeneration(const qulonglong address)
{
    if (m_queue.contains(address))
        return;

    if (m_queue.size() == m_memorizedQueueLength)
        m_queue.pop_back();

    m_queue.prepend(address);


    qDebug() << "TimeLocality m_queue";
    foreach (qulonglong address, m_queue)
        qDebug() << "\taddress=" << address;

}

TimeLocalityGenerator::TimeLocalityGenerator(const qulonglong raidSize):
    IRandomReadTraceAddressGenerator(raidSize)
{}

qulonglong TimeLocalityGenerator::getNextAddress()
{    int randNumber = qrand()%100;
     qulonglong result;
     if (randNumber < m_probability && m_queue.size()>0){
         qulonglong index = getQulonglongRand(m_queue.size());
         qDebug() << "Generating address from queue " << index << ", size = " << m_queue.size();
         result = m_queue.at( index );
     }else{
         qDebug() << "Generating usual address";
         result = getQulonglongRand(getRaidSize());
     }
     statAddressGeneration(result);
     return result;
}

void TimeLocalityGenerator::setParameters(const qulonglong memorizedQueueLength,
                                          const int probability)
{
    m_memorizedQueueLength = memorizedQueueLength;
    m_probability = probability;
}
