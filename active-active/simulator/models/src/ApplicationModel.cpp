#include "ApplicationModel.h"
#include "SettingsReader.h"
#include "RaidModel.h"
#include "defines.h"
#include "ReadTraceFactory.h"
#include "ReadRequest.h"
#include <QDebug>

ApplicationModel::ApplicationModel()
{
    m_readTrace = ReadTraceFactory::getReadTrace();
}

QString ApplicationModel::getElementName() const
{
    return APPLICATION;
}

void ApplicationModel::calculateNextState(GlobalState& currentState)
{

    qulonglong latency = SettingsReader::getValue(APP_LB_REQUEST_SEND_LATENCY).toULongLong();

    currentState.increaseTotalTime(latency);
    currentState.setCurrentElement(StorageModel::getInstance()->getLoadBalancerModel());
}



void ApplicationModel::createNewReadRequest(qulonglong step, QMultiMap<ReadRequest *, GlobalState> &states){

    qulonglong readRequestsCount = SettingsReader::getValue(READ_REQUESTS_COUNT,
                                                     DEFAULT_REQUESTS_COUNT).toULongLong();

    for (int i=0; i<readRequestsCount; i++){
        qDebug() << "Generating " << i << " read request";
        ReadRequest * request = m_readTrace->getNextReadRequest(step);

        if (request == NULL)
            return;


        QVector<GlobalState> stripeReqs = request->getGlobalStates();

//        QVector<GlobalState>::iterator j;
//        for (j = stripeReqs.begin(); j != stripeReqs.end(); ++j)
//        {
 //           states.insert(request, *j);
//        }

        for (int i=0; i<stripeReqs.size(); i++){
            states.insert(request, stripeReqs[i]);
        }
    }
}

bool ApplicationModel::isModelingFinished(qulonglong step) const
{
    return m_readTrace->isTraceFinished(step);
}

ApplicationModel::~ApplicationModel()
{
    delete m_readTrace;
    m_readTrace = NULL;
}
