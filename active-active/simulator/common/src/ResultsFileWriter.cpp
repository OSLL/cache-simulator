#include "ResultsFileWriter.h"
#include "Modeler.h"
#include "defines.h"
#include "SettingsReader.h"

#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <QDebug>

ResultsFileWriter *ResultsFileWriter::m_instance = NULL;

ResultsFileWriter::ResultsFileWriter()
{
    QString currentDateTime = QDateTime::currentDateTime().toString("dd_MM_yyyy_hh:mm:ss:zzz");
    QString fileName = generateFileName(currentDateTime);
    copySettingsFile(currentDateTime);

    qDebug() << "Result at file = " << fileName;

    m_file = new QFile(fileName);

    if (!m_file->open(QIODevice::WriteOnly | QIODevice::Text))
        qFatal("Unable to create results file!");

    m_textStream = new QTextStream(m_file);

}

void ResultsFileWriter::copySettingsFile(const QString& currentDateTime) const
{
    QString command = QString("cp %1 ./settings_%2.ini").
            arg(SettingsReader::getFileName()).arg(currentDateTime);

    system(command.toStdString().c_str());
}

QString ResultsFileWriter::generateFileName(const QString& currentDateTime) const
{
    //QString currentDateTime = QDateTime::currentDateTime().toString("dd_MM_yyyy_hh:mm:ss:zzz");
    QString result = QString("%1%2").arg(FILE_TEMPLATE).arg(currentDateTime);
    return result;
}

void ResultsFileWriter::writeString(const QString &string)
{
    QString result = QString("step=%1\t%2\n").arg(Modeler::getStep()).arg(string);
    *m_textStream << result;
}

ResultsFileWriter *ResultsFileWriter::getInstance()
{
    if (m_instance == NULL)
        m_instance = new ResultsFileWriter();

    return m_instance;
}

ResultsFileWriter::~ResultsFileWriter()
{
    m_file->close();

    delete m_file;
    delete m_textStream;

    m_file = NULL;
    m_textStream = NULL;
}
