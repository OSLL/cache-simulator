#include "LoadBalancerModel.h"
#include "SettingsReader.h"
#include "StorageProcessorModel.h"

#include "defines.h"

#include <QDebug>

LoadBalancerModel::LoadBalancerModel()
{

   m_loadBalancer = LoadBalancingAlgorithmFactory::getLoadBalancingAlgorithm();
   // m_rr.init(SP_COUNT);
}


QString LoadBalancerModel::getElementName() const
{
    return LOAD_BALANCER;
}

StorageProcessorModel * LoadBalancerModel::selectSP(){
    QList<StorageProcessorModel *> sps = StorageModel::getInstance()->getStorageProcessors();

    int nodeNumber = m_loadBalancer->getNodeNumber();

    return sps[nodeNumber];
}

void LoadBalancerModel::calculateNextState(GlobalState& currentState)
{
    //qDebug() << "\tChanging state inside LB";
    qulonglong latency = SettingsReader::getValue(LB_SELECTING_LATENCY).toULongLong();

    StorageProcessorModel * sp = selectSP();

    currentState.increaseTotalTime(latency);
    currentState.setCurrentElement(sp);
    qDebug() << "BALANCING" << currentState.getDataAddress();
}
