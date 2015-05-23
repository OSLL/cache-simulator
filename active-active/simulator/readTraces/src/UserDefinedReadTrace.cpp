#include "UserDefinedReadTrace.h"
#include "ReadRequest.h"

#include <QDebug>
UserDefinedReadTrace::UserDefinedReadTrace()
{
}

ReadRequest *UserDefinedReadTrace::getNextReadRequest(qulonglong step)
{
    TraceFileEntry entry;
    ReadRequest * readRequest = NULL ;

    while (!entry.isReadRequest()){

        entry = m_traceFileReader.getCurrentTraceFileEntry();

        if (m_traceFileReader.isEOF())
            break;

        qulonglong address = entry.getAddress();
        qulonglong offset = entry.getOffset();
        readRequest = new ReadRequest(step, address, offset);
    }
    return readRequest;
}

bool UserDefinedReadTrace::isTraceFinished(qulonglong step) const
{
    bool result = m_traceFileReader.isEOF();
    qDebug() << "isTraceFinished = " << result;
    return result;
}
