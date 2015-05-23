#ifndef TRACEFILEREADER_H
#define TRACEFILEREADER_H

#include "TraceFileEntry.h"

class QFile;
class QTextStream;

class TraceFileReader
{
    QFile * m_file;
    QTextStream *  m_stream;

public:
    TraceFileReader();

    TraceFileEntry getCurrentTraceFileEntry();

    bool isEOF() const;

    ~TraceFileReader();
};

#endif // TRACEFILEREADER_H
