#ifndef LOADBALANCINGALGORITHMFACTORY_H
#define LOADBALANCINGALGORITHMFACTORY_H

#include "ILoadBalancingAlgorithm.h"

class LoadBalancingAlgorithmFactory
{
public:
    static ILoadBalancingAlgorithm* getLoadBalancingAlgorithm();
};

#endif // LOADBALANCINGALGORITHMFACTORY_H
