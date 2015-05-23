#include "LimitedThroughput.h"
#include "Modeler.h"

#include <QDebug>
QList<LimitedThroughput*> LimitedThroughput::s_objects = QList<LimitedThroughput*>();


LimitedThroughput::LimitedThroughput(const QString& latencyParameter,
                                     const QString& throughputParameter):
    m_passedRequestCount(0),m_latencyParameter(latencyParameter),
    m_throughputParameter(throughputParameter){
}

void LimitedThroughput::clearRequestCount(){
    m_passedRequestCount = 0;
}

void LimitedThroughput::removeObject(LimitedThroughput *object)
{
    s_objects.removeAll(object);
}

LimitedThroughput* LimitedThroughput::createNewObject(const QString& latencyParameter,
                                                      const QString& throughputParameter){
    LimitedThroughput* object = new LimitedThroughput(latencyParameter, throughputParameter);

    s_objects.append(object);

    return object;
}

qulonglong LimitedThroughput::getMaxRequestCount() const{
    return SettingsReader::getValue(m_throughputParameter).toULongLong();
}

qulonglong LimitedThroughput::getWaitingRequestsCount() const
{
    qulonglong result;
    if (isNotFull())
        result = 0;
    else
        result = m_passedRequestCount - getMaxRequestCount();
    return result;
}

bool LimitedThroughput::isNotFull() const{
    qulonglong maxRequestCount = getMaxRequestCount();
    qDebug() << "step = " << Modeler::getStep()
             << ", passedRequestCount = "<< m_passedRequestCount
             << ", maxRequestCount = " << maxRequestCount;
    return (m_passedRequestCount < maxRequestCount);
}

void LimitedThroughput::incrementRequestCount() {
    m_passedRequestCount++;
}

qulonglong LimitedThroughput::getWaitingLatency() const{
    return SettingsReader::getValue(m_latencyParameter).toULongLong();
}

void LimitedThroughput::clearForNextStep(){
    foreach(LimitedThroughput* object, s_objects){
        object->clearRequestCount();
    }
}

LimitedThroughput::~LimitedThroughput()
{
    removeObject(this);
}
