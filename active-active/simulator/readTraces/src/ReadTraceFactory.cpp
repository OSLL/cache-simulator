#include "ReadTraceFactory.h"
#include "RandomReadTrace.h"
#include "SequentialReadTrace.h"
#include "SettingsReader.h"
#include "UserDefinedReadTrace.h"
#include "defines.h"

#include <QDebug>

IReadTrace* ReadTraceFactory::m_readTrace = NULL;

//
void ReadTraceFactory::createReadTrace()
{
    QString readTraceType = SettingsReader::getValue(READ_TRACE_TYPE).toString();

    qDebug() <<"readTraceType = "<< readTraceType;

    if (readTraceType == RANDOM_READ_TRACE)
        m_readTrace = new RandomReadTrace();
    else if(readTraceType == SEQUENTIAL_READ_TRACE)
        m_readTrace = new SequentialReadTrace();
    else if (readTraceType == USER_DEFINED_READ_TRACE)
        m_readTrace = new UserDefinedReadTrace();


}

IReadTrace *ReadTraceFactory::getReadTrace()
{
    if (m_readTrace == NULL)
        createReadTrace();

    return m_readTrace;
}
