#include "GlobalState.h"
#include "StorageModel.h"
#include "IStorageElement.h"
#include "ApplicationModel.h"
#include "defines.h"
#include "ResultsFileWriter.h"
#include <QDebug>
#include "StorageProcessorModel.h"
#include "StorageModel.h"
#include "Cache.h"
#include "StorageProcessorsStatistic.h"

qulonglong GlobalState::s_id = 0;

GlobalState::GlobalState(qulonglong stepNumber, qulonglong dataAddress, IStorageElement *currentElement):
     m_id(s_id++), m_dataType(REQUEST), m_dataAddress(dataAddress),  m_totalTime(0),
     m_stepNumber(stepNumber), m_currentElement(NULL), m_storageProcessor(NULL)
{
    qDebug() << "Constructing # " << m_id;
    setCurrentElement(currentElement);
}


GlobalState::~GlobalState(){
    //delete m_elements;
}

void GlobalState::calculateNextStep()
{
    m_currentElement->calculateNextState(*this);
    //TODO - log work
}

DataType GlobalState::getDataType() const
{
    return m_dataType;
}

qulonglong GlobalState::getDataAddress() const
{
    return m_dataAddress;
}
IStorageElement* GlobalState::getCurrentElement() const
{
    return m_currentElement;
}


void GlobalState::setDataType(DataType dataType)
{
    m_dataType = dataType;
}

bool GlobalState::isStorageProcessor( const IStorageElement *element) const{
    return element->getElementName().indexOf(STORAGE_PROCESSOR) != -1;
}

void GlobalState::touchStorageProcessorStatistics(IStorageElement* currentElement){


    IStorageElement* element = NULL;
    int delta = 0;
    if (m_currentElement != NULL && currentElement != NULL){

        if (isStorageProcessor(m_currentElement) &&
                !isStorageProcessor(currentElement)){
            element = m_currentElement;
            delta = -1;
        }else if ( !isStorageProcessor(m_currentElement) &&
                   isStorageProcessor(currentElement)){
            element = currentElement;
            delta = 1;
        }
    }

    if (element != NULL){
        StorageModel * model = StorageModel::getInstance();
        int index =
                model->getStorageProcessorNumber((StorageProcessorModel*)element);

        StorageProcessorsStatistic::getInstance()->updateStatistic(index, delta);
    }
}

void GlobalState::setCurrentElement(IStorageElement* currentElement)
{
    if (currentElement == NULL)
        return;
    touchStorageProcessorStatistics(currentElement);


    m_currentElement = currentElement;
    QString stringToWrite = QString("%1:%2:%3").
            arg( m_currentElement->getElementName()).
            arg(dataTypeToString(getDataType())).
            arg(QString::number(getTotalTime()));
    qDebug() << "void GlobalState::setCurrentElement(IStorageElement* currentElement)" <<
                stringToWrite;

    m_elements.push_back(stringToWrite);


}

QString GlobalState::toString() const
{

    QString result=QString("id=%1\taddress=%2\ttotalTime=%3\t%4\tstates=%5").arg(m_id).
            arg(m_dataAddress).arg(m_totalTime).
	    arg(Cache::getCacheStatistics()).arg(getElementsString());

    qWarning() << result;

    return result;
}


QString GlobalState::getElementsString() const
{
    for (int i=0; i<m_elements.size(); i++){
        qDebug() << "m_elements "<< i <<  m_elements.at(i);
    }

    return m_elements.join(" ");
}

bool GlobalState::isFinished() const
{
    qDebug() << "Checking for finished" << m_id ;
    qDebug() <<  toString();
    bool result = (m_dataType==RESPONSE) && (m_currentElement != NULL) &&
            (m_currentElement->getElementName()==APPLICATION) ;
    return result;
}

void GlobalState::setFinished()
{
    m_dataType = RESPONSE;
    m_currentElement = StorageModel::getInstance()->getApplicationModel();
}

qulonglong GlobalState::getTotalTime() const
{
    return m_totalTime;
}

void GlobalState::increaseTotalTime(qulonglong time)
{
    //qDebug() << "Increasing for " << m_currentElement->getElementName() << " " << time;
    m_totalTime+=time;
}

qulonglong GlobalState::getId() const
{
    return m_id;
}

void GlobalState::setData(const QByteArray &data)
{
    m_data = data;
}

QByteArray GlobalState::getData() const
{
    return m_data;
}

qulonglong GlobalState::getStartStepNumber() const
{
    return m_stepNumber;
}

StorageProcessorModel *GlobalState::getStorageProcessor() const
{
    return m_storageProcessor;
}

void GlobalState::setStorageProcessor(StorageProcessorModel *sp)
{
    m_storageProcessor = sp;
}

bool operator ==(GlobalState a, GlobalState b){
    return (a.getId() == b.getId());
}

uint qHash ( const GlobalState & obj ){
    return qHash(obj.getId());
}


void GlobalState::printRequest() const
{
	ResultsFileWriter::getInstance()->writeString(toString());
}
