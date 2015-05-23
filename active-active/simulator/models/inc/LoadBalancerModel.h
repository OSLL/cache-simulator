#ifndef LOADBALANCERMODEL_H
#define LOADBALANCERMODEL_H

#include "IStorageElement.h"
#include "LoadBalancingAlgorithmFactory.h"

class LoadBalancerModel : public IStorageElement
{
    ILoadBalancingAlgorithm * m_loadBalancer;

    StorageProcessorModel * selectSP();
public:
    LoadBalancerModel();

    virtual QString getElementName() const;
    virtual void calculateNextState(GlobalState& currentState) ;
};

#endif // LOADBALANCERMODEL_H
