#ifndef RESULTSFILEWRITER_H
#define RESULTSFILEWRITER_H

#include <QString>

class QFile;
class QTextStream;

class ResultsFileWriter
{
    static ResultsFileWriter* m_instance;

    QFile* m_file;
    QTextStream* m_textStream;

    ResultsFileWriter();

    QString generateFileName(const QString &currentDateTime) const;

    void copySettingsFile(const QString &currentDateTime) const;
public:

    void writeString(const QString& string);

    static ResultsFileWriter* getInstance();

    ~ResultsFileWriter();

};

#endif // RESULTSFILEWRITER_H
