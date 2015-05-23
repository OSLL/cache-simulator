#include "SpacialLocalityGenerator.h"
#include <QDebug>

SpacialLocalityGenerator::SpacialLocalityGenerator(const qulonglong raidSize):
    IRandomReadTraceAddressGenerator(raidSize)
{
}


qulonglong SpacialLocalityGenerator::getNextAddress()
{
    int randNumber = qrand()%100;
    qulonglong result;
    if (randNumber < m_probability){
        qDebug() << "Generating address from interval";
        // Returning address from [m_leftAddress, m_rightAddress]
        result = m_leftAddress + getQulonglongRand(m_rightAddress - m_leftAddress);
    }else{
        qDebug() << "Generating usual address";
        // Returning usuall address
        result = getQulonglongRand(getRaidSize());
    }
    return result;
}

void SpacialLocalityGenerator::setParameters(const qulonglong leftAddress,
                                             const qulonglong rightAddress, int probability)
{
    m_leftAddress = leftAddress;
    m_rightAddress = rightAddress;
    m_probability = probability;
}
