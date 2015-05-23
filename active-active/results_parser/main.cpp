#include <QtGlobal>
#include <QCoreApplication>
#include <QDebug>
#include <QString>
#include <QFile>
#include <QTextStream>
#include "defines.h"


void parseLine(const QString& line, double& totalLatency, double& totalRequestCount){
    
  QRegExp regExp("totalTime=([^\t]+)");
  int pos = regExp.indexIn(line);
  if (pos != -1){
    QString latency = regExp.cap(1);
    totalLatency += latency.toDouble();
    totalRequestCount++;
//    qDebug() << "Latency == " << latency;
  } else{
    qDebug() << "Problems at line: " << line;
  }


}

int main(int ac, char** av)
{
  QCoreApplication app(ac, av);

  if (ac != 5)
  {
    qDebug() << "Not enaugh arguments. Usage: ./results_parser results_file steps_number a1 a2";
    qDebug() << "results_file - name of file with results";
    qDebug() << "steps - number of modeling steps";
    qDebug() << "a1, a2 - weight coefficients";

    return 1;
  }
  double totalLatency = 0;
  double totalRequestCount = 0;
  double totalStepsNumber = QString(av[2]).toDouble();
  
  double a1 = QString(av[3]).toDouble();
  double a2 = QString(av[4]).toDouble();

  QString fileName = av[1]; 
  QFile inputFile(fileName);
  if (inputFile.open(QIODevice::ReadOnly))
  {
    QTextStream in(&inputFile);
    while ( !in.atEnd() )
    {
      QString line = in.readLine();
      parseLine(line, totalLatency, totalRequestCount);   
    }
    inputFile.close();
  } else 
  {
    qDebug() << "Unable to open file";
    return 1;
  }

  double avgIOPS = totalRequestCount/totalStepsNumber;
  double avgLatency = totalLatency/totalRequestCount;
  double performance = a1*avgIOPS + a2/avgLatency;

//  qDebug() << "performance IOPS latency";
  qDebug() << performance << avgIOPS << avgLatency;


  return 0;
}
