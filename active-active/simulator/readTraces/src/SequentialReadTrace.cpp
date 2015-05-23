#include "SequentialReadTrace.h"
#include "SettingsReader.h"
#include "ReadRequest.h"
#include "RandomReadTrace.h"
#include "defines.h"

#include <QDebug>

SequentialReadTrace::SequentialReadTrace()
{
}

qulonglong SequentialReadTrace::getAddressToRead()
{

    qulonglong readSize = SettingsReader::getValue(READ_BLOCK_SIZE).toULongLong();

    qulonglong raidSize =  SettingsReader::getValue(RAID_SIZE).toULongLong() - readSize;
    m_lastAddress = (m_lastAddress+1)%(raidSize);
    qDebug() << "SEQUENTIAL " << m_lastAddress << ", READ_BLOCK_SIZE" << readSize;
    return m_lastAddress;
}


ReadRequest* SequentialReadTrace::getNextReadRequest(qulonglong step)
{
    qulonglong offset = SettingsReader::getValue(READ_BLOCK_SIZE).toULongLong();
    qulonglong raidSize = SettingsReader::getValue(RAID_SIZE).toULongLong() - offset;
    qulonglong address = RandomReadTrace::getQulonglongRand(raidSize);//getAddressToRead();


    ReadRequest* request = new ReadRequest(step, address, offset);

    return request;
}

bool SequentialReadTrace::isTraceFinished(qulonglong step) const
{
    qulonglong modelingStepsNumber =
            SettingsReader::getValue(MODELING_STEPS_NUMBER).toULongLong();
    return step >= modelingStepsNumber;
}
