#include "ReadRequest.h"
#include "defines.h"
#include "StorageModel.h"
#include "ResultsFileWriter.h"

#include <QDebug>

qulonglong ReadRequest::s_id = 0;

ReadRequest::ReadRequest(qulonglong stepNumber, qulonglong startAddress,
                         qulonglong offset): m_id(s_id++)
{
    // Create set of GlobalStates starting from start address with offset
    IStorageElement* element = (IStorageElement*)
            StorageModel::getInstance()->getApplicationModel();
    for (qulonglong i=0; i<offset ; i++){
        GlobalState state(stepNumber, startAddress+i, element );
        m_globalStates.push_front(state);
    }
}

ReadRequest::ReadRequest(): m_id(s_id++){

}

void ReadRequest::setGlobalStates(const QVector<GlobalState> &states){
    m_globalStates = states;
}

QVector<GlobalState> ReadRequest::getGlobalStates() const
{
    return m_globalStates;
}

bool ReadRequest::isFinished()
{
    qDebug() <<"m_globalStates.size() = " << m_globalStates.size() <<
               "m_results.size() = " << m_results.size();
    return m_globalStates.size() == m_results.size();
}

void ReadRequest::memorizeResults(qulonglong step, GlobalState state)
{


    m_results.insert(step, state);
  //  qDebug() << "|" << m_id << ", this = " << this << " , state_id=" << state.getId() <<
   //             "|" << m_results.size() << " " << &m_results;
}

void ReadRequest::printResults()
{
    QString result = QString("finished ReadRequest, read_request_id = %1 ").arg(m_id);

    //qDebug() << "finished ReadRequest, read_request_id = " << m_id;

    QMultiMap<qulonglong, GlobalState>::iterator j;
    for (j = m_results.begin(); j != m_results.end(); ++j)
    {
        qulonglong finishStep = m_results.key(*j);
        qulonglong startStep = (*j).getStartStepNumber();


        QString stripeResult = QString("\tstrp_req_id = %1, startStep = %2,"
                                "finishStep = %3, address = %4,"
                                " totalTime = %5").arg((*j).getId()).arg(startStep).
                arg(finishStep).arg((*j).getDataAddress()).arg((*j).getTotalTime());

        result = QString("%1\n%2").arg(result).arg(stripeResult);
      //  qDebug() << "\tstrp_req_id = " << (*j).getId() << ",startStep = " << startStep
       //          << ",finishStep =" << finishStep << ", address = " << (*j).getDataAddress()
        //         << ", totalTime = " << (*j).getTotalTime();
    }
    ResultsFileWriter::getInstance()->writeString(result);
}

qulonglong ReadRequest::getId() const
{
    return m_id;
}

bool operator ==(ReadRequest a,ReadRequest  b){
    return (a.getId() == b.getId());
}

bool operator <(ReadRequest a,ReadRequest  b){
    return (a.getId() < b.getId());
}
