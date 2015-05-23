#include "TraceFileReader.h"
#include "SettingsReader.h"
#include "defines.h"

#include <QFile>
#include <QTextStream>
#include <QDebug>

TraceFileReader::TraceFileReader()
{
    QString fileName = SettingsReader::getValue(READ_TRACE_FILE).toString();
    m_file = new QFile(fileName);
    if (m_file->open(QIODevice::ReadOnly))
    {
           m_stream = new QTextStream(m_file);

    }else{
        qFatal(QString("Unable to open trace file : %1").arg(fileName).toStdString().c_str());
    }

}

TraceFileEntry TraceFileReader::getCurrentTraceFileEntry()
{
    TraceFileEntry traceFileEntry;
    if (!isEOF()){
        QString line = m_stream->readLine();
        qDebug() << "read line : "<< line;
        traceFileEntry = TraceFileEntry(line);
    }

    return traceFileEntry;
}

bool TraceFileReader::isEOF() const
{

    return m_stream->atEnd();
}

TraceFileReader::~TraceFileReader()
{
    m_file->close();
    delete m_file;
    m_file = NULL;
}
